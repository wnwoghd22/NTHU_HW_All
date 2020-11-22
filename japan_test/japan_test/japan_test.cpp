#include <iostream>
#include <string>
using namespace std;

bool debug = false;

void Bomb(int** _map, int* _l, int& _idx, int _n, int _m, int posI, int posJ)
{
	for (int i = 0; i < _m; ++i)
	{
		if (_map[i][posJ] != -1)
		{
			if (_map[i][posJ] > 0)
				_l[_idx++] = _map[i][posJ];
			_map[i][posJ] = 0;
		}
	}
	for (int j = 0; j < _n; ++j)
	{
		if (_map[posI][j] != -1)
		{
			if (_map[posI][j] > 0)
				_l[_idx++] = _map[posI][j];
			_map[posI][j] = 0;
		}
	}
}
void Sort(int* _l, int _n, bool _b)
{
	int temp;
	for (int i = 0; i < _n - 1; ++i)
	{
		for (int j = 0; j < _n - 1 - i; ++j)
		{
			if (_b)
			{
				if (_l[j] > _l[j + 1])
				{
					temp = _l[j + 1];
					_l[j + 1] = _l[j];
					_l[j] = temp;
				}
			}
			else
			{
				if (_l[j] < _l[j + 1])
				{
					temp = _l[j + 1];
					_l[j + 1] = _l[j];
					_l[j] = temp;
				}
			}
		}
	}
}
void Switch(int* _bills, int* _l, int _n, int _k)
{
	int idx1 = 0;
	int idx = 0;
	while (_bills[++idx] != 0)
	{
		if (idx > _n)
			break;
	} --idx;
	if(debug)
		cout << "idx :" << idx << endl;
	int idx2 = 0;
	for (int k = 0; k < _k;)
	{
		if (_bills[idx - idx1] == 0) return;
		if (_bills[idx - idx1] < _l[_n - idx2])
		{
			_bills[idx - idx1++] = _l[_n - idx2++];
			++k;
		}
		else
		{
			if (++idx2 > _n) return;
		}
	}
}

int main() {

	int n, m, k;
	cin >> m >> n >> k;
	int** map = new int*[m];
	for (int i = 0; i < m; ++i)
	{
		map[i] = new int[n];
		for (int j = 0; j < n; ++j)
		{
			char c;
			cin >> c;
			if (c == 'B')
				map[i][j] = -1;
			if (int('0') < int(c) && int(c) <= int('9'))
				map[i][j] = int(c) - int('0');
		}
	}
	if (debug)
	{

		cout << "initial : " << endl;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
				cout << map[i][j] << ' ';
			cout << endl;
		}
		
	}

	int* list = new int[n*m];
	for (int i = 0; i < n*m; ++i)
		list[i] = 0;
	int idx = 0;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (map[i][j] == -1)
				Bomb(map, list, idx, n, m, i, j);
		}
	
	if (debug)
	{

		cout << "Bomb : " << endl;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
				cout << map[i][j] << ' ';
			cout << endl;
		}

	}
	
	int* bills = new int[n*m];
	idx = 0;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			if (map[i][j] >= 0)
				bills[idx++] = map[i][j];	
			else if (map[i][j] == -1) bills[idx++] = 0;
	
	if (debug)
	{
		cout << " list : ";
		for (int i = 0; i < n*m; i++)
			cout << list[i] << ' ';
		cout << endl;

		cout << " bills : ";
		for (int i = 0; i < n*m; i++)
			cout << bills[i] << ' ';
		cout << endl;
	}

	Sort(list, n*m, true);
	Sort(bills, n*m, false);
	
	if (debug)
	{
		cout << "after sorting : " << endl;
		for (int i = 0; i < n*m; i++)
			cout << list[i] << ' ';
		cout << endl;
		for (int i = 0; i < n*m; i++)
			cout << bills[i] << ' ';
		cout << endl;
	}
	
	Switch(bills, list, n*m, k);

	if (debug)
	{
		cout << "switch : ";
		for (int i = 0; i < n*m; i++)
			cout << bills[i] << ' ';
		cout << endl;
	}

	int result = 0;
	for (int i = 0; i < n*m; ++i)
		result += bills[i];

	cout << result << endl;

	return 0;
}
