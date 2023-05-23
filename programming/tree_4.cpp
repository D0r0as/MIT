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
{ // прямой обход
   if (tr)
   {
      cout << tr->inf << " "; // корень
      preorder(tr->left);     // левое
      preorder(tr->right);    // правое
   }
}

int levels(tree *tr, int k, int l)
{ // выводит сумму элементы на k уровне
   int res;
   if (tr)
   {
      if (k == l)
         res = tr->inf;                                                  // если уровень нужный, запоминаем значение
      else if (k > l)                                                    // если не дошли до нужного уровня
         res = levels(tr->left, k, l + 1) + levels(tr->right, k, l + 1); // ссумируем леую и правую часть на уровень ниже
      else
         res = 0;
   }
   else
      res = 0;
   return res; // возвращаем сумму
}

int main()
{
   tree *tr = NULL;
   int n, x, k;
   cout << "n = ";
   cin >> n; // ввод количества элементов
   cout << "k = ";
   cin >> k;      // ввод уровня
   create(tr, n); // заполнение исходного дерева

   preorder(tr); // прямой обход

   cout << endl;
   cout << "summ of elements on level k " << endl;
   cout << levels(tr, k, 0); // сумма элементов на к-ом уровне
   return 0;
}
