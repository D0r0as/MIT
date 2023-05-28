#include <iostream> 
#include <algorithm> 
#include <vector> 
 
using namespace std; 
 
int n, m; // кол-во вершин и ребер в графе 
vector<vector<int>> g; // список смежности графа 
vector<int> path;
 
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

void dfs(int start, vector<int> &used)
{
    used[start] = 1;            // помечаем вершину x как посещенную
    
    for (int i = 0; i < n; i++){
        cout << used[i] << " ";
    }
    cout << endl;//path.push_back(start);   
    for (auto u : g[start]){
        if (used[u] == 0){
            dfs(u, used);
        }
        for (int i = 0; i < n; i++){
            cout << used[i] << " ";
        }
    cout << endl;
    }
}
 
int main() { 
    graph(); 
    vector<int> used;
    for (int i = 0; i < n; i++)
        used.push_back(0);
    dfs(0, used);
    bool fl = true;
    for (int i = 0; i < n; i++)
        if (used[i] == 0)
            fl = false;
    if (fl)
        cout << "yes";
    else 
        cout << "no";
    return 0;
}