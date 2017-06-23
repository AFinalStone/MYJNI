#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Class:     com_shi_androidstudy_ndk_MainActivity
 * Method:    encryptPassword
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk_MainActivity_encryptPassword
  (JNIEnv * env, jobject obj, jint password){
	return password ^ 123123;
  }


char* Jstring2CStr(JNIEnv* env, jstring jstr) {

	char* rtn = NULL;

	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env, "GB2312");

	jmethodID mid = (*env)->GetMethodID(env,clsstring, "getBytes", "(Ljava/lang/String;)[B");

	jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env,jstr,mid,strencode); // String.getByte("GB2312");
	jsize alen = (*env)->GetArrayLength(env, barr);
	jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);

	if(alen > 0) {
	rtn = (char*)malloc(alen+1); //"\0"
	memcpy(rtn, ba, alen);
	rtn[alen] = 0;
	}

	(*env) -> ReleaseByteArrayElements(env,barr,ba,0);

	return rtn;
}

/*
 * Class:     com_shi_androidstudy_ndk_MainActivity
 * Method:    encryptString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_shi_androidstudy_ndk_MainActivity_encryptString
  (JNIEnv * env, jobject obj, jstring message){

	char* pc = Jstring2CStr(env, message);

	// 得到jstring的长度
	int size = (**env).GetStringLength(env, message);

	int i = 0;
	for (i = 0; i < size; ++i) {
		char c = *(pc + i);
		*(pc + i) = c + 1;
	}

	return (**env).NewStringUTF(env, pc);
  }