#include <iostream>

bool debug = false;

class Node;
class Level;
class Tree;

class Node
{
private:
public:
	bool isTarget;
	bool isDead;
	bool isPath;
	Node* parent;
	Node* left;
	Node* middle;
	Node* right;
	Node* sibling;
	Node()
	{
		left = NULL;
		right = NULL;
		middle = NULL;
		sibling = NULL;
		isTarget = false;
		isDead = false;
	}
	void SetNode(bool**, const int, const int, const int, const int, Level*, int&, int&, int&);
};
class Level
{
public:
	Level* next;
	Level()
	{
		next = NULL;
		first = NULL;
		last = NULL;
	}
	Node* GetFirst()
	{
		return first;
	}
	void Insert(Node* n)
	{
		if (!first)
		{
			first = n;
			last = n;
		}
		else
		{
			last->sibling = n;
			last = n;
		}
	}
private:
	Node* first;
	Node* last;
};
class Tree
{
private:
	Level* _0;
	Node* root;
public:
	int n1;
	int n3;
	int n4;
	Tree(bool** _map, int width, int height)
	{
		_0 = new Level();
		root = new Node();
		n1 = 0; //# of dead ends
		n3 = 0; //T-junction
		n4 = 0; //cross

		root->SetNode(_map, width, height, 0, 1, _0, n1, n3, n4);
	}
};

void Node::SetNode(bool** _map, const int _width, const int _height, const int x, const int y, Level* _lev, int& n1, int& n3, int& n4)
{
	_map[x][y] = true;
	_lev->Insert(this);

	int path = 0;

	if (x > 0)
	{
		if (!_map[x - 1][y])
		{
			path++;

			Node* temp = new Node();
			if (left)
			{
				if (middle)
					right = temp;
				else
					middle = temp;
			}
			else
				left = temp;
			temp->parent = this;
			if (_lev->next == NULL)
				_lev->next = new Level();

			temp->SetNode(_map, _width, _height, x - 1, y, _lev->next, n1, n3, n4);
		}
	}
	if (x < _width - 1)
	{
		if (!_map[x + 1][y])
		{
			path++;

			Node* temp = new Node();
			if (left)
			{
				if (middle)
					right = temp;
				else
					middle = temp;
			}
			else
				left = temp;
			temp->parent = this;
			if (_lev->next == NULL)
				_lev->next = new Level();

			temp->SetNode(_map, _width, _height, x + 1, y, _lev->next, n1, n3, n4);
		}
	}
	if (y > 0)
	{
		if (!_map[x][y - 1])
		{
			path++;

			Node* temp = new Node();
			if (left)
			{
				if (middle)
					right = temp;
				else
					middle = temp;
			}
			else
				left = temp;
			temp->parent = this;
			if (_lev->next == NULL)
				_lev->next = new Level();

			temp->SetNode(_map, _width, _height, x, y - 1, _lev->next, n1, n3, n4);
		}
	}
	if (y < _height - 1)
	{
		if (!_map[x][y + 1])
		{
			path++;

			Node* temp = new Node();
			if (left)
			{
				if (middle)
					right = temp;
				else
					middle = temp;
			}
			else
				left = temp;
			temp->parent = this;
			if (_lev->next == NULL)
				_lev->next = new Level();

			temp->SetNode(_map, _width, _height, x, y + 1, _lev->next, n1, n3, n4);
		}
	}

	switch (path)
	{
	case 0:
		n1++;
		isDead = true;

		if ((x == _width - 1) && (y == _height - 2))
		{
			n1--;
			isTarget = true;
			isDead = false;
		}
	case 1:
		break;
	case 2:
		n3++;
		break;
	case 3:
		n4++;
		break;
	}
}

