#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "order.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Enter binfile name: ";
	char* binfilename = new char[50];
	//���� ����� ��������� �����
	cin >> binfilename;
	char creatorPath[100];
	//������������� � ���� ������ �������
	sprintf_s(creatorPath, "Creator.exe \"%s\"", binfilename);

	STARTUPINFO siCreator;
	PROCESS_INFORMATION piComCreator;

	ZeroMemory(&siCreator, sizeof(STARTUPINFO));
	siCreator.cb = sizeof(STARTUPINFO);
	//������ Creator
	if(!CreateProcess(NULL, creatorPath, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &siCreator, &piComCreator))
	{
		cout << "The Creator hasn't launched." << endl;
	}
	else cout << "The Creator has launched!" << endl;
	//�������� ����������,����� ��������
	WaitForSingleObject(piComCreator.hProcess, INFINITE);
	CloseHandle(piComCreator.hThread);
	CloseHandle(piComCreator.hProcess);


	order tmp;
	//�������� ��������� ����� � ����� ����������� � ���� ��������
	FILE* inBin = fopen(binfilename, "rb");
	cout << "Binary file contents: " << endl;
	while(!feof(inBin))
	{
		if(fread(&tmp, sizeof(tmp), 1, inBin))
		cout << "Name: " << tmp.name << ", Amount: " << tmp.amount << ", Price: " << tmp.price << endl;
	}
	fclose(inBin);
	//���������� �������� ����� ������
	cout << "Enter report filename: ";
	char* reportfilename = new char[50];
	cin >> reportfilename;
	//���������� ����������� ��� � ����������
	char* minamount = new char[10];
	char* minprice = new char[10];
	cout << "Enter minimal amount: ";
	cin >> minamount;
	cout << "Enter minimal price: ";
	cin >> minprice;
	//�������� ���� � Reporter � �������� �����������
	char reportPath[300];
	sprintf_s(reportPath, "Reporter.exe \"%s\" \"%s\" %s %s", binfilename, reportfilename, minamount, minprice);

	STARTUPINFO siReporter;
	PROCESS_INFORMATION piComReporter;

	ZeroMemory(&siReporter, sizeof(STARTUPINFO));
	siReporter.cb = sizeof(STARTUPINFO);
	//������ Reporter � �������� ����������
	if(!CreateProcess(NULL, reportPath, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &siReporter, &piComReporter))
	{
		cout << "The Reporter hasn't launched." << endl;
	}
	else cout << "The Reporter has launched!" << endl;

	WaitForSingleObject(piComReporter.hProcess, INFINITE);
	CloseHandle(piComReporter.hThread);
	CloseHandle(piComReporter.hProcess);
	//�������� ����� ������ � ����� �����������
	ifstream inRep(reportfilename);
	char* buffer = new char[100];
	while(!inRep.eof())
	{
		inRep.getline(buffer, 100);
		cout << buffer << endl;
	}
	inRep.close();
	system("pause");
	return 0;

}