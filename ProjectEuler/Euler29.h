//
//  Euler29.hpp
//  ProjectEuler
//
//  Created by admin on 01/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#ifndef Euler29_hpp
#define Euler29_hpp

#include <iostream>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <set>
#include <math.h>

int Factor(int a) {
    int sqroot{};
    sqroot = round(sqrt(a)) + 1;
    
    for (int i=2; i<sqroot; ++i) {
        if (a % i == 0) {
            return i;
        }
    }
    return -1;
}

void TestFactor() {
    int a = 161;
    int factor = Factor(a);
    std::cout << factor << "," << a/factor << std::endl;
}

/**
 * Find prime factors of a^b. Which is just the prime factors of a, b times over.
 */
std::multiset<int> PrimeFactors(int a, int b) {
    std::vector<int> primeFactorsOfA;
    std::multiset<int> retval;

    bool isFirstPrimeYet = false;
    while (!isFirstPrimeYet) {
        int factor = Factor(a);
        if (factor == -1) {
            isFirstPrimeYet = true;
            primeFactorsOfA.push_back(a);
        } else {
            primeFactorsOfA.push_back(factor);
            a /= factor;
        }
    }

    for (int i=0; i<b; ++i) {
        for (const auto x : primeFactorsOfA) {
            retval.insert(x);
        }
    }

//    std::sort(retval.begin(), retval.end());

    return retval;
}

void TestPrimeFactors() {
    int a{187}, b{2};
    std::multiset<int> pfs = PrimeFactors(a, b);
    std::cout << "Prime Factors of " << a << "^" << b << " are:\n";
    for (const auto &x : pfs) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
}

struct MultisetHash {
    size_t operator()(const std::multiset<int>& s) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : s) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

//struct SetEqual {
//    bool operator()(const std::set<int>& s1, const std::set<int>& s2) const {
//        if (s1.size() != s2.size()) {
//            return false;
//        }
//        for (int i=0; i<s1.size(); ++i) {
//            if (s1[i] != s2[i]) {
//                return false;
//            }
//        }
//        return true;
//    }
//};

using FactorSet = std::unordered_set<std::multiset<int>, MultisetHash>;

void TestFactorSet() {
    FactorSet s1;
    std::multiset<int> v1 {1, 3, 4, 4};
    std::multiset<int> v2 {1, 3, 5, 4};
    s1.insert(v1);
    s1.insert(v2);
    std::cout << s1.size() << std::endl;
}

void Euler29() {
//    TestFactorSet();
//    TestPrimeFactors();
    
    auto start = std::chrono::system_clock::now();

    //Set of unique vectors of prime factors.
    FactorSet setOfUniquePrimeFactors;

    for (int a=2; a<101; ++a) {
        for (int b=2; b<101; ++b) {
            std::multiset<int> primeFactors = PrimeFactors(a,b);
            setOfUniquePrimeFactors.insert(primeFactors);
        }
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Number of distinct terms: " << setOfUniquePrimeFactors.size() << std::endl;

    std::cout << "Time Taken: " << elapsed.count() << "ms" <<  std::endl;
}

#endif /* Euler29_hpp */
