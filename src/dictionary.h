//
// Created by mihir on 3/5/2026.
//

#pragma once
#include <string>



class dictionary {
public:
    virtual ~dictionary() = default;

    virtual bool insert(std::string en, std::string trans, unsigned long long freq) = 0;
    virtual std::string search(std::string en) = 0;

};


