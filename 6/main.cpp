//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include <charconv>
#include<deque>
#include<fstream>

void find_marker(int marker_length){
    char ch;
    std::fstream fin("../input", std::fstream::in);
    std::string data;
    std::getline(fin, data);
    auto start{data.begin()};
    int size = {1};
    for (int i {1}; i < data.size(); ++i){
        for (int check{1}; check < marker_length && check <= size; check++){
            if (*(start + i) == *(start + i - check)){
                size = check-1;
                break;
            }
        }
        if(size == marker_length-1){
            std::cout << i+1 << std::endl;
            break;
        }
        ++size;
    }
}

int main(){
    auto vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    find_marker(4);
    auto middle {std::chrono::high_resolution_clock::now()};
    find_marker(14);
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << '\n';
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<'\n';
}
