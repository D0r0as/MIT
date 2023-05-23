//Дан неориентированный граф. Выяснить, является ли граф связным.
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

void DFS(map<int, list<int>> gr, int x, bool *&used) //обход в глубину
{ 
	used[x] = 1;
	for (auto it = gr.begin(); it != gr.end(); it++)
	{
		if (it->first == x)
		{
			list<int> a = it->second;
			for (auto iter = a.begin(); iter != a.end(); iter++)
				if (!used[*iter])
					DFS(gr, *iter, used);
			break;
		}
	}
}

int main() //так как граф неориентированный
{
	map<int, list<int>> Graph = graph(0);
	//граф н-ся связным, если из любой вершины есть путь в любую другую вершину
	//запускаем поиск в глубину из любой вершины и после этого проверяем, что мы побывали во всех вершинах
	bool *used = new bool[Graph.size()];
	for (int i = 0; i < Graph.size(); i++)
		used[i] = false;

	DFS(Graph, 0, used);
	
	bool fl = true;
	for (int i = 0; i < Graph.size(); i++)
		if (used[i] == false)
			fl = false;
	if (fl)
		cout << "связный граф";
	else
		cout << "Несвязный граф";
	return 0;
}