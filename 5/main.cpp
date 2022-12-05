//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include <charconv>
#include<deque>

void part1(const std::vector<std::string>& vec){
    std::deque<char> stacks [9];
    bool check_for_end_of_insert{false};
    for(const auto& line : vec){
        if(!check_for_end_of_insert || line[0] == '[') {
            if (line[0] == '['){
                check_for_end_of_insert = true;
            }
            for (int i{0}; i * 4 < line.size(); i++) {
                if (line[i * 4] == '[') {
                    stacks[i].push_front(line[i * 4 + 1]);
                }
            }
        }
        else if (line[0]=='m'){
            int amountindex = line.find_first_of(' ');
            int amountindex_end = line.find_first_of(' ', amountindex+1);
            int from_index = line.find_first_of(' ', amountindex_end+1);
            int from_index_end = line.find_first_of(' ', from_index+1);
            int to_index = line.find_first_of(' ', from_index_end + 1);

            int amount, from, to;
            auto result = std::from_chars(line.data() + amountindex + 1, line.data() + amountindex_end, amount);
            result = std::from_chars(line.data() + from_index+1, line.data() + from_index_end, from);
            result = std::from_chars(line.data() + to_index+1, line.data()+line.size(), to);
            for(int i {0}; i < amount; ++i){
                stacks[to-1].push_back(stacks[from-1].at(stacks[from-1].size()-1));
                stacks[from-1].pop_back();
            }
        }
    }
    for (const auto& stack : stacks){
        std::cout << stack[stack.size()-1];
    }
    std::cout << std::endl;
}


void part2(const std::vector<std::string>& vec){
    std::deque<char> stacks [9];
    bool check_for_end_of_insert{false};
    for(const auto& line : vec){
        if(!check_for_end_of_insert || line[0] == '[') {
            if (line[0] == '['){
                check_for_end_of_insert = true;
            }
            for (int i{0}; i * 4 < line.size(); i++) {
                if (line[i * 4] == '[') {
                    stacks[i].push_front(line[i * 4 + 1]);
                }
            }
        }
        else if (line[0]=='m'){
            int amountindex = line.find_first_of(' ');
            int amountindex_end = line.find_first_of(' ', amountindex+1);
            int from_index = line.find_first_of(' ', amountindex_end+1);
            int from_index_end = line.find_first_of(' ', from_index+1);
            int to_index = line.find_first_of(' ', from_index_end + 1);

            int amount, from, to;
            auto result = std::from_chars(line.data() + amountindex + 1, line.data() + amountindex_end, amount);
            result = std::from_chars(line.data() + from_index+1, line.data() + from_index_end, from);
            result = std::from_chars(line.data() + to_index+1, line.data()+line.size(), to);
            for(int i {0}; i < amount; ++i){
                stacks[to-1].push_back(stacks[from-1].at(stacks[from-1].size()-amount+i));
            }
            for(int i{0}; i < amount;++i){
                stacks[from-1].pop_back();
            }
        }
    }
    for (const auto& stack : stacks){
        std::cout << stack[stack.size()-1];
    }
    std::cout << std::endl;
}


int main(){
    auto vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    part1(vec);
    auto middle {std::chrono::high_resolution_clock::now()};
    part2(vec);
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << '\n';
    //std::cout << p1_new << " required " << std::chrono::duration_cast<std::chrono::microseconds>(middle2 - middle).count() << '\n';
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<'\n';
}
