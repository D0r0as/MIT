#include <iostream> 
#include <algorithm> 
#include <vector> 
 
using namespace std; 
 
int n, m; // кол-во вершин и ребер в графе 
vector<vector<int>> g; // список смежности графа 
 
 
void graph() { 
    cout << "n = "; 
    cin >> n; 
    cout << "m = "; 
    cin >> m; 
    g.resize(n); // выделение памяти в векторе 
    int v, u; 
    for (int i = 0; i < m; ++i) { // добавление ребер в список смежности 
        cin >> v >> u; 
        v--; u--; 
        g[v].push_back(u); 
        g[u].push_back(v); 
    } 
    for (int i = 0; i < n; ++i) { 
        sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины 
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты 
    } 
} 

void output(vector<vector<int>> g){
    for (int i = 0; i < g.size(); ++i){
        cout << i << ": ";
        for(auto it = g[i].begin(); it != g[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }
}
 
int main() { 
    graph(); 
    int a, b;
	cout << "enter the first point: ";
	cin >> a;
	cout << "enter the second point: ";
	cin >> b; 
    a--; b--;

    for (auto iter = g[a].begin(); iter != g[a].end(); iter++){
        if (*iter == b) 
            g[a].erase(iter);
    }
    for (auto iter = g[b].begin(); iter != g[b].end(); iter++){
        if (*iter == a) 
            g[b].erase(iter);
    }
    // g[a].erase(b);
	// g[b].remove(a);
    cout << "The number of vertices adjacent to the given one: ";
    output(g);
}