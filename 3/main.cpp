//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include <string_view>

std::uint64_t get_value(const char& c){
    auto value {static_cast<std::uint64_t>(c)};
    if (value >= 97){
        return value - 96;
    }
    else{
        return value - 38;
    }
}

std::uint64_t part1(const std::vector<std::string>& vec){
    std::uint64_t sum = 0;
    for(const auto& line : vec){
        auto comp1 = line.substr(0,line.size()/2);
        auto comp2 = line.substr(line.size()/2, line.size()/2);
        for(const char& c : comp1){
            if(comp2.find_first_of(c) != std::string::npos){
                sum += get_value(c);
                break;
            }
        }
    }
    return sum;
}

/*std::uint64_t part1_new(const std::vector<std::string>& vec){
    std::uint64_t sum = 0;
    for(const std::string& line : vec){
        const std::string_view s1 {line.begin(), line.begin() +(line.size()/2)};
        const std::string_view s2 {line.begin(), line.begin() +(line.size()/2)};
        for(auto it{}; it != line.begin()+(line.size()/2); ++it){
            const auto result{std::find(line.begin()+(line.size()/2), line.end(),*it)};
            if (result != line.end()){
                sum += get_value(*result);
                break;
            }
        }
    }
    return sum;
}*/

std::uint64_t part2(const std::vector<std::string>& vec){
    std::uint64_t sum = 0;
    for(int index{0}; index < vec.size(); index+=3){
        for(const char& c : vec[index]){
            if(vec[index+1].find_first_of(c) != std::string::npos && vec[index+2].find_first_of(c) != std::string::npos){
                sum += get_value(c);
                break;
            }
        }
    }
    return sum;
}


int main(){
    auto vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    std::uint64_t p1{part1(vec)};
    auto middle {std::chrono::high_resolution_clock::now()};
    //std::uint64_t p1_new{part1_new(vec)};
    //auto middle2 {std::chrono::high_resolution_clock::now()};
    std::uint64_t p2{part2(vec)};
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << p1 << " required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << '\n';
    //std::cout << p1_new << " required " << std::chrono::duration_cast<std::chrono::microseconds>(middle2 - middle).count() << '\n';
    std::cout << p2 << " required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<'\n';
}
