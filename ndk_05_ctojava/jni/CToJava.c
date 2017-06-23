#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "Provider.h"

JNIEnv* jniEnv;

/**
 *  Java 中 声明的native getTime 方法的实现
 */
JNIEXPORT void JNICALL Java_com_shi_androidstudy_ctojava_MainActivity_getTime(JNIEnv* env, jobject thiz)
{

	if(jniEnv == NULL) {
		jniEnv = env;
	}
	GetTime();
//	GetTime02(env);
}

/**
 *  Java 中 声明的native sayHello 方法的实现
 */
JNIEXPORT void JNICALL Java_com_shi_androidstudy_ctojava_MainActivity_sayHello(JNIEnv* env, jobject thiz)
{
	if (jniEnv == NULL) {
		jniEnv = env;
	}

	SayHello();
}
