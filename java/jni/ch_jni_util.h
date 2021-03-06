/*
 *
 *      Filename: ch_jni_util.h
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-06-08 12:23:21
 * Last Modified: 2018-06-08 12:23:21
 */

#ifndef CH_JNI_UTIL_H
#define CH_JNI_UTIL_H

#include <jni.h>
#include <string.h>

static inline void ch_set_int_field(JNIEnv *jenv,jobject jobj,const char *f,int v){

	jclass cls = (*jenv)->GetObjectClass(jenv,jobj);

	jfieldID fid = (*jenv)->GetFieldID(jenv,cls, f, "I");
	(*jenv)->SetIntField(jenv,jobj,fid,v);
}

static inline void ch_set_long_field(JNIEnv *jenv,jobject jobj,const char *f,long v){

	jclass cls = (*jenv)->GetObjectClass(jenv,jobj);
	jfieldID fid = (*jenv)->GetFieldID(jenv,cls, f, "J");
	(*jenv)->SetLongField(jenv,jobj,fid,v);
}

static inline void ch_send_data_to_java(JNIEnv *jenv,jobject jobj,void *data,long dlen){

	jclass cls = (*jenv)->GetObjectClass(jenv,jobj);
	/*call java function updateByteBuffer to adjust the buf*/
	jmethodID upfun = (*jenv)->GetMethodID(jenv,cls,"updateByteBuffer","(J)V");
	(*jenv)->CallVoidMethod(jenv,jobj,upfun,dlen);

	/*copy data into java bytebuffer*/
	jfieldID fid = (*jenv)->GetFieldID(jenv,cls, "dataBuffer", "Ljava/nio/ByteBuffer;");
	jobject jb = (*jenv)->GetObjectField(jenv,jobj, fid);
	void *jb_ptr = (void*)(*jenv)->GetDirectBufferAddress(jenv,jb);

	memcpy(jb_ptr,data,dlen);

}

#endif /*CH_JNI_UTIL_H*/
