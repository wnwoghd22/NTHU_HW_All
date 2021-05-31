#include <iostream>

void Test(bool &_f, int depth, int N, int** _size, bool*** _block, int mapR, int mapC, int** map);
void Put(int depth, int posR, int posC, int blockR, int  blockC, bool** block, int** map)
{
	for (int i = 0; i < blockR; i++)
		for (int j = 0; j < blockC; j++)
			if (block[i][j] == true)
				map[posR + i][posC + j] = depth;
}

void BlockTest(bool &_f, int depth, int N, int posR, int posC, int** _size, bool*** _block, int mapR, int mapC, int** map)
{
	int _r = _size[depth][1];
	int _c = _size[depth][0];
	for (int j = 0; j < _r; j++)
		for (int k = 0; k < _c; k++)
			if ((_block[depth][j][k] == true) && (map[posR + j][posC + k] != 0))
				return;
	Put(depth + 1, posR, posC, _r, _c, _block[depth], map);
	Test(_f, depth + 1, N, _size, _block, mapR, mapC, map);
}

void Test(bool &_f, int depth, int N, int** _size, bool*** _block, int mapR, int mapC , int** map)
{
	if (depth == N)
	{
		for (int i = 0; i < mapC; i++)
		{
			bool _t = false;
			for (int j = 0; j < mapR; j++)
			{
				if (map[j][i] != 0)
					_t = true;
			}
			if (_t == false)
				return;
		}		
		if (!_f)
			std::cout << "Yes" << std::endl;
		_f = true;
		return;
	}
	int** temp = new int*[mapR];
	for (int i = 0; i < mapR; i++)
		temp[i] = new int[mapC];
	for (int i = 0; i < mapR; i++)
		for (int j = 0; j < mapC; j++)
			temp[i][j] = map[i][j];

	for (int posC = 0; posC < mapC - _size[depth][0] + 1; posC++)
		BlockTest(_f, depth, N, mapR - _size[depth][1], posC, _size, _block, mapR, mapC, temp);

	for (int i = 0; i < mapR; i++)
		delete[](temp[i]);
	delete[](temp);
}

int main()
{
	int N;
	std::cin >> N;
	int** size = new int*[N];
	bool*** block = new bool**[N];
	int height = 0;
	for (int i = 0; i < N; i++)
	{
		size[i] = new int[2];
		std::cin >> size[i][0] >> size[i][1];
		block[i] = new bool*[size[i][1]];
		if (height <= size[i][0])
			height = size[i][0];
		for (int j = 0; j < size[i][1]; j++)
		{
			block[i][j] = new bool[size[i][0]];
			for (int k = 0; k < size[i][0]; k++)
			{
				char c;
				std::cin >> c;
				if (c == 'O')
					block[i][j][k] = true;
				else
					block[i][j][k] = false;
			}
		} //0
	}

	int M;
	std::cin >> M;
	int* mapSize = new int[M];

	for (int i = 0; i < M; i++)
	{
		std::cin >> mapSize[i];
	}

	bool flag;
	for (int m = 0; m < M; m++)
	{
		int **map = new int*[height];
		for (int i = 0; i < height; i++)
			map[i] = new int[mapSize[m]];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < mapSize[m]; j++)
				map[i][j] = 0;

		flag = false;
		Test(flag, 0, N, size, block, height, mapSize[m] ,map);
		if (!flag)
			std::cout << "No" << std::endl;
	}
	return 0;
}