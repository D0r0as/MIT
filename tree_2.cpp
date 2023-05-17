#include <iostream>
using namespace std;
struct tree
{ // структура дерева (узла)
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x)
{ // создание узла
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void inorder(tree *tr)
{ // симметричный обход (Л-К-П)
    if (tr)
    {
        inorder(tr->left);      // левое
        cout << tr->inf << " "; // корень
        inorder(tr->right);     // правое
    }
}

void insert(tree *&tr, int x)
{ // вставка
    tree *n = node(x);
    if (!tr)
        tr = n; // если дерево пустое - корень
    else
    {
        tree *y = tr;
        while (y)
        {                        // ищем куда вставлять
            if (n->inf > y->inf) // правая ветка
                if (y->right)
                    y = y->right;
                else
                {
                    n->parent = y; // узел становится правым ребенком
                    y->right = n;
                    break;
                }
            else if (n->inf < y->inf) // левая ветка
                if (y->left)
                    y = y->left;
                else
                {
                    n->parent = y; // узел становится левым ребенком
                    y->left = n;
                    break;
                }
        }
    }
}

void path(tree *tr, tree *p)
{// путь от корня до узла
    cout << tr->inf << " ";
    if (p->inf == tr->inf) // нашелся
        return;
    else if (p->inf < tr->inf) // если меньше текущего узла (как корня)
        path(tr->left, p);
    else // если больше текущего узла (как корня)
        path(tr->right, p);
}

int main()
{
    int n, x, k;
    cout << "n = ";
    cin >> n; // ввод количества элементов
    cout << "x = ";
    cin >> x; // ввод узла
    bool fl = false;
    tree *tr = NULL;

    for (int i = 0; i < n; i++)
    { // заполнение дерева
        cout << i << ": ";
        cin >> k;
        if (k == x)
            fl = true;
        insert(tr, k);
    }

    if (!fl)
        cout << "there is no your element"; // если нет искомого узла в дереве, выводим сообщение
    else
    { // иначе выводим путь
        tree *y = node(x);

        inorder(tr); // прямой обход
        cout << endl;

        cout << "path: " << endl;
        path(tr, y); // путь к узлу от корня
        cout << endl;
    }
    return 0;
}