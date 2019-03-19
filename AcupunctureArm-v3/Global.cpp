#include "stdafx.h"
#include "Global.h"
#include <xtgmath.h>


BOOL CGlobal::connected = FALSE;
BOOL CGlobal::calibrated = FALSE;
double CGlobal::force[5] = { 0.0 };
int CGlobal::export_choose=0;
float CGlobal::niddle_position[5] = { 0.0 };
//double CGlobal::offset[5] = { 0.0 };
//double CGlobal::slide_filter_data[5][4] = { 0.0 };
double CGlobal::velocity[5] = { 0.0 };
double CGlobal::velocity2[5] = { 0.0 };
double CGlobal::acceleration[5] = { 0.0 };
int CGlobal::interval = 200;

double CGlobal::kalman_x = 0.0;
double CGlobal::kalman_A = 0.0;
double CGlobal::kalman_H = 0.0;
double CGlobal::kalman_q = 0.0;
double CGlobal::kalman_r = 0.0;
double CGlobal::kalman_p = 0.0;
double CGlobal::kalman_gain = 0.0;

CGlobal::CGlobal()
{
}


CGlobal::~CGlobal()
{
}


void CGlobal::hex_to_str(char *ptr, char *buf)//hex��ʽת�����ַ�����ʾ
{
	int i;

	for (i = 0; i<16; i++) 
	{
		if (0 == (i % 16)) 
		{   //С���Դ����������С������
			//sprintf(ptr, "%08x", i);
			sprintf(ptr, "", i);
			sprintf(ptr, "%s %02x", ptr, (unsigned char)buf[i]);
		}
		else 
		{
			sprintf(ptr, "%s %02x", ptr, (unsigned char)buf[i]);
		}
	}
}

double CGlobal::hex_to_dec(CString str)//hex��ʽת����ʮ����
{
	int i = 0, count;
	double sum;
	count = str.GetLength();
	sum = 0;
	for (i = count - 1; i >= 0; i--)//��ʮ�����Ƹ�λ��ʼ��ÿλ��ת����ʮ����
	{
		if (str[i] >= '0'&&str[i] <= '9')//�����ַ���ת��
		{
			sum += (str[i] - 48)*pow(16, count - i - 1);
		}
		else if (str[i] >= 'A'&&str[i] <= 'F')//��ĸ�ַ���ת��
		{
			sum += (str[i] - 55)*pow(16, count - i - 1);
		}
	}
	return sum;
}

void CGlobal::kalman_init(double init_q, double init_r)
{
	CGlobal::kalman_x = 1;    //�������ĳ�ʼֵ��������ֵһ�������ֵ
	CGlobal::kalman_p = 5;   //����״̬����ֵ���ķ���ĳ�ʼֵ (��Ϊ0�����ⲻ��)
	CGlobal::kalman_A = 1;
	CGlobal::kalman_H = 1;
	CGlobal::kalman_q = init_q;  //Ԥ�⣨���̣��������� ʵ�鷢���޸����ֵ��Ӱ����������
	CGlobal::kalman_r = init_r;  //�������۲⣩��������
	//���� q,r ������������ؼ���
	CGlobal::kalman_gain = 1;
}

double CGlobal::kalman_filter(double measure)
{
	//Predict 
	kalman_x = kalman_A * kalman_x;
	kalman_p = kalman_A * kalman_A * kalman_p + kalman_q;  //p(n|n-1)=A^2*p(n-1|n-1)+q 

	//Measurement 
	kalman_gain = kalman_p * kalman_H / (kalman_p * kalman_H * kalman_H + kalman_r);
	kalman_x = kalman_x + kalman_gain * (measure - kalman_H * kalman_x);
	kalman_p = (1 - kalman_gain * kalman_H) * kalman_p;

	return kalman_x;
}

double CGlobal::slide_average_filter(double *arr, int len)
{
	double sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum = sum + arr[i];
	}
	return (sum / len);
}


int CGlobal::maxIndex(double a[], int size)
{
	assert(size > 0);
	int maxIndex = 0;
	for (int i = 1; i<size; i++) 
	{
		if (a[i] > a[maxIndex]) 
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

int CGlobal::minIndex(double a[], int size)
{
	assert(size > 0);
	int minIndex = 0;
	for (int i = 1; i<size; i++)
	{
		if (a[i] < a[minIndex])
		{
			minIndex = i;
		}
	}
	return minIndex;
}