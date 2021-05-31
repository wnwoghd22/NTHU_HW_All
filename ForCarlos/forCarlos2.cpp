#include <iostream>
#include <string>
#define __MAX__ 100001

using namespace std;

class Tree;

class Node
{
public:
	Node(int d = __MAX__)
	{
		right = NULL;
		left = NULL;
		parent = NULL;
		data = d;
		sign = false;
		flag = false;

		tower = false;
		defended = false;
	}
	bool GetFlag() { return flag; }
	void SetFlag(bool b) { flag = true; }
	void SetRight(Node* n)
	{
		right = n;
	}
	Node* GetRight()
	{
		return right;
	}
	void Right()
	{
		right = new Node();
		right->parent = this;
	}
	void SetLeft(Node* n)
	{
		left = n;
	}
	Node* GetLeft()
	{
		return left;
	}
	void Left()
	{
		left = new Node();
		left->parent = this;
	}
	void SetValue(int v)
	{
		if (data == __MAX__) data = 0;
		data = 10 * data + v;
	}
	int GetValue()
	{
		return sign ? -1 * data : data;
	}
	void SetSign()
	{
		sign = true;
	}
	Node* GetParent()
	{
		return parent;
	}
	bool isLeaf()
	{
		return !right && !left ;
	}
	void Delete()
	{
		if (parent)
		{
			if (this == parent->left) parent->left = NULL;
			if (this == parent->right) parent->right = NULL;
		}
		delete this;
	}

	void Preorder()
	{
		cout << GetValue() << " ";
		if (left) left->Preorder();
		if (right) right->Preorder();
	}
	void Inorder()
	{
		if (left) left->Inorder();
		cout << GetValue() << " ";
		if (right) right->Inorder();
	}
	void Postorder()
	{
		if(left) left->Postorder();
		if(right) right->Postorder();
		cout << GetValue() << " ";
	}

	int Height()
	{
		if (isLeaf()) return 1;
		else
		{
			if(!right) return left->Height() + 1;
			else if (!left) return right->Height() + 1;
			else
				return right->Height() >= left->Height() ? right->Height() + 1 : left->Height() + 1;
		}
	}
	int Weight()
	{
		if (isLeaf()) return GetValue();
		else
		{
			if (!right) return GetValue() + left->Weight();
			else if (!left) return GetValue() + right->Weight();
			else
				return GetValue() + right->Weight() + left->Weight();
		}
	}
	int MaxPathSum()
	{
		if (isLeaf()) return GetValue();
		else
		{
			if (!right) return GetValue() + left->MaxPathSum();
			else if (!left) return GetValue() + right->MaxPathSum();
			else
				return  right->MaxPathSum() >= left->MaxPathSum() ? right->MaxPathSum() + GetValue() : left->MaxPathSum() + GetValue();
		}
	}
	bool isTower() { return tower; }
	void InstallTower(int& _r)
	{
		++_r;
		tower = true;
		if(right) right->defended = true;
		if(left) left->defended = true;
		if(parent) parent->defended = true;
	}
	bool isDefended() { return defended; }
	void Reset()
	{
		defended = false;
		tower = false;
		if (left) left->Reset();
		if (right) right->Reset();
	}
private:
	Node* right;
	Node* left;
	Node* parent;

	int data;
	bool sign;

	bool tower;
	bool defended;

	bool flag;
};

class Tree
{
public:
	Tree()
	{
		root = new Node();
	}
	void Insert();

	void Preorder() { if (root) { root->Preorder(); cout << endl; } }
	void Inorder() { if (root) { root->Inorder(); cout << endl; } }
	void Postorder() { if (root) { root->Postorder(); cout << endl; } }
	void Traverse() { Preorder(); Inorder(); Postorder(); }

	void Height() { if (root) cout << root->Height() << endl; }
	void WeightSum() { if (root) cout << root->Weight() << endl; }
	void MaxPathSum() { if (root) cout << root->MaxPathSum() << endl; }

	void BinaryTower() { int result = 0; root->Reset(); BinaryTower(root, result); cout << result << endl; }
	void DeleteLeaves() { deleteLeaves(root); }

	bool isFoldable() { if (root->isLeaf()) return true; return Symmetric(root->GetLeft(), root->GetRight()); }
private:
	Node* root;
	void BinaryTower(Node*, int&);
	void deleteLeaves(Node *);
	bool Symmetric(Node *a, Node *b);
};
void Tree::Insert()
{
	Node* ptr = NULL;

	char c;
	cin >> c;

	while (c != '\n')
	{
		switch (c)
		{
		case '(':
			if (ptr == NULL) ptr = root;
			else
			{
				if (!ptr->GetFlag())
				{
					ptr->SetFlag(true);
					ptr->Left();
					ptr = ptr->GetLeft();
				}
				else
				{
					ptr->Right();
					ptr = ptr->GetRight();
				}
			}
			break;
		case ')':
			if (ptr == root) return;
			else
			{
				Node* temp = NULL;
				if (ptr->GetValue() == __MAX__)
					temp = ptr;
				ptr = ptr->GetParent();
				if (temp) temp->Delete();
			}
			break;
		case '-' :
			ptr->SetSign();
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			ptr->SetValue(int(c - '0'));
			break;
		}
		cin >> c;
	}
}

void Tree::BinaryTower(Node* n, int& _r)
{
	if (n == NULL) return;

	if (n->GetLeft()) BinaryTower(n->GetLeft(), _r);
	if (n->GetRight()) BinaryTower(n->GetRight(), _r);

	if (n == root)
	{
		if(!n->isDefended())
			n->InstallTower(_r);
	}
	else
	{
		if (n->GetLeft() && n->GetRight()) //two children
		{
			if (!n->GetLeft()->isDefended() || !n->GetRight()->isDefended())
				n->InstallTower(_r);
		}
		else if (!n->GetLeft() && n->GetRight()) //only right child
		{
			if (!n->GetRight()->isDefended())
				n->InstallTower(_r);
		}
		else if (n->GetLeft() && !n->GetRight()) //only left child
		{
			if (!n->GetLeft()->isDefended())
				n->InstallTower(_r);
		}
		else if (n->isLeaf()) //leaf
			return;
		
	}
}
void Tree::deleteLeaves(Node* n)
{
	if (n == NULL) return;

	if (n->isLeaf())
	{
		n->Delete();
		return;
	}

	if(n->GetLeft()) deleteLeaves(n->GetLeft());
	if(n->GetRight()) deleteLeaves(n->GetRight());
}
bool Tree::Symmetric(Node *a, Node *b)
{
	if (a == NULL && b == NULL) return true;
	else if (a != NULL && b != NULL) 
		return Symmetric(a->GetLeft(), b->GetRight()) && Symmetric(a->GetRight(), b->GetLeft());
	else if (a == NULL || b == NULL) return false;
	return false;
}

int main()
{
	while (true)
	{
		Tree t;
		t.Insert();

		string input;

		while (true)
		{
			cin >> input;
			if (input == "Traverse") t.Traverse();
			else if (input == "Height")  t.Height();
			else if (input == "WeightSum") t.WeightSum();
			else if (input == "MaximumPathSum") t.MaxPathSum();
			else if (input == "BinaryTower") t.BinaryTower();
			else if (input == "Foldable")
			{
				if (t.isFoldable())
					cout << "Yes" << endl;
				else
					cout << "No" << endl;
			}
			else if (input == "DeleteLeaf") t.DeleteLeaves();
			else if (input == "End") break;
			else continue;
		}
		if (cin.eof())
			break;
	}

	return 0;
}