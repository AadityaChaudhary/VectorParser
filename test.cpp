//
// Created by adi on 07/07/19.
//
#include <iostream>
#include "parser.h"

int count(std::string l,std::string regex);


int main() {
    std::string l = "v{pt{8,2,5},pt{1,3,4}}";
    parser p;
    vec v = p.makeVector(l);
    //std::cout << v.dir.y << std::endl;
    v.printInfo();

}

int count(std::string l, std::string regex) {
int x;
for(x = 0; l.find(regex) != std::string::npos; x++)
    {
        l = l.substr(l.find(regex) + regex.length());
    }
return x;
}
