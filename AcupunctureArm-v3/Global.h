#pragma once
class CGlobal
{
public:
	CGlobal();
	~CGlobal();
	static BOOL connected;
	static BOOL calibrated;
	static double force[5];
	static int export_choose;
	static void hex_to_str(char *ptr, char *buf);
	static double hex_to_dec(CString str);
	static float niddle_position[5];
//	static double offset[5];
	static void kalman_init(double init_q, double init_r);
	static double kalman_filter(double measure);
	static double slide_average_filter(double *arr, int len);
//	static double slide_filter_data[5][4];
	static double velocity[5];
	static double velocity2[5];
	static double acceleration[5];
	static int interval;
	static int maxIndex(double a[], int size);
	static int minIndex(double a[], int size);

	/*******kalman_filter parameters********/
	static double kalman_x;  // ϵͳ��״̬�� k-1ʱ�̵��˲�ֵ
	static double kalman_A;  // x(n)=A*x(n-1)+u(n),u(n)~N(0,q) 
	static double kalman_H;  // z(n)=H*x(n)+w(n),w(n)~N(0,r)   
	static double kalman_q;  // Ԥ���������Э����, ��ϵͳ�ⲿ�ⶨ����
	static double kalman_r;  // ������������Э���� ��ϵͳ��ú�ʵ����
	static double kalman_p;  // �������Э����
	static double kalman_gain;//����������
	/****************************/


};

