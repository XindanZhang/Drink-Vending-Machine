module machine_arm(
    input   wire    sys_clk,
    input   wire    gpio_in1,//控制高度的舵机输入端
    input   wire    gpio_in2,//控制伸缩的舵机输入端
    input   wire    gpio_in31,//控制旋转的舵机输入端
    input   wire    gpio_in32,//控制旋转的舵机输入端
    input   wire    gpio_in4,//控制抓放的舵机输入端
    output  reg     pwm_1,//控制高度的舵机输出端
    output  reg     pwm_2,//控制伸缩的舵机输出端
    output  reg     pwm_3,//控制旋转的舵机输出端
    output  reg     pwm_4//控制抓放的舵机输出端
    );

reg [20:0] cnt;
always@(posedge sys_clk)
begin
    if(cnt >= 1000000-1)
        cnt <= 0;
    else
        cnt <= cnt + 1; 
end
/*
    /1度=高电平值555
    sys_clk为50MHz，一个周期是2*10^-8s=2*10^-5ms。
    计数1000000次是20ms。
    转角        |    0        45       60        90       120      135     180      
    脉冲时间    |  0.5ms      1ms     1.16ms    1.5ms    1.66ms    2ms     2.5ms   
    cnt高电平值 |  25000     50000    58333     75000    91667   100000   125000  
*/
always@(posedge sys_clk)
begin
    //控制高度的舵机
    if(gpio_in1 == 0)   //机械臂到达最低处
        begin
            if(cnt >= 80000)
                pwm_1 <= 0;
            else 
                pwm_1 <= 1;
        end
    else if(gpio_in1 == 1)   //机械臂到达最高处
        begin
            if(cnt >= 120000)
                pwm_1 <= 0;
            else 
                pwm_1 <= 1;
        end
        
    //控制伸缩的舵机   
    if(gpio_in2 == 0)   //机械臂到达最后端
        begin
            if(cnt >= 83000)
                pwm_2 <= 0;
            else 
                pwm_2 <= 1;
        end
    else if(gpio_in2 == 1)   //机械臂到达最前端
        begin
            if(cnt >= 112000)
                pwm_2 <= 0;
            else 
                pwm_2 <= 1;
        end
        
    //控制旋转的舵机   
    if(gpio_in31 == 0&&gpio_in32 == 0)   //机械臂为初始位置
        begin
            if(cnt >= 97000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
    else if(gpio_in31 == 0&&gpio_in32 == 1)   //机械臂顺时针旋转至90
        begin
            if(cnt >= 52000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
    else if(gpio_in31 == 1&&gpio_in32 == 0)   //机械臂顺时针旋转至120
        begin
            if(cnt >= 38500)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end  
     else if(gpio_in31 ==1&&gpio_in32 == 1)   //机械臂顺时针旋转至150
        begin
            if(cnt >= 25000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
        
    //控制抓取的舵机   （数值变大 顺时针旋转）
    if(gpio_in4 == 0)   //机械臂放开
        begin
            if(cnt >= 30000)
                pwm_4 <= 0;
            else 
                pwm_4 <= 1;
        end
    else if(gpio_in4 == 1)   //机械臂抓取
        begin
            if(cnt >= 40000)
                pwm_4 <= 0;
            else 
                pwm_4 <= 1;
        end
    else
       begin
            if(cnt >= 120000)
                pwm_1 <= 0;
            else 
                pwm_1 <= 1;
            if(cnt >= 83000)
                pwm_2 <= 0;
            else 
                pwm_2 <= 1;
            if(cnt >= 97000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
            if(cnt >= 30000)
                pwm_4 <= 0;
            else 
                pwm_4 <= 1;
        end
        
        

    
end

endmodule