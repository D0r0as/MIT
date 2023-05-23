//Дан неориентированный граф. Удалить ребро, соединяющее вершины А и B.
#include <iostream>
#include <map>
#include <list>
#include <fstream>

using namespace std;

ifstream in("input.txt");

map<int, list<int>> graph(bool orient) //создание списка смежности графа
{ 
	map<int, list<int>> res;
	int x, y;
	while (in.peek() != EOF) 
	{
		in >> x >> y;
		auto it_x = res.find(x);
		bool fl = true;
		if (it_x != res.end())
		{
			list<int> a = it_x->second;
			for (auto iter = a.begin(); iter != a.end(); iter++)
				if (*iter == y) 
				{
					fl = false;
					break;
				}
		}
		if (orient){
			if (fl) {
				res[x].push_back(y);
				if (res.find(y) == res.end()) 
				{
					res[y].push_back(0);
					auto it = res.find(y);
					it->second.erase(it->second.begin());
				}
			}
		}
		else if (fl) {
			res[x].push_back(y);
			res[y].push_back(x);
		}
	}
	return res;
}

void output(map<int, list<int>> gr) //вывод графа
{ 
	for (auto it = gr.begin(); it != gr.end(); it++) 
	{
		cout << "point " << it->first << ": ";
		list<int> sp = it->second;
		for (auto iter = sp.begin(); iter != sp.end(); iter++)
			cout << *iter << " ";
		cout << endl;
	}
}

int main()  //так как граф неориентированный
{
	int a, b;
	cout << "enter the first point: ";
	cin >> a;
	cout << "enter the second point: ";
	cin >> b;

	map<int, list<int>> Gr = graph(0);
	//output(Gr);

	Gr[a].remove(b);
	Gr[b].remove(a);

	output(Gr);
	return 0;
}