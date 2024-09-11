module machine_arm(
    input   wire    sys_clk,
    input   wire    gpio_in1,//���Ƹ߶ȵĶ�������
    input   wire    gpio_in2,//���������Ķ�������
    input   wire    gpio_in31,//������ת�Ķ�������
    input   wire    gpio_in32,//������ת�Ķ�������
    input   wire    gpio_in4,//����ץ�ŵĶ�������
    output  reg     pwm_1,//���Ƹ߶ȵĶ�������
    output  reg     pwm_2,//���������Ķ�������
    output  reg     pwm_3,//������ת�Ķ�������
    output  reg     pwm_4//����ץ�ŵĶ�������
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
    /1��=�ߵ�ƽֵ555
    sys_clkΪ50MHz��һ��������2*10^-8s=2*10^-5ms��
    ����1000000����20ms��
    ת��        |    0        45       60        90       120      135     180      
    ����ʱ��    |  0.5ms      1ms     1.16ms    1.5ms    1.66ms    2ms     2.5ms   
    cnt�ߵ�ƽֵ |  25000     50000    58333     75000    91667   100000   125000  
*/
always@(posedge sys_clk)
begin
    //���Ƹ߶ȵĶ��
    if(gpio_in1 == 0)   //��е�۵�����ʹ�
        begin
            if(cnt >= 80000)
                pwm_1 <= 0;
            else 
                pwm_1 <= 1;
        end
    else if(gpio_in1 == 1)   //��е�۵�����ߴ�
        begin
            if(cnt >= 120000)
                pwm_1 <= 0;
            else 
                pwm_1 <= 1;
        end
        
    //���������Ķ��   
    if(gpio_in2 == 0)   //��е�۵�������
        begin
            if(cnt >= 83000)
                pwm_2 <= 0;
            else 
                pwm_2 <= 1;
        end
    else if(gpio_in2 == 1)   //��е�۵�����ǰ��
        begin
            if(cnt >= 112000)
                pwm_2 <= 0;
            else 
                pwm_2 <= 1;
        end
        
    //������ת�Ķ��   
    if(gpio_in31 == 0&&gpio_in32 == 0)   //��е��Ϊ��ʼλ��
        begin
            if(cnt >= 97000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
    else if(gpio_in31 == 0&&gpio_in32 == 1)   //��е��˳ʱ����ת��90
        begin
            if(cnt >= 52000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
    else if(gpio_in31 == 1&&gpio_in32 == 0)   //��е��˳ʱ����ת��120
        begin
            if(cnt >= 38500)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end  
     else if(gpio_in31 ==1&&gpio_in32 == 1)   //��е��˳ʱ����ת��150
        begin
            if(cnt >= 25000)
                pwm_3 <= 0;
            else 
                pwm_3 <= 1;
        end
        
    //����ץȡ�Ķ��   ����ֵ��� ˳ʱ����ת��
    if(gpio_in4 == 0)   //��е�۷ſ�
        begin
            if(cnt >= 30000)
                pwm_4 <= 0;
            else 
                pwm_4 <= 1;
        end
    else if(gpio_in4 == 1)   //��е��ץȡ
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