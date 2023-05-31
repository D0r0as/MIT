#include <iostream>	 //библиотека потоков ввода-вывода
#include <vector>	 //библиотека для работы с вектором
#include <fstream>	 //библиотека для работы с файловыми потоками
#include <string>	 //библиотека для работы со строками
#include <iomanip>	 //библиотека для работы с разными длинами в строках
#include <algorithm> //библиотека алгоритмов
#include <cmath>	 //математическая библиотека
using namespace std;

ifstream in("list.txt");	   // определение ввода данных из файла
//ofstream out("list-out3.txt"); // определение вывода данных в файл

struct people
{						// создание структуры
	string Surname;		// строка с фамилией
	string Profession;	// строка с профессией
	int Experience;		// число стажа работы
	string DateOfBirth; // строка даты рождения
	int Salary;			// число зарплаты
};

vector<people> inFile()
{ // считывание данных из файла в вектор структур
	vector<people> x;
	people temp;
	while (in.peek() != EOF)
	{ // пока не закончился файл заполняем вектор структур
		in >> temp.Surname;
		in >> temp.Profession;
		in >> temp.Experience;
		in >> temp.DateOfBirth;
		in >> temp.Salary;
		x.push_back(temp);
	}
	return x; // возвращаем получившийся вектор для дальнейшей работы с ним
}

void print(people x)
{												  // запись итоговых данных в выходной файл
	cout << setw(10) << left << x.Surname << "\t"; // запись фамилий
	cout << setw(10) << x.Profession << "\t";	  // запись профессий
	cout << setw(10) << x.Experience << "\t";	  // запись стажа
	cout << setw(10) << x.DateOfBirth << "\t";	  // запись даты рождения
	cout << setw(10) << x.Salary << endl;		  // запись зарплаты
}


int h(people s) // функция получения хэша по зарплате сотрудника (взяли число 19 для его получения)
{	
	return s.Salary % 19;
}

void create(vector <people> a, vector<vector<people>> &table) // функция создания хэш-таблицы
{	
	table.resize(19);	// размерность таблицы равна числу возможных хэшей т.е 19 от 0 до 18
	for (int i = 0; i < a.size(); i++) 
	{
		int k = h(a[i]);	// определяем хэш для каждого сотрудника и записываем его в соответствующую строку 
		table[k].push_back(a[i]);
	}
}

void find_el_on_hash(vector<vector<people>> table, int x) // функция поиска сотрудника по зарплате в хэш-таблице
{	
	int hesh = x % 19;		// определим, в какой строке будут находиться сотрудники с данной зарплатой
	bool fl = false;	// отдельно будем проверять, вдруг такого сотрудника нет вообще
	cout << "hesh: " << hesh << " ";
	for (auto it = table[hesh].begin(); it != table[hesh].end(); it++) 
	{
		people c = *it;
		if (c.Salary == x)
		{
			cout << "information about employee: "; print(c);	// если нашли нужных сотрудников, выведем информацию о них
			fl = true;
		}
	}
	if (!fl) 
	{
		cout << "error";	// если никого не нашли, то выводим сообщение об этом
	}
	cout << endl;
}

void del_el(vector<vector<people>>& table, int x) // функция удаления элемента в хэш-таблице
{	
	int hesh = x % 19;	// находим хэш заданного числа
	bool fl = false;
	for (auto it = table[hesh].begin(); it != table[hesh].end(); it++) // просматриваем в соответствующей строке таблицы сотрудников	
	{	
		people c = *it;
		if (c.Salary == x) // если нашли, то удаляем
		{	
			fl = true;
            print(c);
            cout << " ---1--- " <<endl;
			table[hesh].erase(it);
			if (!table[hesh].empty()) it = table[hesh].begin(); // перекидываем указатель на начало, для избежания ошибок
			else break;	// иначе, смотрим на пустую строку
		}
	}
	if (!fl)
	{
		cout << "error";
	}
    cout << endl;
}


int main()
{
	vector<people> x;				   // создание вектора структур
	x = inFile();					   // заполняем вектор данными из исходного файла
	vector <vector <people>> table;
	create(x, table); // создадим хэш-таблицу сотрудников
	for (int i = 0; i < table.size(); i++) 
	{
		cout << i << ": ";
		for (auto it = table[i].begin(); it != table[i].end(); it++) 
		{
			people x = *it;
			print(x); // выведем её
		}
		cout << "\n";
	}
	cout << "\n";
	int s;
	cout << "please, enter the salary of worker, which you need to find: ";
	cin >> s;
	find_el_on_hash(table, s);
	cout << "please, enter the salary of worker, which you need to delete: ";
	cin >> s;
	del_el(table, s); // вводим искомые числа
	cout << "this man was deleted, you can check it in hesh-table:\n";
	for (int i = 0; i < table.size(); i++) 
	{
		cout << i << ": ";
		for (auto it = table[i].begin(); it != table[i].end(); it++) 
		{
			people x = *it;
			print(x);	//ещё раз выведем таблицу для проверки того, действительно ли удалились нужные элементы
		}
		cout << "\n";
	}
    
    return 0;
}
