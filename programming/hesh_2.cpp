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

int help_h(int s) // функция нахождния вспомогательного хэша методом умножения
{	
	float s_frac = s * 0.61803;
	int integ = int(s_frac);
	float frac = s_frac - integ;
	frac *= 32;
	return int(frac);
}

int lin_h(int h_s, int i)
{
	return ((h_s + i) % 32); // Функция нахождения основного линейного хэша
}

void create(vector <people> a, vector<people> &table) // функция создания закрытой хэш-таблицы
{	
	table.resize(32); // размерность хэш-таблицы равна числу всех возможных хэшей от 0 до 31 в нашем случае
	int j = 0; // создадим ещё одну переменную для работы линейного хэширования
	for (int i = 0; i < a.size(); i++)
	{
		int k = help_h(a[i].Experience); // для каждого нового элемента найдём вспомогательный хэш
		for (int o = 0; o < 32; o++) 
		{
			int p = lin_h(k, j); // чтобы найти для него основной хэш
			if (table[p].Experience == 0) 
			{
				table[p] = a[i]; // и если ячейка, стоящая под этим хэшом пустая, то заполним её эти элементом 
				break;
			}
			else
				j++; // иначе продвинемся дальше, чтобы найти для него место
		}
	}
}

bool operator == (people a, people b) { // переопределение оператора сравнения
    return (a.Surname == b.Surname && a.Salary == b.Salary && a.Profession == b.Profession &&
            a.Experience == b.Experience && a.DateOfBirth == b.DateOfBirth);
}

void find_el(int x, vector<people> table) // функция нахождения элемента в таблице
{
	//int hesh = help_h(x); // находим хэш для заданного числа
	bool fl = false;
	for (auto it : table) 
	{
        people c = it;
		if (c == x)
			fl = true;
	}
	if (fl) cout << "yes";
	else cout << "no";
}

int main()
{
	vector<people> tab;
	vector<people> x;
    	x = inFile();
	create(x, tab); // создадим хэш-таблицу работников
	for (int i = 0; i < tab.size(); i++) 
	{
		cout << " " << i << ": "; print(tab[i]);
		cout << "\n"; // выведем хэш-таблицу
	}
	cout << "\n";
	people e;
	cout << "please, enter person you want to check: ";
	cin >> e.Surname >> e.Profession >> e.Experience >> e.DateOfBirth >> e.Salary; // спрашиваем искомый опыт и находим людей с ним
	find_el(e, tab);
    	return 0;
}
