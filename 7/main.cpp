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

class Node{
    std::map<std::string, Node *> subnodes;
    std::map<std::string, int> files;
    std::uint64_t files_size{0};
    std::uint64_t all_size{0};
    Node* parent = nullptr;
    bool calculated{false};
public:
    Node(){}
    void addNode(const std::string_view& name){
        if(subnodes.contains(name.data())){
            return;
        }
        auto temp = new Node();
        temp->setParent(this);
        subnodes.emplace(name, temp);
    }
    void setParent(Node* newParent){
        parent = newParent;
    }
    Node* getParent(){
        return parent;
    }
    void addFile(const std::string_view& name, int filesize){
        if(files.contains(name.data())){
            return;
        }
        files.emplace(name, filesize);
        files_size += filesize;
    }
    Node* cd(const std::string& name){
        return subnodes.at(name);
    }
    ~Node(){
        for(auto& node_pair : subnodes){
            delete node_pair.second;
        }
    }
    std::uint64_t calculateSize(){
        if(calculated){
            return all_size;
        }
        all_size = this->files_size;
        for(const auto& subnode_pair : subnodes){
            all_size += subnode_pair.second->calculateSize();
        }
        calculated = true;
        return all_size;
    }
    std::uint64_t get_sum_of_dirs_by_max(int max_size){
        std::uint64_t sum{0};
        for(const auto& subnode_pair : subnodes){
            if(subnode_pair.second->calculateSize() <= max_size){
                sum+= subnode_pair.second->calculateSize();
            }
            sum+=subnode_pair.second->get_sum_of_dirs_by_max(max_size);
        }
        return sum;
    }
    void get_smallest_needed(std::uint64_t needed_freeup, std::uint64_t& current_min){
        current_min = all_size < current_min && all_size >= needed_freeup ? all_size : current_min;
        for(const auto& subnode_pair : subnodes){
            subnode_pair.second->get_smallest_needed(needed_freeup, current_min);
        }

    }
};

int main(){
    auto vec {Input::GetStringData("../input")};
    auto start {std::chrono::high_resolution_clock::now()};
    Node root;
    Node* temp = &root;
    for(int i{0}; i < vec.size();++i){
        if (vec[i][2] == 'c'){
            const std::string_view& name{vec[i].begin()+5, vec[i].end()};
            if(name == ".." && temp != &root){
                temp = temp->getParent();
            }
            else if(name == "/"){
                temp = &root;
            }
            else{
                temp = temp->cd(name.data());
            }
        }
        else if(vec[i][2] == 'l'){
            do{
                ++i;
                if(vec[i][0] == 'd'){
                    const std::string_view& name{vec[i].begin()+4, vec[i].end()};
                    temp->addNode(name);
                }
                else{
                    int space = vec[i].find_first_of(' ');
                    const std::string_view& name{vec[i].begin()+space+1, vec[i].end()};
                    int file_size;
                    auto result = std::from_chars(vec[i].data(), vec[i].data() + space, file_size);
                    temp->addFile(name, file_size);
                }
            }
            while(i < vec.size()-1 && vec[i+1][0] != '$');
        }
    }
    std::uint64_t total_size {root.calculateSize()};
    std::uint64_t p1{root.get_sum_of_dirs_by_max(100000)};
    auto middle {std::chrono::high_resolution_clock::now()};
    std::uint64_t p2{total_size};
    root.get_smallest_needed(total_size - 40000000, p2);
    auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "P1 answer " << p1 << std::endl;
    std::cout << "P2 answer " << p2 << std::endl;
    std::cout << "P1 required " << std::chrono::duration_cast<std::chrono::microseconds>(middle - start).count() << " microsec.\n";
    std::cout << "P2 required " << std::chrono::duration_cast<std::chrono::microseconds>(end - middle).count() <<" microsec.\n";
}
