#pragma once
#include<iostream>
#include<chrono>

using namespace std;
using namespace chrono;

class Timer
{
    chrono::steady_clock::time_point start_time;
    chrono::steady_clock::time_point end_time;
    
public:
    void start() { start_time = steady_clock::now(); }
    void stop(char c)
    {
        end_time = steady_clock::now();

        switch (c)
        {
        case 'u':
            cout << duration_cast<microseconds>(end_time - start_time).count() << " uSeconds Elapsed\n";
            break;
        case 'm':
            cout << duration_cast<milliseconds>(end_time - start_time) << " Milliseconds Elapsed\n";
            break;
        case 's':
        case 'S':
            cout << duration_cast<seconds>(end_time - start_time).count() << " Seconds Elapsed\n";
            break;
        case 'M':
            cout << duration_cast<minutes>(end_time - start_time).count() << " Minutes\n";
            break;
        }
    }
};