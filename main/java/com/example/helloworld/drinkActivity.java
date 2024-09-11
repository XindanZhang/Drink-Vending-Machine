package com.example.helloworld;

import android.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.DialogInterface;
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
import androidx.appcompat.app.AppCompatActivity;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.friendlyarm.FriendlyThings.HardwareControler;
import android.app.Activity;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.PopupWindow;
import android.widget.ScrollView;
import android.widget.TextView;
import android.util.Log;
import android.text.Html;
import android.widget.Toast;
import java.util.Timer;
import java.util.TimerTask;
import com.friendlyarm.FriendlyThings.HardwareControler;
import com.friendlyarm.FriendlyThings.BoardType;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.content.Context;
import android.content.Intent;
import java.util.LinkedList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class drinkActivity extends AppCompatActivity {
    //声明控件
    private ImageView mIvHead1;
    private SlideMenu slideMenu;
    private Button drink1;
    private Button drink2;
    private Button drink3;
    private String a1 = "b";
    private String a2 = "k";
    private String a3 = "n";
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
    private String str;

    @Override
    public void onDestroy() {
        timer.cancel();
        if (devfd != -1) {
            HardwareControler.close(devfd);
            devfd = -1;
        }
        super.onDestroy();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_drink);

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
                            String str = new String(buf, 0, retSize);
                            remoteData.append(str);

                            //Log.d(TAG, "#### LineCount: " + fromTextView.getLineCount() + ", remoteData.length()=" + remoteData.length());
                            if (fromTextView.getLineCount() > MAXLINES) {
                                int nLineCount = fromTextView.getLineCount();
                                int i = 0;
                                for (i = 0; i < remoteData.length(); i++) {
                                    if (remoteData.charAt(i) == '\n') {
                                        nLineCount--;

                                        if (nLineCount <= MAXLINES) {
                                            break;
                                        }
                                    }
                                }
                                remoteData.delete(0, i);
                                //Log.d(TAG, "#### remoteData.delete(0, " + i + ")");
                                if(remoteData.toString().equals("abc")){
                                    fromTextView.setText("123");
                                }
                            } else {
                                if(remoteData.toString().equals("abc")){
                                    fromTextView.setText("123");
                                }
                            }

                            ((ScrollView)findViewById(R.id.scroolView)).fullScroll(View.FOCUS_DOWN);
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
            }

        }


    }



}