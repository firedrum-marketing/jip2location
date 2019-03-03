package com.ip2location;

import java.net.URISyntaxException;
import java.nio.file.Paths;
import java.lang.ref.ReferenceQueue;
import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class IP2Location {
	private static final Map<Long, NativeHandle> WEAK_REFERENCE_MAINTAINER = new HashMap<>();
	private static final ReferenceQueue<IP2Location> REFERENCES = new ReferenceQueue<>();

	private static final ExecutorService CLEANUP_THREAD_EXECUTOR_SERVICE;
	private static Thread cleanupThread;

	private final NativeHandle nativeHandle;
	
	private static IP2Location instance;

	public static class NativeHandle extends WeakReference<IP2Location> {
		long handle = 0;
		private final Lock cleanupLock = new ReentrantLock();

		public NativeHandle(final IP2Location referent) {
			super( referent, REFERENCES );
		}

		public void setHandle(final long handle) {
			if ( this.handle != handle ) {
				if ( this.handle != 0 ) {
					WEAK_REFERENCE_MAINTAINER.remove( this.handle );
				}

				this.handle = handle;

				if ( handle != 0 ) {
					WEAK_REFERENCE_MAINTAINER.put( handle, this );
				}
			}
		}

		public void release(final Iterator<NativeHandle> iterator) {
			if ( handle != 0 && cleanupLock.tryLock() ) {
				try {
					if ( iterator != null ) {
						iterator.remove();
					} else {
						WEAK_REFERENCE_MAINTAINER.remove( handle );
					}
					IP2Location.closeDatabase( handle );
					handle = 0;
				} finally {
					cleanupLock.unlock();
				}
			}
		}
	}

	private static void cleaner() {
		for ( ; ; ) {
			try {
				checkContextClassLoaders();
				NativeHandle handle = (NativeHandle) REFERENCES.remove( 5000 );
				if ( handle != null ) {
					handle.release( null );
				}
			} catch ( InterruptedException e ) {
				cleanupThread = null;
				Iterator<NativeHandle> iterator = WEAK_REFERENCE_MAINTAINER.values().iterator();
				while ( iterator.hasNext() ) {
					NativeHandle handle = iterator.next();
					handle.release( iterator );
				}
				return;

			} catch ( Exception ex ) {
				// Nowhere to really log this.
			}
		}
	}

	static {
		CLEANUP_THREAD_EXECUTOR_SERVICE = Executors.newSingleThreadExecutor( new ThreadFactory() {
			public Thread newThread(Runnable r) {
				Thread t = new Thread( r, "IP2Location JNI Memory Cleaner" );
				t.setDaemon( true );
				// Tie the thread's context ClassLoader to the ClassLoader that loaded the class instead of inheriting the context ClassLoader from the current
				// thread, which would happen by default.
				// Application servers may use this information if they attempt to shutdown this thread. By leaving the default context ClassLoader this thread
				// could end up being shut down even when it is shared by other applications and, being it statically initialized, thus, never restarted again.
				t.setContextClassLoader( IP2Location.class.getClassLoader() );
				return cleanupThread = t;
			}
		} );
		CLEANUP_THREAD_EXECUTOR_SERVICE.execute( IP2Location::cleaner );

		try {
			System.loadLibrary( "JIP2Location" );
			instance = openDatabase( Paths.get( IP2Location.class.getProtectionDomain().getCodeSource().getLocation().toURI() )
					.getParent()
					.resolve( "IP2LOCATION-LITE-DB11.BIN" )
					.toAbsolutePath()
					.toString() );
		} catch ( UnsatisfiedLinkError | URISyntaxException e ) {
			e.printStackTrace();
		}
	}

	/**
	 * Checks if the context ClassLoaders from this and the caller thread are the same.
	 * 
	 * @return true if both threads share the same context ClassLoader, false otherwise
	 */
	private static boolean consistentClassLoaders() {
		ClassLoader callerCtxClassLoader = Thread.currentThread().getContextClassLoader();
		ClassLoader threadCtxClassLoader = cleanupThread.getContextClassLoader();
		return callerCtxClassLoader != null && threadCtxClassLoader != null && callerCtxClassLoader == threadCtxClassLoader;
	}

	/**
	 * Shuts down this thread either checking or not the context ClassLoaders from the involved threads.
	 * 
	 * @param checked
	 *            does a checked shutdown if true, unchecked otherwise
	 */
	private static void shutdown(boolean checked) {
		if ( checked && !consistentClassLoaders() ) {
			// This thread can't be shutdown from the current thread's context ClassLoader. Doing so would most probably prevent from restarting this thread
			// later on. An unchecked shutdown can still be done if needed by calling shutdown(false).
			return;
		}
		CLEANUP_THREAD_EXECUTOR_SERVICE.shutdownNow();
	}

	/**
	 * Checks if the thread's context ClassLoader is active. This is usually true but some application managers implement a life-cycle mechanism in their
	 * ClassLoaders that is linked to the corresponding application's life-cycle. As such, a stopped/ended application will have a ClassLoader unable to load
	 * anything and, eventually, they throw an exception when trying to do so. When this happens, this thread has no point in being alive anymore.
	 */
	private static void checkContextClassLoaders() {
		try {
			cleanupThread.getContextClassLoader().getResource( "" );
		} catch ( Throwable e ) {
			// Shutdown no matter what.
			uncheckedShutdown();
		}
	}

	/**
	 * Performs a checked shutdown, i.e., the context ClassLoaders from this and the caller thread are checked for consistency prior to performing the shutdown
	 * operation.
	 */
	public static void checkedShutdown() {
		shutdown( true );
	}

	/**
	 * Performs an unchecked shutdown, i.e., the shutdown is performed independently of the context ClassLoaders from the involved threads.
	 */
	public static void uncheckedShutdown() {
		shutdown( false );
	}

	/**
	 * Look up an IP Address.
	 *
	 * @param ipAddress
	 *            the IP Address to look up
	 * @return an IP2LocationRecord or {@code null} if the record cannot be found in the database
	 */
	public static IP2LocationRecord lookupIpAddress(String ipAddress) {
		return ipAddress == null || instance == null ? null : instance.lookup( ipAddress );
	}

	private IP2Location() {
		nativeHandle = new NativeHandle( this );
	}

	/**
	 * Closes the binary database.
	 */
	private static native void closeDatabase(long handle);

	/**
	 * Opens a binary database.
	 *
	 * @param database
	 *            the binary database file's absolute path
	 * @return an IP2Location instance for the requested database
	 * @throws RuntimeException
	 *             if the requested database cannot be found or accessed
	 */
	private static native IP2Location openDatabase(String database);

	/**
	 * Look up an IP Address.
	 *
	 * @param ipAddress
	 *            the IP Address to look up
	 * @return an IP2LocationRecord or {@code null} if the record cannot be found in the database
	 */
	private native IP2LocationRecord lookup(String ipAddress);
}
