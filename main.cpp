/* 
 * File:   main.cpp
 * Author: artur
 *
 * Created on 28 kwiecień 2012, 15:48
 */

#include <cstdlib>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

const int infty = 1000000000; // limit
int verticesNum;
int edgesNum;
vector< vector< pair<int, int> > > comparisionMatrix;
vector<int> pathWeight;

struct cmp // warunek kopca
{
    // czy a jest mniejsze od b

    bool operator() (const int &a, const int &b) {
        if (pathWeight[a] < pathWeight[b]) return true;
        if (pathWeight[a] > pathWeight[b]) return false;
        return a<b;
    }
};

set<int, cmp> kopiec; // ;-)

void prim_dijkstra(int s) //s punkt startowy
{
    int v, u, c;

    pathWeight.clear();
    pathWeight.resize(verticesNum, infty);
    pathWeight[s] = 0;

    kopiec.clear();
    for (int i = 0; i < verticesNum; i++) { //wrzucam wierzchołki do kopca
        kopiec.insert(i);
    }

    while (!kopiec.empty()) //przechodzimy kopiec do skutku
    {
        u = *(kopiec.begin()); // weź wierzchołek najbliżej drzewa MST
        kopiec.erase(kopiec.begin());

        for (int i = 0; i < comparisionMatrix[u].size(); i++) //połączenia danego wierzchołka i koszty
        {
            v = comparisionMatrix[u][i].first;

            c = comparisionMatrix[u][i].second;
            if (pathWeight[u] + c < pathWeight[v]) // w alg. Prima jest tutaj c < pathWeight[v]
            {
                // uaktualniamy wagę wierzchołka v - poprawnośc przez indukcję, dla co raz większego drzewa mst wybieramy krawędzie o najmiejszej wadze
                kopiec.erase(kopiec.find(v));
                pathWeight[v] = pathWeight[u] + c; // w alg. Prima jest tutaj pathWeight[v] = c ;
                kopiec.insert(v);
                //	mstClosingVertices[v] = u; // domykam krawędź
            }
          
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    int a, b, c, s, g;
    FILE *input = fopen("graph.txt", "r+");
    fscanf(input, "%d %d", &verticesNum, &edgesNum);
    comparisionMatrix.resize(verticesNum); // pierwsze krawędzie po kolei

    bool directed = false;
    fscanf(input, "%d", &directed);
    for (int i = 0; i < edgesNum; i++) {
        fscanf(input, "%d %d %d", &a, &b, &c); // c = koszt krawędzi od a do b
        comparisionMatrix[a].push_back(make_pair(b, c)); // skierowany nie skierowany 
        if(!directed)
        comparisionMatrix[b].push_back(make_pair(a, c)); //
    }
    
    
    fscanf(input, "%d %d", &s, &g); // sTART gOAL
    prim_dijkstra(s); // true skierowany false nie skierowany

    printf("[DIJKSTRA]\nKoszt minimalnej ścieżki od %d do %d w grafie %s wynosi %d\n", s, g, (directed)?"skierowanym":"nie skierowanym", pathWeight[g]); // index 5 czyli v nr 6
    printf("Najkrótsze ścieżki do innych wierzchołków od %d:\n", s);
    for (int i = 0; i < verticesNum; i++) // specjalnie pomijam wierzhołek nr 0
        printf("do: %d -- [Koszt %d]\n", i, pathWeight[i]);
    return 0;
}

