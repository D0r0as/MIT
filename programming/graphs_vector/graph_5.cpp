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




struct queue
{ // структура очереди
    int inf;
    queue *next;
};

void push_queue(queue *&h, queue *&t, int x)
{
    queue *r = new queue; // создаём новый элемент
    r->inf = x;           // информационное поле = х
    r->next = NULL;       // всегда последний
    if (!h && !t)         // если очередь пуста
        h = t = r;        // это и голова и хвост
    else
    {
        t->next = r; // r - следующий для хвоста
        t = r;       // теперь r - хвост
    }
}

int pop_queue(queue *&h, queue *&t)
{
    queue *r = h;   // создаём указатель на голову
    int i = h->inf; // сохраняем значение головы
    h = h->next;    // сдвигаем указатель на следующий эдлемент
    if (!h)         // если удаляем последний элемент из очереди
        t = NULL;
    delete r; // удаляем первый элемент
    return i; // возвращаем его значение
}

vector<int> bfs(vector<vector<int>> graph, int start, *&used)
{
    queue *head = NULL, *tail = NULL; // создаем очередь и инициализируем ее
    int y;
    vector<int> a; // создаем массив A размерности N и заполняем его нулями
    for (int i = 0; i < n; i++)
    {
        a.push_back(0);
    }
    a[start] = 1;                  // помечаем вершину x как посещенную
    push_queue(head, tail, start); // помещаем вершину x в очередь
    cout << start << " ";          // выводим x на экран
    while (head && tail)
    {                                  // цикл пока очередь не пуста
        int x = pop_queue(head, tail); // извлекаем голову очереди x
        for (int i = 0; i < graph[x].size(); i++)
        {
            if (a[graph[x][i]] == 0)
            { // если существует непосещенная вершина, смежная x
                y = graph[x][i];
                a[y] = 1;                  // помечаем y как посещенную вершину
                push_queue(head, tail, y); // помещаем ее в очередь
                cout << y << " ";          // выводим x на экран
            }
        }
    }
    for (int i = 0; i < n; i++)
    { // если остались непосещенные вершины то
        if (a[i] == 0)
        {
            bfs(graph, i); // вызываем рассмотренный алгоритм для непосещенной вершины
        }
    }
    return a;
}
 
int main() { 
    graph(); 
    vector<int> used;
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++)
    {
        vector<int>path = bfs(g, i, used[i]);
        bool fl = true;
        for (int j = 0; j < g[i].size(); i++)
            if (used[j] == 0)
                fl = false;
        if (fl){
            cout << i << ": ";
            for (int j = 0; j < path.size(); j++)
                cout << path[j] << " ";
            cout << endl;
        }

        for (int i = 0; i< n; i++)
            used[i] = 0
    }
    return 0;
}