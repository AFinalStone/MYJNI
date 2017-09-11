package com.afinalstone.administrator.ndk_06_decompilation;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.mt.mtxx.image.JNI;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("mtimage-jni");
    }

    private ImageView imageView_result;
    private JNI jni;
    private Bitmap bitmap;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView_result = (ImageView) findViewById(R.id.imageView_result);
        jni = new JNI();
        InputStream is = getResources().openRawResource(R.mipmap.timg);
        bitmap = BitmapFactory.decodeStream(is);
    }

    public void onClick(View view){
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
        jni.StyleLomoB(pixels, width, height);
        // 用处理好的像素数组 创建一张新的图片就是经过特效处理的
        Bitmap bitmap_result = Bitmap.createBitmap(pixels, width, height, bitmap.getConfig());
        imageView_result.setImageBitmap(bitmap_result);
    }
}
