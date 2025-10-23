#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

class SegmentTree
{
private:
    vector<int> tree;
    int n;

    void build(const vector<int> &data)
    {
        for (int i = 0; i < n; i++)
        {
            tree[i + n] = data[i];
        }
        for (int i = n - 1; i > 0; i--)
        {
            int left = tree[2 * i];
            int right = tree[2 * i + 1];

            // Konstrukcja podrozwiązań
            tree[i] = min(left, right);
        }
    }

public:
    SegmentTree(const vector<int> &data)
    {
        n = data.size();
        tree.resize(2 * n);
        build(data);
    }

    void update(int index, int value)
    {
        index += n;
        tree[index] = value;
        while (index > 1)
        {
            index /= 2;
            int left = tree[2 * index];
            int right = tree[2 * index + 1];

            // Aktualizacja podrozwiązań
            tree[index] = min(left, right);
        }
    }

    int query(int left, int right)
    {
        left += n;
        right += n;
        int result = INT_MAX;   // Inicjalizacja wartości minimalnej
        
        while (left < right)
        {
            if (left % 2 == 1)
            {
                result = min(result, tree[left]);
                left++;
            }
            if (right % 2 == 1)
            {
                right--;
                result = min(result, tree[right]);
            }
            left /= 2;
            right /= 2;
        }
        return result;
    }
};

int main()
{
    vector<int> data = {1, 4, 5, -7, 9, 11};
    SegmentTree segTree(data);

    cout << segTree.query(0, 4) << "\n";
    cout << segTree.query(1, 5) << "\n";

    segTree.update(3, 12);
    cout << segTree.query(1, 4) << "\n";

    return 0;
}
