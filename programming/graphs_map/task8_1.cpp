// Дан неориентированный граф. Вывести количество вершин, смежных с данной.
#include <iostream>
#include <map>
#include <list>
#include <fstream>

using namespace std;

ifstream in("input.txt");

map<int, list<int>> graph(bool orient) //создание списка смежности графа
{ 
	map <int, list<int> > res;
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
		if (orient)
		{
			if (fl) 
			{
				res[x].push_back(y);
				if (res.find(y) == res.end()) 
				{
					res[y].push_back(0);
					auto it = res.find(y);
					it->second.erase(it->second.begin());
				}
			}
		}
		else if (fl) 
		{
			res[x].push_back(y);
			res[y].push_back(x);
		}
	}
	return res;
}

int main() 
{
	setlocale(LC_ALL, "RUS");
	map <int, list<int> > Graph = graph(0);
	int vertex, cnt = 0;
	cout << "Вершина: ";
	cin >> vertex;
	cout << "Количество смежных вершин: ";
	cout << Graph[vertex].size();
	return 0;
}