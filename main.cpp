#include <iostream>
#include <vector>
#include <utility>
#include "mersenne_twister.h"
#include <fstream>

using namespace std;

int random_seed = 1;
void finderRec(const std::vector<int>& path, const std::vector<std::vector<std::pair<int, int>>>& adj, int& count, const int& verticeNumber, const int& previousVertice, int& len) {
    for (int j = 0; j < adj.size(); ++j) {
        if (adj[verticeNumber][j].second == path[len] && (verticeNumber != adj[verticeNumber][j].first) && (adj[verticeNumber][j].first != previousVertice)) {
            len++;
            if (len < path.size())
                finderRec(path, adj, count, adj[verticeNumber][j].first, verticeNumber, len);
            else if (len == path.size())
                count++;
            else if (len > path.size())
                break;
        }
    }
}

int pathFinder(const std::vector<int>& path, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    int count = 0;
    int len = 0; // current chain length
    for (int i = 0; i <= adj.size()-1; ++i) 
        for (int j = 0; j <= adj.size()-1; ++j)
            if (adj[i][j].second == path[0]) {
                len++;
                finderRec(path, adj, count, adj[i][j].first, i, len);
                len = 0;
            }
    return count;
}

std::vector<std::vector<std::pair<int, int>>> generateGraph(const int& size, const vector<int>& labels) {
    std::vector<std::vector<std::pair<int, int>>> adj(size+1);
    int j = 0; // number of the vertex next to the vertex i.
    int len = labels.size() - 1; // length - 1 of vector labels 
    int wt;
    for (int i = 0; i <= size; ++i) {
        j = i + 1;
        while (j <= size) {
            CRandomMersenne randgen_three(random_seed+43);
            random_seed++;
            wt = labels[randgen_three.IRandom(0, len)];
            adj[i].push_back(std::make_pair(j, wt));
            adj[j].push_back(std::make_pair(i, wt));
            j++;
        }
    }
    return adj;
}

void printGraph(const std::vector<std::vector<std::pair<int, int>>>& adj, const int& size){
    for (int i = 0; i <= size; ++i) 
        for (const auto u : adj[i]) 
            std::cout << i << " " << u.first << " " << u.second << "\n";  
}

int main()
{
	std::cout << "Hello, World!\n";
    int size = 20;
    int m = 500;
    std::vector<int> labels{1,2}; // set of labels
    std::vector<int> path{1,1,1,1}; // paths we are looking for
    std::ofstream out;// поток для записи
    out.open("MonteCarlo.txt"); // окрываем файл для записи
    if (out.is_open())
        for (int i = 0; i < m; ++i) {
            std::vector<std::vector<std::pair<int, int>>> adj = generateGraph(size, labels);
            out << pathFinder(path, adj) << " ";
        }
    cout << "done!" << endl;
    return 0;
}
