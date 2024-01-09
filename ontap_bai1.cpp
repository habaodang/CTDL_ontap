#include <iostream>
#include <fstream>
using namespace std;
#define MAX 100
int a[MAX][MAX];
int n;


int queue[MAX];
int front;
int rear;

void initQueue()
{
	front = 0;
	rear = -1;
}

void push(int x)
{
	queue[++rear] = x;
}

void pop(int& x)
{
	x = queue[front++];
}

bool empty()
{
	return front > rear;
}

void input()
{
	ifstream f;
	f.open("input.txt");
	f >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			f >> a[i][j];
	f.close();
}

void display()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

int c[MAX];
int bfs[MAX];
int idx = 0;
char kitu[8] = { 'a','b','c','d','e','g','h','k' };
void BFS(int s)
{
	initQueue();
	for (int i = 0; i < n; i++)
		c[i] = 1;
	push(s);
	int u;
	c[s] = 0;
	while (!empty())
	{
		pop(u);
		bfs[idx++] = u;
		for (int v = 0; v < n; v++)
		{
			if (a[u][v] != 0 && c[v]==1)
			{
				push(v);
				c[v] = 0;
			}
		}
	}
}

void outputBfs()
{
	for (int i = 0; i < idx; i++)
	{
		cout << kitu[bfs[i]] << " ";
	}
	cout << endl;
}

bool checkDirected()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != a[j][i])
				return false;

		}
	}
	return true;
}
int countDegree(int v)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[v][i] != 0)
			count++;
	}
	return count;
}

void degreeGraph()
{
	
	for (int i = 0; i < n; i++)
	{
		cout << "dinh " << kitu[i] << " co " << countDegree(i) << " bac" << endl;
	}
}

void bfsXtoY(int x, int y)
{
	initQueue();
	int u;
	int count = 0;
	for (int i = 0; i < n; i++)
		c[i] = 1;
	push(x);
	c[x] = 0;
	cout << "duyet tu dinh " << kitu[x] << "den " << kitu[y] << ": ";
	while (!empty())
	{
		pop(u);
		cout << kitu[u] << " ";
		count++;
		if (u == y) break;
		for (int v = 0; v < n; v++)
		{
			if (a[u][v] != 0 && c[v] == 1)
			{
				push(v);
				c[v] = 0;
			}
		}
	}
	cout << "\ntong so dinh di qua la " << count << endl;
}

int E1[MAX];
int E2[MAX];
int wE[MAX];
int nE = 0;

int T1[MAX];
int T2[MAX];
int wT[MAX];
int nT = 0;

bool tontai(int v, int D[], int nD)
{
	for (int i = 0; i < nD; i++)
	{
		if (v == D[i])
			return true;
	}
	return false;
}

void xoadinh(int i)
{
	for (int j = i; j < nE; j++)
	{
		E1[j] = E1[j + 1];
		E2[j] = E2[j + 1];
		wE[j] = wE[j + 1];
	}
	nE--;
}
void xoacanh(int u, int v)
{
	for (int i = 0; i < nE; i++)
	{
		if (E1[i] == u && E2[i] == v)
		{
			xoadinh(i);
			break;
		}
	}
}
void prim(int s)
{
	int u = s, min, d1, d2, i;
	while (nT < n - 1)
	{
		for (int v = 0; v < n; v++)
		{
			if (a[u][v] != 0)
			{
				if (!tontai(v, T2, nT))
				{
					E1[nE] = u;
					E2[nE] = v;
					wE[nE] = a[u][v];
					nE++;
				}
			}
		}

		for (i = 0; i < n; i++)
		{
			if (!tontai(E2[i], T2, nT))
			{
				min = wE[i];
				d1 = E1[i];
				d2 = E2[i];
				break;
			}
		}
		for (i = 0; i < n; i++)
		{
			if (!tontai(E2[i], T2, nT))
			{
				if (min>wE[i])
				{
					min = wE[i];
					d1 = E1[i];
					d2 = E2[i];
				}
			}
		}

		T1[nT] = d1;
		T2[nT] = d2;
		wT[nT] = a[d1][d2];
		a[d1][d2] = 0;
		a[d2][d1] = 0;
		nT++;
		u = d2;
	}
}
void outputPrim()
{
	int tong = 0;
	for (int i = 0; i < nT; i++)
	{
		cout << endl << "(" << kitu[T1[i]] << "," << kitu[T2[i]]
			<< ") = " << wT[i];
		tong += wT[i];
	}
	cout << "\n Tong = " << tong;
}
void menu()
{
	int yourSelect;
	cout << "[0] xuat do thi" << endl;
	cout << "[1] duyet bfs" << endl;
	cout << "[2] kiem tra do thi co huong" << endl;
	cout << "[3] tinh bac" << endl;
	cout << "[4] duyet tu x den y" << endl;
	cout << "[5] cay bao trum prim" << endl;
	cout << "nhap lua chon: ";
	cin >> yourSelect;
	int x, y;
	switch (yourSelect) 
	{
	case 0:
		display();
		break;
	case 1:
		BFS(0);
		cout << "BFS" << endl;
		outputBfs();
		break;
	case 2:
		if (checkDirected())
			cout << "do thi vo huong" << endl;
		else
			cout << "do thi co huong" << endl;
		break;
	case 3:
		degreeGraph();
		break;
	case 4:
		
		cout << "nhap gia tri x va y: ";
		cin >> x >> y;
		bfsXtoY(x,y);
		break;
	case 5:
		cout << "nhap bat dau: ";
		cin >> x;
		prim(x);
		outputPrim();
		break;
	}
}
int main()
{
	while(1)
	{
		input();
		system("cls");
		menu();
		int check;
		cout << "thoat[0]" << endl;
		cin >> check;
		if (check == 0)break;
	}
	return 0;
}