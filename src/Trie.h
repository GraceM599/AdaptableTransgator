//
// Created by mihir on 3/5/2026.
//
#include <vector>

#include "dictionary.h"
struct Node {
    int val = 0;
    Node* next = nullptr;
};
class Trie : dictionary{
    Trie();
    ~Trie();
    std::vector<Node*> root;
public:
    bool insert(std::string en, std::string trans) override;
    std::string search(std::string en) override;
};


