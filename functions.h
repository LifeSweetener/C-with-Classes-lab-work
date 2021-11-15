#pragma once
#include <string>

using namespace std;

/* ��������� ������ ������������� ������-������ ������ ����: */
void handle_input(int& value)
{
	const int ERROR = -1;
	string str = "";
	std::cin >> str;  // �����, ���� ������������ ����� ��������
	try
	{
		value = stoi(str);  // ����������� ���� ������������ � ����� �����
	}
	catch (const invalid_argument& e)
	{
		value = ERROR;  // ������ ��������� -1 � ��������� ������������ ������ ������ ��� ����� ��� ���
	}
}

/* ���� �� ����� � ������ � ����� ������: */
bool int_string_contains_letters(string str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))  // ���� � ������ ���� ����� ��� ��� ���-������ �����, �� ������� true
			return true;
	}
	return false;  // ���� � ������ ������ �����, �� ������� false
}

/* ���� �� ����� � ������ � ���������� ������: */
bool double_string_containts_letters(string str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]) && str[i] != '.')  // ������ ���� ������ ����� � �����
			return true;
	}
	return false;
}

const int STREAMS_NUM = 6;  // ���������� �������������� ���������� �����
bool FILE_INPUT = false;  // ���� �� �����?
bool stop = false;  // ��������� ����� � ����?