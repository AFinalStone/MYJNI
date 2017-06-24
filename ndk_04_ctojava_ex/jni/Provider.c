#include "Provider.h"
#include <android/log.h>

extern JNIEnv* jniEnv;//上下文虚拟机设备,extern的意思是这个变量在其他文件夹中声明过

jclass TestProvider;//获取TestProvider类
jobject mTestProvider;//TestProvider对应的实体对象
jmethodID getTime;//需要使用的函数ID，这个方法调用TestProvider的静态方法 public static String getTime();
jmethodID sayHello;//需要使用的函数ID，这个方法调用TestProvider的非静态方法 public void sayHello(String msg);

int GetProviderInstance(jclass obj_class);//通过传输的类对象，产生对应的对象实例

/**
 * 初始化 类、对象、方法
 */
int InitProvider() {

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  1" );

	if(jniEnv == NULL) {
		return 0;
	}

	if(TestProvider == NULL) {
	    //获取TestProvider的类对象
		TestProvider = (*jniEnv)->FindClass(jniEnv,"com/shi/androidstudy/ctojava/TestProvider");
		if(TestProvider == NULL){
			return -1;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  2 ok" );
	}

	if (mTestProvider == NULL) {
		//获取TestProvider的对象实例
		if (GetProviderInstance(TestProvider) != 1) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			return -1;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  3 ok" );
	}

	if (getTime == NULL) {
		getTime = (*jniEnv)->GetStaticMethodID(jniEnv, TestProvider, "getTime","()Ljava/lang/String;");
		if (getTime == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			return -2;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  4 ok" );
	}

	if (sayHello == NULL) {
		sayHello = (*jniEnv)->GetMethodID(jniEnv, TestProvider, "sayHello","(Ljava/lang/String;)V");
		if (sayHello == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, getTime);
			return -3;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  5 ok" );
	}

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  6" );
	return 1;

}

int GetProviderInstance(jclass obj_class) {

	if(obj_class == NULL) {
		return 0;
	}

	jmethodID construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class,"<init>", "()V");

	if (construction_id == 0) {
		return -1;
	}

	mTestProvider = (*jniEnv)->NewObject(jniEnv, obj_class,	construction_id);

	if (mTestProvider == NULL) {
		return -2;
	}

	return 1;
}

/**
 * 获取时间 ---- 调用 Java 方法
 */
void GetTime() {
	if(TestProvider == NULL || getTime == NULL) {
		int result = InitProvider();
		if (result != 1) {
			return;
		}
	}

	jstring jstr = NULL;
	char* cstr = NULL;

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin" );
	jstr = (*jniEnv)->CallStaticObjectMethod(jniEnv, TestProvider, getTime);
	cstr = (char*) (*jniEnv)->GetStringUTFChars(jniEnv,jstr, 0);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "Success Get Time from Java , Value = %s",cstr );
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime End" );

	(*jniEnv)->ReleaseStringUTFChars(jniEnv, jstr, cstr);
	(*jniEnv)->DeleteLocalRef(jniEnv, jstr);
}

/**
 * SayHello ---- 调用 Java 方法
 */
void SayHello() {
	if(TestProvider == NULL || mTestProvider == NULL || sayHello == NULL) {
		int result = InitProvider() ;
		if(result != 1) {
			return;
		}
	}

	jstring jstrMSG = NULL;
	jstrMSG =(*jniEnv)->NewStringUTF(jniEnv, "Hi,I'm From C");
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello Begin" );
	(*jniEnv)->CallVoidMethod(jniEnv, mTestProvider, sayHello,jstrMSG);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello End" );

	(*jniEnv)->DeleteLocalRef(jniEnv, jstrMSG);
}



