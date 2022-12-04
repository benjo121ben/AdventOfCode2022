//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include <charconv>


void get_min_max(const std::string_view& linepart, std::uint64_t array[2]){
    int dash_index = linepart.find_first_of('-');
    auto result = std::from_chars(linepart.data(), linepart.data() + dash_index, array[0]);
    if (result.ec == std::errc::invalid_argument) {
        std::cout << "Could not convert1." << *linepart.data() << *(linepart.data() + dash_index);
    }
    result = std::from_chars(linepart.data() + dash_index + 1, linepart.data() + linepart.size(), array[1]);
    if (result.ec == std::errc::invalid_argument) {
        std::cout << "Could not convert2." << *linepart.data() << *(linepart.data() + dash_index);
    }
    //std::cout << array[0] << "," << array[1] << std::endl;
}

std::uint64_t part1(const std::vector<std::string>& vec){
    std::uint64_t sum = 0;
    for(const auto& line : vec){
        auto comma {line.find_first_of(',')};
        std::uint64_t first_minMax[2];
        std::uint64_t second_minMax[2];
        const std::string_view& firstPart {line.begin(), line.begin() + comma};
        const std::string_view& secondPart {line.begin() + comma + 1, line.end()};
        //std::cout << firstPart << " " << secondPart << std::endl;
        get_min_max(firstPart, first_minMax);
        get_min_max(secondPart, second_minMax);
        if((first_minMax[0] <= second_minMax[0] && first_minMax[1] >= second_minMax[1]) || (first_minMax[0] >= second_minMax[0] && first_minMax[1] <= second_minMax[1])){
            sum++;
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
    std::uint64_t first_minMax[2];
    std::uint64_t second_minMax[2];
    for(const auto& line : vec){
        auto comma {line.find_first_of(',')};
        const std::string_view& firstPart {line.begin(), line.begin() + comma};
        const std::string_view& secondPart {line.begin() + comma + 1, line.end()};
        //std::cout << firstPart << " " << secondPart << std::endl;
        get_min_max(firstPart, first_minMax);
        get_min_max(secondPart, second_minMax);
        if(!(first_minMax[1] < second_minMax[0]|| first_minMax[0] > second_minMax[1])){
            sum++;
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
