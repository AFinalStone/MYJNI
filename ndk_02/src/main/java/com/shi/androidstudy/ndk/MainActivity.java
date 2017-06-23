package com.shi.androidstudy.ndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    String str;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClick(View view){
        Toast.makeText(this, useJavah(), Toast.LENGTH_SHORT).show();
    }

    public native String useJavah();

    static {
        // 导入动态库
        System.loadLibrary("javah");
    }
}
