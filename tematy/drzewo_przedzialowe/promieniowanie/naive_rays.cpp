//
// Created by adrian on 22.12.2024.
//

#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

double process(const vector<double> &rays, double target_min_ray_len) {
    double min_ray_len = numeric_limits<double>::max();
    double elongation_cost = 0.0;

    for (int i = 0; i < rays.size(); i++) {
        min_ray_len = min(min_ray_len, rays[i]);
        if (rays[i] < target_min_ray_len) {
            elongation_cost += target_min_ray_len - rays[i];
        }
    }
    
    return (elongation_cost > 0) ? elongation_cost : max(0.0, min_ray_len - target_min_ray_len);
}

/*
6 3.4
5 2 2.3 5 1 3
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(9);

    int n, target;
    cin >> n >> target;

    vector<double> rays(n);
    for (double &ray : rays) cin >> ray;

    process(rays, target);
}
