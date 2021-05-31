#include <iostream>
#include <cstring>

class Node;
class NodeX;
class NodeY;
class Person
{
public:
	enum Status
	{
		HEALTHY,
		SICK,
		MASK,
		inICU,
		DEAD,
	};
	int posX;
	int posY;
	Person* nextX;
	Person* postX;
	Person* nextY;
	Person* postY;
	Person* nextOrd;
	Person(int _posX, int _posY, char* _name, Status _stat)
	{
		strcpy_s(name, _name);
		posX = _posX;
		posY = _posY;
		stat = _stat;
		surround_c = 0;
		surround_day = 0;
		recovery_c = 0;
		if (stat == SICK)
			recovery_day = 14;
		else
			recovery_day = 0;
		nextX = NULL;
		postX = NULL;
		nextY = NULL;
		postY = NULL;
		nextOrd = NULL;
	}
	void Effect()
	{
		if (stat == HEALTHY)
		{
			if (postX && (posX - (postX->posX) == 1) && (postX->stat == SICK))
			{
				surround_c++;
				injPostX = true;
			}
			if (nextX && ((nextX->posX) - posX == 1) && (nextX->stat == SICK))
			{
				surround_c++;
				injNextX = true;
			}
			if (postY && (posY - (postY->posY) == 1) && (postY->stat == SICK))
			{
				surround_c++;
				injPostY = true;
			}
			if (nextY && ((nextY->posY) - posY == 1) && (nextY->stat == SICK))
			{
				surround_c++;
				injNextY = true;
			}
		}
		if (stat == SICK)
		{
			if (postX && (posX - (postX->posX) == 1) && postX->stat == SICK)
			{
				surround_c++;
				if (!injPostX)
				{
					recovery_c++;
					injPostX = true;
				}
			}
			if (nextX && ((nextX->posX) - posX == 1) && nextX->stat == SICK)
			{
				surround_c++;
				if (!injNextX)
				{
					recovery_c++;
					injNextX = true;
				}
			}
			if (postY && (posY - (postY->posY) == 1) && postY->stat == SICK)
			{
				surround_c++;
				if (!injPostY)
				{
					recovery_c++;
					injPostY = true;
				}
			}
			if (nextY && ((nextY->posY) - posY == 1) && nextY->stat == SICK)
			{
				surround_c++;
				if (!injNextY)
				{
					recovery_c++;
					injNextY = true;
				}
			}
		}
	}
	void React(int& _icu, int& _death)
	{
		switch (stat)
		{
		case HEALTHY:
			if (surround_c > 0)
				GetSick(surround_c);
			if (recovery_day > 28)
			{
				if (_icu > 0)
				{
					stat = inICU;
					_icu--;
				}
			}
			break;
		case SICK:
			recovery_day--;
			if (recovery_day == 0)
			{
				Recover();
				break;
			}
			recovery_day += recovery_c * 7;
			if (recovery_day > 28)
			{
				if (_icu > 0)
				{
					stat = inICU;
					_icu--;
				}
			}
			if (surround_c > 3)
				surround_day++;
			if (surround_day > 7)
			{
				recovery_day = 0;
				stat = DEAD;
				_death++;
				break;
			}
			break;
		default:
			break;
		}
		surround_c = 0;
		recovery_c = 0;
	}
	void PrintName(bool &_f)
	{
		switch (stat)
		{
		case HEALTHY:
		case SICK:
		case MASK:
			std::cout << name;
			_f = true;
			break;
		default:
			break;
		}
	}
private:
	char name[30];
	Status stat;
	int surround_day;
	int surround_c;
	int recovery_day;
	int recovery_c;
	bool injNextX;
	bool injNextY;
	bool injPostX;
	bool injPostY;
	void Recover()
	{
		stat = HEALTHY;
		surround_day = 0;
		recovery_day = 0;
		injNextX = false;
		injNextY = false;
		injPostX = false;
		injPostY = false;
		if (postX && (posX - (postX->posX) == 1) && (postX->injNextX))
			postX->injNextX = false;
		if (nextX && ((nextX->posX) - posX == 1) && (nextX->injPostX))
			nextX->injPostX = false;
		if (postY && (posY - (postY->posY) == 1) && (postY->injNextY))
			postY->injNextY = false;
		if (nextY && ((nextY->posY) - posY == 1) && (nextY->injPostY))
			nextY->injPostY = false;
	}
	void GetSick(int _c)
	{
		stat = SICK;
		recovery_day = 14 + _c * 7;
	}
};

