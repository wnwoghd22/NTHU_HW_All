#include "pch.h"
#include <iostream>

void Test(bool &_f, int depth, int N, int** _size, bool**** _block, int mapR, int mapC, bool** map);
void Put(int posR, int posC, int blockR, int  blockC, bool** block, bool** map)
{
	for (int i = 0; i < blockR; i++)
		for (int j = 0; j < blockC; j++)
			if (block[i][j] == true)
				map[posR + i][posC + j] = true;
}

void BlockTest(bool &_f, int depth, int N, int posR, int posC, int** _size, bool**** _block, int mapR, int mapC, bool** map)
{
	int _r = _size[depth][1];
	int _c = _size[depth][0];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < _r; j++)
			for (int k = 0; k < _c; k++)
				if (_block[depth][i][j][k] & map[posR + j][posC + k])
					continue;
		Put(posR, posC, _r, _c, _block[depth][i], map);
		Test(_f, depth + 1, N, _size, _block, mapR, mapC, map);
	}
}

void Test(bool &_f, int depth, int N, int** _size, bool**** _block, int mapR, int mapC, bool** map)
{
	if (depth == N)
	{
		for (int i = 0; i < mapR; i++)
			for (int j = 0; j < mapC; j++)
				if (map[i][j] == false)
					return;
		if (!_f)
			std::cout << "Yes" << std::endl;
		_f = true;
		return;
	}
	bool** temp = new bool*[mapR];
	for (int i = 0; i < mapR; i++)
		temp[i] = new bool[mapC];

	for (int posR = 0; posR < mapR - _size[depth][1] + 1; posR++)
		for (int posC = 0; posC < mapC - _size[depth][0] + 1; posC++)
		{
			for (int i = 0; i < mapR; i++)
				for (int j = 0; j < mapC; j++)
					temp[i][j] = map[i][j];
			BlockTest(_f, depth, N, posR, posC, _size, _block, mapR, mapC, temp);
		}
	for (int posR = 0; posR < mapR - _size[depth][0] + 1; posR++)
		for (int posC = 0; posC < mapC - _size[depth][1] + 1; posC++)
		{
			for (int i = 0; i < mapR; i++)
				for (int j = 0; j < mapC; j++)
					temp[i][j] = map[i][j];
			BlockTest_transpose(_f, depth, N, posR, posC, _size, _block, mapR, mapC, temp);
		}

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
	for (int i = 0; i < N; i++)
	{
		size[i] = new int[2];
		std::cin >> size[i][0] >> size[i][1];
		block[i][j] = new bool*[size[i][1]];

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
	int** mapSize = new int*[M];
	bool*** maps = new bool**[M];

	for (int i = 0; i < M; i++)
	{
		mapSize[i] = new int[2];
		std::cin >> mapSize[i][0] >> mapSize[i][1];
		maps[i] = new bool*[mapSize[i][1]];

		for (int j = 0; j < mapSize[i][1]; j++)
		{
			maps[i][j] = new bool[mapSize[i][0]];
			for (int k = 0; k < mapSize[i][0]; k++)
			{
				char c;
				std::cin >> c;
				if (c == 'O')
					maps[i][j][k] = true;
				else
					maps[i][j][k] = false;
			}
		}
	}

	bool flag;
	for (int m = 0; m < M; m++)
	{
		flag = false;
		Test(flag, 0, N, size, block, mapSize[m][1], mapSize[m][0], maps[m]);
		if (!flag)
			std::cout << "No" << std::endl;
	}
	return 0;
}