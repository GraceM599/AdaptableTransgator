#pragma once
#include "dictionary.h"

class HashMap : dictionary{
    HashMap();
    ~HashMap();
    int hash(std::string en);
public:
    bool insert(std::string en, std::string trans) override;
    std::string search(std::string en) override;
};


