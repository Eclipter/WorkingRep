#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "..\\Lab1_Processes\\order.h"

using namespace std;


int main(int argc, char* argv[])
{
	//�������� ����������
	char* binfilename = argv[1];
	char* reportfilename = argv[2];
	int minamount = atoi(argv[3]);
	double minprice = atof(argv[4]);
	//�������� ���� � ��������� �����
	char binfilepath[100] = "..\\Lab1_Processes\\";
	strcat(binfilepath, binfilename);
	//�������� ��������� ����� � �������� ����� ������
	FILE* fin = fopen(binfilepath, "rb");
	FILE* fout = fopen(reportfilename, "w");
	fprintf(fout, "Report of file %s: \n", binfilename);
	//���������� ��������, ������ � ���������� �� ������ � ���� ������
	order x;
	bool f = false;
	while(!feof(fin))
	{
		if(fread(&x, sizeof(x), 1, fin))
		{
			double fprice = x.amount*x.price;
			if(x.amount < minamount || fprice < minprice)
			{
				f = true;
				fprintf(fout, "Name: %s, Amount: %d, Full Price: %f\n", x.name, x.amount, fprice);
			}
		}
	}
	if(!f)
	fprintf(fout, "No orders to report.");
	//���� ��������� �� �����
	cout << "The report was created successfully!" << endl;
	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}