#pragma once
#include <string>
#include <vector>
#include "IValide.h"
#include "functions.h"

using namespace std;

/* ������ ����������� (���������): */
IValide* valides[STREAMS_NUM] = { new ValideInt, new ValideDouble, new ValideBool, new ValideString, new ValideChar, new ValideArray };

// ������������ �����:
class IStream
{
public:
	virtual string get_name() = 0;  // �������� ����������� ��� ������
    virtual void read(bool ignore_errors) = 0;  // ������� ���� ������������
};

// ���������� ������������� ������ - ���� ����� �����:
class StreamInt : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "int";  // �������� ������������� ��� ������
    string value_str;  // ���� ������������
    bool ignore_errors;  // ���������� �� ���������� ��������� ��� ������������� ������
public:
	// �������� �������������� ��� ������
    string get_name() override
    {
        return this->input_type;
    }

	// ������� � ���������� ���� ������������:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        int value = 0;

        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ������ ������ �����: */
				input >> value_str;
				
				if (int_string_contains_letters(value_str))  // � ������ ������ - ����������� ���������� (�������� ������������ � ������� �� ������)
				{
					throw std::invalid_argument("invalid argument");  // ����������� ����������
				}
				value = stoi(value_str);  // ���� ������������ ���� ������ ����� �����, �� ��������������� ���� � ��� �����
				
				input.close();  // ������� ����
			} else {  // ����� - ������ ������ � �������...
				getline(cin >> ws, value_str);  // ��������� �� ������������ ����...
				if (int_string_contains_letters(value_str))  // � ������ ������ - ����������� ���������� (�������� ������������ � ������� �� ������)
				{
					throw std::invalid_argument("invalid argument");  // ����������� ����������
				}
				value = stoi(value_str);  // ���� ������������ ���� ������ ����� �����, �� ��������������� ���� � ��� �����
			}
            successful_input(value);  // � ���������� ������������ ���������� ����...
        }
        catch (const std::exception& error)  // ����� � ������������ ���������� (������)...
        {
            if (ignore_errors)  // ���� ������������ ����� ������������ ������, �� ���������� ������
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else  // ����� �������� ������������ ���� � ������� � ����� �� ���������
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(int value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your int value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* ������� ���������: */
		if (valides[0]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* ���������� ������������ ����������: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// ���������� ������������� ������ - ���� ���������� �����:
class StreamDouble : public IStream 
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "double";
    string value_str;  // ���� ������������
    bool ignore_errors;  // ���������� �� ���������� ��������� ��� ������������� ������
public:
	// �������� �������������� ��� ������
    string get_name() override
    {
        return this->input_type;
    }

	// ������� � ���������� ���� ������������:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        double value;
        
        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ������ ������ �����: */
				input >> value_str;
				
				if (double_string_containts_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				value = stod(value_str);  // ������������� ��������� ������ � ���������� �����
				
				input.close();  // ������� ����
			} else {  // ����� - ������ ������ � �������...
				getline(cin >> ws, value_str);
				if (double_string_containts_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				value = stod(value_str);  // ������������� ��������� ������ � ���������� �����
			}
			
            successful_input(value);
        }
        catch (const std::exception& error)
        {
            if (ignore_errors)  // ���� ������������ ����� ������������ ������, �� ���������� ������
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else  // ����� �������� ������������ ���� � ������� � ����� �� ���������
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(double value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your double value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* ������� ���������: */
		if (valides[1]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* ���������� ������������ ����������: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// ���������� ������������� ������ - ���� ������� ��������:
class StreamBool : public IStream 
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "bool";
    string value_str;
    bool ignore_errors;
public:
    string get_name() override
    {
        return this->input_type;
    }

    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Input format:\n1 - true\n0 - false" << endl;
        cout << "Your input: " << endl;

        bool value;

        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ������ ������ �����: */
				input >> value_str;
				
				if (int_string_contains_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				int temp = stoi(value_str);
				value = temp == 1 ? true : temp == 0 ? false : throw std::invalid_argument("invalid argument");
				
				input.close();  // ������� ����
			} else {  // ����� - ������ ������ � �������...
				getline(cin >> ws, value_str);
				if (int_string_contains_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				int temp = stoi(value_str);
				value = temp == 1 ? true : temp == 0 ? false : throw std::invalid_argument("invalid argument");
			}
			
            successful_input(value);
        }
        catch (const std::exception& error)
        {
            if (ignore_errors)
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat your input." << endl;
                read(ignore_errors);
            }
            else
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(int value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your bool value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* ������� ���������: */
		if (valides[2]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* ���������� ������������ ����������: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// ���������� ������������� ������ - ���� �����:
class StreamString : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "string";  // �������� ��� ������
    string value_str;  // �������� ������
    bool ignore_errors;  // ������������ �� ������ � ���������
public:
    string get_name() override
    {
        return this->input_type;
    }

    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        string value;

        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ������ ������ �����: */
				input >> value_str;
				value = value_str;
				
				input.close();  // ������� ����
			} else {  // ����� - ������ ������ � �������...
				getline(cin >> ws, value_str);
				value = value_str;
			}
			
			successful_input(value);
        }
        catch (const std::exception& error)
        {
            if (ignore_errors)
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(string value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your string value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* ������� ���������: */
		if (valides[3]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* ���������� ������������ ����������: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;  // stop - ���������� ����������
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// ���������� ������������� ������ - ���� ��������:
class StreamChar : public IStream 
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "char";  // ��� �������� ������������� ������
    string value_str;  // �������� ������ � ���� ������
    bool ignore_errors;  // ���������� �� ������ ��� ������ � ���������
	
public:
    string get_name() override
    {
        return this->input_type;
    }

    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        char value;

        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ������ ������ �����: */
				input >> value_str;
				
				if (value_str.length() > 1)
				{
					throw std::invalid_argument("invalid argument");
				}
				value = value_str[0];
				
				input.close();  // ������� ����
			} else {  // ����� - ������ ������ � �������...
				getline(cin >> ws, value_str);
				if (value_str.length() > 1)
				{
					throw std::invalid_argument("invalid argument");
				}
				value = value_str[0];
			}
			
			successful_input(value);
        } catch (const std::exception& error)
        {
            if (ignore_errors)
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(char value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your char value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* ������� ���������: */
		if (valides[4]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* ���������� ������������ ����������: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;  // stop - ���������� ����������
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// ���������� ������������� ������ - ���� ��������:
class StreamArray : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "array";  // ��� �������� ������
    string value_str;  // ���� ������������ (�����)
	vector <string> values = {};  // �������� ������������� ������
	string all_value_str;  // ���� ������������ (����)
    bool ignore_errors;  // ���������� �� ������ ��� ������ � ���������
	
public:
	// �������������� ������ ����������� ������� �������� ������:
    string get_name() override
    {
        return this->input_type;
    }

	// �������������� ��� ���� ������ ����������� ������� �������� ������:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
		
        cout << "Your input: " << endl;
		
		string str;
		
        try
        {
			if (FILE_INPUT) {  // ���� ���� ���� �� �����, �� ������� �� �����...
				ifstream input;  // �������� ����������-����
				input.open("input.txt");  // ������� ���������� ���� (�� ������ ���� ������)
				
				/* ������� ���� �� �����: */
				while (!input.eof()) {
					input >> value_str;
					all_value_str += " " + value_str;
					values.push_back(value_str);  // ���������� ��������� ��������� ������� � ������
				}
				
				input.close();  // ������� ����
			} else {  // ����� ������� ����� �� �������
				while (getline(cin >> ws, value_str)) {
					if (value_str == "000")  // ��� ����� � ������� ������������ �� ��������� �������� "000"
						break;
					else {
						all_value_str += " " + value_str;
						values.push_back(value_str);  // ���������� ��������� ��������� ������� � ������
					}
				}
			}
            successful_input(values);
        }
        catch (const std::exception& error)
        {
            if (ignore_errors)
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else
            {
                throw error;
            }
        }
    }
	
	// ����� ������������� ����� ������������ ������� ���������, � ����� ���������� ���������� ����:
    void successful_input(vector <string> &values)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your array values: ";
		
		//�����:
		for (int i = 0; i < values.size(); i++) {
			cout << values[i] << " ";
		}
		
        cout << "Your input: " << all_value_str << endl << endl;
		all_value_str = "";  // �������� ���� ������� ���� (������)
		
		if (valides[5]->check(&values))
			cout << "array" << " is valid" << endl;
		else
			cout << "array" << " is not valid" << endl;
		
		// �������:
		while (!values.empty())
			values.pop_back();  // �������� �������� ������� � �����
		
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);  // ���������� ����� ������������
        stop = repeat == NO ? true : false;  // stop - ���������� ����������
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(values);
    }
};
