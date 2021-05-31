#include <iostream>

#define u_size 100
#define v_size 100
#define airlines_size 10

class airport {
public:

	airport() {
		cost = 0;
		Fill();
	}
	void Add(int start, int destination, int cost, int air);
	void Delete(int u, int v, int airline);
	void Request(int start, int destination, int constraint);
	void Fill() {
		for (int i = 0; i < u_size; i++) {
			for (int j = 0; j < v_size; j++)
				for (int k = 0; k < airlines_size; k++)
					flights[i][j][k] = 0;
		}
	}

	int MinCost(int dist[], bool visited[]);
	int dijkstra(int flights[u_size][v_size][airlines_size], int start, int destination);

private:
	int flights[100][100][10]; //[destination][Airlines]
	int cost;
};


void airport::Add(int s, int d, int p, int air) {
	flights[s][d][air - 1] = p;
	flights[d][s][air - 1] = p;
}

void airport::Request(int start, int destination, int constraint) {
	int price = dijkstra(flights, start, destination);

	if (price <= constraint) {
		std::cout << price << std::endl;
	}
	else {
		std::cout << -1 << std::endl;
	}
}

void airport::Delete(int u, int v, int airline) {
	//  for(int i=0; i<u_size;i++)
		 // for(int j = 0; i<u_size; j++)
	flights[u][v][airline] = 0;
}

int airport::MinCost(int dist[], bool visited[]) {
	int min = INT_MAX; //infinite
	int index = 0;

	for (int i = 0; i < u_size; i++) {
		if (visited[i] == false && dist[i] <= min)
		{
			min = dist[i];
			index = i;
		}
	}

	return index; //vertex with minimum cost
}

int airport::dijkstra(int flights[u_size][v_size][airlines_size], int start, int destination) {
	int dist[u_size];
	bool visited[u_size];
	int airline[u_size];

	for (int i = 0; i < u_size; ++i)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
		airline[i] = -1;
	}

	dist[start] = 0; //this is the starting point

	for (int k = 0; k < u_size - 1; ++k)
	{
		int u = MinCost(dist, visited);
		visited[u] = true; // for first case
		for (int v = 0; v < v_size; v++) {
			for (int ar = 0; ar < airlines_size; ar++) {
				if ((!visited[v] && flights[u][v][ar] && dist[u] != INT_MAX)) {
					if (dist[u] + flights[u][v][ar] < dist[v] && airline[u] == ar) { //same airline
						dist[v] = dist[u] + flights[u][v][ar];
						//   cout<<"ar "<<ar<<endl;
						   //transfer = ar;
						 //  cout<<"U2 "<<dist[u]<<" flight "<<flights[u][v][ar]<<endl;
					}if ((airline[v] != ar && airline[v] != -1) && (dist[u] + flights[u][v][ar] + 5 < dist[u] + flights[u][v][airline[v]]) && dist[u] + flights[u][v][ar] + 5 < dist[v]) { //transferring
						dist[v] = dist[u] + flights[u][v][ar] + 5;
						//    cout<<"ar "<<ar<<endl;
						airline[v] = ar;
						//     cout<<"U "<<dist[u]<<" flight "<<flights[u][v][ar]<<endl;
						 //   cout<<"DV "<<dist[v]<<endl;
					}
					else if (dist[u] + flights[u][v][ar] < dist[v] && airline[v] == -1) { //first case
						dist[v] = dist[u] + flights[u][v][ar];
						//   cout<<"ar "<<ar<<endl;
						airline[v] = ar;
						/*   cout<<"UT "<<dist[u]<<" flight "<<flights[u][v][ar]<<endl;
						   cout<<"DV "<<dist[v]<<endl;*/
					}
					else if ((airline[v] != ar && airline[v] != -1) && (dist[u] + flights[u][v][ar] + 5 < dist[v])) { //when there is no other alternative
						dist[v] = dist[u] + flights[u][v][ar] + 5;
						//   cout<<"ar "<<ar<<endl;
						airline[v] = ar;
						/*      cout<<"U3 "<<dist[u]<<" flight "<<flights[u][v][ar]<<endl;
							  cout<<"DV "<<dist[v]<<endl;*/
					}
				}
			}
		}
	}

	return dist[destination];

}

int main()
{
	airport a;

	/*a.Add(0,1,4,1);
	a.Add(1,2,8,0);
	a.Add(1,2,5,1);
	a.Add(3,2,45,0);
	a.Add(0,1,4,0);
	a.Add(1,2,8,0);
	a.Add(1,2,5,1);
	a.Add(3,2,45,0);
	a.Add(0,1,4,0);
	a.Add(1,2,15,1);
	a.Add(1,2,10,2);*/
	//a.cal(0);

	char* input = new char[8];
	while (std::cin >> input) {

		if (input == "Add") {
			int st, dest, p, ar;
			std::cin >> st >> dest >> p >> ar;
			a.Add(st, dest, p, ar);
		}
		else if (input == "Request") {
			int st, dest, p;
			std::cin >> st >> dest >> p;
			a.Request(st, dest, p);
		}
		else if (input == "Delete") {
			int u, v, ar;
			std::cin >> u >> v >> ar;
			a.Delete(u, v, ar);
		}
		else {
			continue;
		}
	}
	return 0;
}

