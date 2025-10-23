#include <iostream>
#include <vector>
#include <queue>


using namespace std;
using Graph = vector<vector<int>>;

void printSolution(const vector<int> &sol) {
    cout << sol.size() << endl;

    for (size_t i = 0; i < sol.size(); ++i) {
        cout << sol[i] + 1;
        if (i < sol.size() - 1) {
            cout << " ";
        }
    }
}

Graph readGraph(int numNodes) {
    Graph graph(numNodes);
    for (int i = 0; i < numNodes - 1; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    return graph;
}

vector<int> selectNodes(const Graph &graph, int maxDistance) {
    bool isOdd = maxDistance % 2;
    int numIterations = maxDistance / 2 + isOdd;

    vector<vector<int>> levels(numIterations);
    vector<bool> visited(graph.size(), false);
    vector<int> selected;
    queue<int> nodeQueue;

    for (int currLevel = 0; currLevel < numIterations; ++currLevel) {
        if (currLevel == 0) {
            for (size_t node = 0; node < graph.size(); ++node) {
                if (graph[node].size() == 1) {
                    visited[node] = true;
                    levels[0].push_back(node);
                    nodeQueue.push(node);
                }
            }
            selected.insert(selected.end(), levels[0].begin(), levels[0].end());
        } else {
            int queueSize = nodeQueue.size();
            for (int i = 0; i < queueSize; ++i) {
                int currentNode = nodeQueue.front();
                nodeQueue.pop();
                for (int neighbor : graph[currentNode]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        levels[currLevel].push_back(neighbor);
                        nodeQueue.push(neighbor);
                    }
                }
            }
            if (currLevel == numIterations - 1 && isOdd) {
                selected.push_back(levels[currLevel][0] + 1);
            } else {
                selected.insert(selected.end(), levels[currLevel].begin(), levels[currLevel].end());
            }
        }
    }
    return selected;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int numNodes, maxDistance;
    cin >> numNodes >> maxDistance;

    Graph graph = readGraph(numNodes);
    vector<int> selectedNodes = selectNodes(graph, maxDistance);


    printSolution(selectedNodes);
    return 0;
}
