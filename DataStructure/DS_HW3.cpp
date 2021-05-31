#include <iostream>

using namespace std;

class Node;
class Level;
class Tree;

class Node
{
public:
	Node()
	{
		left = NULL;
		right = NULL;
		sibling = NULL;
		val = 0;
	}
	Node* sibling;
	void SetValue(int*, int, Level*);
	void InOrderTraversal(int* list, int* arr, int len, int& ref)
	{
		if (left)
			left->InOrderTraversal(list, arr, len, ref);
		for (int i = 0; i < len; i++)
		{
			if (val == list[i])
			{
				arr[i] = ref++;
				break;
			}
		}
		if (right)
			right->InOrderTraversal(list, arr, len, ref);
	}
	bool Compare(int i)
	{
		return val == i;
	}
private:
	int val;
	Node* left;
	Node* right;
	void SetLeftChild(int* _arr, int len, Level* _l)
	{
		left = new Node();
		left->SetValue(_arr, len, _l);
	}
	void SetRightChild(int* _arr, int len, Level* _l)
	{
		right = new Node();
		right->SetValue(_arr, len, _l);
	}
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
public:
	Tree(int* arr, int len)
	{
		flag = true;
		_0 = new Level();
		root = new Node();
		root->SetValue(arr, len, _0);
	}
	void Traversal(int* arr, int* result, int len, int& ref)
	{
		root->InOrderTraversal(arr, result, len, ref);
	}
	void Check()
	{
		Level* tempLevel = _0;
		Node* temp;
		int idx = 0;
		while (true)
		{
			temp = tempLevel->GetFirst();
			while (true)
			{
				if (!temp->Compare(idx))
					flag = false;
				if (temp->sibling)
				{
					idx++;
					temp = temp->sibling;
				}
				else
					break;
			}
			if (tempLevel->next)
			{
				idx++;
				tempLevel = tempLevel->next;
			}
			else
				break;
		}
	}
	void PrintResult()
	{
		if (flag)
			cout << "Yes";
		else
			cout << "No";
	}
private:
	bool flag;
	Level* _0;
	Node* root;
};
void Node::SetValue(int* arr, int len, Level* level)
{
	level->Insert(this);
	Level* tempNext;
	
	int min = arr[0];
	int idx = 0;
	for (int i = 0; i < len; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
			idx = i;
		}
	}
	val = min;

	if (idx > 0)
	{
		if (!level->next)
			level->next = new Level;
		tempNext = level->next;
		int* temp = new int[idx];
		for (int i = 0; i < idx; i++)
			temp[i] = arr[i];
		SetLeftChild(temp, idx, tempNext);		
	}
	if (len - 1 - idx > 0)
	{
		if (!level->next)
			level->next = new Level;
		tempNext = level->next;
		int* temp = new int[len - 1 - idx];
		for (int i = 0; i < len - 1 - idx; i++)
			temp[i] = arr[idx  + 1 + i];
		SetRightChild(temp, len - 1 - idx, tempNext);
	}
}

void solution(char* levelOrder, char* inOrder)
{
	const int len = strlen(levelOrder);
	int* arr = new int[len];
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (inOrder[i] == levelOrder[j])
			{
				arr[i] = j;
				break;
			}
		}
	}
	Tree tree(arr, len);
	for (int i = 0; i < len; i++)
		arr[i] = i;
	int* result = new int[len];
	int ref = 0;
	tree.Traversal(arr, result, len, ref);
	tree.Check();

	cout << levelOrder << endl;
	cout << inOrder << ' ';
	for (int i = 0; i < len; i++)
	{
		cout << result[i];
		if (i < len - 1)
			cout << '-';
	}
	cout << ' ';
	tree.PrintResult();
}

int main()
{
	int N;
	cin >> N;

	char LevelOrder[1000], InOrder[1000];
	cout << N << "\n";
	while (N--)
	{
		cin >> LevelOrder;
		cin >> InOrder;
		
		solution(LevelOrder, InOrder);
	}
}