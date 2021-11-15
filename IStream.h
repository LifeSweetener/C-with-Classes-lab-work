#pragma once
#include <string>
#include <vector>
#include "IValide.h"
#include "functions.h"

using namespace std;

/* Массив валидаторов (глобально): */
IValide* valides[STREAMS_NUM] = { new ValideInt, new ValideDouble, new ValideBool, new ValideString, new ValideChar, new ValideArray };

// Интерфейсный класс:
class IStream
{
public:
	virtual string get_name() = 0;  // получить считываемый тип данных
    virtual void read(bool ignore_errors) = 0;  // считать ввод пользователя
};

// Реализация интерфейсного класса - ввод целых чисел:
class StreamInt : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "int";  // вводимый пользователем тип данных
    string value_str;  // ввод пользователя
    bool ignore_errors;  // продолжить ли выполнение программы при возникновении ошибки
public:
	// получить обрабатываемый тип данных
    string get_name() override
    {
        return this->input_type;
    }

	// принять и обработать ввод пользователя:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        int value = 0;

        try
        {
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать ПЕРВУЮ строку файла: */
				input >> value_str;
				
				if (int_string_contains_letters(value_str))  // в случае ошибки - выбрасываем исключение (сообщаем пользователю в консоль об ошибке)
				{
					throw std::invalid_argument("invalid argument");  // выбрасываем исключение
				}
				value = stoi(value_str);  // если пользователь ввёл именно целое число, то преобразовываем ввод в это число
				
				input.close();  // закрыть файл
			} else {  // иначе - ввести данные с консоли...
				getline(cin >> ws, value_str);  // принимаем от пользователя ввод...
				if (int_string_contains_letters(value_str))  // в случае ошибки - выбрасываем исключение (сообщаем пользователю в консоль об ошибке)
				{
					throw std::invalid_argument("invalid argument");  // выбрасываем исключение
				}
				value = stoi(value_str);  // если пользователь ввёл именно целое число, то преобразовываем ввод в это число
			}
            successful_input(value);  // и предлагаем пользователю продолжить ввод...
        }
        catch (const std::exception& error)  // ловим и обрабатываем исключение (ошибку)...
        {
            if (ignore_errors)  // если пользователь хочет игнорировать ошибки, то продолжить работу
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else  // иначе показать пользователю окно с ошибкой и выйти из программы
            {
                throw error;
            }
        }
    }
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(int value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your int value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* Вызвать валидатор: */
		if (valides[0]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* Предложить пользователю продолжить: */
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

// Реализация интерфейсного класса - ввод десятичных чисел:
class StreamDouble : public IStream 
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "double";
    string value_str;  // ввод пользователя
    bool ignore_errors;  // продолжить ли выполнение программы при возникновении ошибки
public:
	// получить обрабатываемый тип данных
    string get_name() override
    {
        return this->input_type;
    }

	// принять и обработать ввод пользователя:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
        cout << "Your input: " << endl;

        double value;
        
        try
        {
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать ПЕРВУЮ строку файла: */
				input >> value_str;
				
				if (double_string_containts_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				value = stod(value_str);  // преобразовать введённую строку в десятичное число
				
				input.close();  // закрыть файл
			} else {  // иначе - ввести данные с консоли...
				getline(cin >> ws, value_str);
				if (double_string_containts_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				value = stod(value_str);  // преобразовать введённую строку в десятичное число
			}
			
            successful_input(value);
        }
        catch (const std::exception& error)
        {
            if (ignore_errors)  // если пользователь хочет игнорировать ошибки, то продолжить работу
            {
                system("cls");
                cout << "Caught exception: " << error.what() << endl;
                cout << "Repeat input:" << endl;
                read(ignore_errors);
            }
            else  // иначе показать пользователю окно с ошибкой и выйти из программы
            {
                throw error;
            }
        }
    }
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(double value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your double value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* Вызвать валидатор: */
		if (valides[1]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* Предложить пользователю продолжить: */
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

// Реализация интерфейсного класса - ввод булевых значений:
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
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать ПЕРВУЮ строку файла: */
				input >> value_str;
				
				if (int_string_contains_letters(value_str))
				{
					throw std::invalid_argument("invalid argument");
				}
				int temp = stoi(value_str);
				value = temp == 1 ? true : temp == 0 ? false : throw std::invalid_argument("invalid argument");
				
				input.close();  // закрыть файл
			} else {  // иначе - ввести данные с консоли...
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
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(int value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your bool value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* Вызвать валидатор: */
		if (valides[2]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* Предложить пользователю продолжить: */
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

// Реализация интерфейсного класса - ввод строк:
class StreamString : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "string";  // вводимый тип данных
    string value_str;  // вводимая строка
    bool ignore_errors;  // игнорировать ли ошибки в программе
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
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать ПЕРВУЮ строку файла: */
				input >> value_str;
				value = value_str;
				
				input.close();  // закрыть файл
			} else {  // иначе - ввести данные с консоли...
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
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(string value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your string value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* Вызвать валидатор: */
		if (valides[3]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* Предложить пользователю продолжить: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;  // stop - глобальная переменная
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// Реализация интерфейсного класса - ввод символов:
class StreamChar : public IStream 
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "char";  // тип вводимых пользователем данных
    string value_str;  // вводимый символ в виде строки
    bool ignore_errors;  // продолжать ли работу при ошибке в программе
	
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
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать ПЕРВУЮ строку файла: */
				input >> value_str;
				
				if (value_str.length() > 1)
				{
					throw std::invalid_argument("invalid argument");
				}
				value = value_str[0];
				
				input.close();  // закрыть файл
			} else {  // иначе - ввести данные с консоли...
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
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(char value)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your char value: " << value << endl;
        cout << "Your input: " << value_str << endl << endl;
		
		/* Вызвать валидатор: */
		if (valides[4]->check(&value))
			cout << "value " << value << " is valid" << endl;
		else
			cout << "value " << value << " is not valid" << endl;
		
		/* Предложить пользователю продолжить: */
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);
        stop = repeat == NO ? true : false;  // stop - глобальная переменная
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(value);
    }
};

// Реализация интерфейсного класса - ввод массивов:
class StreamArray : public IStream
{
private:
    const int YES = 1;
    const int NO = 2;
    string input_type = "array";  // тип вводимых данных
    string value_str;  // ввод пользователя (часть)
	vector <string> values = {};  // вводимый пользователем массив
	string all_value_str;  // ввод пользователя (весь)
    bool ignore_errors;  // продолжать ли работу при ошибке в программе
	
public:
	// Переопределяем чистую виртуальную функцию базового класса:
    string get_name() override
    {
        return this->input_type;
    }

	// Переопределяем ещё одну чистую виртуальную функцию базового класса:
    void read(bool ignore_errors) override
    {
        this->ignore_errors = ignore_errors;
		
        cout << "Your input: " << endl;
		
		string str;
		
        try
        {
			if (FILE_INPUT) {  // если ввод идёт из файла, то считать из файла...
				ifstream input;  // объявить переменную-файл
				input.open("input.txt");  // открыть конкретный файл (он должен быть создан)
				
				/* Считать файл до конца: */
				while (!input.eof()) {
					input >> value_str;
					all_value_str += " " + value_str;
					values.push_back(value_str);  // запихиваем очередной введённый элемент в массив
				}
				
				input.close();  // закрыть файл
			} else {  // иначе считать прямо из консоли
				while (getline(cin >> ws, value_str)) {
					if (value_str == "000")  // при вводе с консоли остановиться на введённом значении "000"
						break;
					else {
						all_value_str += " " + value_str;
						values.push_back(value_str);  // запихиваем очередной введённый элемент в массив
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
	
	// после безошибочного ввода пользователя вызвать валидатор, а затем предложить продолжить ввод:
    void successful_input(vector <string> &values)
    {
        system("cls");
        cout << "Reading complete" << endl;
        cout << "Your array values: ";
		
		//ВЫВОД:
		for (int i = 0; i < values.size(); i++) {
			cout << values[i] << " ";
		}
		
        cout << "Your input: " << all_value_str << endl << endl;
		all_value_str = "";  // очистить весь прошлый ввод (строку)
		
		if (valides[5]->check(&values))
			cout << "array" << " is valid" << endl;
		else
			cout << "array" << " is not valid" << endl;
		
		// ОЧИСТКА:
		while (!values.empty())
			values.pop_back();  // удаление элемента вектора с конца
		
        cout << "Repeat?" << endl;
        cout << "1. Yes\n2. No\n";
        int repeat;
        handle_input(repeat);  // обработать выбор пользователя
        stop = repeat == NO ? true : false;  // stop - глобальная переменная
        if (stop)
        {
            return;
        }
        repeat == YES ? this->read(this->ignore_errors) : successful_input(values);
    }
};
