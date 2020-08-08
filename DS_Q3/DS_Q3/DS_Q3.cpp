#include "pch.h"
#include <iostream>

class Node;
class Level;
class Tree;

class Node
{
public:
	int val;
	Node()
	{
		left = NULL;
		right = NULL;
		sibling = NULL;
		val = -1;
	}
	Node* sibling;
	void SetValue(int*, int);
	void SetHeap(int*, int, int, Level*);
	void InOrderTraversal(int* arr, int& ref)
	{
		if (left)
			left->InOrderTraversal(arr, ref);
		
		if (val != -1)
		{
			//cout << arr[ref];
			val = arr[ref];
			ref++;
		}

		if (right)
			right->InOrderTraversal(arr, ref);
	}
	bool Compare(int i)
	{
		return val == i;
	}
private:
	Node* left;
	Node* right;
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
		root->SetHeap(arr, len, 0, _0);
	}
	void SetValue(int* arr, int len)
	{
		root->SetValue(arr, len);
	}
	void Traversal(int* result, int len, int& ref)
	{
		root->InOrderTraversal(result, ref);
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
				if (!temp->Compare(-1))
				{
					if (!temp->Compare(idx))
						flag = false;
					else
						idx++;
				}			
					
				if (temp->sibling)
				{				
					temp = temp->sibling;
				}
				else
					break;
			}
			if (tempLevel->next)
			{
				tempLevel = tempLevel->next;
			}
			else
				break;
		}
	}
	void SetResult(bool& r)
	{
		if (!flag)
			r = false;
	}
private:
	bool flag;
	Level* _0;
	Node* root;
};
void Node::SetValue(int* arr, int len)
{
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

	if (left)
	{
		if (idx > 0)
		{
			int* temp = new int[idx];
			for (int i = 0; i < idx; i++)
				temp[i] = arr[i];
			left->SetValue(temp, idx);
		}
	}
	
	if (right)
	{
		if (len - 1 - idx > 0)
		{
			int* temp = new int[len - 1 - idx];
			for (int i = 0; i < len - 1 - idx; i++)
				temp[i] = arr[idx + 1 + i];
			right->SetValue(temp, len - 1 - idx);
		}
	}
	
}
void Node::SetHeap(int* _arr, int len, int _idx, Level* level)
{
	level->Insert(this);
	Level* temp = new Level;

		if (_idx * 2 + 1 < len)
		{
			if (_arr[_idx * 2 + 1] == 1)
			{
				if (!level->next)
					level->next = temp;
				left = new Node();
				left->SetHeap(_arr, len, _idx * 2 + 1, level->next);
			}
		}

		if (_idx * 2 + 2 < len)
		{
			if (_arr[_idx * 2 + 2] == 1)
			{
				if (!level->next)
					level->next = temp;
				right = new Node();
				right->SetHeap(_arr, len, _idx * 2 + 2, level->next);
			}
		}
}
void solution(int* _arr, int _len, char* levelOrder, char* inOrder, bool& answer)
{
	Tree tree(_arr, _len);

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
	
	//for (int i = 0; i < len; i++)
		//cout << arr[i];

	tree.SetValue(arr, len);
	/*
	int* result = new int[len];
	for (int i = 0; i < len; i++)
		result[i] = 0;
	int ref = 0;
	tree.Traversal(result, len, ref);

	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << result[i];
		if (arr[i] != result[i])
			answer = false;
	}*/

	tree.Check();
	tree.SetResult(answer);
}

int main()
{
	int len;
	std::cin >> len;
	int* heapArr = new int[len];
	for (int i = 0; i < len; i++)
		std::cin >> heapArr[i];
	
	int N;
	std::cin >> N;
	bool* result = new bool[N];
	for (int i = 0; i < N; i++)
		result[i] = true;
	char LevelOrder[1000], InOrder[1000];

	for (int i = 0; i < N; i++)
	{
		std::cin >> LevelOrder;
		std::cin >> InOrder;

		solution(heapArr, len, LevelOrder, InOrder, result[i]);
	}

	for (int i = 0; i < N; i++)
	{
		if (result[i])
			std::cout << "Yes" << std::endl;
		else
			std::cout << "No" << std::endl;

	}
}