#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

using Points = vector<pair<int, int>>;
using Graph = vector<map<int, int>>;

vector<int> sortedIndices(Points &points, bool dim)
{
    vector<int> indices(points.size());
    iota(indices.begin(), indices.end(), 0);

    sort(indices.begin(), indices.end(),
              [&](int a, int b)
              {
                  return !dim ? points[a].first < points[b].first : points[a].second < points[b].second;
              });

    return indices;
}

void updateGraph(Graph &graph, const int a, const int b, const int dist, const bool ensureKeyNonExists = false)
{
    if (ensureKeyNonExists || graph[a].count(b) == 0)
    {
        graph[a][b] = dist;
        graph[b][a] = dist;
    }
    else
    {
        graph[a][b] = min(graph[a][b], dist);
        graph[b][a] = min(graph[b][a], dist);
    }
}

Graph buildGraph(Points &points)
{
    vector<int> pointIndicesSortedByX = sortedIndices(points, false);
    vector<int> pointIndicesSortedByY = sortedIndices(points, true);

    Graph graph(points.size());

    int pointAIndex = pointIndicesSortedByX[0];
    pair pointA = points[pointAIndex];

    for (int i = 1; i < pointIndicesSortedByX.size(); i++)
    {
        int pointBIndex = pointIndicesSortedByX[i];
        pair pointB = points[pointBIndex];

        int dist = abs(pointA.first - pointB.first);

        updateGraph(graph, pointAIndex, pointBIndex, dist, true);

        pointAIndex = pointBIndex;
        pointA = pointB;
    }

    pointAIndex = pointIndicesSortedByY[0];
    pointA = points[pointAIndex];

    for (int i = 1; i < pointIndicesSortedByY.size(); i++)
    {
        int pointBIndex = pointIndicesSortedByY[i];
        pair pointB = points[pointBIndex];

        int dist = abs(pointA.second - pointB.second);

        updateGraph(graph, pointAIndex, pointBIndex, dist, false);

        pointAIndex = pointBIndex;
        pointA = pointB;
    }

    return graph;
}

vector<int> dijkstra(const Graph &graph, int start, int target = -1)
{
    int n = graph.size();
    vector<int> distances(n, numeric_limits<int>::max());
    distances[start] = 0;

    using NodeDist = pair<int, int>;
    priority_queue<NodeDist, vector<NodeDist>, greater<>> pq;
    pq.push({start, 0});

    while (!pq.empty())
    {
        auto [currentNode, currentDistance] = pq.top();
        pq.pop();

        if (currentDistance > distances[currentNode])
        {
            continue;
        }

        if (currentNode == target)
        {
            break;
        }

        for (const auto &[neighbor, weight] : graph[currentNode])
        {
            int newDistance = currentDistance + weight;
            if (newDistance < distances[neighbor])
            {
                distances[neighbor] = newDistance;
                pq.push({neighbor, newDistance});
            }
        }
    }

    return distances;
}

/*
5
2 2
1 1
4 5
7 1
6 7
*/
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int nPoints;
    cin >> nPoints;

    Points points(nPoints);
    for (int i = 0; i < nPoints; i++)
    {
        int x, y;
        cin >> x >> y;

        points[i] = pair(x, y);
    }

    Graph graph = buildGraph(points);
    int minDist = dijkstra(graph, 0, nPoints - 1)[nPoints - 1];

    cout << minDist << endl;

    return 0;
}
