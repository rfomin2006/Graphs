#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <map>

extern "C" {
    int _sum(int, int);
    int _sub(int, int);
    int _mult(int, int);
    void _print(const char*);
}

struct Edge;

struct Vertex {
    std::string name;
    std::vector<Edge> edges;
};

struct Edge {
    int len;
    Vertex* from = nullptr;
    Vertex* to = nullptr;
};

struct Graph {
    std::vector<Vertex> vertexes;
    std::vector<Edge> edges;

    void addVertex(std::string name) {
        Vertex v = Vertex{ name };
        vertexes.push_back(v);
    }

    Vertex getOrCreateVertex(std::string name) {
        for (Vertex v : vertexes) {
            if (v.name == name) return v;
        }
        _print("Not found, created new");
        return Vertex{ name };
    }



};

int main()
{
    Graph graph;
    graph.addVertex("Moscow");
    graph.addVertex("Piter");

    char* name1 = new char[graph.getOrCreateVertex("Moscow").name.length() + 1];
    std::strcpy(name1, graph.getOrCreateVertex("Moscow").name.c_str());
    _print(name1);
    _print("\n");
    char* name2 = new char[graph.getOrCreateVertex("Piter").name.length() + 1];
    std::strcpy(name2, graph.getOrCreateVertex("Piter").name.c_str());
    _print(name2);

    return 0;
}