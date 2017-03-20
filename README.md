## NDK学习笔记<五> java调用JNI进行简单加减,加密操作

>之前写的项目都是非常简单的项目，这次进一步加深NDK的使用，C语言函数会稍微复杂一点


##### 一、先看一下我们这次要实现的效果图

![效果图](/screen/ndk02_01.gif)

##### 二、首先我们还是建立一个普通的Android项目，

- **添加MainActivity.java**

```java

public class MainActivity extends AppCompatActivity {

    EditText et_addA;
    EditText et_addB;
    EditText et_minuend;
    EditText et_sub;
    EditText et_userName;
    EditText et_userPassword;
    EditText et_strMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et_addA = (EditText) findViewById(R.id.et_addA);
        et_addB = (EditText) findViewById(R.id.et_addB);
        et_minuend = (EditText) findViewById(R.id.et_minuend);
        et_sub = (EditText) findViewById(R.id.et_sub);
        et_userName = (EditText) findViewById(R.id.et_userName);
        et_userPassword = (EditText) findViewById(R.id.et_userPassword);
        et_strMessage = (EditText) findViewById(R.id.et_strMessage);
    }

    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.tv_add:
                int addA = Integer.parseInt(et_addA.getText().toString().trim());
                int addB = Integer.parseInt(et_addB.getText().toString().trim());
                showMessage("两数相加结果为：" + add(addA, addB));
                break;
            case R.id.tv_sub:
                int subA = Integer.parseInt(et_minuend.getText().toString().trim());
                int subB = Integer.parseInt(et_sub.getText().toString().trim());
                showMessage("两数相减结果为：" + sub(subA, subB));
                break;
            case R.id.tv_encryptPassword:
                int passWord = Integer.parseInt(et_userPassword.getText().toString().trim());
                showMessage("密码异或加密之后为：" + encryptPassword(passWord));
                break;
            case R.id.tv_encryptMessage:
                showMessage("字符串加密之后为：" + encryptString(et_strMessage.getText().toString().trim()));
                break;
        }
    }

    private void showMessage(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public native int add(int i, int j);

    public native int sub(int i, int j);

    public native int encryptPassword(int password);

    public native String encryptString(String strMessage);

    static {
        System.loadLibrary("MyNdk");
    }

}


```

- **添加activity_main.xml**

非常简单的布局，这里就不给出具体的xml代码了。需

##### 三、添加NDK文件，jni文件夹，AddAndSub.c，Encrypt.c Android.mk，Application.mk


AddAndSub.c文件
```c
#include <jni.h>

/*
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    add
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk02_MainActivity_add
  (JNIEnv * env, jobject obj, jint i, jint j){
    return i+j;
  }

/*
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    sub
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk02_MainActivity_sub
  (JNIEnv * env, jobject obj, jint i, jint j){
    return i-j;
  }

```

Encrypt.c文件
```c
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    encryptPassword
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk02_MainActivity_encryptPassword
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
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    encryptString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_shi_androidstudy_ndk02_MainActivity_encryptString
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

```

Android.mk文件

```mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := MyNdk
LOCAL_SRC_FILES := AddAndSub.c Encrypt.c

include $(BUILD_SHARED_LIBRARY)

```

Application.mk文件

```mk

APP_ABI := all

```
##### 四、依然不要忘记修改gradle文件，否则项目会找不到库文件

到这里运行程序，应该就能得到我们想要的效果了，界面输入我没有进行判空处理，所以别输入空的字符串，
密码加密因为是C语言的int类型，所以不能过长，其他部分主要是Encrypt.c中的代码看起来可能有点生疏，
多看多西靠应该问题不大，在编写C语言的过程中，经常需要进行各种java变量和C变量的类型转换，
可以尝试多看看jni.h文件，对于我们理解类型转换会很有帮助










