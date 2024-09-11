package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;

import com.example.helloworld.util.SlideMenu;
import com.friendlyarm.FriendlyThings.HardwareControler;

import java.util.Timer;


public class aqActivity extends AppCompatActivity {
    //声明控件
    private ImageView mIvHead1;
    private SlideMenu slideMenu;
    private Button drink1;
    private Button drink2;
    private Button drink3;
    private Button drink4;
    private String a1 = "m";
    private String a2 = "z";
    private String a3 = "x";
    private String a4 = "y";
    private String strread = null;


    private static final String TAG = "SerialPort";
    private TextView fromTextView = null;
    private EditText toEditor = null;
    private final int MAXLINES = 200;
    private StringBuilder remoteData = new StringBuilder(256 * MAXLINES);

    // NanoPC-T4 UART4
    private String devName = "/dev/ttyAMA3";
    private int speed = 115200;
    private int dataBits = 8;
    private int stopBits = 1;
    private int devfd = -1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_aq);

//        if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
//            setContentView(R.layout.serialport_dataprocessview_landscape);
//        } else if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
//            setContentView(R.layout.serialport_dataprocessview);
//        }
//
//        String winTitle = devName + "," + speed + "," + dataBits + "," + stopBits;
//        setTitle(winTitle);

        //找到控件
//        mIvHead1=findViewById(R.id.iv_head1);
//        slideMenu=findViewById(R.id.slideMenu);
        drink1=findViewById(R.id.lb_1);
        drink2=findViewById(R.id.lb_2);
        drink3=findViewById(R.id.lb_3);
        drink4=findViewById(R.id.lb_4);
        fromTextView = (TextView)findViewById(R.id.fromTextView);


//        ((Button)findViewById(R.id.rb_1)).setOnClickListener(this);
//        ((Button)findViewById(R.id.sendButton)).setOnClickListener(this);



        //实现侧滑部分,点击加侧滑
//        mIvHead1.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                slideMenu.switchMenu();
//            }
//        });
        setListener();

    }
    private void setListener(){
        OnClick onClick=new OnClick();

        //对每一个按钮进行setonClickListener
        drink1.setOnClickListener(onClick);
        drink2.setOnClickListener(onClick);
        drink3.setOnClickListener(onClick);
        drink4.setOnClickListener(onClick);

    }


    private final int BUFSIZE = 512;
    private byte[] buf = new byte[BUFSIZE];
    private Timer timer = new Timer();
    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {

            switch (msg.what) {
                case 1:
                    if (HardwareControler.select(devfd, 0, 0) == 1) {
                        int retSize = HardwareControler.read(devfd, buf, BUFSIZE);
                        if (retSize > 0) {

                            /*
                                str是串口接受到的数据
                             */
                            String str = new String(buf, 0, retSize);
                            strread=str;

                        }
                    }
            }
            super.handleMessage(msg);
        }
    };


    private  class OnClick implements  View.OnClickListener{


        @SuppressLint("NonConstantResourceId")
        @Override
        public void onClick(View view) {
            devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
            switch (view.getId()){
                case R.id.lb_1:
                    HardwareControler.write(devfd,a1.getBytes());
                    break;
                case R.id.lb_2:
                    //  devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a2.getBytes());
                    break;
                case R.id.lb_3:
                    //  devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a3.getBytes());
                    break;
                case R.id.lb_4:
                    //  devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a4.getBytes());
                    break;
            }

        }


    }



}