#ifndef _TMP006_H_INCLUDED
#define _TMP006_H_INCLUDED

#include <Wire.h>
#include <math.h>

//�����ĵ�ַ��ܽŵ����ӷ�ʽ�й�
#define ICADDR	0X40

//tmp006������Ĵ����ĵ�ַ
#define VOBJ	0x00
#define TAMB	0x01
#define CONFIG	0x02
#define MID		0xFE
#define DID		0xFF

//���ô�����tmp006�Ĳ�������
#define mode1  0x0000		//4��ÿ�� 4conversion/sec
#define mode2  0x0200		//2��ÿ�� 2conversion/sec
#define mode3  0x0400		//1��ÿ�� 1conversion/sec(Ĭ��״̬)
#define mode4  0x0600		//0.5��ÿ�� 0.5conversion/sec
#define mode5  0x0800		//0.25��ÿ�� 0.25conversion/sec

//�����¶�ʱ�õ��Ĳ���
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

	double vobj;		//����Ŀ�����õ��õ�ѹֵ��-51.2mv����2.15mv��
	double tdie;		//�������¶ȣ���ʽ�¶ȣ�K�����������¶ȣ�
	double tobj;		//����Ŀ����¶ȣ���ʽ�¶ȣ�K�����������¶ȣ�

	void begin();		//��ʼ��
	void reset();		//�������

	unsigned int read( int);	//���Ĵ���

	void write(int,int);		//д�Ĵ���

	double gettmp(void);		//�������Ŀ����¶ȣ�����ֵʱ�����¶�

	void setmode(int);			//����tmp006�Ĳ�������

	void end(void);				//ֹͣ����������power downģʽ
};

extern TMP006Class TMP006;

#endif
