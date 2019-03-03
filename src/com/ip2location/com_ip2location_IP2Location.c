#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jni.h>

#include "IP2Location.h"
#include "com_ip2location_IP2Location.h"

#ifndef JIP2LOCATION_EMPTY_RECORD_STRING
#define JIP2LOCATION_EMPTY_RECORD_STRING "-"
#endif


/*
 * Convenience function to retrieve the java handle from an object.
 *
 * Input:
 *   env               Java VM environment
 *   obj               Java object for which handle is to be retrieved
 *   nativeFieldId     if non-null, contains the nativeHandle field ID. 0 to request retrieval.
 *
 * Output:
 *   nativeFieldId     if non-null, will contain field ID of the nativeHandle on output.
 */
void *getHandle(JNIEnv *env,
		jobject obj,
		jfieldID *nativeFieldId)
{
	jobject nativeHandleObj;
	jclass nativeHandleObjClass;
	jclass objClass;
	jfieldID nativeHandleFid;
	jfieldID handleFid;
	
	/* Retrieve the field ID of the nativeHandle */
	if (nativeFieldId == NULL) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return NULL;
		}
		nativeHandleFid = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lcom/ip2location/IP2Location$NativeHandle;");
	} else if (*nativeFieldId == 0) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return NULL;
		}
		nativeHandleFid = *nativeFieldId = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lcom/ip2location/IP2Location$NativeHandle;");
	} else {
		nativeHandleFid = *nativeFieldId;
	}

	nativeHandleObj = (*env)->GetObjectField(env, obj, nativeHandleFid);

	/* Retrieve the field ID of the handle */
	nativeHandleObjClass = (*env)->GetObjectClass(env, nativeHandleObj);
	if (nativeHandleObjClass == 0) {
		return NULL;
	}
	handleFid = (*env)->GetFieldID(env, nativeHandleObjClass, "handle", "J");

	return (void*) (*env)->GetLongField(env, nativeHandleObj, handleFid);
}

/*
 * Convenience function to set the java handle in an object.
 *
 * Input:
 *   env               Java VM environment
 *   obj               Java object for which handle is to be retrieved
 *   handle            the handle value to set
 *   nativeFieldId     if non-null, contains the nativeHandle field ID. 0 to request retrieval.
 *
 * Output:
 *   nativeFieldId     if non-null, will contain field ID of the nativeHandle on output.
 *
 * Return:
 *   non-zero          if successful
 *   zero              if failure
 */
int setHandle(JNIEnv *env,
		jobject obj,
		void *handle,
		jfieldID *nativeHandleFieldId)
{
	jobject nativeHandleObj;
	jclass nativeHandleObjClass;
	jclass objClass;
	jfieldID nativeHandleFid;
	jmethodID setHandleMethodID;

	/* Retrieve the field ID of the handle */
	if (nativeHandleFieldId == NULL) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return 0;
		}
		nativeHandleFid = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lcom/ip2location/IP2Location$NativeHandle;");
	} else if (*nativeHandleFieldId == 0) {
		objClass = (*env)->GetObjectClass(env, obj);
		if (objClass == 0) {
			return 0;
		}
		nativeHandleFid = *nativeHandleFieldId = (*env)->GetFieldID(env, objClass, "nativeHandle", "Lcom/ip2location/IP2Location$NativeHandle;");
	} else {
		nativeHandleFid = *nativeHandleFieldId;
	}

	if (nativeHandleFid == 0) {
		return 0;
	}
	
	nativeHandleObj = (*env)->GetObjectField(env, obj, nativeHandleFid);

	/* Retrieve the method ID of the setHandle(long handle) method */
	nativeHandleObjClass = (*env)->GetObjectClass(env, nativeHandleObj);
	if (nativeHandleObjClass == 0) {
		return 0;
	}
	setHandleMethodID = (*env)->GetMethodID(env, nativeHandleObjClass, "setHandle", "(J)V");

	if (setHandleMethodID == 0) {
		return 0;
	}

	(*env)->CallVoidMethod(env, nativeHandleObj, setHandleMethodID, (jlong) handle);

	return 1;
}

/*
 * Convenience function to set a String in an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which String is to be retrieved
 *   fieldName  name of the String in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the String on output.
 *
 * Return:
 *   non-zero    if successful
 *   zero        if failure
 */
