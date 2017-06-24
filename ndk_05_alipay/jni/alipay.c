#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

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

JNIEXPORT jint JNICALL Java_com_shi_androidstudy_alipay_MainActivity_pay
  (JNIEnv *env, jobject obj, jstring account, jstring pwd, jint count) {


    // 找到类com.shi.androidstudy.alipay.MainActivity
    // jclass (*FindClass)(JNIEnv*, const char*);
    jclass clazz = (**env).FindClass(env, "com/shi/androidstudy/alipay/MainActivity");

    // 得到非静态方法   public void showProgressBar(final String msg)和public void hideProgressBar()
    // jmethodID (*GetMethodID)(JNIEnv*, jclass 类, const char* 方法名, const char* 方法签名(需要使用javap获取方法签名;)返回类型);

    jmethodID methodId_showProgressBar = (**env).GetMethodID(env, clazz, "showProgressBar", "(Ljava/lang/String;)V");
    jmethodID methodId_hideProgressBar = (**env).GetMethodID(env, clazz, "hideProgressBar", "()V");

    // 得到静态方法     public static void println(String msg)；
    // jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass 类, const char* 方法名, const char* 方法签名(需要使用javap获取方法签名));
    jmethodID methodId_println = (**env).GetStaticMethodID(env, clazz, "println", "(Ljava/lang/String;)V");
    jmethodID methodId_printlnAndBack = (**env).GetStaticMethodID(env, clazz, "printlnAndBack", "(Ljava/lang/String;)Ljava/lang/String;");


    // 调用获取到的方法
    // void (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
     jstring msg  =(*env)->NewStringUTF(env, "请稍等...");
    (**env).CallVoidMethod(env, obj, methodId_showProgressBar, msg);

	// 校验账号密码
	LOGD("正在校验账号密码");
	sleep(2);

	// 验证登陆
	LOGD("正在验证登陆");
	sleep(2);

	// 支付
	LOGD("正在支付");
	sleep(2);
    (**env).CallVoidMethod(env, obj, methodId_hideProgressBar);

    sleep(2);
    //void  (*CallStaticVoidMethod)(JNIEnv*, jclass 类, jmethodID 方法名, ...);
    jstring tip  =(*env)->NewStringUTF(env, "操作完成...");
    (**env).CallStaticVoidMethod(env, clazz, methodId_println, tip);

    //jobject     (*CallStaticObjectMethod)(JNIEnv*, jclass, jmethodID, ...);
    jstring tipBack = (**env).CallStaticObjectMethod(env, clazz, methodId_printlnAndBack, tip);
    (**env).CallStaticVoidMethod(env, clazz, methodId_println, tipBack);

	// 拿到C语言可以使用的字符串
	char* pa = Jstring2CStr(env, account);
	char* pp = Jstring2CStr(env, pwd);

	// 定义正确的账号和密码
	char* par = "abc";
	char* ppr = "123";

	// 判断字符串
	int ia = strcmp(pa, par);
	int ip = strcmp(pp, ppr);

	if (ia == 0 && ip == 0) {

		if (count > 5000) {
			// 金额超限
			return 2;
		}

		return 0;

	} else {
		// 账号密码错误
		return 1;
	}
}



