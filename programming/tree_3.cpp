#include <iostream>
#include <cmath>
using namespace std;
struct tree
{ // структура дерева (узла)
   int inf;
   tree *right;
   tree *left;
};

tree *node(int x)
{ // создание узла
   tree *n = new tree;
   n->inf = x;
   n->left = n->right = NULL;
   return n;
}

void create(tree *&tr, int n)
{ // создание и заполнение исходного дерева
   int x;
   if (n > 0)
   { // если количество элементов не 0
      cin >> x;
      tr = node(x);
      int l = n / 2;
      int r = n - l - 1;
      create(tr->left, l);  // заполнение левой ветки
      create(tr->right, r); // заполнение правой ветки
   }
}

void preorder(tree *tr)
{
   if (tr)
   {
      cout << tr->inf << " "; // корень
      preorder(tr->left);     // левое
      preorder(tr->right);    // правое
   }
}

void lifts(tree *tr)
{ // выводит все листья
   if (tr)
   {
      lifts(tr->left); // просмотр левого ребенка
      if (!tr->left && !tr->right)
         cout << tr->inf << " "; // если лист, то выводим
      lifts(tr->right);          // просмотр правого ребенка
   }
}

int main()
{
   tree *tr = NULL;
   int n, x;
   cout << "n = ";
   cin >> n;      // ввод количества элементов
   create(tr, n); // заполнение дерева

   preorder(tr); // прямой обход
   cout << endl;

   cout << "leaves" << endl;
   lifts(tr); // вывод листьев
   cout << endl;
   return 0;
}
