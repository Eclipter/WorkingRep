#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "..\\Lab1_Processes\\order.h"

using namespace std;


int main(int argc, char* argv[])
{
	order buffer;
	char* name = new char[50];
	name = argv[1];
	int amount;
	//Ввод количества заказов
	cout << "Enter amount: ";
	cin >> amount;
	ofstream out(name, ios::binary);
	//Ввод объектов в файл
	for(int i = 0; i < amount; i++)
	{
		printf("Order number: %d\n", i+1);
		cout << "Name: ";
		cin.getline(buffer.name, sizeof(buffer.name));
		//cin >> buffer.name;
		cout << "Amount: ";
		cin >> buffer.amount;
		cout << "Price: ";
		cin >> buffer.price;
		out.write((char*)&buffer, sizeof(buffer));
	}
	//Завершено успешно и программа не упала
	cout << "Objects were written!" << endl;
	out.close();
	system("pause");
	return 0;
}