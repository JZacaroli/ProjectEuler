//
//  Euler49.cpp
//  ProjectEuler
//
//  Created by admin on 01/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <set>

bool is_prime(int N){
    int i = 2;
    int sqroot;
    sqroot = round(sqrt(N)) + 1;
    
    while(i < sqroot){
        if(N%i==0){
            return false;
        }
        
        i += 1;
    }
    return true;
}

std::multiset<int> DigitsInNumber(int x) {
    std::multiset<int> digits;
    while (x>0) {
        digits.insert(x%10);
        x /= 10;
    }
    return digits;
}

void TestDigitsInNumber() {
    std::multiset<int> digits = DigitsInNumber(10231);
    for (const auto &x : digits) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
}

void Euler49() {
    std::cout << "Hello Euler 49!\n";
    
//    TestDigitsInNumber();
    
    std::set<int> primes {};

    for (int x=1000; x<10000; ++x) {
        if (is_prime(x)) primes.insert(x);
    }

    for (const auto &x : primes) {
        for (const auto &y : primes) {
            if (y <= x) continue;
            if (y-x != 3330) continue;
            if (DigitsInNumber(x) != DigitsInNumber(y)) continue;
            if (primes.find(y + (y-x))!=primes.end()) {
                std::cout << x << ",";
                std::cout << y << ",";
                std::cout << (2*y)-x << std::endl;
            }
        }
    }
    
}
