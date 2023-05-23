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

struct stack // создаём структуру стека
{
    int inf;
    stack *next;
};

void push_stack(stack *&h, char x) // вставка элемента
{
    stack *r = new stack; // создаём новый элемент
    r->inf = x;           // информационное поле = х
    r->next = h;          // h является следующим элементом
    h = r;                // r является головой
}

int pop_stack(stack *&h) // удаление элемента
{
    char i = h->inf; // значение первого элемента
    stack *r = h;    // указатель на голову стека
    h = h->next;     // переносим указатель на следующий элемент
    delete r;        // удаляем первый элемент
    return i;        // возвращаем его значение
}

void dfs(vector<vector<int>> graph, int start)
{
    stack *head = NULL; // создаем стек и инициализируем его
    int y;
    vector<int> a; // создаем массив A размерности N и заполняем его нулями
    for (int i = 0; i < n; i++)
    {
        a.push_back(0);
    }
    a[start] = 1;            // помечаем вершину x как посещенную
    push_stack(head, start); // помещаем вершину x в стек
    cout << start << " ";    // выводим x на экран
    bool fl = false;
    while (head)
    {                      // цикл пока стек не пуст
        int x = head->inf; // · Рассматриваем вершину стека, не извлекая ее
        for (int i = 0; i < graph[x].size(); i++)
        {
            if (a[graph[x][i]] == 0)
            { // если существует непосещенная вершина
                y = graph[x][i];
                fl = true;
                break;
            }
        }
        if (fl == true)
        {                        // если нашли нужную вершину
            a[y] = 1;            // помечаем y как посещенную вершину
            push_stack(head, y); // помещаем ее в стек
            cout << y << " ";    // выводим на экран
            fl = false;          // возвращяем значение для прохождения списка
        }
        else
            pop_stack(head); // извлекаем вершину стека
    }
    for (int i = 0; i < n; i++)
    { // если остались непосещенные вершины то
        if (a[i] == 0)
            dfs(graph, i); // вызываем рассмотренный алгоритм для непосещенной вершины
    }
}
 
int main() { 
    graph(); 
    vector<int> used;
    for (int i = 0; i < n; i++)
        used[i] = 0;
    dfs(g, 0);
    bool fl = true;
    for (int i = 0; i < n; i++)
        if (used[i] == 0)
            fl = false;
    if (fl)
        cout << "yes";
    else cout << "no";
    //cout << "The number of vertices adjacent to the given one: " << g[x].size();
}