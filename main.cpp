#include <iostream>
#include <vector>
#include <tuple>

std::vector<int> path{1,2,3,4}; // paths we are looking for

void finderRec(std::vector<std::tuple<int,int,int>>& edges, int& p, int k, int& TotalNumber){
    for (int i = 0; i < edges.size(); ++i){
        if (std::get<2>(edges[i]) == path[k] && (p == std::get<0>(edges[i]) || p == std::get<1>(edges[i]))){
            if (p == std::get<0>(edges[i]) && k + 1 < path.size())
                finderRec(edges, std::get<1>(edges[i]), k + 1, TotalNumber);
            else if (p == std::get<1>(edges[i]) && k + 1 < path.size())
                finderRec(edges, std::get<0>(edges[i]), k + 1, TotalNumber);
            else
                TotalNumber++;
        }
    }
}

int pathFinder(std::vector<int>& path, std::vector<std::tuple<int,int,int>>& edges){
    int TotalNumber = 0;
    for (auto& x: edges)
        if (std::get<2>(x) == path[0]){
            finderRec(edges, std::get<0>(x), 1, TotalNumber);
            finderRec(edges, std::get<1>(x), 1, TotalNumber);
            }
    return TotalNumber;
}

std::vector<std::tuple<int,int,int>> generateGraph(int& n, std::vector<int>& W){
    std::vector<std::tuple<int,int,int>> edges;
    int m = (n * (n - 1)) / 2; // number of edges in a complete graph
    int j = 0; // number of the vertex next to the vertex i
    int random;
    int len = W.size(); // length of vector W
    int sel_elem;
    for (int i = 1; i <= n; ++i){
        j = i + 1;
        while (j <= n){
            random = rand() % len;
            sel_elem = W[random];
            edges.push_back({i,j,sel_elem});
            j++;
        }
    }
    return edges;
}

int main(){
    std::cout << "Hello, World!" << "\n";
    int n; // number of vertices
    std::cout << "Input the number of vertices n: ";
    std::cin >> n;
    std::vector<int> W{1,2,3,4,5}; // set of labels
    //std::cout << "Input the desired set of labels W ";
    //std::vector<int> path{1,2,3}; // paths we are looking for
    std::vector<std::tuple<int,int,int>> edges = generateGraph(n, W);
    //for (auto& x: edges)
      //cj  std::cout << std::get<2>(x) << " ";
    
    std::cout << "\n";
    std::cout << "Total number of paths = " <<  pathFinder(path, edges) << "\n";
    return 0;
}