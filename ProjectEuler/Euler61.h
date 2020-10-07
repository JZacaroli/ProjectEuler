//
//  Euler61.cpp
//  ProjectEuler
//
//  Created by admin on 04/10/2020.
//  Copyright © 2020 JZ. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <list>

// Figurate number functions
auto triangleFn = [](int i){return i*(i+1)/2;};
auto squareFn = [](int i){return i*i;};
auto pentagonalFn = [](int i){return (i*((3*i)-1))/2;};
auto hexagonalFn = [](int i){return i*((2*i)-1);};
auto heptagonalFn = [](int i){return (i*((5*i)-3)/2);};
auto octagonalFn = [](int i){return i*((3*i)-2);};

template<typename F>
std::vector<int> Create4DigitFnNumbers(F &fn) {
    std::vector<int> fnNums;
    for (int i=0; i>-1; i++) {
        int num = fn(i);
        if (num > 9999) {
            return fnNums;
        } else if (num > 999) {
            fnNums.push_back(num);
        }
    }
    return fnNums;
}

void TestCreate4DigitFnNumbers() {
    std::vector<int> tNums = Create4DigitFnNumbers(triangleFn);
    auto sNums = Create4DigitFnNumbers(squareFn);
    auto pNums = Create4DigitFnNumbers(pentagonalFn);
    auto hexNums = Create4DigitFnNumbers(hexagonalFn);
    auto heptNums = Create4DigitFnNumbers(heptagonalFn);
    auto oNums = Create4DigitFnNumbers(octagonalFn);
    std::cout << "Breakpoint me and check they're all here.\n";
}

//Creates all the cyclic number combinations from one set of figurate numbers to another.
std::vector<std::pair<int, int>> CreateCyclicNumbersFrom_A_to_B(const std::vector<int> &A, const std::vector<int> &B) {
    std::vector<std::pair<int, int>> cyclicFrom_A_to_B;
    for (auto a : A) {
        int last2NumsOfa = a % 100;
        if (last2NumsOfa < 10) continue; //Cannot be a cyclic pair if the third number is 0.
        std::for_each(B.begin(),
                      B.end(),
                      [&](int b) {
            if (b%100<10) return;
            if (last2NumsOfa == b/100) { //Cyclic if the first two numbers of b are the same as the last two numbers of a.
                cyclicFrom_A_to_B.push_back(std::make_pair(a, b));
            }
        });
    }
    return cyclicFrom_A_to_B;
}

