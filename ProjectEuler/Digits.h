//
//  Digits.cpp
//  ProjectEuler
//
//  Created by admin on 02/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <vector>
#include <algorithm>

inline std::vector<int> CreateDigitsFromInt(int a) {
    if (a < 0) {
        std::cout << "Why are you trying to convert a negative integer to digit form!!\n";
    }
    std::vector<int> digits;
    while (a>0) {
        digits.insert(digits.begin(), a%10);
        a/=10;
    }
    return digits;
}

inline int CreateIntFromDigits(std::vector<int> &digits) {
    int num{0};
    for (int i=0; i<digits.size(); i++) {
        num = (10*num) + digits[i];
    }
    return num;
}

inline std::vector<int> ConcatenateDigits(std::vector<int> &a, std::vector<int> &b) {
    std::vector<int> concatenated(a.size()+b.size());
    std::copy(a.begin(), a.end(), concatenated.begin());
    std::copy(b.begin(), b.end(), concatenated.begin()+a.size());
    return concatenated;
}

inline int ConcatenateInts(int &a, int &b) {
    std::vector<int> a_digits = CreateDigitsFromInt(a);
    std::vector<int> b_digits = CreateDigitsFromInt(b);
    std::vector<int> conc = ConcatenateDigits(a_digits, b_digits);
    return CreateIntFromDigits(conc);
}

void TestConcatenateDigits() {
    std::vector<int> a{1, 4, 7, 3};
    std::vector<int> b{2, 8, -1};
    std::vector<int> c = ConcatenateDigits(a, b);
    std::cout << "Concatenating {1, 4, 7, 3} with {2, 8, -1}. Result is: \n{";
    for (auto x : c) {
        std::cout << x << ",";
    }
    std::cout << "}" << std::endl;
}

void TestConcatenateInts() {
    int a = 364;
    int b = 52;
    int c = ConcatenateInts(a, b);
    std::cout << "Concatenating " << a << " and " << b << " gives " << c << std::endl;
}
