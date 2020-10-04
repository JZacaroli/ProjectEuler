//
//  Euler21.cpp
//  ProjectEuler
//
//  Created by admin on 30/09/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <stdio.h>
#include <vector>

std::vector<int> ProperDivisorsOf(int n) {
    std::vector<int> properDivisors;
    for (int i=1; i < n; i++) {
        if (n % i == 0) {
            properDivisors.push_back(i);
        }
    }
//    for (const auto &x : properDivisors) {
//        std::cout << x << std::endl;
//    }
    return properDivisors;
}

int SumOfProperDivisorsOf(int n) {
    std::vector<int> properDivisorsOfN;
    properDivisorsOfN = ProperDivisorsOf(n);
    int sum = 0;
    for (const auto &x : properDivisorsOfN) {
        sum += x;
    }
    return sum;
}

bool IsAmicable(int n) {
    int sumOfProperDivisorsOfN = SumOfProperDivisorsOf(n);
    int sumOfProperDivisorsOfsumOfProperDivisorsOfN = SumOfProperDivisorsOf(sumOfProperDivisorsOfN);
    if (sumOfProperDivisorsOfsumOfProperDivisorsOfN == n && sumOfProperDivisorsOfN != n) {
        return true;
    }
    return false;
}

int Euler21() {
    std::cout << "Euler 21\n";
    
//    if (IsAmicable(221)) {
//        std::cout << "Success!\n";
//    }
    
    int sum = 0;
    for (int n=0; n<10000; n++) {
        if (IsAmicable(n))
            sum += n;
    }
    std::cout << sum << std::endl;
    
    return 0;
}
