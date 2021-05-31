#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

// reference to the code: Miguel Diaz in https://stackoverflow.com/questions/43759341/bron-kerbosch-algorithm-in-c
using namespace std;

class UndirectedGraph {
    map<int, vector<int>> vertices;
    int totalNodes = 0;
public:
    vector<int>best_clique;
    UndirectedGraph();
    void addVertice(const int& A, const int& B);
    void find(const int& u);
    void clique(vector<int> R, vector<int> P, vector<int> X);
    void compact();
};


UndirectedGraph::UndirectedGraph() = default;


void UndirectedGraph::addVertice(const int& A, const int& B) {
    vertices[A].push_back(B);
    vertices[B].push_back(A);
    totalNodes++;
}


void UndirectedGraph::clique(vector<int> R, vector<int> P, vector<int> X) {
    // Revisa si est? vac?s, lo que implicar? que hay un clique
    if (P.empty() && X.empty()) {
        //cout << "Clique found!" << endl;
        if (R.size() > best_clique.size()) {
            best_clique = R;
            cout << "R " << R.size() << "\n";
            //  for (const auto& it: R)
              //   cout << it << " " << endl;
        }
        return;
    }
    // He copies P in order to avoid problems with iterator.
    vector<int> pCopy(P);
    for (const auto& v : pCopy) {
        vector<int> unionSet;
        vector<int> intersectionSetPNv;
        vector<int> intersectionSetXNv;
        vector<int> neighborsP;
        vector<int> vVector = { v };
        // neighbors of P
        for (const auto& neighbors : vertices[v]) neighborsP.push_back(neighbors);
        // R Union {v}
        set_union(R.begin(), R.end(), vVector.begin(), vVector.end(), back_inserter(unionSet));
        // Intersection between P and N(v)
        set_intersection(P.begin(), P.end(), neighborsP.begin(), neighborsP.end(), back_inserter(intersectionSetPNv));
        set_intersection(X.begin(), X.end(), neighborsP.begin(), neighborsP.end(), back_inserter(intersectionSetXNv));
        clique(unionSet, intersectionSetPNv, intersectionSetXNv);
        vector<int> PminusV;
        vector<int> XunionV;
        // Obtains P - {v} y X Union {v}
        set_difference(P.begin(), P.end(), vVector.begin(), vVector.end(), inserter(PminusV, PminusV.begin()));
        set_union(X.begin(), X.end(), vVector.begin(), vVector.end(), back_inserter(XunionV));

        P = vector<int>(PminusV);
        X = vector<int>(XunionV);
    }


}

void UndirectedGraph::compact() {
    cout << "Compact" << endl;
}

ifstream infile("sample_input.txt");
ofstream outfile("cliques.txt");
int main(int argc, char* argv[])
{
    UndirectedGraph ug;
    int n, A, B, v;
    vector<int>P;
    //cin>>v;
    infile >> v;

    for (int i = 0; i < v; i++)
        P.push_back(i);
    //cin>>n;
    infile >> n;
    while (n--) {
        infile >> A >> B;
        ug.addVertice(A, B);
    }

    vector<int> R = {};
    vector<int> X = {};
    ug.clique(R, P, X);
    for (const auto& it : ug.best_clique)
        outfile << it << "\n";

    return 0;
}
