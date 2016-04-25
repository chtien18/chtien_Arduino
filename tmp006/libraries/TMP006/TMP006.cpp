
#include <TMP006.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
TMP006Class TMP006;

void TMP006Class::begin() {				//��ʼ����ʼ��IICͨѶģ�飬��ʼ��TMP006
	unsigned int config =0x7400;
	Wire.begin();
	write(CONFIG,config);    
}

void TMP006Class::reset() {				//�����������tmp006ģ��
	unsigned int reset =0x8000;
	write(CONFIG,reset);
}

unsigned int TMP006Class::read(int reg){	//��ȡtmp006�Ĵ�����ֵ�������ǼĴ�����ַ
	
	unsigned int reading = 0;				//ÿ���Ĵ������ҽ���16λ����ÿ��ֻ��ȡһ��int�����ݼ���

	Wire.beginTransmission(ICADDR);			//tmp006��ַ����ܽ�ADR0��ADR1�����ӷ�ʽ�йأ����datasheet��8ҳ
#if ARDUINO >= 100
	Wire.write(reg);	
#else
	Wire.send(reg);	
#endif
							//д��Ҫ��ȡ�Ĵ����ĵ�ַ
	Wire.endTransmission();					//��������


	Wire.requestFrom(ICADDR, 2);			//Ҫ����tmp006��ȡ�����ֽڵ�����


	if(2 <= Wire.available())				//�õ������ֽ����ݺ�д��reading
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

void TMP006Class::write(int reg,int data){		//��tmp006��Ӧ�ļĴ�����reg��д�����ݣ�data��
	Wire.beginTransmission(ICADDR);				//д��������ַ

#if ARDUINO >= 100
	Wire.write(reg);								//�Ĵ�����ַ
	Wire.write((unsigned char)(data>>8));        //��д���8λ
	Wire.write((unsigned char)(data&0x00FF));    //д���8λ	
#else
	Wire.send(reg);								//�Ĵ�����ַ
	Wire.send((unsigned char)(data>>8));        //��д���8λ
	Wire.send((unsigned char)(data&0x00FF));    //д���8λ
#endif

	Wire.endTransmission();						//д������  
}

double TMP006Class::gettmp(){					//ͨ����ȡtmp006�ļĴ������������Ŀ����¶ȷ��ص��������¶�
//����vobj
	int data1=0,data2=0;
	double s=0,vos=0,fvobj=0;

	while(read(CONFIG)&0x0080!=0x0080){			//�ȴ�ת�����
	}

	data1=read(VOBJ);							//��ȡvobj�Ĵ���ֵ���Ҽ����Ӧ���źŵ�ѹֵ
	if(data1>>15)
	{
		vobj=-(~data1+1)*0.00000015625;
	}else
	{
		vobj=data1*0.00000015625;
	}
	

	data2=read(TAMB);							//��ȡtamb�Ĵ���ֵ���Ҽ����Ӧ�Ļ����¶�
	if(data2>>15)
	{
		data2=((~data2)>>2)+1;
		tdie=-0.03125*data2+273.15;
	}else
	{
		data2=data2>>2;
		tdie=0.03125*data2+273.15;
	}

	s=s0*(1+a1*(tdie-tref)+a2*(tdie-tref)*(tdie-tref));	//������Ӧ�ļ��㹫ʽ���������Ŀ����¶�
	vos=b0+b1*(tdie-tref)+b2*(tdie-tref)*(tdie-tref);
	fvobj=(vobj-vos)+c2*(vobj-vos)*(vobj-vos);
	tobj=sqrt(sqrt((tdie*tdie*tdie*tdie)+(fvobj/s)));

	return (tobj-273.15);								//��ɼ��㣬ת��Ϊ�����¶ȷ��ء�
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

