package com.shi.androidstudy.ndk;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new Thread(new Runnable() {
            @Override
            public void run() {
                SystemClock.sleep(2000);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this,sayHello(),Toast.LENGTH_LONG).show();
                    }
                });
            }
        }).start();
    }

    public native String sayHello();

    static {
        // 导入动态库
        System.loadLibrary("hello");
    }
}
