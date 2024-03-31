#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <vector>
#include <stack>

extern "C" {
    int _sum(int, int);
    int _sub(int, int);
    int _mult(int, int);
    void _print(const char*);
}

int menu();
void cprint(std::string str);
struct Edge {
    std::string from;
    std::string to;
    int length;
};
struct Vertex {
    std::string name;
    std::vector<Edge> edges;
};
class Graph {
public:
    std::vector<Vertex> vertexes;

    void addVertex(std::string name) {
        vertexes.push_back({ name, {} });
    }

    void addEdge(std::string from, std::string to, int length) {
        Vertex* v1 = findVertex(from);
        Vertex* v2 = findVertex(to);
        v1->edges.push_back({from, to, length});
        v2->edges.push_back({to, from, length});
    }

    void printGraph() {
        for (Vertex& vertex : vertexes) {
            cprint(vertex.name + ": ");
            for (Edge& e : vertex.edges) {
                cprint(e.to + " (" + std::to_string(e.length) + "), ");
            }
            cprint("\n");
        }
    }

    void findAllPaths(std::string from, std::string to) {
        std::vector<Edge> currentPath;
        std::vector<bool> visited(vertexes.size(), false);
        int currentLength = 0;
        DFS(from, to, currentPath, currentLength, visited);
    }

private:
    Vertex* findVertex(std::string name) {
        for (auto &v : vertexes) {
            if (v.name == name) return &v;
        }
        return nullptr;
    }
    
    void DFS(std::string current, std::string target, std::vector<Edge>& currentPath, int currentLength, std::vector<bool>& visited) {
        visited[getIndex(current)] = true;
        currentPath.push_back({ current, current, 0 });

        if (current == target) {
            printPath(currentPath, currentLength);
        }

        for (Edge& edge : findVertex(current)->edges) {
            if (!visited[getIndex(edge.to)]) {
                currentLength += edge.length;
                DFS(edge.to, target, currentPath, currentLength, visited);
                currentLength -= edge.length;
            }
        }

        visited[getIndex(current)] = false;
        currentPath.pop_back();
    }

    int getIndex(std::string name) {
        for (size_t i = 0; i < vertexes.size(); i++) {
            if (vertexes[i].name == name) {
                return i;
            }
        }
        return -1;
    }

    void printPath(std::vector<Edge>& path, int length) {
        std::cout << "Path: ";
        for (Edge& edge : path) {
            cprint(edge.from + " -> ");
        }
        cprint("Length: " + std::to_string(length) + "\n");
    }
};

int main()
{
    std::vector<std::pair<std::vector<Edge>, int>> paths;
    Graph g = Graph();
    int choice;
    std::string name;
    std::string from;
    std::string to;
    int length;
    menuLabel:
        choice = menu();
    switch (choice)
    {
    case 1:
    {
        cprint("\n");
        g.printGraph();
        cprint("\n");
        goto menuLabel;
        break;
    }
    case 2:
    {
        cprint("\nEnter vertex name: ");
        std::cin >> name;
        g.addVertex(name);
        cprint("\n");
        goto menuLabel;
        break;
    }
    case 3:
    {
        cprint("\nEnter first vertex: ");
        std::cin >> from;
        cprint("\nEnter second vertex: ");
        std::cin >> to;
        cprint("\nEnter edge length: ");
        std::cin >> length;
        g.addEdge(from, to, length);
        goto menuLabel;
        break;
    }
    case 4:
    {
        cprint("\nEnter first vertex: ");
        std::cin >> from;
        cprint("\nEnter second vertex: ");
        std::cin >> to;
        cprint("\n");
        g.findAllPaths(from, to);
        cprint("\n");
        goto menuLabel;
        break;
    }
    case 5:
    {
        break;
    }
    }

    return 0;
}

int menu() {
    int choice;
    cprint("Menu:\n"
           "  1.Print graph\n"
           "  2.Add vertex\n"
           "  3.Add edge\n"
           "  4.Find all paths with lengths from A to B\n"
           "  5.Exit\n\n"
           "  Choice: ");
    std::cin >> choice;
    return choice;
}

void cprint(std::string str) {
    char* chars = new char[str.length() + 1];
    std::strcpy(chars, str.c_str());
    _print(chars);
    delete[] chars;
}