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
 
 
int main() { 
    graph(); 
    int x; // заданная вершина  
    cout << "Enter the number of vertices: "; 
    cin >> x; 
    x--; 
    cout << "The number of vertices adjacent to the given one: " << g[x].size();
}