int setString(JNIEnv* env, jobject obj, const char* fieldName, jstring string, jfieldID* fieldId) {
	jclass objClass;
	jfieldID handleFid;

	/* Retrieve the field ID of the handle */
	if ( fieldId == NULL ) {
		objClass = (*env)->GetObjectClass( env, obj );
		if ( objClass == 0 ) {
			return 0;
		}
		handleFid = (*env)->GetFieldID( env, objClass, fieldName, "Ljava/lang/String;" );
	} else if (fieldId == 0) {
		objClass = (*env)->GetObjectClass( env, obj );
		if ( objClass == 0 ) {
			return 0;
		}
		handleFid = *fieldId = (*env)->GetFieldID( env, objClass, fieldName, "Ljava/lang/String;" );
	} else {
		handleFid = *fieldId;
	}

	if ( handleFid == 0 ) {
		return 0;
	}

	(*env)->SetObjectField( env, obj, handleFid, string );

	return 1;
}

/*
 * Convenience function to set a BigDecimal in an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which BigDecimal is to be retrieved
 *   fieldName  name of the BigDecimal in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the BigDecimal on output.
 *
 * Return:
 *   non-zero    if successful
 *   zero        if failure
 */
int setBigDecimal(JNIEnv* env, jobject obj, const char* fieldName, jobject bigDecimal, jfieldID* fieldId) {
	jclass objClass;
	jfieldID handleFid;

	/* Retrieve the field ID of the handle */
	if ( fieldId == NULL ) {
		objClass = (*env)->GetObjectClass( env, obj );
		if ( objClass == 0 ) {
			return 0;
		}
		handleFid = (*env)->GetFieldID( env, objClass, fieldName, "Ljava/math/BigDecimal;" );
	} else if (fieldId == 0) {
		objClass = (*env)->GetObjectClass( env, obj );
		if ( objClass == 0 ) {
			return 0;
		}
		handleFid = *fieldId = (*env)->GetFieldID( env, objClass, fieldName, "Ljava/math/BigDecimal;" );
	} else {
		handleFid = *fieldId;
	}

	if ( handleFid == 0 ) {
		return 0;
	}

	(*env)->SetObjectField( env, obj, handleFid, bigDecimal );

	return 1;
}

/*
 * Convenience function to help throw a RuntimeException.
 *
 * Input:
 *   message       error message
 */
void throwRuntimeException(JNIEnv* env, const char* message) {
	jclass runtimeExceptionClass;
	jmethodID consMethodID = 0;
	jobject newObj;
	jstring jmessage;
	int result;

	/* Find the class ID */
	runtimeExceptionClass = (*env)->FindClass( env, "java/lang/RuntimeException" );
	if ( runtimeExceptionClass == 0 ) {
		return;
	}

	/* Find the constructor ID */
	consMethodID = (*env)->GetMethodID( env, runtimeExceptionClass, "<init>", "(Ljava/lang/String;)V" );
	if ( consMethodID == 0 ) {
		return;
	}

	/* Obtain the string objects */
	jmessage = (*env)->NewStringUTF( env, message );
	if ( jmessage == NULL ) {
		return;
	}

	/* Create the RuntimeException object */
	newObj = (*env)->NewObject( env, runtimeExceptionClass, consMethodID, jmessage );
	if ( newObj == NULL ) {
		return;
	}

	/* Throw the exception. */
	result = (*env)->Throw( env, newObj );
}

JNIEXPORT jobject JNICALL Java_com_ip2location_IP2Location_openDatabase(JNIEnv *env, jclass cls, jstring jdatabase) {
	jmethodID jmid;
	jobject jobj = NULL;
	IP2Location* pIP2Location = NULL;

	const char* database =  (*env)->GetStringUTFChars( env, jdatabase, 0 );
	pIP2Location = IP2Location_open( (char*) database, 1 );
	if ( pIP2Location == NULL ) {
		(*env)->ReleaseStringUTFChars( env, jdatabase, database );
		throwRuntimeException( env, "Could not initialize the database requested" );
		return NULL;
	}

	jmid = (*env)->GetMethodID( env, cls, "<init>", "()V" );
	if ( jmid == NULL ) {
		IP2Location_close( pIP2Location );
		(*env)->ReleaseStringUTFChars( env, jdatabase, database );
		throwRuntimeException( env, "Could not find the IP2Location class constructor" );
		return NULL;
	}

	jobj = (*env)->NewObject( env, cls, jmid );
	if ( jobj == NULL ) {
		IP2Location_close( pIP2Location );
		(*env)->ReleaseStringUTFChars( env, jdatabase, database );
		throwRuntimeException( env, "Could not create a new IP2Location instance" );
		return NULL;
	}

	if ( !setHandle( env, jobj, (void*) pIP2Location, NULL ) ) {
		IP2Location_close( pIP2Location );
		(*env)->ReleaseStringUTFChars( env, jdatabase, database );
		throwRuntimeException( env, "Could not set handle for new IP2Location instance" );
		return NULL;
	}

	(*env)->ReleaseStringUTFChars( env, jdatabase, database );

	return jobj;
}

