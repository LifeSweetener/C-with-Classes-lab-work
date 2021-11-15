#include <iostream>
#include <string>
#include <fstream>
#include "IStream.h"
#include "functions.h"

using namespace std;

class Client
{
private:
	const int NO = 2;
	const int YES = 1;
	const int RETURN = 0;
	IStream* streams[STREAMS_NUM] = { new StreamInt, new StreamDouble, new StreamBool, new StreamString, new StreamChar, new StreamArray };
public:
	void main_menu()
	{
		system("cls");  // очистить терминал

		int source;  // источник - файл или консоль
		cout << "Choose reading source:" << endl;
		cout << "1. Console\n2. File" << endl;
		cout << "Source: ";

		handle_input(source);
		
		FILE_INPUT = false;
		
		source == YES ? console_input() : source == NO ? file_input() : main_menu();
	}
	
	void console_input()
	{
		system("cls");  // очистить терминал
		
		int input_type;
		cout << "Choose input type:" << endl;
		cout << "1. Int\n2. Double\n3. Bool\n4. String\n5. Char\n6. Array\n0. Go back" << endl;
		cout << "Input type: ";
		
		handle_input(input_type);

		if (input_type >= 1 && input_type <= 6)
		{
			bool ignore_errors = ignore_errors_func(input_type);
			system("cls");  // очистить терминал
			
			streams[input_type - 1]->read(ignore_errors);
			if (exit)
			{
				main_menu();
			}
		}
		else if (input_type != RETURN)
		{
			console_input();
		}
		else
		{
			main_menu();
		}
	}

	bool ignore_errors_func(int input_type)
	{
		system("cls");  // очистить терминал

		int temp;
		cout << "Input type: " << streams[input_type-1]->get_name() << endl;
		cout << "Ignore errors?" << endl;
		cout << "1. Yes\n2. No\n0. Main menu" << endl;

		handle_input(temp);
		
		if ((temp == YES) || (temp == NO))
		{
			return (temp == YES) ? true : (temp == NO) ? false : throw -1;
		}
		else if (temp != RETURN)
		{
			ignore_errors_func(input_type);
		}
		else
		{
			console_input();
		}
	}

	void file_input()
	{
		system("cls");
		FILE_INPUT = true;  // установить в глобальную переменную значение "ВВОД ИЗ ФАЙЛА"
		console_input();
	}
};

int main()
{
	Client client;
	client.main_menu();
}
