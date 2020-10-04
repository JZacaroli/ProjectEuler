//
//  Euler60.cpp
//  ProjectEuler
//
//  Created by admin on 02/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <set>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <iterator>
#include <string>

#include "Prime.h"
#include "Digits.h"

inline bool IsFunkySet(std::vector<int> &funkySetCandidate, std::unordered_map<int, std::set<int>> &pairPrimes) {
    for (int a : funkySetCandidate) {
        for (int b : funkySetCandidate) {
            if (a >= b) continue;
            auto itr = pairPrimes.find(a);
            std::set<int> pairPrimesForA = itr->second;
            if (pairPrimesForA.find(b) == pairPrimesForA.end()) return false;
        }
    }
    return true;
}

void TestIsFunkySet(std::unordered_map<int, std::set<int>> &pairPrimes) {
    
    std::vector<int> funkySet{3, 7, 109, 673};
    if (IsFunkySet(funkySet, pairPrimes)) {
        std::cout << "{3, 7, 109, 673} is a funky set!\n";
    }
    std::vector<int> notFunkySet{1, 5, 2};
    if (!IsFunkySet(notFunkySet, pairPrimes)) {
        std::cout << "{1, 5, 2} is not a funky set\n";
    }
}

constexpr int N{3000};
std::array<int, N> CreateFirstNPrimes() {
    std::array<int, N> arr;
    int arr_index=0;
    arr[arr_index++] = 3;
    int prevNumChecked = 5;

    while(arr_index<N) {
        if (IsPrime(prevNumChecked)) {
            arr[arr_index++] = prevNumChecked;
        }
        prevNumChecked++;
        prevNumChecked++;
    }
    return arr;
}

void TestFirstNPrimes() {
    std::array<int, N> arr = CreateFirstNPrimes();
    std::cout << "First " << arr.size() << " primes:\n{";
    for (const auto x : arr) {
        std::cout << x << ",";
    }
    std::cout << "}\n";
}

std::unordered_map<int, std::set<int>> CreatePairPrimes(std::array<int, N> &primes) {
    std::unordered_map<int, std::set<int>> pairPrimes{};
    
    for (auto &p1 : primes) {
        std::set<int> p1_set{};
        for (auto &p2 : primes) {
            int conc = ConcatenateInts(p1, p2);
            if (IsPrime(conc)) {
                int concReverse = ConcatenateInts(p2, p1);
                if (IsPrime(concReverse)) {
                    p1_set.insert(p2);
                }
            }
        }
        pairPrimes.insert(std::make_pair(p1, p1_set));
    }
    
    return pairPrimes;
}

void Euler60() {
//    TestConcatenateDigits();
//    TestConcatenateInts();
//    TestFirstNPrimes();
    
    std::array<int, N> primes = CreateFirstNPrimes();
    std::unordered_map<int, std::set<int>> pairPrimes = CreatePairPrimes(primes);
    
    std::cout << "Created Pair Primes set. Now searching for funky sets.\n";
    
    int minSum{std::numeric_limits<int>::max()};
    
    for (int a : primes) {
        if (a>minSum) continue; //No use searching using primes that are larger than the smallest sum we've found
        
        std::set<int> a_pair_primes = pairPrimes.find(a)->second;
        
        
        for (int b : a_pair_primes) {
            if (b<=a) continue;
            if (a+b>minSum) continue;
            
            //We know any 5-set candidate is going to have to come from the intersection of a_pair_primes and b_pair_primes
            auto itrb = pairPrimes.find(b);
            if (itrb == pairPrimes.end()) continue;
            std::set<int> b_pair_primes = itrb->second;
            
            std::set<int> ab_pair_prime_intersect;
            std::set_intersection(a_pair_primes.begin(), a_pair_primes.end(), b_pair_primes.begin(), b_pair_primes.end(), std::inserter(ab_pair_prime_intersect,ab_pair_prime_intersect.begin()));
            
            if (ab_pair_prime_intersect.size() == 0) continue;
            
            for (int c : ab_pair_prime_intersect) {
                
                if (c<=b) continue;
                if (a+b+c>=minSum) continue;
                
                auto itrc = pairPrimes.find(c);
                if (itrc == pairPrimes.end()) continue;
                std::set<int> c_pair_primes = itrc->second;
                
                std::set<int> abc_pair_prime_intersect;
                std::set_intersection(ab_pair_prime_intersect.begin(), ab_pair_prime_intersect.end(), c_pair_primes.begin(), c_pair_primes.end(), std::inserter(abc_pair_prime_intersect,abc_pair_prime_intersect.begin()));
                
                if (abc_pair_prime_intersect.size() == 0) continue;

                for (int d : abc_pair_prime_intersect) {
                    if (a+b+c+d>=minSum) continue;
                    if (d<=c) continue;
                    
                    auto itrd = pairPrimes.find(d);
                    if (itrd == pairPrimes.end()) continue;
                    std::set<int> d_pair_primes = itrd->second;

                    std::set<int> abcd_pair_prime_intersect;
                    std::set_intersection(abc_pair_prime_intersect.begin(), abc_pair_prime_intersect.end(), d_pair_primes.begin(), d_pair_primes.end(), std::inserter(abcd_pair_prime_intersect,abcd_pair_prime_intersect.begin()));

                    if (abcd_pair_prime_intersect.size() == 0) continue;

                    for (int e : abcd_pair_prime_intersect) {
                        if (e<=d) continue;

                        int sum = a + b + c + d + e;
                        if (sum < minSum) {
                            std::cout << "{" << a << "," << b << "," << c << "," << d << "," << e << "}\n";
                            std::cout << "Sum = " << sum << std::endl;
                            minSum=sum;
                        }
                    }
                }
            }
        }
    }
}
