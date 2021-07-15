#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;


int main()
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp,"rand1.csv","w");
	if ((err)!=0)
	{
		cout << "can't open file\n";

	}

	else
	{
		int a[1000][13];

		for (int i = 0; i < 1000; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j == 0)
					a[i][j] = i + 1;
				else
					a[i][j] = rand() % 2;
				fprintf_s(fp, "%d,", a[i][j]);
			}
			fprintf_s(fp, "\n");
		}

		fclose(fp);
	}




	system("pause");
	return 1;
}