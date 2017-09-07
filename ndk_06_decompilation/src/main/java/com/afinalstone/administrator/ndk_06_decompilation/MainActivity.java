package com.afinalstone.administrator.ndk_06_decompilation;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;

import com.mt.mtxx.image.ImageDispose;
import com.mt.mtxx.image.JNI;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("mtimage-jni");
    }

    private ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView = (ImageView) findViewById(R.id.imageView);
        JNI jni = new JNI();

        InputStream is = getResources().openRawResource(R.mipmap.timg);
        Bitmap bitmap = BitmapFactory.decodeStream(is);
        byte[] ss = ImageDispose.Bitmap2Bytes(bitmap);
        jni.GaussIIRBlurImage(ss, bitmap.getWidth(), bitmap.getHeight(), bitmap.getWidth(), bitmap.getHeight());
    }
}
