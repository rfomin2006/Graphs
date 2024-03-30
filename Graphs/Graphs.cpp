#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

extern "C" {
    int _sum(int, int);
    int _sub(int, int);
    int _mult(int, int);
    void _print(const char*);
}

int menu();
void cprint(std::string str);
struct Graph
{
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> vertexes;

    void addVertex(std::string name) {
        if (vertexes.find(name) == vertexes.end())
        {
            vertexes[name] = std::vector<std::pair<std::string, int>>();
        }
    }

    void addEdge(std::string from, std::string to, int length) {
        vertexes[from].push_back(std::make_pair(to, length));
        vertexes[to].push_back(std::make_pair(from, length));
    }

    void printGraph() {
        for (auto const &vertex : vertexes)
        {
            cprint(vertex.first + " ");
            for (auto const& edge : vertex.second) {
                cprint(" -> " + edge.first + " (" + std::to_string(edge.second) + ")");
            }
            cprint("\n");
        }
    }

    std::vector<std::vector<std::string>> findAllPaths(std::string from, std::string to) {
        std::vector<std::vector<std::string>> allPaths;
        std::vector<std::string> currentPath = { from };
        std::stack<std::pair<std::string, std::vector<std::string>>> stack;
        stack.push({ from, currentPath });

        while (!stack.empty())
        {
            std::string vertex = stack.top().first;
            std::vector<std::string> path = stack.top().second;
            stack.pop();

            if (vertex == to) {
                allPaths.push_back(path);
            }
            else
            {
                for (auto const& edge : vertexes[vertex]) {
                    if (std::find(path.begin(), path.end(), edge.first) == path.end()) {
                        std::vector<std::string> newPath = path;
                        newPath.push_back(edge.first);
                        stack.push({ edge.first, newPath });
                    }
                }
            }
        }
        return allPaths;
    }

    void getAllPathLengths(std::string from, std::string to) {
        std::vector<std::vector<std::string>> paths = findAllPaths(from, to);
        std::vector<int> pathLengths;
        for (auto const& path : paths) {
            int pathLength = 0;
            std::string pathName = "";
            for (int i = 0; i < _sub(path.size(), 1); i++) {
                pathName += path[i] + " -> ";
                for (auto const& edge : vertexes[path[i]]) {
                    if (edge.first == path[_sum(i, 1)]) {
                        pathLength = _sum(pathLength, edge.second);
                        break;
                    }
                }
            }
            pathName += to;
            cprint(pathName + " (" + std::to_string(pathLength) + ")\n");
            pathLengths.push_back(pathLength);
        }
    }
};

int main()
{
    Graph g;
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
        cprint("\n");
        g.printGraph();
        cprint("\n");
        goto menuLabel;
        break;
    case 2:
        cprint("\nEnter vertex name: ");
        std::cin >> name;
        g.addVertex(name);
        cprint("\n");
        goto menuLabel;
        break;
    case 3:
        cprint("\nEnter first vertex: ");
        std::cin >> from;
        cprint("\nEnter second vertex: ");
        std::cin >> to;
        cprint("\nEnter edge length: ");
        std::cin >> length;
        g.addEdge(from, to, length);
        goto menuLabel;
        break;
    case 4:
        cprint("\nEnter first vertex: ");
        std::cin >> from;
        cprint("\nEnter second vertex: ");
        std::cin >> to;
        cprint("\n");
        g.getAllPathLengths(from, to);
        cprint("\n");
        goto menuLabel;
        break;
    case 5:
        break;
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