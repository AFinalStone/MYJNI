#include <jni.h>

/*
 * 对应的native方法, 需要一个string的返回值
 * jstring 对应Java中的String
 * Java_com_shi_androidstudy_myjni_MainActivity_sayHello 方法名
 * Java_包名(.改成_)_类名_方法名
 *
 * JNIEnv* Java当前虚拟机运行环境
 * jobject 当前调用这个函数的Java对象
 */
jstring Java_com_shi_androidstudy_ndk_MainActivity_sayHello(JNIEnv* env, jobject obj) {
	char* pc = "Hello from c";
	// jstring返回值  (*NewStringUTF)(JNIEnv*  java虚拟机运行环境, const char* C语言中的字符串);
	jstring str = (**env).NewStringUTF(env, pc);
	return str;
}
