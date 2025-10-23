//
// Created by adrian on 22.12.2024.
//

/**
 * Makra i 'using namespace' MOGĄ przyśpieszyć proces pisania kodu
 * https://www.ibm.com/docs/en/i/7.3?topic=directive-function-like-macros
 * 
 * 
 * sync_with_stdio oraz tie zwiększają wydajność kodu
 * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
 */

#include <iostream>

#define _PNT(x) cout << x << endl
#define _TIMES(n) for (int i = 0; i < n; i++)

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;

    cin >> test_cases;
    
    for (int i = 0; i < test_cases; i++) {
        int a, b;

        cin >> a >> b;
        _PNT(a + b);
        _PNT(a - b);
    }
}
