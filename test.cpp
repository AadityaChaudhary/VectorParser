//
// Created by adi on 07/07/19.
//
#include <iostream>
#include "parser.h"

int count(std::string l,std::string regex);


int main() {
    std::string l = "dv{x,y,z},point{x,y,z}";
    if(l.find(",d") != std::string::npos)
    {

    }
    else if(l.find(",p") != std::string::npos)
    {

    }
    else
    {

    }
}

int count(std::string l, std::string regex) {
int x;
for(x = 0; l.find(regex) != std::string::npos; x++)
    {
        l = l.substr(l.find(regex) + regex.length());
    }
return x;
}
