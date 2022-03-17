#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<math.h>
using namespace std;


void BubbleSort(float arr[], int n)//冒泡排序求出最大值量化Y轴分度
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

float function[1024] = { 0 };

void AD_function(void)//分解对应函数
{
	for (int t = 0; t < 1024; t++)
	{
		function[t] = 2*sin((2 * 3.14 / 1024) * t);
	}

}


int main()
{

	int N = 0;
	cout << "请输入绘图点数：";
	cin >> N;
	cout << endl;

	int X_Flag_drawing = 1220 / N;
	float Y_Flag_drawing = 1;

	float* Data_Storage = (float*)calloc(N, sizeof(float));
	float* Max_Data = (float*)calloc(N, sizeof(float));

	cout << "请输入点数幅度值：" << endl;

	for (int i = 0; i < N; i++)
	{
		cin >> Data_Storage[i];
		Max_Data[i] = Data_Storage[i];

	}

	BubbleSort(Max_Data, N);//排序后Max_Data[N-1]为最大值
	


	Y_Flag_drawing = 400 / Max_Data[N - 1];

	for (int i = 0; i < N; i++)
	{
		Data_Storage[i] = Data_Storage[i] * Y_Flag_drawing;
	}

	string X_sign;
	string Y_sign;
	float X_Division_Value;
	float Y_Division_Value;

	cout << "请输入X坐标的单位和分度值：";
	cout << endl;
	cin >> X_sign;
	cin >>  X_Division_Value;
	cout << endl;
	
	cout << "请输入Y坐标的单位和分度值：";
	cout << endl;
	cin >> Y_sign;
	cin >> Y_Division_Value;
	cout << endl;
	
	float Y_N = Max_Data[N - 1] / Y_Division_Value;//Y轴方向的画线标度数
	
	wchar_t* wc_X = new wchar_t[X_sign.size()];
	swprintf(wc_X, 100, L"%S", X_sign.c_str());
	wchar_t* wc_Y = new wchar_t[Y_sign.size()];
	swprintf(wc_Y, 100, L"%S", Y_sign.c_str());
	
	cout << "按任意键开始画图";
	_getch();
	
	initgraph(1280, 480);  // 创建绘图窗口，大小为 640x480 像素
	setbkcolor(RGB(255, 255, 255)); cleardevice();//设置背景色为白色
	setlinecolor(RGB(255, 0, 0));   // 设置当前线条颜色
	line(80, 440, 1250, 440);//X轴
	line(1230, 420, 1250, 440);
	line(1230, 460, 1250, 440);//箭头
	
	line(80, 440, 80, 20);//Y轴
	line(60, 40, 80, 20);
	line(100, 40, 80, 20);//箭头
	
	settextcolor(RGB(255, 0, 0));
	


	outtextxy(1250,450, wc_X);//X轴需要修改的单位
	outtextxy(80,5, wc_Y);   //Y轴需要修改的单位

	wchar_t* wc_X_Data = new wchar_t[sizeof(float)]; 
	wchar_t* wc_Y_Data = new wchar_t[sizeof(float)];//X、Y的标度
	
	for (int i = 0; i<Y_N ; i++)
	{
		line(80, 440-(Max_Data[N - 1]/Y_N)* Y_Flag_drawing*i, 100, 440 - (Max_Data[N - 1] / Y_N) * Y_Flag_drawing*i);
		swprintf(wc_Y_Data, 100, L"%.2f", (Max_Data[N - 1] / Y_N) * i);
		outtextxy(0, 432 - (Max_Data[N - 1] / Y_N) * Y_Flag_drawing * i, wc_Y_Data);
	}
	for (int i = 0; i < N; i++)
	{ 
		setfillcolor(RGB(255, 0, 0));
		fillcircle(X_Flag_drawing * i+80, 440-Data_Storage[i], 4);
		if (i<N-1)//绘制图像
		{
			line(X_Flag_drawing * i + 80, 440 - Data_Storage[i], X_Flag_drawing * (i + 1) + 80, 440 - Data_Storage[i + 1]);
		}
		line(X_Flag_drawing * i + 80, 440, X_Flag_drawing * i + 80, 430);
		swprintf(wc_X_Data, 100, L"%.2f", i* X_Division_Value);
		outtextxy(X_Flag_drawing * i + 65, 450, wc_X_Data);//画出坐标
	}
	
	_getch();                       // 按任意键继续
	closegraph();                   // 关闭图形环境
	
}