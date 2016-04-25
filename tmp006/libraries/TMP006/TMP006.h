#ifndef _TMP006_H_INCLUDED
#define _TMP006_H_INCLUDED

#include <Wire.h>
#include <math.h>

//器件的地址与管脚的连接方式有关
#define ICADDR	0X40

//tmp006中五个寄存器的地址
#define VOBJ	0x00
#define TAMB	0x01
#define CONFIG	0x02
#define MID		0xFE
#define DID		0xFF

//设置传感器tmp006的采样速率
#define mode1  0x0000		//4次每秒 4conversion/sec
#define mode2  0x0200		//2次每秒 2conversion/sec
#define mode3  0x0400		//1次每秒 1conversion/sec(默认状态)
#define mode4  0x0600		//0.5次每秒 0.5conversion/sec
#define mode5  0x0800		//0.25次每秒 0.25conversion/sec

//计算温度时用到的参数
#define s0		0.00000000000006
#define a1		0.00175
#define a2		-0.00001678
#define tref	298.15 
#define b0		-0.0000294
#define b1		-0.00000057
#define b2		0.00000000463
#define c2		13.4

class TMP006Class {
public:

	double vobj;		//测量目标所得到得电压值（-51.2mv——2.15mv）
	double tdie;		//环境的温度（开式温度，K，不是摄氏温度）
	double tobj;		//测量目标的温度（开式温度，K，不是摄氏温度）

	void begin();		//初始化
	void reset();		//软件重启

	unsigned int read( int);	//读寄存器

	void write(int,int);		//写寄存器

	double gettmp(void);		//计算测量目标的温度，返回值时摄氏温度

	void setmode(int);			//设置tmp006的测量速率

	void end(void);				//停止测量，进入power down模式
};

extern TMP006Class TMP006;

#endif
