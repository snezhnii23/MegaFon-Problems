// Megafon_Problem.cpp : Defines the entry point for the console application.
//

// Solving problem "Conway's Game of Life" from MegaFon
// Written by Roman Varlashov

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define pr pair <int, int>

set <pr>::iterator it;

const long long p = 2147483647;

// —оздадим стркутуру дл€ хранени€ "уникальных" идентификаторов массива дл€ каждой итерации

struct mini_hash
{
	long long a;
	long long b;
	long long c;
};

// ‘ункци€ построени€ идентификаторов

mini_hash hash_maker(vector <vector <int>> &Matrix, int n, int m)
{
	long long a, b, c;
	a = 0;
	b = 0;
	c = 0;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Matrix[i][j])
				k++;
			a = (1901 * a + Matrix[i][j]) % p;
			b = (3323 * b + Matrix[i][j]) % p;
			c = (5119 * c + Matrix[i][j]) % p;
		}
	}
	mini_hash New;
	New.a = a;
	New.b = b;
	New.c = c;

	if (k == n * m)
	{
		New.a = -1;
	}
	if (k == 0)
	{
		New.a = -2;
	}

	return New;
}

// —оздадим множество дл€ проверки уникальности матрицы на текущем шаге

set <pair <long long, pair <long long, long long> > > Uniq;

