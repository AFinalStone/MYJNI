#include <jni.h>

JNIEXPORT jstring JNICALL Java_com_shi_androidstudy_ndk_MainActivity_useJavah
  (JNIEnv * env, jobject obj){
  	char* pc = "use javah make .h文件";
  	jstring str = (**env).NewStringUTF(env, pc);
  	return str;
  }