class NodeX
{
	friend Node;
private:
	int idx;
	NodeX* next;
	Person* first;
	void Insert(Person* _new, Person* _p)
	{
		_new->nextY = _p->nextY;
		_p->nextY->postY = _new;
		_p->nextY = _new;
		_new->postY = _p;
	}
	void InsertLast(Person* _new, Person* _p)
	{
		_p->nextY = _new;
		_new->postY = _p;
	}
public:
	NodeX(int i)
	{
		idx = i;
		next = NULL;
		first = NULL;
	}
	void Insert(Person* _new)
	{
		if (first)
		{
			Person* temp = first;

			if (_new->posY < temp->posY)
			{
				temp->postY = _new;
				_new->nextY = temp;
				first = _new;
				return;
			}
			while (true)
			{
				if (!(temp->nextY))
				{
					InsertLast(_new, temp);
					break;
				}
				else if (_new->posY < temp->nextY->posY)
				{
					Insert(_new, temp);
					break;
				}
				else
					temp = temp->nextY;
			}
		}
		else
			first = _new;
	}
};
class NodeY
{
	friend Node;
private:
	int idx;
	NodeY* next;
	Person* first;
	void Insert(Person* _new, Person* _p)
	{
		_new->nextX = _p->nextX;
		_p->nextX->postX = _new;
		_p->nextX = _new;
		_new->postX = _p;
	}
	void InsertLast(Person* _new, Person* _p)
	{
		_p->nextX = _new;
		_new->postX = _p;
	}
public:
	NodeY(int i)
	{
		idx = i;
		next = NULL;
		first = NULL;
	}
	void Insert(Person* _new)
	{
		if (first)
		{
			Person* temp = first;

			if (_new->posX < temp->posX)
			{
				temp->postX = _new;
				_new->nextX = temp;
				first = _new;
				return;
			}
			while (true)
			{
				if (!(temp->nextX))
				{
					InsertLast(_new, temp);
					break;
				}
				else if (_new->posX < temp->nextX->posX)
				{
					Insert(_new, temp);
					break;
				}
				else
					temp = temp->nextX;
			}
		}
		else
			first = _new;
	}
};
class Node
{
private:
	NodeX* posX;
	NodeY* posY;
	Person* first;
	Person* last;
	int icu;
	int death;
	void InsertX(Person* _p)
	{
		if (posX)
		{
			NodeX* tempX = posX;
			if (_p->posX < tempX->idx)
			{
				NodeX* newX = new NodeX(_p->posX);
				newX->next = tempX;
				posX = newX;
				newX->Insert(_p);
				return;
			}
			while (true)
			{
				if (_p->posX == tempX->idx)
				{
					tempX->Insert(_p);
					return;
				}
				else if ((tempX->next) == NULL)
				{
					NodeX* newX = new NodeX(_p->posX);
					tempX->next = newX;
					newX->Insert(_p);
					return;
				}
				else if (_p->posX < tempX->next->idx)
				{
					NodeX* newX = new NodeX(_p->posX);
					newX->next = tempX->next;
					tempX->next = newX;
					newX->Insert(_p);
					return;
				}
				else
					tempX = tempX->next;
			}
		}
		else
		{
			NodeX* tempX = new NodeX(_p->posX);
			posX = tempX;
			tempX->Insert(_p);
			return;
		}
	}
	void InsertY(Person* _p)
	{
		if (posY)
		{
			NodeY* tempY = posY;
			if (_p->posY < tempY->idx)
			{
				NodeY* newY = new NodeY(_p->posY);
				newY->next = tempY;
				posY = newY;
				newY->Insert(_p);
				return;
			}
			while (true)
			{
				if (_p->posY == tempY->idx)
				{
					tempY->Insert(_p);
					return;
				}
				else if ((tempY->next) == NULL)
				{
					NodeY* newY = new NodeY(_p->posY);
					tempY->next = newY;
					newY->Insert(_p);
					return;
				}
				else if (_p->posY < tempY->next->idx)
				{
					NodeY* newY = new NodeY(_p->posY);
					newY->next = tempY->next;
					tempY->next = newY;
					newY->Insert(_p);
					return;
				}
				else
					tempY = tempY->next;
			}
		}
		else
		{
			NodeY* tempY = new NodeY(_p->posY);
			posY = tempY;
			tempY->Insert(_p);
			return;
		}
	}
	void SimulateEffect()
	{
		if (first)
		{
			Person* temp = first;
			while (true)
			{
				temp->Effect();
				if (temp->nextOrd)
					temp = temp->nextOrd;
				else
					break;
			}
		}
		else
			return;
	}
	void SimulateReact()
	{
		if (first)
		{
			Person* temp = first;
			while (true)
			{
				temp->React(icu, death);
				if (temp->nextOrd)
					temp = temp->nextOrd;
				else
					break;
			}
		}
		else
			return;
	}
public:
	Node(int x, int y, int _icu)
	{
		posX = NULL;
		posY = NULL;
		first = NULL;
		last = NULL;
		icu = _icu;
		death = 0;
	}
	int GetDeath()
	{
		return death;
	}
	void Insert(Person* _p)
	{
		if (first)
		{
			last->nextOrd = _p;
			last = _p;
		}
		else
		{
			first = _p;
			last = _p;
		}
		InsertX(_p);
		InsertY(_p);
	}
	void Simulate()
	{
		SimulateEffect();
		SimulateReact();
	}
	void PrintResult()
	{
		bool flag = false;
		NodeX* tempX = posX;
		Person* temp;
		while (true)
		{
			temp = tempX->first;
			while (true)
			{
				temp->PrintName(flag);
				if (temp->nextY)
				{
					if (flag)
					{
						std::cout << ' ';
						flag = false;
					}
					temp = temp->nextY;
				}
				else
					break;
			}
			if (tempX->next)
			{
				tempX = tempX->next;
				if (flag)
				{
					std::cout << ' ';
					flag = false;
				}
			}
			else
				break;
		}
	}
};

