//
//  Euler22.c
//  ProjectEuler
//
//  Created by admin on 30/09/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void Euler22() {
    std::vector<std::string> names {};
    
    std::ifstream in;
    in.open("/Users/admin/Documents/XCode/ProjectEuler/ProjectEuler/Names.txt");
    std::string line;
    if (in.is_open())
    {
      while ( getline (in,line,',') )
      {
          names.push_back(line);
      }
      in.close();
    }
    std::sort(names.begin(), names.end());
    
    int nameOrdinal {0};
    int totalScore {0};
    for (const auto &x : names) {
        nameOrdinal++;
        int nameScore = 0;
        for (const auto &ch : x) {
            int asciVal = (int)ch;
            if (asciVal<65 || (asciVal>90&&asciVal<97) || asciVal>122)
                continue;
            if (asciVal > 90)
                asciVal -= 32;
            nameScore += (asciVal-64);
        }

        totalScore += (nameScore*nameOrdinal);
    }
    
    std::cout << totalScore << std::endl;
}

