#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <queue>
 
using namespace std; 
 
int n, m; // кол-во вершин и ребер в графе 
vector<vector<int>> g; // список смежности графа 
vector<int> used;
 
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
    } 
    for (int i = 0; i < n; ++i) { 
        sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины 
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты 
    } 
} 

vector<int> bfs(int start, int &us)
{
    used[start] = 1;
    queue<int> q;
    q.push(start);
    vector<int> path;
    path.push_back(start);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int w : g[u]){
            if (used[w]) continue;
            used[w] = 1;
            path.push_back(w);
            q.push(w);
        }
    }
    return path;
}
 
int main() { 
    graph(); 
    for (int i = 0; i < n; i++)
        used.push_back(0);

    for (int i = 0; i < n; i++)
    {
        vector<int>path = bfs(i, used[i]);
        bool fl = true;
        for (int j = 0; j < g[i].size(); j++)
            if (used[j] == 0)
                fl = false;
        if (fl){
            cout << i << ": ";
            for (int j = 0; j < path.size(); j++)
                cout << path[j] << " ";
            cout << endl;
        }

        for (int i = 0; i< n; i++)
            used[i] = 0;
    }
    return 0;
}