int main()
{
	int r; int c; int icu_cap; int t;
	std::cin >> r >> c >> icu_cap >> t;
	Node world(r, c, icu_cap);

	int n;
	std::cin >> n;
	int* insertTime = new int[n];
	int* posX = new int[n];
	int* posY = new int[n];
	char** name = new char*[n];
	for (int i = 0; i < n; i++)
		name[i] = new char[30];

	Person::Status* stat = new Person::Status[n];
	for (int i = 0; i < n; i++)
	{
		char* temp = new char[10];
		std::cin >> insertTime[i] >> posX[i] >> posY[i] >> name[i] >> temp;
		if (strcmp(temp, "Healthy") == 0)
			stat[i] = Person::HEALTHY;
		if (strcmp(temp, "Sick") == 0)
			stat[i] = Person::SICK;
		if (strcmp(temp, "Masked") == 0)
			stat[i] = Person::MASK;
	}

	for (int d = 0; d <= t; d++)
	{
		world.Simulate();

		for (int i = 0; i < n; i++)
			if (insertTime[i] == d)
			{
				Person* _temp = new Person(posX[i], posY[i], name[i], stat[i]);
				world.Insert(_temp);
			}
	}
	double surv_rate = (double)(n - world.GetDeath()) / (double)n * 100; // int n, int GetDeath
	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << surv_rate << '%' << std::endl;
	world.PrintResult();
}