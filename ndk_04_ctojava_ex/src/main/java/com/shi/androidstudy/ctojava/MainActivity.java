package com.shi.androidstudy.ctojava;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/**
 * C 调用 Java 例子
 *
 * @author AFinalStone
 *
 */
public class MainActivity extends Activity {
    //也就是你mk配置文件中的  LOCAL_MODULE    := NDK_04
    private static final String libSoName = "NDK_04";
    private static final String tag = "MainActivity";

    public static Context mContext = null;
    private Button btnClickStatic = null;
    private Button btnClick = null;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mContext = this;
        //初始化控件
        initViews();
    }

    /**
     * 初始化控件
     */
    private void initViews() {

        btnClickStatic = (Button) this.findViewById(R.id.btn_click_static);
        btnClickStatic.setOnClickListener(new OnClickListener() {

            public void onClick(View v) {
                getTime();
            }
        });

        btnClick = (Button) this.findViewById(R.id.btn_click_noStatic);
        btnClick.setOnClickListener(new OnClickListener() {

            public void onClick(View v) {
                sayHello();
            }
        });


    }

    public native void getTime() ;

    public native void sayHello() ;

    /**
     * 载入JNI生成的so库文件
     */
    static {
        System.loadLibrary(libSoName);
    }

}