void Swap(int* a1, int* a2)
{
	int temp;
	for (int i = 0; i < 5; i++)
	{
		temp = a1[i];
		a1[i] = a2[i];
		a2[i] = temp;
	}
}
void Compare(int* a1, int* a2)
{
	if (a1[0] == a2[0])
	{
		if (a1[2] == a2[2])
		{
			if (a1[3] == a2[3])
			{
				if (a1[4] < a2[4])
					Swap(a1, a2);
			}
			else if (a1[3] < a2[3])
				Swap(a1, a2);
		}
		else if (a1[2] < a2[2])
			Swap(a1, a2);
	}
	else if (a1[0] < a2[0])
		Swap(a1, a2);
}
void BubbleSort(int** _arr, int _N)
{
	while (--_N)
	{
		for (int i = 0; i < _N; i++)
			Compare(_arr[i], _arr[i + 1]);
	}
}

void Copy(int* a1, int* a2)
{
	for (int i = 0; i < 5; i++)
		a1[i] = a2[i];
}
bool Compare(int* a1, int* a2, int _i)
{
	return a1[_i] < a2[_i] ? true : false;
}
void Merge(int** a, const int left, const int mid, const int right, const int _i, const int N)
{
	int _l, _r, _idx;

	_l = left;
	_r = mid + 1;
	_idx = left;

	int** tmp_arr = new int*[N];
	for (int i = 0; i < N; i++)
		tmp_arr[i] = new int[5];

	// left ~ mid, mid + 1 ~ right
	while (_l <= mid && _r <= right)
	{
		if (Compare(a[_l], a[_r], _i))
		{
			Copy(tmp_arr[_idx], a[_r]);
			_r++;
		}		
		else
		{
			Copy(tmp_arr[_idx], a[_l]);
			_l++;
		}
		_idx++;
	}

	// left done, right yet
	if (_l > mid)
		for (int m = _r; m <= right; m++)
		{
			Copy(tmp_arr[_idx], a[m]);
			_idx++;
		}
	// left yet
	else
		for (int m = _l; m <= mid; m++)
		{
			Copy(tmp_arr[_idx], a[m]);
			_idx++;
		}

	for (int m = left; m <= right; m++)
		Copy(a[m], tmp_arr[m]);
}
void MergeSort(int** a, const int left, const int right, const int _i, const int N)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(a, left, mid, _i, N);
		MergeSort(a, mid + 1, right, _i, N);

		Merge(a, left, mid, right, _i, N);
	}
}

int main()
{
	int N;
	std::cin >> N;
	int** data = new int*[N];
	for (int i = 0; i < N; i++)
	{
		data[i] = new int[5];
		int serial, width, height;
		std::cin >> serial >> width >> height;

		data[i][4] = serial;

		bool** map = new bool*[width];
		for (int j = 0; j < width; j++)
			map[j] = new bool[height];
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				char c;
				std::cin >> c;
				if (c == 'N')
					map[k][j] = true;
				else
					map[k][j] = false;
			}
		}

		if (debug)
		{
			for (int j = 0; j < height; j++)
			{
				for (int k = 0; k < width; k++)
				{
					if (map[k][j])
						std::cout << 1;
					else
						std::cout << 0;
				}
				std::cout << std::endl;
			}
		}

		Tree* temp = new Tree(map, width, height);
		data[i][0] = temp->n1 + temp->n3 + temp->n4;
		data[i][1] = temp->n1;
		data[i][2] = temp->n3;
		data[i][3] = temp->n4;

		delete temp;
		/*for (int i = 0; i < width; i++)
			delete[]map[i];
		delete[]map;*/
	}

	//BubbleSort(data, N);
	
	MergeSort(data, 0, N - 1, 4, N); //serial
	MergeSort(data, 0, N - 1, 2, N); //n3
	MergeSort(data, 0, N - 1, 3, N); //n4
	MergeSort(data, 0, N - 1, 0, N); //over
	

	for (int j = 0; j < N; j++)
	{
		std::cout << data[j][4] << ':' << ' ' << data[j][0] << ' ' << data[j][3] << ' ' << data[j][2] << ' ' << data[j][1] << std::endl;
	}
}