package com.example.helloworld;

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



public class chActivity extends AppCompatActivity {
    //声明控件
    private ImageView mIvHead1;
    private SlideMenu slideMenu;
    private Button mBtn1;
    private Button mBtn2;
    private Button mBtn3;
    private  Button mBtn4;
    private  Button mBtn5;
    private  Button mBtn6;
    private  Button mBtn7;
    private  Button mBtn8;
    private  Button mBtn9;
    private  Button mBtn10;
    private  Button mBtn11;
    private  Button mBtn12;
    private String a1 = "a";
    private String a2 = "b";
    private String a3 = "c";
    private String a4 = "d";
    private String a5 = "e";
    private String a6 = "f";
    private String a7 = "g";
    private String a8 = "h";
    private String a9 = "i";
    private String a10 = "j";
    private String a11 = "k";
    private String a12 = "l";

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
        setContentView(R.layout.activity_ch);

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
        mBtn1=findViewById(R.id.rb_1);
        mBtn2=findViewById(R.id.rb_2);
        mBtn3=findViewById(R.id.rb_3);
        mBtn4=findViewById(R.id.rb_4);
        mBtn5=findViewById(R.id.rb_5);
        mBtn6=findViewById(R.id.rb_6);
        mBtn7=findViewById(R.id.rb_7);
        mBtn8=findViewById(R.id.rb_8);
        mBtn9=findViewById(R.id.rb_9);
        mBtn10=findViewById(R.id.rb_10);
        mBtn11=findViewById(R.id.rb_11);
        mBtn12=findViewById(R.id.rb_12);


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
        mBtn1.setOnClickListener(onClick);
        mBtn2.setOnClickListener(onClick);
        mBtn3.setOnClickListener(onClick);
        mBtn4.setOnClickListener(onClick);
        mBtn5.setOnClickListener(onClick);
        mBtn6.setOnClickListener(onClick);
        mBtn7.setOnClickListener(onClick);
        mBtn8.setOnClickListener(onClick);
        mBtn9.setOnClickListener(onClick);
        mBtn10.setOnClickListener(onClick);
        mBtn11.setOnClickListener(onClick);
        mBtn12.setOnClickListener(onClick);

    }

    private  class OnClick implements  View.OnClickListener{


        @SuppressLint("NonConstantResourceId")
        @Override
        public void onClick(View view) {
            devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
            Intent intent = null;
            switch (view.getId()){
                case R.id.rb_1:
                    HardwareControler.write(devfd,a1.getBytes());
                    break;
                case R.id.rb_2:
                  //  devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a2.getBytes());
                    break;
                case R.id.rb_3:
                  //  devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a3.getBytes());
                    break;
                case R.id.rb_4:
                 //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a4.getBytes());
                    break;
                case R.id.rb_5:
                 //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a5.getBytes());
                    break;
                case R.id.rb_6:
                 //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a6.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_7:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a7.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_8:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a8.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_9:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a9.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_10:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a10.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_11:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a11.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);

                case R.id.rb_12:
                    //   devfd=HardwareControler.openSerialPort(devName,speed,dataBits,stopBits);
                    HardwareControler.write(devfd,a12.getBytes());
                    break;
                //                    intent=new Intent(chActivity.this,chActivity.class);
            }

        }


    }

}