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

struct list { // описание двусвязного списка
    people inf; // значение элемента
    list* prev; // указатель на предыдущий элемент
    list* next; // указатель на слудующий элемент
};

struct para{
    list *first = NULL;
    list *second = NULL;
};

int m; // размер хэш-таблицы
vector<para> hash_t; // хэш-таблица
vector<people> all; // вектор "людей"

void push_back(list*& head, list*& tail, people x) { // вставка в конец списка
    list* p = new list;
    p->inf = x;
    p->next = NULL;
    if (!head && !tail) { // если список пуст
        p->prev = NULL;
        head = p;
    }
    else {
        tail->next = p;
        p->prev = tail;
    }
    tail = p; // элемент становится хвостом 
}

void input()
{ // считывание данных из файла в вектор структур
	ifstream in ("list.txt");
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
}

bool operator == (people a, people b) { // переопределение оператора сравнения
    return (a.Surname == b.Surname && a.Salary == b.Salary && a.Profession == b.Profession &&
            a.Experience == b.Experience && a.DateOfBirth == b.DateOfBirth);
}

list* find(list*& head, list*& tail, people a) { // поиск элемента со значением х в списке
    list* p = head; // указатель на голову
    while (p) { // проход по списку 
        if (p->inf == a) return p;
        p = p->next;
    }
    return NULL;
}

int h(int sal) { // хэш-функция, деление
    return sal % m;
}

void hash_table() { // заполнение хэш-таблицы
    hash_t.resize(m);
    for (auto man : all) {
        int i = h(man.Salary);
        push_back(hash_t[i].first, hash_t[i].second, man);
    }
}

list* find_in_hash(people x) { // поиск элемента в хэш-таблице
    int i = h(x.Salary);
    auto head = hash_t[i].first;
    auto tail = hash_t[i].second;
    return find(head, tail, x);
}

void del_elem(list*& head, list*& tail, list* p, int k) { // удаление эл-та p
    if (p == head && p == tail) { // р единственный эл-т в списке
        head = tail = NULL;
        hash_t[k].first = head;
        hash_t[k].second = tail;
    }
    else if (p == head) { // р - это голова
        head = head->next;
        head->prev = NULL;
        hash_t[k].first = head;
    }
    else if (p == tail) { // р - хвост
        tail = tail->prev;
        hash_t[k].second = tail;
        tail->next = NULL;
    }
    else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }
    delete p; // очищение памяти, удаление р 
} 


void del_from_hash(people x, list*& p) { // удаление элемента из хэш-таблицы
    int k = h(x.Salary);
    auto head = hash_t[k].first;
    auto tail = hash_t[k].second;
    del_elem(head, tail, p, k);
}

void print()
{	
	for (int i = 0; i < m; i++){
		cout << i << ": " << endl;
		list *p = hash_t[i].first;
		while(p){
			people man = p->inf;											  // запись итоговых данных в выходной файл
			cout << setw(10) << left << x.Surname << "\t"; // запись фамилий
			cout << setw(10) << x.Profession << "\t";	  // запись профессий
			cout << setw(10) << x.Experience << "\t";	  // запись стажа
			cout << setw(10) << x.DateOfBirth << "\t";	  // запись даты рождения
			cout << setw(10) << x.Salary << endl;		  // запись зарплаты
			p = p->next;
		}
		cout << endl;
	}
}



int main()
{
	input();
	m = 19;
	hash_table();
	print();
	int elem;
	people man;
	cout << "please, enter the person you need to check: ";
	cin >> man.Surname >> man.Profession >> man.Experience >> man.DateOfBirth  >> man.Salary;
	list* p = find_in_hash(man); // поиск элемента 
	if (p) { 
        	cout << "This person is on the list\n";
        	cout << "Enter 1 to remove: ";
        	cin >> elem;
        	if (elem == 1) { // удаление эл-та
            		del_from_hash(man, p);
            		print();
        	}
    	}
    	else cout << "There is no the person\n";
    	cout << endl;
	return 0;
}
