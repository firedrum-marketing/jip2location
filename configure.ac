AC_INIT(src/com/ip2location/IP2Location.java)
AC_CANONICAL_SYSTEM

dnl Get the OS name

if test -x "/bin/uname" ; then
  UNAME=/bin/uname
elif test -x "/usr/bin/uname" ; then
  UNAME=/usr/bin/uname
elif test -x "/usr/local/bin/uname" ; then
  UNAME=/usr/local/bin/uname
else
  echo configure: cannot find uname
  exit 1
fi

LIB=lib
if test -x "/usr/lib64" ; then
  LIB=lib64
fi

OS=`$UNAME -s`

dnl The version number must change with every release
VER_MAJOR=1
VER_MINOR=0
VER_MICRO=0

SHARED_LIB_EXT=.so

dnl Need the -G flag on Solaris when creating shared libraries.
case "$target" in
*solaris*)
	SHARED_LDFLAGS="-G"
	;;
*freebsd*|*linux*)
	SHARED_LDFLAGS="-shared"
	;;
dnl Make sure we use -dynamiclib parameter for OS X Leopard
*darwin9.*|*darwin10.*)
	SHARED_LDFLAGS="-dynamiclib"
	SHARED_LIB_EXT=.jnilib
	;;
*darwin1.[0-2])
	;;
*darwin*)
	LIBTOOL_LINK_FLAG='-module'
	;;
*-*-cygwin|*-*-mingw32)
	SHARED_LDFLAGS="-shared"
	SHARED_LIB_EXT=.dll
	JFLAGS="-Xlint:deprecation -Xlint:unchecked"
	JAVA_HOME=$(cygpath -C UTF8 "$(cygpath -C UTF8 -d "${JAVA_HOME}")")
	;;
esac

dnl By default, we look at /usr/local. Need to explicitly do this because
dnl some compilers don't.
LDFLAGS="${LDFLAGS} -L/usr/local/${LIB}"
CFLAGS="${CFLAGS} -I/usr/local/include"

dnl Get the full path of the source directory.
PROJ_BASE_DIR=`cd ${srcdir} && pwd`
AC_SUBST(PROJ_BASE_DIR)

dnl Determine if we have gcc
AC_PROG_CC
if test -z "${CC}"; then
    AC_MSG_ERROR('No suitable C compiler found')
fi
if test "${GCC}" != yes; then
    AC_MSG_WARN('You don't have the GNU GCC. Should\'t you be using one?')
fi
AC_SUBST(CC)

dnl Determine how to run the preprocessor
AC_PROG_CPP

dnl Check for install program
AC_PROG_INSTALL

dnl Check for large file support. This test was taken from ImageMagick.
dnl If this step is removed, there will be a mismatch of structures in
dnl the ImageMagick headers.
AC_PATH_PROG(GETCONF, getconf, not_found)
if (test $GETCONF != not_found); then
    AC_MSG_CHECKING(whether large file support needs explicit enabling)
    result='no'
    NEW_CFLAGS=`$GETCONF LFS_CFLAGS 2> /dev/null`
    if (test -n "$NEW_CFLAGS"); then
        CFLAGS="$CFLAGS $NEW_CFLAGS"
        result='yes'
    fi
    NEW_LDFLAGS=`$GETCONF LFS_LDFLAGS 2> /dev/null`
    if (test -n "$NEW_LDFLAGS"); then
        LDFLAGS="$LDFLAGS $NEW_LDFLAGS"
        result='yes'
    fi
    NEW_LIBS=`$GETCONF LFS_LIBS 2> /dev/null`
    if (test -n "$NEW_LIBS"); then
        LIBS="$LIBS $NEW_LIBS"
        result='yes'
    fi
    AC_MSG_RESULT($result)
fi

dnl Determine the OS we are running on and set the class path
dnl separator accordingly.
case ${build_os} in
*-*-cygwin|*-*-mingw32)
	CLASSSEP=;
	;;
*)
	CLASSSEP=:
esac
AC_SUBST(CLASSSEP)

dnl Determine if we have a decent Java distribution
AC_ARG_WITH(java-home, --with-java-home Java installation path,
            JAVA_HOME=${withval})
AC_ARG_WITH(java-includes, --with-java-includes Java includes path,
            JAVA_INCLUDE_PATH="${withval}")
if test -n "${JAVA_INCLUDE_PATH}" -a -d "${JAVA_INCLUDE_PATH}" ; then
	dnl Java include path supplied
	JAVA_INCLUDES=-I${JAVA_INCLUDE_PATH}
elif test -d "${JAVA_HOME}/include" ; then
	JAVA_INCLUDES=-I${JAVA_HOME}/include
	dnl The Blackdown JDK seems to have genunix.
	if test -d "${JAVA_HOME}/include/genunix" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/genunix"
	fi
	dnl The Sun Linux JDK seems to use linux
	if test -d "${JAVA_HOME}/include/linux" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/linux"
	fi
	dnl The Sun Solaris JDK seems to use solaris
	if test -d "${JAVA_HOME}/include/solaris" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/solaris"
	fi
	dnl The Sun FreeBSD JDK seems to use freebsd
	if test -d "${JAVA_HOME}/include/freebsd" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/freebsd"
	fi
	dnl The Sun Windows JDK seems to use win32
	if test -d "${JAVA_HOME}/include/win32" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/win32"
	fi
	if test -d "${JAVA_HOME}/include/bsd" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/bsd"
	fi
	dnl Modern Oracle JDK on OS X
	if test -d "${JAVA_HOME}/include/darwin" ; then
		JAVA_INCLUDES="$JAVA_INCLUDES -I${JAVA_HOME}/include/darwin"
	fi
