#pragma once
#include <string>

using namespace std;

/* обработка выбора пользователем какого-нибудь пункта меню: */
void handle_input(int& value)
{
	const int ERROR = -1;
	string str = "";
	std::cin >> str;  // ждать, пока пользователь введёт значение
	try
	{
		value = stoi(str);  // преобразуем ввод пользователя в целое число
	}
	catch (const invalid_argument& e)
	{
		value = ERROR;  // выдать ошибочную -1 и попросить пользователя ввести нужную ему цифру ещё раз
	}
}

/* есть ли буквы в строке с целым числом: */
bool int_string_contains_letters(string str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))  // если в строке есть буква или ещё что-нибудь такое, то вернуть true
			return true;
	}
	return false;  // если в строке только цифры, то вернуть false
}

/* есть ли буквы в строке с десятичным числом: */
bool double_string_containts_letters(string str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]) && str[i] != '.')  // должны быть только цифры и точка
			return true;
	}
	return false;
}

const int STREAMS_NUM = 6;  // количество обрабатываемых программой типов
bool FILE_INPUT = false;  // ввод из файла?
bool stop = false;  // вернуться назад в меню?