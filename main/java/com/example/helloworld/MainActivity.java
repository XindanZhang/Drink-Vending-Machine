package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


import com.example.helloworld.util.ToastUtil;
//
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.app.Activity;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.util.Log;
import android.text.Html;
import android.widget.Toast;
import java.util.Timer;
import java.util.TimerTask;

import com.example.helloworld.util.SlideMenu;
import com.friendlyarm.FriendlyThings.HardwareControler;
import com.friendlyarm.FriendlyThings.BoardType;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.content.Context;
import android.content.Intent;
//
public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    //声明控件(需要用到的控件）
    private Button mBtnLogin;
    private EditText mEtUser;
    private EditText mEtpassword;
    private static final String TAG = "SerialPort";
    private EditText toEditor = null;
    private final int MAXLINES = 200;
    private StringBuilder remoteData = new StringBuilder(256 * MAXLINES);

    private String a1 = "a1";

    // NanoPC-T4 UART4
    private String devName = "/dev/ttyAMA3";
    private int speed = 115200;
    private int dataBits = 8;
    private int stopBits = 1;
    private int devfd = -1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //找到控件,找到登录按钮
        mBtnLogin =findViewById(R.id.btn_login);
        mEtUser=findViewById(R.id.et_1);
        mEtpassword=findViewById(R.id.et_2);

//        //实现直接跳转
//        mBtnLogin.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Intent intent=null;
//                intent=new Intent(MainActivity.this,FuncitionActivity.class);
//                startActivity(intent);
//            }
//        });

        //需要匹配对应的用户名和密码才能登录
        mBtnLogin.setOnClickListener(this);

        devfd = HardwareControler.openSerialPort( devName, speed, dataBits, stopBits );
        if (devfd >= 0) {
            timer.schedule(task, 0, 500);
        } else {
            devfd = -1;
            //fromTextView.append("Fail to open " + devName + "!");
        }

    }

    private final int BUFSIZE = 512;
    private byte[] buf = new byte[BUFSIZE];
    private Timer timer = new Timer();
    private String strsr ="s";

    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 1:
                    if (HardwareControler.select(devfd, 0, 0) == 1)
                    {
                        int retSize = HardwareControler.read(devfd, buf, BUFSIZE);
                        if (retSize > 0) {
                            String str = new String(buf, 0, retSize);
                            remoteData.append(str);
                            //Log.d(TAG, "#### LineCount: " + fromTextView.getLineCount() + ", remoteData.length()=" + remoteData.length());
                                int i = 0;
                                for (i = 0; i < remoteData.length(); i++) {
                                    if(remoteData.charAt(i)=='a')
                                    {
                                      //  HardwareControler.write(devfd, strsr.getBytes());
                                    }
                                }
                                //Log.d(TAG, "#### remoteData.delete(0, " + i + ")");
                        }
                    }
                    break;
            }
            super.handleMessage(msg);
        }
    };

    private TimerTask task = new TimerTask() {
        public void run() {
            Message message = new Message();
            message.what = 1;
            handler.sendMessage(message);
        }
    };

    public void onClick(View v) {
        devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
        HardwareControler.write(devfd,a1.getBytes());
        //需要获取输入的用户名和密码
        String username = mEtUser.getText().toString();
        String password = mEtpassword.getText().toString();
        //弹出的内容设置
        String ok = "登陆成功";
        String fail = "密码或者账号有误，请重新登录";
        Intent intent = null;

        //假设正确的账号和密码分别是houlang,123456
        if (username.equals("hl") && password.equals("a")) {
            //toast普通版
            //Toast.makeText(getApplicationContext(),ok,Toast.LENGTH_SHORT).show();

            //封装好的类
            ToastUtil.showMsg(MainActivity.this, ok);
            //如果正确的话进行跳转
            intent = new Intent(MainActivity.this, SlideActivity.class);
            startActivity(intent);
        } else {
            //不正确,弹出登陆失败
            //提升版，居中显示
//            Toast toastCenter = Toast.makeText(getApplicationContext(), fail, Toast.LENGTH_SHORT);
//            toastCenter.setGravity(Gravity.CENTER, 0, 0);
//            toastCenter.show();
            //使用封装好的类
            ToastUtil.showMsg(getApplicationContext(),fail);


            //如果错误进行选择
        }


    }
        @Override
        public void onPointerCaptureChanged(boolean hasCapture) {
        super.onPointerCaptureChanged(hasCapture);
    }
}