dnl check for Mac OS X series of systems with old Apple JDKs
elif test -d "${JAVA_HOME}/Headers" ; then
	JAVA_INCLUDES=-I${JAVA_HOME}/Headers
else
	AC_MSG_ERROR('Unable to locate Java directories')
fi

dnl Determine if there is a shared library extension supplied
AC_ARG_WITH(shared_lib_ext, --with-shared-lib-ext Shared library file extension,
            SHARED_LIB_EXT=${withval}, SHARED_LIB_EXT=${SHARED_LIB_EXT})

dnl Determine if jni.h is available
OLD_CPPFLAGS=${CPPFLAGS}
CPPFLAGS="${JAVA_INCLUDES} ${CPPFLAGS}"
AC_CHECK_HEADER(jni.h, HAVE_JNI_HEADER=yes, HAVE_JNI_HEADER=no)
if test ${HAVE_JNI_HEADER} = no ; then
	AC_MSG_ERROR('Unable to locate jni.h')
fi
CPPFLAGS=${OLD_CPPFLAGS}

dnl Determine where the Java interpreter is
OLDPATH=${PATH}
PATH=${JAVA_HOME}/bin:${PATH}
export PATH
AC_PATH_PROG(JAVA, java, not_found)
if test ${JAVA} = not_found; then
	AC_MSG_ERROR('No Java interpreter found')
fi
AC_SUBST(JAVA)

dnl Determine if we prefer to use Jikes.
AC_ARG_WITH(jikes, --with-jikes	use the IBM Jikes compiler,
            PREFER_JIKES=yes,
            PREFER_JIKES=no)
if test ${PREFER_JIKES} = yes; then
	dnl Determine if Jikes is available.
	AC_PATH_PROG(JIKES, jikes, not_found)
	if test ${JIKES} = not_found; then
		dnl Jikes not found, so we check for javac
		AC_PATH_PROG(JAVAC, javac, not_found)
		if test ${JAVAC} = not_found; then
			AC_MSG_ERROR('No Java compiler found')
		else
			AC_MSG_WARN('Jikes not found. Use javac.')
		fi
	else
		JAVAC=${JIKES}
	fi
else
	dnl Determine if we have the Java compiler.
	AC_PATH_PROG(JAVAC, javac, not_found)
	if test ${JAVAC} = not_found; then
		AC_PATH_PROG(JIKES, jikes, not_found)
		if test ${JIKES} = not_found; then
			AC_MSG_ERROR('No Java compiler found')
		else
			JAVAC=${JIKES}
		fi
	fi
fi
AC_SUBST(JAVAC)

dnl Determine if we have jar
AC_PATH_PROG(JAR, jar, not_found)
if test ${JAR} = not_found; then
	AC_MSG_ERROR('No jar found')
fi
AC_SUBST(JAR)

dnl Determine if we have javadoc
AC_PATH_PROG(JAVADOC, javadoc, )
AC_SUBST(JAVADOC)

PATH=${OLDPATH}
export PATH

dnl Check if javadoc destination specified
JAVADOC_DIR='${prefix}/share/doc/jip2location'
AC_ARG_WITH(javadoc-dir, --with-javadoc-dir=path where Javadoc is generated,
            JAVADOC_DIR=${withval})
AC_SUBST(JAVADOC_DIR)

dnl Do you print extra diagnostic?
AC_ARG_ENABLE(diagnostic,
              --enable-diagnostic enable C diagnostic output (default off),
              C_DEBUG=-DDIAGNOSTIC,C_DEBUG=)
AC_SUBST(C_DEBUG)

dnl The -L. is needed to prevent a libtool bug on Windows
IP2LOCATION_LIB_PATH=/usr/local/lib
IP2LOCATION_LIBS="-L. -L/usr/local/lib -lIP2Location"
IP2LOCATION_INCLUDES=-I/usr/local/include

dnl Check for the IP2Location header
OLD_CPPFLAGS=${CPPFLAGS}
if test -n "${IP2LOCATION_INCLUDES}"; then
	CPPFLAGS="${IP2LOCATION_INCLUDES} ${CPPFLAGS}"
fi

AC_CHECK_HEADER(IP2Location.h, HAVE_IP2LOCATION_HEADER=yes, HAVE_IP2LOCATION_HEADER=no)
if test "${HAVE_IP2LOCATION_HEADER}" = no ; then
	AC_MSG_ERROR('Unable to find IP2Location header file: IP2Location.h')
fi

dnl Check for the IP2Location library
OLD_LDFLAGS=${LDFLAGS}
if test -n "${IP2LOCATION_LIBS}"; then
	LDFLAGS="${IP2LOCATION_LIBS} ${LDFLAGS}"
fi

AC_CHECK_LIB(IP2Location, IP2Location_open,
         HAVE_IP2LOCATION_LIB=yes, HAVE_IP2LOCATION_LIB=no)
if test ${HAVE_IP2LOCATION_LIB} = no; then
	AC_MSG_ERROR('Unable to find IP2Location library: IP2Location')
fi

CPPFLAGS=${OLD_CPPFLAGS}
LDFLAGS=${OLD_LDFLAGS}

dnl Configure libtool
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_SUBST(JAVA_INCLUDES)
AC_SUBST(IP2LOCATION_LIB_PATH)
AC_SUBST(IP2LOCATION_LIBS)
AC_SUBST(IP2LOCATION_INCLUDES)
AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(JFLAGS)
AC_SUBST(LIBS)
AC_SUBST(SHARED_LDFLAGS)
AC_SUBST(LIBTOOL_LINK_FLAG)
AC_SUBST(VER_MAJOR)
AC_SUBST(VER_MINOR)
AC_SUBST(VER_MICRO)
AC_SUBST(SHARED_LIB_EXT)
AC_SUBST(OS)

AC_OUTPUT([Make.def])
