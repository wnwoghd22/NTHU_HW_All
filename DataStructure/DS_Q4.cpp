#include <iostream>

int Dijkstra(int** _map, const int mapSize, const int _start, const int _end, int* order)
{
	int* distance = new int[mapSize];
	bool* visited = new bool[mapSize];
	int minCost;
	int nextV;

	for (int i = 0; i < mapSize; i++)
	{
		distance[i] = _map[_start][i];
		visited[i] = false;
		if (distance[i] < 65535)
			order[i] = _start;
	}
	visited[_start] = true;

	for (int i = 0; i < mapSize; i++)
	{
		minCost = 65535;

		for (int j = 0; j < mapSize; j++)
		{
			if (distance[j] < minCost && !visited[j])
			{
				minCost = distance[j];
				nextV = j;
			}
		}
		visited[nextV] = true;

		for (int k = 0; k < mapSize; k++)
		{
			if (!visited[k])
				if (_map[nextV][k] > 0 && (minCost + _map[nextV][k] < distance[k]))
				{
					distance[k] = minCost + _map[nextV][k];
					order[k] = nextV;
				}
		}
	}
	return distance[_end];
}

int main()
{
	int N, M; // # of V, # of E
	std::cin >> N >> M;

	int** map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				map[i][j] = 0;
			else
				map[i][j] = 65535; // distance = infinite
		}
	}

	int startV;
	int endV;

	char start, end;
	std::cin >> start >> end;
	startV = int(start) - int('A');
	endV = int(end) - int('A');

	while (M--)
	{
		std::cin >> start >> end;
		map[int(start) - int('A')][int(end) - int('A')] = 1;
	}

	int* Sequence = new int[N];
	for (int i = 0; i < N; i++)
		Sequence[i] = -1;

	int result = Dijkstra(map, N, startV, endV, Sequence);
	std::cout << result << std::endl;

	int* order = new int[N];
	order[0] = endV;
	int sort = endV;
	int idx = 0;
	while (sort != startV)
	{
		order[++idx] = Sequence[sort];
		sort = Sequence[sort];
	}

	while (true)
	{
		std::cout << char(order[idx] + int('A'));
		if (order[idx--] == endV)
			break;
		std::cout << ' ';
	}
}