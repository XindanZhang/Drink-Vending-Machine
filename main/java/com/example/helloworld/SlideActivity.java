package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.helloworld.util.SlideMenu;


public class SlideActivity extends AppCompatActivity {
    //声明控件
    private ImageView mIvHead;
    private SlideMenu slideMenu;
    private Button mBtnch;
    private Button mBtnly;
    private Button mBtnfd;
    private  Button mBtnaq;
    private  Button mBtnhj;

    private String a1 = "a1";
    private String a2 = "a2";
    private String a3 = "a3";
    private String a4 = "a4";
    private String a5 = "a5";
    private String a6 = "a6";

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
        setContentView(R.layout.activity_slide);

        //找到控件
        mIvHead=findViewById(R.id.iv_head);
        slideMenu=findViewById(R.id.slideMenu);
        mBtnch=findViewById(R.id.btn_main_1);
        mBtnly=findViewById(R.id.btn_main_2);
        mBtnaq=findViewById(R.id.btn_main_3);
        mBtnfd=findViewById(R.id.btn_main_4);
        mBtnhj=findViewById(R.id.btn_main_5);


        //实现侧滑部分,点击加侧滑
        mIvHead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                slideMenu.switchMenu();
            }
        });
        setListener();

    }
    private void setListener(){
        OnClick onClick=new OnClick();

        //对每一个按钮进行setonClickListener
        mBtnch.setOnClickListener(onClick);
        mBtnly.setOnClickListener(onClick);
        mBtnaq.setOnClickListener(onClick);
        mBtnfd.setOnClickListener(onClick);
        mBtnhj.setOnClickListener(onClick);

    }

    private  class OnClick implements  View.OnClickListener{


        @Override
        public void onClick(View view) {
            Intent intent = null;
            switch (view.getId()){
                case R.id.btn_main_1:
                    intent=new Intent(SlideActivity.this,chActivity.class);
                    break;

                case R.id.btn_main_2:
                    intent=new Intent(SlideActivity.this, drinkActivity.class);

                    break;
                case R.id.btn_main_3:
                    intent=new Intent(SlideActivity.this,aqActivity.class);
                    break;
                case R.id.btn_main_4:
                    intent=new Intent(SlideActivity.this,fdActivity.class);
                    break;
                case R.id.btn_main_5:
                    intent=new Intent(SlideActivity.this,hjActivity.class);
                    break;

            }
            startActivity(intent);

        }


    }

}