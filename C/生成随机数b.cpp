#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{
	FILE *fp1;
	FILE *fp2;
	errno_t err1 = fopen_s(&fp1, "rand1.csv", "r");
	errno_t err2 = fopen_s(&fp2, "rand2.csv", "a");
	if (err1 != 0 || err2 != 0) //如果没有成功打开文件
	{
		if (err1 != 0)
			cout << "cannot open rand1.csv" << endl;
		if (err2 != 0)
			cout << "cannot open rand2.csv" << endl;
	}
	else
	{
		int row = 12;
		int line = 1000;
		for (int i = 0; i < line; i++)
		{
			int sum = 0;
			int thisline[row + 1] = {0};
			for (int j = 0; j < row + 1; j++)
			{
				//thisline [0]里面存的是行号，剩下后面的12个数存的是随机数0/1
				fscanf(fp1, "%d,", &thisline[j]);
				if (j != 0)
					sum += thisline[j];
			}
			fscanf(fp1, "\n");			 //吸收掉结束的换行符
			double average = sum / 12.0; //平均数
			//标准差
			double sigma = pow((((1 - average) * (1 - average) * sum + average * average * (row - sum)) / (double)row), 0.5);
			fprintf_s(fp2, "%d,%lf,%lf\n", thisline[0], average, sigma);
		}
	}

	fclose(fp1);
	fclose(fp2);

	system("pause");
	return 0;
}