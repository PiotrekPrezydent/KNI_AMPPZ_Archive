#include <iostream>
#include <limits>
#include <vector>
#include <string>

/*
SUBOPTIMAL SOLUTION
O(2^n) complexity
*/

using namespace std;

#include <stdbool.h>

bool isUnified(const string &binStr, const vector<bool> &mask) {
    bool foundOnes = false;
    bool gapDetected = false;


    for (size_t i = 0; i < binStr.size(); i++) {
        if (!mask[i]) continue;

        if (binStr[i] == '1') {
            if (gapDetected) return false;
            foundOnes = true;
        } else if (foundOnes) {
            gapDetected = true;
        }
    }

    return true;
}


int backtrace(string binStr, vector<bool> mask)
{
    if (isUnified(binStr, mask))
    {
        return 0;
    }

    char c;
    int i = 0;
    int minCost = numeric_limits<int>::max();

    for (int i = 0; i < binStr.size(); ++i) {
        if (!mask[i]) {
            continue;
        }

        mask[i] = false;
        int cost = backtrace(binStr, mask) + 1;
        mask[i] = true;

        minCost = min(minCost, cost);
    }

    return minCost;
}


int main()
{
    string buffer;
    vector<bool> mask(51, true);

    cin >> buffer;
    // cout << endl << isUnified(buffer, mask) << endl;
    cout << endl << backtrace(buffer, mask) << endl;

    return 0;
}
