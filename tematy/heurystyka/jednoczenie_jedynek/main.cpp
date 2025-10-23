#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

#define PRINT(x) for (auto i : x) { cout << i << " "; } cout << endl;
#include <stdbool.h>

void solve(string str)
{
    while (str.back() == '0')
    {
        str.pop_back();
    }

    while (str.front() == '0')
    {
        str.erase(str.begin());
    }

    vector<int> zeros;
    vector<int> ones;
    bool nowOnes = true;
    int count = 0;

    for (char c : str)
    {
        if ((c == '1' && nowOnes) || (c == '0' && !nowOnes))
        {
            count++;
        }
        else
        {
            (nowOnes ? ones : zeros).push_back(count);
            count = 1;
            nowOnes = !nowOnes;
        }
    }

    (nowOnes ? ones : zeros).push_back(count);

    // PRINT(ones);
    // PRINT(zeros);

    // 1. Koszt usunięcia wszystkich zer ze środka ciągu
    // równy sumie listy zeros
    int remZeros = 0;
    for (int i = 0; i < zeros.size(); ++i)
    {
        remZeros += zeros[i];
    }

    // 2. Koszt usunięcia wszystkich jedynek (prócz maksymalnej grupy)
    int maxOnes = numeric_limits<int>::min();
    int sumOfOnes = 0;
    for (int i = 0; i < ones.size(); ++i)
    {
        maxOnes = max(maxOnes, ones[i]);
        sumOfOnes += ones[i];
    }
    int remOnes = sumOfOnes - maxOnes;

    // 3. Wszystkie możliwości usuwania zer i jedynek, od lewej
    /*
    _4  5  2  6  2 
      3 _5 _2 _5

    _4 _5  2  6  2 
      3  5 _2 _5

    _4 _5 _2  6  2 
      3  5  2 _5
    */
    int bestLeft = numeric_limits<int>::max();
    for (size_t i = 1; i < zeros.size(); i++)
    {
        int sumOfOnes = 0;
        int sumOfZeros = 0;

        for (size_t j = i; j < zeros.size(); j++)
        {
            sumOfZeros += zeros[j];
        }

        for (size_t j = 0; j < i; j++)
        {
            sumOfOnes += ones[j];
        }
        bestLeft = min(bestLeft, sumOfOnes + sumOfZeros);
    }
    // 3. Check all combinations of removing ones and zeros, from right
    /*
    4 5 2 6 2
     3 5 2 5
    */
    int bestRight = numeric_limits<int>::max();
    for (size_t i = 1; i < zeros.size(); i++)
    {
        int sumOfOnes = 0;
        int sumOfZeros = 0;

        for (size_t j = 0; j < zeros.size() - i; j++)
        {
            sumOfZeros += zeros[j];
        }

        for (size_t j = ones.size() - i; j < ones.size(); j++)
        {
            sumOfOnes += ones[j];
        }
        bestRight = min(bestRight, sumOfOnes + sumOfZeros);
    }
    // remZeros, remOnes, bestLeft, bestRight
    
    cout << min(min(remZeros, remOnes), min(bestLeft, bestRight)) << endl;
}

int main()
{
    string buffer;

    cin >> buffer;
    solve(buffer);

    return 0;
}
