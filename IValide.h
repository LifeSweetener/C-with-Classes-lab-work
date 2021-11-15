#pragma once
#include <string>
#include <vector>
using namespace std;

// Интерфейсный класс:
class IValide
{
public:
    virtual bool check(void* value) = 0;
};

/* РЕАЛИЗАЦИИ IValide: */

class ValideInt : public IValide {
	private:
		const int LIMIT = 1000;  // граница валидных чисел, для примера 1000
	
	public:
		bool check(void* value) override
		{
			int *i = (int*)value;  // преобразование указателей
			if (*i > LIMIT)
				return false;
			
			return true;
		}
};

class ValideDouble : public IValide {
	private:
		const double OST = 0.5;  // начальная десятичная часть валидных дробных чисел, для примера 0.5
	public:
		bool check(void* value) override
		{
			double *d = (double*)value;  // преобразование указателей
			int div = *d;  // получение целой части десятичного числа
			double ost = *d - div;  // получение цифр уже после запятой
			
			if (ost < OST)  // если десятичная часть введённого числа меньше валидной границы, то дробь невалидная
				return false;
			
			return true;
		}
};

class ValideBool : public IValide {
	private:
	
	public:
		bool check(void* value) override
		{
			bool *b = (bool*)value;  // преобразование указателей
			if (!*b)
				return false;
			
			return true;
		}
};

class ValideString : public IValide {
	private:
		const int LENGTH = 5;  // максимальный размер валидной строки
	public:
		bool check(void* value) override
		{
			string* str= (string*)value;  // преобразование указателей (указатель на строку)
			if (str->length() > LENGTH)  // str->length() - получаем длину строки
				return false;
			
			return true;
		}
};

class ValideChar : public IValide {
	private:
		const int SPECIAL = 'c';  // невалидный символ
	public:
		bool check(void* value) override
		{
			char* c = (char*)value;  // преобразование указателей
			if (*c == SPECIAL)
				return false;
			
			return true;
		}
};

class ValideArray : public IValide {
	private:
		const int LENGTH = 4;  // максимальный размер вводимых валидных массивов
	public:
		bool check(void* value) override
		{
			vector <string> *v = (vector <string>*)value;  // преобразование указателей (указатель на вектор строк)
			if (v->size() > LENGTH)  // v->size() - получаем размер введённого пользователем вектора
				return false;
			
			return true;
		}
};