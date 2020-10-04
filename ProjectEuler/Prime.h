//
//  Prime.cpp
//  ProjectEuler
//
//  Created by admin on 02/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <cmath>

inline bool IsPrime(long N){
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