void TestCreateCyclicNumbersFrom_A_to_B() {
    auto tNums = Create4DigitFnNumbers(triangleFn);
    auto sNums = Create4DigitFnNumbers(squareFn);
    std::vector<std::pair<int, int>> cyclicsT_to_S = CreateCyclicNumbersFrom_A_to_B(tNums, sNums);
    for (auto p : cyclicsT_to_S) {
        std::cout << p.first << ":" << p.second << "  ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<std::vector<std::pair<int, int>>>> transitionPairsFromA_to_B;
std::chrono::time_point<std::chrono::system_clock> start1;
std::chrono::time_point<std::chrono::system_clock> start2;

void VisitAllNodes(int currentNode, std::vector<int> nodesToVisit, std::vector<int> nodesVisited, std::vector<int> nodeValues) {
    if (nodesToVisit.size()==0) {
        //Reached the final node.
        if (nodesVisited.size() > 6) {
            std::cout << "Wtf..\n";
        }
        for (std::pair<int, int> transitionsBackToStart : transitionPairsFromA_to_B[currentNode][nodesVisited[0]]) {
            //CHeck if the previous transition is allowed
            if (nodeValues[nodeValues.size()-1] != transitionsBackToStart.first) continue;
            //Check if the final transition back to the start number is allowed
            if (nodeValues[0] == transitionsBackToStart.second) {
                
                //Found the answer!
                auto end1 = std::chrono::system_clock::now();
                auto elapsed1 =
                    std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
                std::cout << "Found with recursion!\n{";
                for (int x : nodeValues) {
                    std::cout << x << ",";
                }
                std::cout << "}\n";
                std::cout << "Time Taken: " << elapsed1.count() << "ms" <<  std::endl;
            }
        }
    } else {
        for (int nextNode : nodesToVisit) {
            //Check all the possible next nodes

            std::vector<int> nodesVisitedCopy = nodesVisited;
            std::vector<int> nodesToVisitCopy = nodesToVisit;
            if (nodesVisited.size() == 0) {
                nodesVisitedCopy.push_back(currentNode);
                nodesToVisitCopy.erase(std::remove(nodesToVisitCopy.begin(), nodesToVisitCopy.end(), currentNode), nodesToVisitCopy.end());
            }
            nodesVisitedCopy.push_back(nextNode);
            
            nodesToVisitCopy.erase(std::remove(nodesToVisitCopy.begin(), nodesToVisitCopy.end(), nextNode), nodesToVisitCopy.end());
            
            for (std::pair<int, int> transitionToNextNode : transitionPairsFromA_to_B[currentNode][nextNode]) {
                //Look through all the transitions from this node to the next.
                
                std::vector<int> nodeValuesCopy = nodeValues;
                if (nodeValues.size() > 0) {
                    //Check if this transition is allowed based on the previous node's value.
                    if (transitionToNextNode.first != nodeValues[nodeValues.size()-1]) continue;
                } else {
                    //First nodes value is defined by the first transition we use.
                    nodeValuesCopy.push_back(transitionToNextNode.first);
                }
                nodeValuesCopy.push_back(transitionToNextNode.second);
                VisitAllNodes(nextNode, nodesToVisitCopy, nodesVisitedCopy, nodeValuesCopy);
            }
        }
    }
}

std::vector<std::vector<std::vector<std::pair<int, int>>>> CreateTransitionPairsFromA_to_B(int numNodes, std::vector<std::vector<int>> figurateNums) {
    std::vector<std::vector<std::vector<std::pair<int, int>>>> transitionsFromA_to_B;
    for (int i=0; i<numNodes; i++) {
        std::vector<std::vector<std::pair<int, int>>> transitionsFromA;
        std::vector<int> figurateNums1 = figurateNums[i];
        for (int j=0; j<numNodes; j++) {
            if (j==i) {
                std::vector<std::pair<int, int>> dummyVec;
                transitionsFromA.push_back(dummyVec);
                continue;
            }
            std::vector<int> figurateNums2 = figurateNums[j];
            auto A_to_B = CreateCyclicNumbersFrom_A_to_B(figurateNums1, figurateNums2);
            transitionsFromA.push_back(A_to_B);
        }
        transitionsFromA_to_B.push_back(transitionsFromA);
    }
    return transitionsFromA_to_B;
}

std::vector<std::vector<int>> Create4DigitFigurateNumbers() {
    auto tNums = Create4DigitFnNumbers(triangleFn);
    auto sNums = Create4DigitFnNumbers(squareFn);
    auto pNums = Create4DigitFnNumbers(pentagonalFn);
    auto hexNums = Create4DigitFnNumbers(hexagonalFn);
    auto heptNums = Create4DigitFnNumbers(heptagonalFn);
    auto oNums = Create4DigitFnNumbers(octagonalFn);
    std::vector<std::vector<int>> figurateNums {tNums, sNums, pNums, hexNums, heptNums, oNums};
    return figurateNums;
}

void Euler61() {
    
//    TestCreate4DigitFnNumbers();]
//    TestCreateCyclicNumbersFrom_A_to_B();
    
    auto start0 = std::chrono::system_clock::now();
    
    std::vector<std::vector<int>> figurateNumbers = Create4DigitFigurateNumbers();
    
    int numNodes = 6;
    
    //Programmatically create the transition matrices. There will be 6x5=30 different cyclic arrays
    transitionPairsFromA_to_B = CreateTransitionPairsFromA_to_B(numNodes, figurateNumbers);
    
    auto end0 = std::chrono::system_clock::now();
    auto elapsed0 =
        std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0);
    std::cout << "Time taken to create data structures: " << elapsed0.count() << "ms" << std::endl;
    
    /* METHOD 1 (Recursion) */
    //Recursively visit all nodes
    start1 = std::chrono::system_clock::now();
    std::vector<int> nodesToVisit {0, 1, 2, 3, 4, 5};
    std::vector<int> nodeValues {};
    std::vector<int> nodesVisited {};
    VisitAllNodes(3, nodesToVisit, nodesVisited, nodeValues);
    
    
    /* METHOD 2 (Greedy search) */
    start2 = std::chrono::system_clock::now();
    //Start arbitrarily defined as the triangle numbers.
    int node1 = 0;
    //First nodes value is defined by the first transition we use.
    for (int node2=1; node2<numNodes; node2++) {
        std::vector<std::pair<int, int>> &node_1_2_transitions = transitionPairsFromA_to_B[node1][node2];
        for (auto pair_1_2 : node_1_2_transitions) {
            int node1value = pair_1_2.first;
            int node2value = pair_1_2.second;
            
            for (int node3=1; node3<numNodes; node3++) {
                if (node3==node2) continue;
                std::vector<std::pair<int, int>> &node_2_3_transitions = transitionPairsFromA_to_B[node2][node3];
                for (auto pair_2_3 : node_2_3_transitions) {
                    if (pair_2_3.first != pair_1_2.second) continue;
                    int node3value = pair_2_3.second;
                    
                    
                    for (int node4=1; node4<numNodes; node4++) {
                        if (node4 == node2 || node4 == node3) continue;
                        std::vector<std::pair<int, int>> &node_3_4_transitions = transitionPairsFromA_to_B[node3][node4];
                        for (auto pair_3_4 : node_3_4_transitions) {
                            if (pair_3_4.first != pair_2_3.second) continue;
                            int node4value = pair_3_4.second;


                            for (int node5=1; node5<numNodes; node5++) {
                                if (node5 == node2 || node5 == node3 || node5 == node4) continue;
                                std::vector<std::pair<int, int>> &node_4_5_transitions = transitionPairsFromA_to_B[node4][node5];
                                for (auto pair_4_5 : node_4_5_transitions) {
                                    if (pair_4_5.first != pair_3_4.second) continue;
                                    int node5value = pair_4_5.second;

                                    
                                    for (int node6=1; node6<numNodes; node6++) {
                                        if (node6 == node2 || node6 == node3 || node6 == node4 || node6 == node5) continue;
                                        std::vector<std::pair<int, int>> &node_5_6_transitions = transitionPairsFromA_to_B[node5][node6];
                                        for (auto pair_5_6 : node_5_6_transitions) {
                                            if (pair_5_6.first != pair_4_5.second) continue;
                                            int node6value = pair_5_6.second;


                                            std::vector<std::pair<int, int>> &node_6_1_transitions = transitionPairsFromA_to_B[node6][node1];
                                            for (auto pair_6_1 : node_6_1_transitions) {
                                                if (pair_6_1.first != pair_5_6.second) continue;
                                                if (pair_6_1.second == pair_1_2.first) {
                                                    std::cout << "Found without recursion!\n";
                                                    std::cout << "{" << node1value << "," << node2value << "," << node3value << "," << node4value << "," << node5value << "," << node6value << "}" << std::endl;
                                                    std::cout << node1value+node2value+node3value+node4value+node5value+node6value << std::endl;
                                                    auto end2 = std::chrono::system_clock::now();
                                                    auto elapsed2 =
                                                        std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                                                    std::cout << "Time Taken: " << elapsed2.count() << "ms" <<  std::endl;
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
