#include <iostream>

void Sum(int** data, int sum_of_value, int sum_of_weight, int depth, int _N, int _K, int& r )
{
	if (sum_of_weight > _K)
		return;
	if (depth == _N) 
	{
		if (r < sum_of_value)
			r = sum_of_value;
	}
	else
	{
		Sum(data, sum_of_value, sum_of_weight, depth + 1, _N, _K, r);
		Sum(data, sum_of_value + data[depth][0], sum_of_weight + data[depth][1], depth + 1, _N, _K, r);
	}
	return;	
}
void Sum_test(int** data, int sum_of_value, int sum_of_weight, int depth, int _N, int _K, int& w)
{
	if (sum_of_weight > w)
		return;
	if (depth == _N)
	{
		if (_K < sum_of_value)
			if (w > sum_of_weight)
				w = sum_of_weight;
	}
	else
	{
		Sum(data, sum_of_value, sum_of_weight, depth + 1, _N, _K, w);
		Sum(data, sum_of_value + data[depth][0], sum_of_weight + data[depth][1], depth + 1, _N, _K, w);
	}
	return;
}
int main()
{
	int N, K;
	std::cin >> N >> K;

	if (N <= 0)
	{
		std::cout << 0;
		return 0;
	}

	int **data = new int*[N];
	for (int i = 0; i < N; i++)
	{
		data[i] = new int[2];
		std::cin >> data[i][0] >> data[i][1];
	}

	int result = 0;
	Sum(data, 0, 0, 0, N, K, result);

	int _w = 0;
	for (int i = 0; i < N; i++)
		_w += data[i][1];
	Sum_test(data, 0, 0, 0, N, K, _w);

	std::cout << result << _w;

	for (int i = 0; i < N; i++)
		delete[] data[i];
	delete[] data;
	return 0;
}