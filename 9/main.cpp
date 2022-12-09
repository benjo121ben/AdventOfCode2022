//
// Created by benja on 02/12/2022.
//
#include "../Input.h"
#include<iostream>
#include<chrono>
#include<charconv>
#include<fstream>
#include<unordered_set>

std::uint64_t hash(std::uint64_t x, std::uint64_t y){
    return y*10000 + x;
}

int get_distance(int* head, int* tail){
    return std::max(abs(head[0] - tail[0]), abs(head[1] - tail[1]));
}

int get_sign(int a){
    return (0 < a) - (a < 0);
}

void update_tail(int* head, int* tail){
    if(get_distance(head,tail) < 2) return;

    if(head[0] == tail[0]){
        tail[1] += get_sign(head[1] - tail[1]);
    }
    else if(head[1] == tail[1]){
        tail[0] += get_sign(head[0] - tail[0]);
    }
    else{
        tail[0] += get_sign(head[0] - tail[0]);
        tail[1] += get_sign(head[1] - tail[1]);
    }
}

void update_head(int *head, char d) {
    switch(d){
        case 'L':
            head[0]-=1;
            break;
        case 'R':
            head[0]+=1;
            break;
        case 'U':
            head[1]+=1;
            break;
        case 'D':
            head[1]-=1;
            break;
    }
}


void execute_command(std::unordered_set<int>& visited_set, int* head, int* tail, char d, int steps){
    for(int i{0}; i < steps; ++i){
        update_head(head, d);
        update_tail(head, tail);
        visited_set.emplace(hash(tail[0], tail[1]));
    }
}

struct Knot{
    int pos[2]{0,0};
};

void execute_command_knots(std::unordered_set<int>& visited_set, Knot* knots, char d, int steps){
    for(int i{0}; i < steps; ++i){
        update_head(knots[0].pos, d);
        for(int b{1}; b < 10; ++b) {
            update_tail(knots[b-1].pos, knots[b].pos);
        }
        visited_set.emplace(hash(knots[9].pos[0], knots[9].pos[1]));
    }
}


int main(){
    std::vector<std::string> vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    int head[2]{0,0};
    int tail[2]{0,0};
    std::unordered_set<int> visited_set{0};
    for(const auto& line : vec){
        int steps{0};
        std::from_chars(line.data() + 2, line.data() + line.size(), steps);
        execute_command(visited_set, head, tail, line[0], steps);
    }
    auto p1{visited_set.size()};
    auto middle {std::chrono::high_resolution_clock::now()};
    visited_set.clear();
    Knot knots[10];
    for(const auto& line : vec){
        int steps{0};
        std::from_chars(line.data() + 2, line.data() + line.size(), steps);
        execute_command_knots(visited_set, knots, line[0], steps);
    }
    auto p2{visited_set.size()};
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 answer " << p1 << std::endl;
    std::cout << "P2 answer " << p2 << std::endl;
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << " microsec.\n";
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<" microsec.\n";
}
