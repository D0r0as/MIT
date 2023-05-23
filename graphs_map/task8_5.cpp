//Дан ориентированный граф. Вывести все истоки графа.
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <fstream>

using namespace std;

ifstream in("input.txt");

map<int, list<int>> graph(bool orient)  //создание списка смежности графа
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

vector<int> BFS(map<int, list<int>> gr, int v, bool *&used) //обход в ширину
{ 
	used[v] = true;
	queue<int> q;
	q.push(v);
	vector<int> path;
	path.push_back(v);
	while (!q.empty()) 
	{
		int u = q.front();
		q.pop();
		for (auto it = gr.begin(); it != gr.end(); it++)
		{
			if (it->first == u) 
			{
				list<int> a = it->second;
				for (auto iter = a.begin(); iter != a.end(); iter++)
					if (!used[*iter]) 
					{
						used[*iter] = true;
						path.push_back(*iter);
						q.push(*iter);
					}
				break;
			}
		}
	}
	return path;
}

int main() //так как граф ориентированный
{ 
	map<int, list<int>> Graph = graph(1);
	//вершина, из которой существует путь во все остальные называется истоком
	bool *used = new bool[Graph.size()];
	for (int i = 0; i < Graph.size(); i++)
		used[i] = false;

	for (auto it = Graph.begin(); it != Graph.end(); it++)
	{
		vector<int> path = BFS(Graph, it->first, used);
		bool fl = true;

		for (int i = 0; i < Graph.size(); i++)
			if (used[i] == false)
				fl = false;

		if (fl)
		{
			cout << "Вершина " << it->first << " является истоком: ";
			for (vector<int>::iterator it1 = path.begin(); it1 != path.end(); it1++)
				cout << *it1 << " ";
			cout << endl;
		}
        
		for (int i = 0; i < Graph.size(); i++)
			used[i] = false;
	}
	return 0;
}