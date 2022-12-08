//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include <charconv>
#include<deque>
#include<fstream>
#include<map>

std::uint64_t hash(std::uint64_t x, std::uint64_t y){
    return y*1000 + x;
}


void prepare_map(std::unordered_map<std::uint64_t, int>& map, const std::vector<std::string>& vec){
    for (size_t y{0}; y < vec.size(); y++){
        for(size_t x{0}; x < vec[y].size(); x++){
            int nr;
            std::from_chars(vec[y].data()+x, vec[y].data()+x+1, nr);
            map.emplace(hash(x,y), nr);
        }
    }
}

uint64_t get_scenic_value(int x, int y, int sizeX, int sizeY, const std::unordered_map<std::uint64_t, int>& tree_map){
    int self_height{tree_map.at(hash(x,y))};
    uint64_t result{1};

    for(int distance{1}; x + distance < sizeX; distance++){
        if(tree_map.at(hash(x+distance, y)) >= self_height || x+distance == sizeX-1){
            result *= distance;
            break;
        }
    }
    for(int distance{1}; x - distance >= 0; distance++){
        if(tree_map.at(hash(x-distance, y)) >= self_height || x-distance == 0){
            result *= distance;
            break;
        }
    }
    for(int distance{1}; y + distance < sizeY; ++distance){
        if(tree_map.at(hash(x, y + distance)) >= self_height || y+distance == sizeY-1){
            result *= distance;
            break;
        }
    }
    for(int distance{1}; y - distance >= 0; ++distance){
        if(tree_map.at(hash(x, y - distance)) >= self_height || y-distance == 0){
            result *= distance;
            break;
        }
    }
    return result;
}

int main(){
    std::vector<std::string> vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    std::unordered_map<std::uint64_t, int> tree_map;
    std::unordered_map<std::uint64_t, int> visible_map;
    prepare_map(tree_map, vec);

    std::uint64_t p1{vec.size() * 2 + (vec[0].size()-2) * 2};
    for(size_t y{1}; y < vec.size()-1; y++) {
        int highest{tree_map.at(hash(0, y))};
        for (size_t x{1}; x < vec[0].size()-1; x++) {

            int base{0};
            int value = tree_map.at(hash(x, y));
            if(highest < value) {
                base = 1;
                highest = value;
            }
            visible_map.emplace(hash(x, y), base);
        }
    }

    for(size_t y{1}; y < vec.size()-1; y++) {
        int highest{tree_map.at(hash(vec[y].size() - 1, y))};
        for (auto x{vec[0].size()-2}; x >= 1;x--) {
            int base{visible_map[hash(x, y)]};
            int value = tree_map.at(hash(x, y));
            if(highest < value) {
                base = 1;
                highest = value;
            }

            visible_map[hash(x, y)] = base;
        }
    }

    for (size_t x{1}; x < vec[0].size()-1; x++) {
        int highest{tree_map.at(hash(x,0))};
        for(size_t y{1}; y < vec.size()-1; y++) {
            int base{visible_map[hash(x, y)]};
            int value = tree_map.at(hash(x, y));
            if(highest < value) {
                base = 1;
                highest = value;
            }

            visible_map[hash(x, y)] = base;
        }
    }

    for (size_t x{1}; x < vec[0].size()-1; x++) {
        int highest{tree_map.at(hash(x,vec.size()-1))};
        for(auto y{vec.size()-2}; y >= 1; y--) {
            int base{visible_map[hash(x, y)]};
            int value = tree_map.at(hash(x, y));
            if(highest < value) {
                base = 1;
                highest = value;
            }
            if (base){
                p1++;
            }
            visible_map[hash(x, y)] = base;

        }
    }
    auto middle {std::chrono::high_resolution_clock::now()};
    uint64_t p2{0};
    for (size_t y{1}; y < vec.size() - 1; y++) {
        for (size_t x{1}; x < vec[0].size() - 1; x++) {
            auto value = get_scenic_value(x, y, vec[0].size(), vec.size(), tree_map);
            if (p2 < value) {
                p2 = value;
            }
        }
    }
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 answer " << p1 << std::endl;
    std::cout << "P2 answer " << p2 << std::endl;
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << " microsec.\n";
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<" microsec.\n";
}
