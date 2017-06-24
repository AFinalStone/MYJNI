#include <string.h>
#include <android/log.h>
#include <jni.h>

/**
 *  把jstring类型转化成char*类型
 */
char* jstringToChar(JNIEnv* env, jstring jstr) {

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


/**
 *  Java 中 声明的native getTime 方法的实现
 */
JNIEXPORT void JNICALL Java_com_shi_androidstudy_ctojava_MainActivity_getTime(JNIEnv* env, jobject thiz)
{
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始获取TestProvider.class" );

    // 找到类com.shi.androidstudy.ctojava.TestProvider
    // jclass (*FindClass)(JNIEnv*, const char*);
    jclass clazz_TestProvider = (**env).FindClass(env, "com/shi/androidstudy/ctojava/TestProvider");

    __android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始获取TestProvider的getTime方法ID" );
    // 得到静态方法   public static String getTime();
    // jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass 类, const char* 方法名, const char* 方法签名(需要使用javap获取方法签名));
    jmethodID methodId_getTime = (**env).GetStaticMethodID(env, clazz_TestProvider, "getTime", "()Ljava/lang/String;");

    __android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin" );
    //jobject     (*CallStaticObjectMethod)(JNIEnv*, jclass, jmethodID, ...);
    jstring jstr = (**env).CallStaticObjectMethod(env, clazz_TestProvider, methodId_getTime);
    char* cstr = jstringToChar(env,jstr);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "Success Get Time from Java , Value = %s",cstr);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime End" );
	(*env)->ReleaseStringUTFChars(env, jstr, cstr);
	(*env)->DeleteLocalRef(env, jstr);
}


/**
 *  Java 中 声明的native sayHello 方法的实现
 */
JNIEXPORT void JNICALL Java_com_shi_androidstudy_ctojava_MainActivity_sayHello(JNIEnv* env, jobject thiz)
{
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始获取TestProvider.class" );
    // 找到类com.shi.androidstudy.ctojava.TestProvider
    // jclass (*FindClass)(JNIEnv*, const char*);
	jclass	clazz_TestProvider = (*env)->FindClass(env,"com/shi/androidstudy/ctojava/TestProvider");

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始获取TestProvider的初始化<init>方法的ID" );
	jmethodID methodID_getObjectInstance = (*env)->GetMethodID(env, clazz_TestProvider,"<init>", "()V");

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始生成对象实例mTestProvider" );
	jobject object_TestProvider = (*env)->NewObject(env, clazz_TestProvider, methodID_getObjectInstance);

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "开始获取TestProvider的sayHello方法ID" );
	jmethodID methodID_sayHello = (*env)->GetMethodID(env, clazz_TestProvider, "sayHello","(Ljava/lang/String;)V");

	jstring jstrMSG = NULL;
	jstrMSG =(*env)->NewStringUTF(env, "Hi,I'm From C");
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello Begin" );
	(*env)->CallVoidMethod(env, object_TestProvider, methodID_sayHello,jstrMSG);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello End" );

	(*env)->DeleteLocalRef(env, jstrMSG);
}
