#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <numeric>

#include "Timer.h"

using namespace std;

double analyse(vector<int>& vec, int cycles)
{
    int target = cycles / vec.size();
    vector<double> variation(vec.size(), 0.0);
    
    auto lambda_a = [&](int& a)
        {
            int x = abs(a - target);
            return x * 100.0 / target;
        };

    transform(vec.begin(), vec.end(), variation.begin(), lambda_a);
    auto lambda_b = [&](double a, double b) { return a + b / variation.size(); };
    return accumulate(variation.begin(), variation.end(), 0.0, lambda_b);
}

int main()
{
    int num{};
    int cycles = 1E11;
    int dist_max = 1000;
    vector<int> vec(dist_max);
    double avg_variation = 0.0;
    Timer t;
        
    //The C way:
    t.start();
    fill(vec.begin(), vec.end(), 0);
    srand(time(nullptr));
    for (int i{}; i < cycles; i++) { vec.at(rand() % dist_max)++; }
    avg_variation = analyse(vec, cycles);
    cout << "The C Way: " << avg_variation << ' ';
    t.stop('m');
    
    //The C Style C++ Way:
    t.start();
    fill(vec.begin(), vec.end(), 0);
    default_random_engine r(time(NULL));
    for (int i{}; i < cycles; i++) { vec.at(r() % dist_max)++; }
    avg_variation = analyse(vec, cycles);
    cout << "The C Style C++ Way: " << avg_variation << ' ';
    t.stop('m');
    
    //The C++ Way:
    t.start();
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    fill(vec.begin(), vec.end(), 0);
    default_random_engine re(seed);
    uniform_int_distribution<int> dist(0, 999);
    for (int i{}; i < cycles; i++) { vec.at(dist(re))++; }
    avg_variation = analyse(vec, cycles);
    cout << "The C++ Way: " << avg_variation << ' ';
    t.stop('m');
    
    //The Mersenne Twister Way:
    t.start();
    seed = chrono::steady_clock::now().time_since_epoch().count();
    fill(vec.begin(), vec.end(), 0);
    mt19937 mt(seed);
    for (int i{}; i < cycles; i++) { vec.at(dist(mt))++; }
    avg_variation = analyse(vec, cycles);
    cout << "The Mersenne Twister Way: " << avg_variation << ' ';
    t.stop('m');
}