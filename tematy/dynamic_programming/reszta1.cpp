#include <vector>
#include <cmath>
#include <limits.h>
#include <vector>
#include <iostream>


using namespace std;

int main()
{
    const int CHANGE = 7;
    // const int COINS[] = {1, 2, 5, 5, 5, 10, 10, 10};
    const int COINS[] = {1, 3, 3, 5};

    const int nCoins = sizeof(COINS) / sizeof(COINS[0]);

    int sums[CHANGE + 1][nCoins];
    int counts[CHANGE + 1][nCoins];

    for (int i = 0; i < CHANGE + 1; ++i)
    {
        for (int j = 0; j < nCoins; j++)
        {
            if (i == 0)
            {
                sums[i][j] = 0;
                counts[i][j] = 0;
                continue;
            }

            if (j == 0)
            {
                if (COINS[0] <= i)
                {
                    sums[i][j] = COINS[0];
                    counts[i][j] = 1;
                }
                else
                {
                    sums[i][j] = 0;
                    counts[i][j] = 0;
                }
                continue;
            }

            if (COINS[j] == i)
            {
                // Można wydać jedną monetą
                sums[i][j] = i;
                counts[i][j] = 1;
                continue;
            }

            int tempSum = INT_MAX;
            int tempCount = INT_MAX;

            if (sums[i][j - 1] == i)
            {
                // Nie uwzględniamy monety
                tempSum = sums[i][j - 1];
                tempCount = counts[i][j - 1];
            }

            if (i >= COINS[j] && sums[i - COINS[j]][j - 1] + COINS[j] == i && counts[i - COINS[j]][j - 1] + 1 < tempCount)
            {
                // Uwzględniamy monetę, jeśli jest to bardziej optymalne
                tempSum = i;
                tempCount = counts[i - COINS[j]][j - 1] + 1;
            }

            if (tempCount != INT_MAX)
            {
                sums[i][j] = tempSum;
                counts[i][j] = tempCount;
            }
            else
            {
                sums[i][j] = COINS[j];
                counts[i][j] = 1;
            }
        }
    }

    int i = CHANGE;
    int j = nCoins - 1;

    std::vector<int> chosenCoins;

    if (sums[i][j] != CHANGE)
    {
        std::cout << "Nie można wydać reszty";
        return -1;
    }

    while (true)
    {
        // Wzięliśmy jedną monetę, bieżącą
        if (sums[i][j] == COINS[j])
        {
            chosenCoins.push_back(COINS[j]);
            break;
        }
        // Wzięliśmy monetę, ale nie była to jedyna moneta
        if (counts[i][j] != counts[i][j - 1])
        {
            chosenCoins.push_back(COINS[j]);
            i -= COINS[j];
            j--;
            continue;
        }

        // Nie wzięliśmy monety
        j--;
    }

    for (auto elem : chosenCoins)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