JNIEXPORT jobject JNICALL Java_com_ip2location_IP2Location_lookup(JNIEnv *env, jobject self, jstring jipAddress) {
	IP2Location* pIP2Location;
	IP2LocationRecord* pIP2LocationRecord;
	jclass jcls;
	jclass jFloatCls;
	jmethodID jmid;
	jmethodID jFloatMid;
	jobject jobj = NULL;
	jobject bigDecimal = NULL;

	pIP2Location = getHandle( env, self, NULL );
	if ( pIP2Location != NULL ) {
		jcls = (*env)->FindClass( env, "com/ip2location/IP2LocationRecord" );
		if ( jcls == NULL ) {
			throwRuntimeException( env, "Could not find the IP2LocationRecord class" );
			return NULL;
		}

		jmid = (*env)->GetMethodID( env, jcls, "<init>", "()V" );
		if ( jmid == NULL ) {
			throwRuntimeException( env, "Could not find the IP2LocationRecord class constructor" );
			return NULL;
		}

		jobj = (*env)->NewObject( env, jcls, jmid );
		if ( jobj == NULL ) {
			throwRuntimeException( env, "Could not create a new IP2LocationRecord instance" );
			return NULL;
		}

		jcls = (*env)->FindClass( env, "java/math/BigDecimal" );
		if ( jcls == NULL ) {
			throwRuntimeException( env, "Could not find the BigDecimal class" );
			return NULL;
		}

		jmid = (*env)->GetMethodID( env, jcls, "<init>", "(Ljava/lang/String;)V" );
		if ( jmid == NULL ) {
			throwRuntimeException( env, "Could not find the BigDecimal(String) class constructor" );
			return NULL;
		}

		jFloatCls = (*env)->FindClass( env, "java/lang/Float" );
		if ( jFloatCls == NULL ) {
			throwRuntimeException( env, "Could not find the Float class" );
			return NULL;
		}

		jFloatMid = (*env)->GetStaticMethodID( env, jFloatCls, "toString", "(F)Ljava/lang/String;" );
		if ( jFloatMid == NULL ) {
			throwRuntimeException( env, "Could not find the Float.toString(float) method" );
			return NULL;
		}

		const char* ipAddress = (*env)->GetStringUTFChars( env, jipAddress, 0 );
		pIP2LocationRecord = IP2Location_get_all( pIP2Location, (char*) ipAddress );
		if ( pIP2LocationRecord == NULL ) {
			(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
			return NULL;
		}

		if ( pIP2LocationRecord->latitude != 0.0 ) {
			bigDecimal = (*env)->NewObject( env, jcls, jmid, (*env)->CallStaticObjectMethod( env, jFloatCls, jFloatMid, pIP2LocationRecord->latitude ) );
			if ( bigDecimal == NULL ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not create a new BigDecimal instance" );
				return NULL;
			}
			if ( !setBigDecimal( env, jobj, "latitude", bigDecimal, NULL ) ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not set handle for a new BigDecimal instance" );
				return NULL;
			}
		}

		if ( pIP2LocationRecord->longitude != 0.0 ) {
			bigDecimal = (*env)->NewObject( env, jcls, jmid, (*env)->CallStaticObjectMethod( env, jFloatCls, jFloatMid, pIP2LocationRecord->longitude ) );
			if ( bigDecimal == NULL ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not create a new BigDecimal instance" );
				return NULL;
			}
			if ( !setBigDecimal( env, jobj, "longitude", bigDecimal, NULL ) ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not set handle for a new BigDecimal instance" );
				return NULL;
			}
		}

		if ( pIP2LocationRecord->elevation != 0.0 ) {
			bigDecimal = (*env)->NewObject( env, jcls, jmid, (*env)->CallStaticObjectMethod( env, jFloatCls, jFloatMid, pIP2LocationRecord->elevation ) );
			if ( bigDecimal == NULL ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not create a new BigDecimal instance" );
				return NULL;
			}
			if ( !setBigDecimal( env, jobj, "elevation", bigDecimal, NULL ) ) {
				IP2Location_free_record( pIP2LocationRecord );
				(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
				throwRuntimeException( env, "Could not set handle for a new BigDecimal instance" );
				return NULL;
			}
		}

		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->country_short ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->country_short ) ) {
			setString( env, jobj, "countryShort", (*env)->NewStringUTF( env, pIP2LocationRecord->country_short ), NULL );
		}

		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->country_long ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->country_long ) ) {
			setString( env, jobj, "countryLong", (*env)->NewStringUTF( env, pIP2LocationRecord->country_long ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->region ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->region ) ) {
			setString( env, jobj, "region", (*env)->NewStringUTF( env, pIP2LocationRecord->region ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->city ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->city ) ) {
			setString( env, jobj, "city", (*env)->NewStringUTF( env, pIP2LocationRecord->city ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->isp ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->isp ) ) {
			setString( env, jobj, "isp", (*env)->NewStringUTF( env, pIP2LocationRecord->isp ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->domain ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->domain ) ) {
			setString( env, jobj, "domain", (*env)->NewStringUTF( env, pIP2LocationRecord->domain ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->zipcode ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->zipcode ) ) {
			setString( env, jobj, "zipCode", (*env)->NewStringUTF( env, pIP2LocationRecord->zipcode ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->timezone ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->timezone ) ) {
			setString( env, jobj, "timeZone", (*env)->NewStringUTF( env, pIP2LocationRecord->timezone ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->netspeed ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->netspeed ) ) {
			setString( env, jobj, "netSpeed", (*env)->NewStringUTF( env, pIP2LocationRecord->netspeed ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->iddcode ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->iddcode ) ) {
			setString( env, jobj, "iddCode", (*env)->NewStringUTF( env, pIP2LocationRecord->iddcode ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->areacode ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->areacode ) ) {
			setString( env, jobj, "areaCode", (*env)->NewStringUTF( env, pIP2LocationRecord->areacode ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->weatherstationcode ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->weatherstationcode ) ) {
			setString( env, jobj, "weatherStationCode", (*env)->NewStringUTF( env, pIP2LocationRecord->weatherstationcode ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->weatherstationname ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->weatherstationname ) ) {
			setString( env, jobj, "weatherStationName", (*env)->NewStringUTF( env, pIP2LocationRecord->weatherstationname ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->mcc ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->mcc ) ) {
			setString( env, jobj, "mcc", (*env)->NewStringUTF( env, pIP2LocationRecord->mcc ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->mnc ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->mnc ) ) {
			setString( env, jobj, "mnc", (*env)->NewStringUTF( env, pIP2LocationRecord->mnc ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->mobilebrand ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->mobilebrand ) ) {
			setString( env, jobj, "mobileBrand", (*env)->NewStringUTF( env, pIP2LocationRecord->mobilebrand ), NULL );
		}
		
		if ( strcmp( JIP2LOCATION_EMPTY_RECORD_STRING, pIP2LocationRecord->usagetype ) && strcmp( NOT_SUPPORTED, pIP2LocationRecord->usagetype ) ) {
			setString( env, jobj, "usageType", (*env)->NewStringUTF( env, pIP2LocationRecord->usagetype ), NULL );
		}

		IP2Location_free_record( pIP2LocationRecord );
		(*env)->ReleaseStringUTFChars( env, jipAddress, ipAddress );
	} else {
		throwRuntimeException( env, "Could not find IP2Location pointer" );
		return NULL;
	}

	return jobj;
}

JNIEXPORT void JNICALL Java_com_ip2location_IP2Location_closeDatabase(JNIEnv *env, jclass class, jlong handle) {
	IP2Location* pIP2Location = (IP2Location*) handle;
	if ( pIP2Location != NULL ) {
		IP2Location_close( pIP2Location );
	}

	return;
}
