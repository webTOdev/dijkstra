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
vector< vector< pair<int, double> > > comparisionMatrix;
vector<double> pathWeight;

struct cmp // the condition of the mound
{
    // if a is smaller than b

    bool operator() (const int &a, const int &b) {
        if (pathWeight[a] < pathWeight[b]) return true;
        if (pathWeight[a] > pathWeight[b]) return false;
        return a<b;
    }
};

set<int, cmp> kopiec; // ;-)

void prim_dijkstra(int s) //s starting point
{
    int v, u;
    double c;

    pathWeight.clear();
    pathWeight.resize(verticesNum, infty);
    pathWeight[s] = 0;

    kopiec.clear();
    for (int i = 0; i < verticesNum; i++) { //throw vertices, k to the mound
        kopiec.insert(i);
    }

    while (!kopiec.empty()) //go to the mound effect
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
    int a, b, s, g;
    double c;
    FILE *input = fopen("graph.txt", "r+");
    fscanf(input, "%d %d", &verticesNum, &edgesNum);
    comparisionMatrix.resize(verticesNum); // first edge � will turn

    bool directed = false;
    fscanf(input, "%d", &directed);
    for (int i = 0; i < edgesNum; i++) {
        fscanf(input, "%d %d %lf", &a, &b, &c); // c = Cost edge from a to b
        printf("input, %d to %d cost %lf\n", a, b, c);

        comparisionMatrix[a].push_back(make_pair(b, c)); // directed not addressed
        if(!directed)
        comparisionMatrix[b].push_back(make_pair(a, c)); //
    }
    
    
    fscanf(input, "%d %d", &s, &g); // sTART gOAL
    prim_dijkstra(s); // true false targets not addressed

    printf("[DIJKSTRA]\nThe cost of the minimum path from %d to %d  %s is %lf\n", s, g, (directed)?"directed":"not directed", pathWeight[g]); // index 5 czyli v nr 6
    printf("The shortest and hottest path-to other vertices, Efforts of %d:\n", s);
    for (int i = 0; i < verticesNum; i++) // specjalnie pomijam wierzhołek nr 0
        printf("to: %d -- [Cost %lf]\n", i, pathWeight[i]);
    return 0;
}

