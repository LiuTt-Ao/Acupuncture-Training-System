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

//神经网络算法参数赋值
const int  innode = 6;       //输入结点数
const int  hidenode = 4;    //隐含结点数
const int  outnode = 3;     //输出结点数

//隐含结点权值
double w_hide[innode][hidenode] = { 12.1173, -6.4072, -1.44907, -9.86228,
1.64972, -2.01997, -3.06478, -5.45661,
7.24468, -0.62819, -1.99527, 0.107522,
20.7301, -5.38325, -11.244, -7.04914,
17.5022, -7.85717, -0.554172, -6.02311,
13.273, -6.78725, -0.497668, -4.13597 };

//输出结点权值
double w_out[hidenode][outnode] = { 11.7393,4.82232,-17.3816,
18.0415,-28.0022,3.63444,
-9.58769,1.49593,21.7807,
-17.6815,31.0677,-13.9477 };

//隐含层阀值
double b1[hidenode] = { 9.24491, -0.857766, 4.79399, 2.10829 };
//输出层阈值
double b2[outnode] = { -3.21151, -9.17268, -2.33308 };
double result[outnode] = { 0.0 };


CGlobal::CGlobal()
{
}


CGlobal::~CGlobal()
{
}


void CGlobal::hex_to_str(char *ptr, char *buf)//hex格式转化成字符串显示
{
	int i;

	for (i = 0; i<16; i++) 
	{
		if (0 == (i % 16)) 
		{   //小数对大数求余等于小数本身
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

double CGlobal::hex_to_dec(CString str)//hex格式转换成十进制
{
	int i = 0, count;
	double sum;
	count = str.GetLength();
	sum = 0;
	for (i = count - 1; i >= 0; i--)//从十六进制个位开始，每位都转换成十进制
	{
		if (str[i] >= '0'&&str[i] <= '9')//数字字符的转换
		{
			sum += (str[i] - 48)*pow(16, count - i - 1);
		}
		else if (str[i] >= 'A'&&str[i] <= 'F')//字母字符的转换
		{
			sum += (str[i] - 55)*pow(16, count - i - 1);
		}
	}
	return sum;
}

void CGlobal::kalman_init(double init_q, double init_r)
{
	CGlobal::kalman_x = 1;    //待测量的初始值，如有中值一般设成中值
	CGlobal::kalman_p = 5;   //后验状态估计值误差的方差的初始值 (不为0，问题不大)
	CGlobal::kalman_A = 1;
	CGlobal::kalman_H = 1;
	CGlobal::kalman_q = init_q;  //预测（过程）噪声方差 实验发现修改这个值会影响收敛速率
	CGlobal::kalman_r = init_r;  //测量（观测）噪声方差
	//这里 q,r 两个参数是最关键的
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

double* CGlobal::recognize(double *p)
{
	static double x[innode];       //输入向量
	static double out1[hidenode];  //隐含结点状态值
	static double out2[outnode];   //输出结点状态值
	static double net1[hidenode];  //隐含层激活值
	static double net2[hidenode];  //输出层激活值

	int i, j, k;
	for (i = 0; i<innode; i++)
		x[i] = p[i];

	for (j = 0; j<hidenode; j++)
	{
		net1[j] = 0.0;
		for (i = 0; i<innode; i++)
			net1[j] = net1[j] + w_hide[i][j] * x[i];         //隐含层各单元激活值
		out1[j] = 1.0 / (1.0 + exp(-net1[j] - b1[j]));  //隐含层各单元输出
	}

	for (k = 0; k<outnode; k++)
	{
		net2[k] = 0.0;
		for (j = 0; j<hidenode; j++)
			net2[k] = net2[k] + w_out[j][k] * out1[j];     //输出层各单元激活值
		out2[k] = 1.0 / (1.0 + exp(-net2[k] - b2[k]));  //输出层各单元输出
	}

	for (k = 0; k<outnode; k++)
	{
		result[k] = out2[k];
	}
	return result;
}

