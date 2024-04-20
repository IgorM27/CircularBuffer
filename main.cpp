#include "iostream"
#include "CCircularBuffer.h"
#include "algorithm"

int main() {
    CCircularBuffer<int> a(12);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    std::sort(a.begin(),a.end());
    for(auto i:a){
        std::cout<<i<<' ';
    }
}
