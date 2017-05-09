package com.shi.androidstudy.ndk04_alipay;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private EditText et_account, et_pwd, et_count;
    private LinearLayout linearLayout_progressBar;
    private TextView tv_msg;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 初始化控件
        initViews();
    }

    private void initViews() {
        et_account = (EditText) findViewById(R.id.et_account);
        et_pwd = (EditText) findViewById(R.id.et_pwd);
        et_count = (EditText) findViewById(R.id.et_count);
        linearLayout_progressBar = (LinearLayout) findViewById(R.id.linearLayout_progressBar);
        tv_msg = (TextView) findViewById(R.id.tv_msg);
    }

    public void onClick(View view) {
        // 拿到数据
        final String account = et_account.getText().toString().trim();
        final String pwd = et_pwd.getText().toString().trim();
        final int count = Integer.parseInt(et_count.getText().toString());

        new Thread() {
            @Override
            public void run() {
                // 调用C语言支付
                int code = pay(account, pwd, count);

                switch (code) {
                    case 0:
                        showMessage("支付成功");
                        break;
                    case 1:
                        showMessage("账号或者密码错误");
                        break;
                    case 2:
                        showMessage("金额超限");
                        break;
                }
            }
        }.start();
    }

    private void showMessage(final String str) {
        runOnUiThread(new Runnable() {

            @Override
            public void run() {
                Toast.makeText(MainActivity.this, str, Toast.LENGTH_SHORT).show();
            }
        });
    }

    public void showProgressBar(final String msg) {

        runOnUiThread(new Runnable() {

            @Override
            public void run() {
                tv_msg.setText(msg);
                linearLayout_progressBar.setVisibility(View.VISIBLE);
            }
        });

    }

    public void hideProgressBar() {

        runOnUiThread(new Runnable() {

            @Override
            public void run() {
                linearLayout_progressBar.setVisibility(View.GONE);
            }
        });
    }

    public static void println(String msg) {
        System.out.println(msg);
    }


    public static String printlnAndBack(String msg) {
        String backStr = "我是返回值:"+msg;
        return backStr;
    }

    /**
     * 返回码
     * 0 支付成功
     * 1 账号或者密码错误 账号 abc 密码 123
     * 2 金额超限 不能超过5000
     */
    public native int pay(String account, String pwd, int count);

    static {
        System.loadLibrary("alipay");
    }
}
