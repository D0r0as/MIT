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
{ // симметричный обход
    if (tr)
    {
        inorder(tr->left);  // левое
        cout << tr->inf;    // корень
        inorder(tr->right); // правое
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

tree *find(tree *tr, int x)
{                            // поиск
    if (!tr || x == tr->inf) // нашли или дошли до конца ветки
        return tr;
    if (x < tr->inf)
        return find(tr->left, x); // ищем по левой ветке
    else
        return find(tr->right, x); // ищем по правой ветке
}

tree *Min(tree *tr)
{ // поиск min
    if (!tr->left)
        return tr; // нет левого ребенка
    else
        return Min(tr->left); // идем по левой ветке до конца
}

tree *Next(tree *tr, int x)
{ // поиск следующего
    tree *n = find(tr, x);
    if (n->right)             // если есть правый ребенок
        return Min(n->right); // min по правой ветке

    tree *y = n->parent; // родитель
    while (y && n == y->right)
    {          // пока не дошли до корня или узел - правый ребенок
        n = y; // идем вверх по дереву
        y = y->parent;
    }
    return y; // возвращаем родителя
}

void Delete(tree *&tr, tree *v)
{ // удаление узла
    tree *p = v->parent;
    if (!p && !v->left && !v->right)
        tr = NULL; // дерево содержит один узел
    else if (!v->left && !v->right)
    {                     // если нет детей
        if (p->left == v) // указатель у родителя меняем на NULL
            p->left = NULL;
        if (p->right == v)
            p->right = NULL;
        delete v;
    }
    else if (!v->left || !v->right)
    { // если только один ребенок
        if (!p)
        { // если удаляем корень, у которого 1 ребенок
            if (!v->left)
            {                   // если есть правый ребенок
                tr = tr->right; // он становится корнем
            }
            else
            { // аналогично для левого
                tr = tr->left;
            }
            tr->parent = NULL;
        }
        else
        {
            if (!v->left)
            {                           // если есть правый ребенок
                if (p->left == v)       // если удаляемый узел явл. левым ребенком
                    p->left = v->right; // ребенок удаляемого узла становится левым ребенком своего "деда"
                else
                    p->right = v->right; // ребенок удаляемого узла становится правым ребенком своего "деда"
                v->right->parent = p;    // родителем ребенка становится его "дед"
            }
            else
            { // аналогично для левого ребенка
                if (p->left == v)
                    p->left = v->left;
                else
                    p->right = v->left;
                v->left->parent = p;
            }
            delete v;
        }
    }
    else
    {                                  // есть оба ребенка
        tree *succ = Next(tr, v->inf); // следующий за удаляемым узлом
        v->inf = succ->inf;            // присваиваем значение
        if (succ->parent->left == succ)
        {                                           // если succ левый ребенок
            succ->parent->left = succ->right;       // его правый ребенок становится левым ребенком своего "деда"
            if (succ->right)                        // если этот ребенок существует
                succ->right->parent = succ->parent; // его родителем становится "дед"
        }
        else
        { // аналогично если succ - правый ребенок
            succ->parent->right = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        delete succ;
    }
}

void del_2(tree *&tr)
{ // удаление четных элементов
    if (tr)
    {
        tree *p = tr;     // инициализация дерева
        del_2(tr->left);  // рекурсивное применение функции для левого ребенка
        del_2(tr->right); // рекурсивное применение функции для правого ребенка
        if (p->inf % 2 != 0 && p->inf)
            Delete(tr, p); // удаление если элемент четный
    }
}
// 5 3 7 1 9 4 2 8 6 0
int main()
{
    int n, x;
    cout << "n = ";
    cin >> n; // ввод количества элементов дерева
    tree *tr = NULL;

    for (int i = 0; i < n; i++)
    { // заполнение дерева
        cout << i << " = ";
        cin >> x;      // ввод текущего элеиента
        insert(tr, x); // вставка этого элемента на свое мемсто в дереве
    }

    inorder(tr); // дерево при рассмотрении симметричного обхода
    cout << endl;

    del_2(tr); // удаляем четные элементы
    cout << endl;

    inorder(tr); // конечный вариант дерева при рассмотрении симметричного обхода
    cout << endl;

    return 0;
}