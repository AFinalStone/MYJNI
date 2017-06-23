>之前写的项目都是非常简单的项目，这次进一步加深NDK的使用，C语言函数会稍微复杂一点


##### 一、首先看一下我们这次要实现的效果图

![效果图](http://img.blog.csdn.net/20170321134033196?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

##### 二、首先我们还是建立一个普通的Android项目，

- **添加MainActivity.java**

```java

package com.shi.androidstudy.ndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

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
        et_addB = (EditText) findViewById(R .id.et_addB);
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

```xml
<?xml version="1.0" encoding="utf-8"?>
<ScrollView xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:orientation="vertical"
        android:padding="@dimen/activity_horizontal_margin">

        <LinearLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:orientation="vertical">

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_addA"
                    android:layout_width="match_parent"
                    android:layout_height="wrap_content"
                    android:inputType="number"
                    android:hint="输入加数A" />
            </android.support.design.widget.TextInputLayout>

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_addB"
                    android:inputType="number"
                    android:layout_width="match_parent"
                    android:layout_height="wrap_content"
                    android:hint="输入加数B" />

            </android.support.design.widget.TextInputLayout>
        </LinearLayout>

        <Button
            android:id="@+id/tv_add"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:gravity="center"
            android:onClick="onClick"
            android:text="调用Add方法" />

        <LinearLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:orientation="vertical">

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_minuend"
                    android:layout_width="match_parent"
                    android:inputType="number"
                    android:layout_height="wrap_content"
                    android:hint="输入被减数" />
            </android.support.design.widget.TextInputLayout>

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_sub"
                    android:inputType="number"
                    android:layout_width="match_parent"
                    android:layout_height="wrap_content"
                    android:hint="输入减数" />

            </android.support.design.widget.TextInputLayout>
        </LinearLayout>

        <Button
            android:id="@+id/tv_sub"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:layout_marginTop="10dp"
            android:gravity="center"
            android:onClick="onClick"
            android:text="调用Sub方法" />

        <LinearLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:orientation="vertical">

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_userName"
                    android:layout_width="match_parent"
                    android:layout_height="wrap_content"
                    android:hint="请输入用户名" />
            </android.support.design.widget.TextInputLayout>

            <android.support.design.widget.TextInputLayout
                android:layout_width="match_parent"
                android:layout_height="wrap_content">

                <EditText
                    android:id="@+id/et_userPassword"
                    android:layout_width="match_parent"
                    android:layout_height="wrap_content"
                    android:inputType="numberPassword"
                    android:hint="请输入登录密码" />

            </android.support.design.widget.TextInputLayout>
        </LinearLayout>

        <Button
            android:id="@+id/tv_encryptPassword"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:layout_marginTop="10dp"
            android:gravity="center"
            android:onClick="onClick"
            android:text="对密码进行异或加密" />

        <android.support.design.widget.TextInputLayout
            android:layout_width="match_parent"
            android:layout_height="wrap_content">

            <EditText
                android:id="@+id/et_strMessage"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:hint="输入需要加密的字符串" />

        </android.support.design.widget.TextInputLayout>


        <Button
            android:id="@+id/tv_encryptMessage"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:layout_marginTop="10dp"
            android:gravity="center"
            android:onClick="onClick"
            android:text="信息加密" />
    </LinearLayout>
</ScrollView>
```

##### 三、添加生成.so库需要的文件：jni文件夹，AddAndSub.c，Encrypt.c Android.mk，Application.mk


AddAndSub.c文件
```c
#include <jni.h>

/*
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk_MainActivity_add
  (JNIEnv * env, jobject obj, jint i, jint j){
    return i+j;
  }

/*
 * Class:     com_shi_androidstudy_ndk02_MainActivity
 * Method:    sub
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_shi_androidstudy_ndk_MainActivity_sub
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
密码加密因为是C语言的int类型，所以不能过长，Encrypt.c中的C代码看起来可能有点生疏，
多看多思考应该问题不大，在编写C语言的过程中，经常需要进行各种java变量和C变量的类型转换，
可以尝试多看看jni.h文件，对于我们理解类型转换会很有帮助。

> [项目地址](https://github.com/AFinalStone/MYJNI)