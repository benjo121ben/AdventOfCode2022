//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>

int get_value(int i){
    switch (i) {
        case 0: return 1;
        case 1: return 2;
        case 2: return 3;
    }
    throw std::runtime_error("ERROR, invalid value");
}

int get_points(const std::string& line){
    int p1 = static_cast<int>(line[0]) -65;
    int p2 = static_cast<int>(line[2]) -88;
    int points = 0;
    if (p1 == p2){
        points += 3;
    }
    else if ((p1+1) %3 == p2){
        points += 6;
    }
    return points + get_value(p2);
}

int get_points2(const std::string& line){
    int p1 = static_cast<int>(line[0]) -65;
    int win = static_cast<int>(line[2]) -88;
    int p2;
    int points = 0;
    switch (win) {
        case 0: {
            p2 = (p1 +2) %3;
            break;
        }
        case 1: {
            p2 = p1;
            points += 3;
            break;
        }
        case 2: {
            p2 = (p1 + 1) %3;
            points+=6;
            break;
        }
    }
    return points + get_value(p2);
}


int main(){
    auto vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    int p{0};
    for(const auto& line : vec){
         p+= get_points(line);
    }

    auto middle {std::chrono::high_resolution_clock::now()};
    int p2{0};
    for(const auto& line : vec){
         p2+= get_points2(line);
    }
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << p << " required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << '\n';
    std::cout << p2 << " required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<'\n';
}
