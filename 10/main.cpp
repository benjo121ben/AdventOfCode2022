//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include<charconv>


int part1(const std::vector<std::string> &vec) {
    int result{0};
    int check_cycles[6] {20, 60, 100, 140, 180, 220};
    int check_index{0};
    int cycle{1};
    int X{1};
    for(const auto& line : vec){
        int steps{1};
        int increase{0};
        if (line[0] == 'a') {
            steps = 2;
            std::from_chars(line.data() + 5, line.data() + line.size(), increase);
        }
        while(check_index < 6 && cycle + steps > check_cycles[check_index]){
            result += X * check_cycles[check_index];
            check_index++;
        }
        cycle += steps;
        X += increase;
        if(check_index < 6 && cycle == check_cycles[check_index]){
            result += X * check_cycles[check_index];
            check_index++;
        }
        if(check_index == 6) break;
    }
    return result;
}

void part2(const std::vector<std::string> &vec) {
    int X{1};
    int drawing_loc{0};
    for(const auto& line : vec){
        int steps{1};
        int increase{0};
        if (line[0] == 'a') {
            steps = 2;
            std::from_chars(line.data() + 5, line.data() + line.size(), increase);
        }
        for(int i{0}; i < steps; ++i){
            std::cout << ((drawing_loc >= X - 1 && drawing_loc <= X + 1) ? '#' : '.');
            drawing_loc++;
            if(drawing_loc == 40){
                std::cout << std::endl;
                drawing_loc = 0;
            }
        }
        X += increase;
    }
}



int main(){
    std::vector<std::string> vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    int p1{part1(vec)};
    auto middle {std::chrono::high_resolution_clock::now()};
    part2(vec);
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 answer " << p1 << std::endl;
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << " microsec.\n";
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<" microsec.\n";
}


