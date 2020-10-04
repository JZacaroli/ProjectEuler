//
//  Euler20.cpp
//  Euler
//
//  Created by admin on 30/09/2020.
//  Copyright © 2020 Joseph Zacaroli. All rights reserved.
//

#include <iostream>
#include <vector>

void multiplyVecNumByNumber(std::vector<u_long> &vecNum, u_long number) {
    u_long carry = 0;
    for (int i=vecNum.size()-1; i>=0; --i) {
        vecNum[i] = (vecNum[i]*number)+carry;
        if (vecNum[i] > 10) {
            carry = vecNum[i] / 10;
            vecNum[i] = vecNum[i] % 10;
        }
        else {
            carry=0;
        }
    }
    if (carry > 0) {
        while (carry > 10) {
            u_long newCarry = carry / 10;
            vecNum.insert(vecNum.begin(), carry%10);
            carry = newCarry;
        }
        vecNum.insert(vecNum.begin(), carry);
    }
}

void Euler20() {
    std::vector<u_long> vecNum {1};
    for (int i=1; i<101; ++i) {
        multiplyVecNumByNumber(vecNum, i);
    }
    u_long sum = 0;
    for (const auto &x : vecNum) {
        sum += x;
        std::cout << x;
    }
    std::cout << std::endl;
    std::cout << "Sum:" << sum << std::endl;
}
