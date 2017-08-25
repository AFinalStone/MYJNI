package com.afinalstone.administrator.ndk_07_buildbyas;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(this,checkSum("123"),Toast.LENGTH_SHORT).show();
    }

    native String checkSum(String msg);

    static {
        System.loadLibrary("native-lib");
    }

}