int main()
{
	int n, m; // ќбъ€вл€ем параметры дл€ количества строк и стоблцов таблицы
	cin >> n >> m;
	
	vector <vector <int>> Matrix, Matrix_New;

	// „итаем матрицу размером n * m, обозначени€: 1 - жизнь, 0 - отсутствие жизни. ј также объ€вл€ем матрицы.

	set <pr> Interest_Dots, Interest_Dots_New;
	// —оздаем множество, которое будет хранить интересные нам клетки, то есть которые могут изменитьс€ на следующем шаге. ћножество, чтобы избавитьс€ от повторов.

	for (int i = 0; i < n; i++)
	{
		vector <int> String;
		vector <int> String_New;

		for (int j = 0; j < m; j++)
		{
			int a;
			cin >> a;
			if (a)
			{
				Interest_Dots.insert({ i, j });
			}
			String.push_back(a);
			String_New.push_back(0);
		}
		Matrix.push_back(String);
		Matrix_New.push_back(String_New);
	}

	// ¬ы берем из окрестностей живых клеток кандидатов на изменение на следующем шаге

	for (it = Interest_Dots.begin(); it != Interest_Dots.end(); it++)
	{
		if (it->first > 0 && it->second > 0)
		{
			Interest_Dots_New.insert({ it->first - 1, it->second - 1 });
		}
		if (it->first > 0)
		{
			Interest_Dots_New.insert({ it->first - 1, it->second });
		}
		if (it->first > 0 && it->second + 1 < m)
		{
			Interest_Dots_New.insert({ it->first - 1, it->second + 1 });
		}
		if (it->second > 0)
		{
			Interest_Dots_New.insert({ it->first, it->second - 1 });
		}
		if (it->second + 1 < m)
		{
			Interest_Dots_New.insert({ it->first, it->second + 1 });
		}
		if (it->first + 1 < n && it->second > 0)
		{
			Interest_Dots_New.insert({ it->first + 1, it->second - 1 });
		}
		if (it->first + 1 < n)
		{
			Interest_Dots_New.insert({ it->first + 1, it->second });
		}
		if (it->first + 1 < n && it->second + 1 < m)
		{
			Interest_Dots_New.insert({ it->first + 1, it->second + 1 });
		}
		Interest_Dots_New.insert({ it->first, it->second });
	}
	Interest_Dots = Interest_Dots_New;

	// ¬ыведем изначальную матрицу, дл€ красоты будем обозначать жизнь за "+", остутствие жизни за "-"

	cout << endl << "Step - 0" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Matrix[i][j])
			{
				cout << "+";
			}
			else
				cout << "-";
		}
		cout << endl;
	}

	// ƒобавим эту матрицу в множество всех возможных состо€ний дл€ проверки уникальности получившейс€ матрицы

	mini_hash null_count = hash_maker(Matrix, n, m);
	Uniq.insert({ null_count.a, { null_count.b, null_count.c } });

	// Ќачнем итерационно смотреть, что будет измен€тьс€ с течение времени.
	for (int k = 1; k < 20; k++)
	{
		for (it = Interest_Dots.begin(); it != Interest_Dots.end(); it++)
		{
			int i = it->first;
			int j = it->second;
			int kol = 0;
			if (i > 0 && j > 0 && Matrix[i - 1][j - 1])
			{
				kol++;
			}
			if (i > 0 && Matrix[i - 1][j])
			{
				kol++;
			}
			if (i > 0 && j + 1 < m && Matrix[i - 1][j + 1])
			{
				kol++;
			}
			if (j > 0 && Matrix[i][j - 1])
			{
				kol++;
			}
			if (j + 1 < m && Matrix[i][j + 1])
			{
				kol++;
			}
			if (i + 1 < n && j > 0 && Matrix[i + 1][j - 1])
			{
				kol++;
			}
			if (i + 1 < n && Matrix[i + 1][j])
			{
				kol++;
			}
			if (i + 1 < n && j + 1 < m && Matrix[i + 1][j + 1])
			{
				kol++;
			}
			if (Matrix[i][j])
			{
				if (kol == 2 || kol == 3)
				{
					Matrix_New[i][j] = 1;
				}
				else
					Matrix_New[i][j] = 0;
			}
			else
			{
				if (kol == 3)
				{
					Matrix_New[i][j] = 1;
				}
			}
			// ƒобавл€ем новых кандидатов

			if (it->first > 0 && it->second > 0)
			{
				Interest_Dots_New.insert({ it->first - 1, it->second - 1 });
			}
			if (it->first > 0)
			{
				Interest_Dots_New.insert({ it->first - 1, it->second });
			}
			if (it->first > 0 && it->second + 1 < m)
			{
				Interest_Dots_New.insert({ it->first - 1, it->second + 1 });
			}
			if (it->second > 0)
			{
				Interest_Dots_New.insert({ it->first, it->second - 1 });
			}
			if (it->second + 1 < m)
			{
				Interest_Dots_New.insert({ it->first, it->second + 1 });
			}
			if (it->first + 1 < n && it->second > 0)
			{
				Interest_Dots_New.insert({ it->first + 1, it->second - 1 });
			}
			if (it->first + 1 < n)
			{
				Interest_Dots_New.insert({ it->first + 1, it->second });
			}
			if (it->first + 1 < n && it->second + 1 < m)
			{
				Interest_Dots_New.insert({ it->first + 1, it->second + 1 });
			}
			Interest_Dots_New.insert({ it->first, it->second });
		}
		Interest_Dots = Interest_Dots_New;
		Matrix = Matrix_New;

		// ѕроверим на совпадени€, если в матрице все единицы, то в значении пол€ a будет -1, если все 0, то -2

		mini_hash New_count = hash_maker(Matrix, n, m);
		if (New_count.a == -1)
		{
			cout << "Life win on step " << k << endl;
			cout << endl;
			break;
		}
		if (New_count.a == -2)
		{
			cout << "Death WIN on step " << k << endl;
			cout << endl;
			break;
		}
		if (Uniq.find({ New_count.a, { New_count.b, New_count.c } }) != Uniq.end())
		{
			cout << "Cycle exist on step " << k << endl;
			cout << endl;
			break;
		}
		else
		{
			Uniq.insert({ New_count.a, { New_count.b, New_count.c } });
		}

		// —делаем вывод матрицы

		cout << "Step - " << k << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (Matrix[i][j])
				{
					cout << "+";
				}
				else
					cout << "-";
			}
			cout << endl;
		}
		cout << endl;
	}

	// »тоговое поле
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Matrix[i][j])
			{
				cout << "+";
			}
			else
				cout << "-";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");

	return 0;
}

