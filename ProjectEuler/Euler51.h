//
//  Euler51.h
//  ProjectEuler
//
//  Created by admin on 01/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <set>

bool IsPrime(int N){
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

int NumberOfPrimesWhenReplacingDigits(std::vector<int> digits) {
    int numberOfPrimes{0};
    
    for (int replacement=0; replacement<10; ++replacement) {
        std::vector<int> newDigits{};
        newDigits.reserve(digits.size());
        
        for (auto digit : digits) {
            if (digit==-1) digit=replacement;
            newDigits.push_back(digit);
        }
        if (newDigits[0] == 0) continue;
        
        //Reconstruct the new number from the new digits
        int replacedNumber{0};
        for (int i=0; i<digits.size(); i++) {
            replacedNumber = (10*replacedNumber) + newDigits[i];
        }
        
        //Check if it's prime
        if (IsPrime(replacedNumber)) {
            numberOfPrimes++;
        }
    }
    return numberOfPrimes;
}

void TestNumberOfPrimesWhenReplacingDigits() {
    std::vector<int> digits {-1, 3};
    int numPrimes = NumberOfPrimesWhenReplacingDigits(digits);
    std::cout << numPrimes << std::endl;
    
    digits = {5, 6, -1, -1, 3};
    numPrimes = NumberOfPrimesWhenReplacingDigits(digits);
    std::cout << numPrimes << std::endl;
}

int MaxNumberOfPrimesWhenReplacingDigits(int a) {
    int maxNumPrimes = 0;
    //Convert it into digit form
    std::vector<int> digits;
    while (a>0) {
        digits.insert(digits.begin(), a%10);
        a/=10;
    }
    //Find the unique set of digits
    std::set<int> uniqueDigits;
    for (const auto d : digits) {
        if (d>2) continue;
        uniqueDigits.insert(d);
    }
    
    //Sequentially replace all matching digits with all other digits
    for (const auto digitToReplace : uniqueDigits) {
        std::vector<int> placeholderDigits{};
        for (auto digit : digits) {
            if (digit == digitToReplace) {
                digit = -1;
            }
            placeholderDigits.push_back(digit);
        }
        int numPrimes = NumberOfPrimesWhenReplacingDigits(placeholderDigits);
        if (numPrimes>maxNumPrimes) {
            maxNumPrimes = numPrimes;
        }
        if (maxNumPrimes > 8) {
            std::cout << "Found 8 replacement primes with " << a << "!!\n";
        }
    }
    
    return maxNumPrimes;
}

void TestMaxNumberOfPrimesWhenReplacingDigits() {
    int testNum1 {56003};
    int maxNumPrimes1 = MaxNumberOfPrimesWhenReplacingDigits(testNum1);
    std::cout << "Max number of primes for " << testNum1 << " is " << maxNumPrimes1 << std::endl;
    int testNum2 {13};
    int maxNumPrimes2 = MaxNumberOfPrimesWhenReplacingDigits(testNum2);
    std::cout << "Max number of primes for " << testNum2 << " is " << maxNumPrimes2 << std::endl;
}

void Euler51() {
//    TestNumberOfPrimesWhenReplacingDigits();
//    TestMaxNumberOfPrimesWhenReplacingDigits();
    
    int maxNumPrimesFound = 0;
    for (int number=11; number>0; number++) {
        int maxNumPrimesWhenReplacingDigs = MaxNumberOfPrimesWhenReplacingDigits(number);
        if (maxNumPrimesWhenReplacingDigs > maxNumPrimesFound) {
            std::cout << "Found a better one! " << maxNumPrimesWhenReplacingDigs << " primes in " << number << std::endl;
            maxNumPrimesFound = maxNumPrimesWhenReplacingDigs;
            if (maxNumPrimesFound > 7) {
                return;
            }
        }
        number++;
    }
}
