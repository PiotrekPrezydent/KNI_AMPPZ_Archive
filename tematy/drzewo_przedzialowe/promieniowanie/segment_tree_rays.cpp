//
// Created by adrian on 22.12.2024.
//


// UWAGA: Nie działa

#include <iostream>
#include <vector>
#include <climits>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

typedef pair<double, double> Pair;

vector<Pair> buildTree(const vector<double> &data, double target_min_len)
{
    int n = data.size();
    vector<Pair> tree(n * 2);

    for (int i = 0; i < n; i++)
    {
        double elongation_cost = max(0., target_min_len - data[i]);
        tree[i + n] = make_pair(data[i], elongation_cost);
    }
    for (int i = n - 1; i > 0; i--)
    {
        Pair first_pair = tree[2 * i];
        Pair second_pair = tree[2 * i + 1];

        tree[i].first = min(first_pair.first, second_pair.first);
        tree[i].second = first_pair.second + second_pair.second;
    }

    return tree;
}

double processQuery(vector<Pair> &tree, int left, int right, double targetMin)
{
    int n = tree.size() / 2;

    left += n;
    right += n;

    // Poszukiowanie minimalnej długości promienia
    // oraz kosztu wydłużenia promieni
    double min_len = numeric_limits<double>::max();
    double elong_const = 0;

    while (left < right)
    {
        if (left % 2 == 1)
        {
            // result = min(result, tree[left]);
            min_len = min(min_len, tree[left].first);
            elong_const += tree[left].second;

            left++;
        }
        if (right % 2 == 1)
        {
            right--;
            // result = min(result, tree[right]);
            min_len = min(min_len, tree[right].first);
            elong_const += tree[right].second;
        }
        left /= 2;
        right /= 2;
    }

    if (elong_const != 0)
        return elong_const;
    return min_len - targetMin;
}

/*
1
6 3.4
5 2 2.3 5 1 3
3
2 6
1 4
3 6
 */
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(9);

    int n_ray_sets;

    cin >> n_ray_sets;

    for (int i = 0; i < n_ray_sets; i++)
    {
        int ray_set_size;
        double target_min_ray_len;

        cin >> ray_set_size >> target_min_ray_len;

        vector<double> rays(ray_set_size);
        for (double &ray : rays) cin >> ray;

        // create tree
        vector<Pair> tree = buildTree(rays, target_min_ray_len);

        int n_queries;
        cin >> n_queries;

        for (int j = 0; j < n_queries; j++)
        {
            int start, end;
            cin >> start >> end;

            // process query for tree
            double result = processQuery(tree, start, end, target_min_ray_len);
            cout << result << endl;
        }
    }
}
