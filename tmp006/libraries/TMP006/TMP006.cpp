
#include <TMP006.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
TMP006Class TMP006;

void TMP006Class::begin() {				//开始，初始化IIC通讯模块，初始化TMP006
	unsigned int config =0x7400;
	Wire.begin();
	write(CONFIG,config);    
}

void TMP006Class::reset() {				//软件重新启动tmp006模块
	unsigned int reset =0x8000;
	write(CONFIG,reset);
}

unsigned int TMP006Class::read(int reg){	//读取tmp006寄存器的值，参数是寄存器地址
	
	unsigned int reading = 0;				//每个寄存器有且仅有16位，故每次只读取一个int型数据即可

	Wire.beginTransmission(ICADDR);			//tmp006地址，与管脚ADR0、ADR1的连接方式有关，详见datasheet第8页
#if ARDUINO >= 100
	Wire.write(reg);	
#else
	Wire.send(reg);	
#endif
							//写入要读取寄存器的地址
	Wire.endTransmission();					//发送数据


	Wire.requestFrom(ICADDR, 2);			//要求向tmp006读取两个字节的数据


	if(2 <= Wire.available())				//得到两个字节数据后写入reading
	{
#if ARDUINO >= 100
		reading = Wire.read();  
		reading = reading << 8;    
		reading |= Wire.read(); 
#else
		reading = Wire.receive();  
		reading = reading << 8;    
		reading |= Wire.receive(); 
#endif
		
	}
	else{
#ifdef __TMP_DEBUG
		Serial.print("error\n");
#endif
	}

	return reading; 
}

void TMP006Class::write(int reg,int data){		//向tmp006相应的寄存器（reg）写入数据（data）
	Wire.beginTransmission(ICADDR);				//写入器件地址

#if ARDUINO >= 100
	Wire.write(reg);								//寄存器地址
	Wire.write((unsigned char)(data>>8));        //先写入高8位
	Wire.write((unsigned char)(data&0x00FF));    //写入低8位	
#else
	Wire.send(reg);								//寄存器地址
	Wire.send((unsigned char)(data>>8));        //先写入高8位
	Wire.send((unsigned char)(data&0x00FF));    //写入低8位
#endif

	Wire.endTransmission();						//写入数据  
}

double TMP006Class::gettmp(){					//通过读取tmp006的寄存器，计算测量目标的温度返回的是摄氏温度
//计算vobj
	int data1=0,data2=0;
	double s=0,vos=0,fvobj=0;

	while(read(CONFIG)&0x0080!=0x0080){			//等待转换完成
	}

	data1=read(VOBJ);							//读取vobj寄存器值并且计算对应的信号电压值
	if(data1>>15)
	{
		vobj=-(~data1+1)*0.00000015625;
	}else
	{
		vobj=data1*0.00000015625;
	}
	

	data2=read(TAMB);							//读取tamb寄存器值并且计算对应的环境温度
	if(data2>>15)
	{
		data2=((~data2)>>2)+1;
		tdie=-0.03125*data2+273.15;
	}else
	{
		data2=data2>>2;
		tdie=0.03125*data2+273.15;
	}

	s=s0*(1+a1*(tdie-tref)+a2*(tdie-tref)*(tdie-tref));	//根据相应的计算公式计算出测量目标的温度
	vos=b0+b1*(tdie-tref)+b2*(tdie-tref)*(tdie-tref);
	fvobj=(vobj-vos)+c2*(vobj-vos)*(vobj-vos);
	tobj=sqrt(sqrt((tdie*tdie*tdie*tdie)+(fvobj/s)));

	return (tobj-273.15);								//完成计算，转换为摄氏温度返回。
}

void TMP006Class::setmode(int mode){
	unsigned int config=0x7000;

	config=config|mode;
	write(CONFIG,config);
}

void TMP006Class::end(void){
	unsigned int config=0x0400;

	write(CONFIG,config);
}

