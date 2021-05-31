#include <iostream>
#include <string>
using namespace std;

bool debug = true;

void Convert(int** _graph, int* _stores, int* _tele, int _s, int _n, int _m)
{
	int** verteces = new int*[2];
	verteces[0] = new int[_n + 2];
	verteces[1] = new int[_n + 2];

	verteces[0][0] = 0;
	for (int i = 1; i < _n + 2; ++i)
		verteces[0][i] = _stores[i] - _stores[i - 1];

	if (_tele > 0)
	{
		verteces[1][0] = _tele[0]; verteces[1][_n + 1] = _s - _tele[_m - 1];
		for (int i = 0; i < _n; ++i)
		{
			verteces[1][i + 1] = _s;
			for (int j = 0; j < _m; ++j)
				if (abs(_stores[i + 1] - _tele[j]) < verteces[1][i + 1])
					verteces[1][i + 1] = abs(_stores[i + 1] - _tele[j]);
		}
	}

	if (debug)
	{
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < _n + 2; ++j)
				cout << verteces[i][j] << ' ';
			cout << endl;
		}
	}

	int sum;
	for (int i = 0; i < _n + 2; ++i)
	{
		for (int j = i; j < _n + 2; ++j)
		{
			sum = 0;
			if (i == j) _graph[i][j] = 0;
			else
			{
				for (int k = i + 1; k < j + 1; ++k)
					sum += verteces[0][k];
				if (sum > verteces[1][i] + verteces[1][j])
					_graph[i][j] = verteces[1][i] + verteces[1][j];
				else
					_graph[i][j] = sum;
			}
		}
	}
	for (int i = 1; i < _n + 2; ++i)
		for (int j = 0; j < i; ++j)
			_graph[i][j] = _graph[j][i];

	if (debug)
	{
		for (int i = 0; i < _n + 2; ++i)
		{
			for (int j = 0; j < _n + 2; ++j)
				cout << _graph[i][j] << ' ';
			cout << endl;
		}
	}
}

//recursive
void Minimum(int* _r, int** graph, int _n, int _sum, int _i ,int _idx)
{
	for (int _j = _i + 1; _j < _n + 2; ++_j)
	{
		if (_j == _n + 1)
		{
			if (debug) cout << _idx << ',' << _i << ',' << _j << ',' << graph[_i][_j] << ',' << _sum << endl;
			if (_r[_idx] > _sum + graph[_i][_j])
				_r[_idx] = _sum + graph[_i][_j];
			return;
		}
		else
		{
			if (debug) cout << _idx << ',' << _i << ',' << _j << endl;
			Minimum(_r, graph, _n, _sum + graph[_i][_j], _j, _idx + 1);
		}
	}
}

int main()
{
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int* stores = new int[n + 2];
	stores[0] = 0; stores[n + 1] = s;
	for (int i = 0; i < n; ++i)
		cin >> stores[i + 1];

	int* tele = new int[m];
	for (int j = 0; j < m; ++j)
		cin >> tele[j];

	if (debug)
	{
		cout << "stores : ";
		for (int i = 0; i < n + 2; ++i)
			cout << stores[i] << ' ';
		cout << endl << "tele : ";
		for (int i = 0; i < m; ++i)
			cout << tele[i] << ' ';
		cout << endl;
	}

	int** graph = new int*[n + 2];
	for(int i = 0; i < n + 2; ++i)
		graph[i] = new int[n + 2];

	Convert(graph, stores, tele, s, n, m);

	int result;
	int* r = new int[n + 1];
	for (int i = 0; i < n + 2; ++i)
		r[i] = 10000000;
	r[0] = graph[0][n + 1];
	
	int idx = 0;
	Minimum(r, graph, n, 0, 0, idx);

	if (debug)
	{
		for (int i = 0; i < n + 2; ++i)
			cout << r[i] << ' ';
		cout << endl;
	}

	idx = 0;

	for (int i = 1; i < n + 1; ++i)
	{
		if (i + r[i] < t)
		{
			result = i + r[i];
			idx = i;
		}

	}
	cout << idx << ' ' << result << endl;

	return 0;
}
