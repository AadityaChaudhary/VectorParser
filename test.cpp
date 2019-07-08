//
// Created by adi on 07/07/19.
//
#include <iostream>
#include "parser.h"

void makePoint(std::string line);

int main() {
    makePoint("point{5,6,7}");
}

point makePoint(std::string l)
{
    std::string line = l;

    line = line.substr(line.find('{') + 1); //line now is ####,#####,####}
    line = line.substr(0,line.length()- 1);
    std::cout << line << std::endl;
    double x = std::stod(line.substr(0,line.find(',')));
    std::cout << x << std::endl;
    line = line.substr(line.find(',') + 1);
    double y = std::stod(line.substr(0, line.find(',')));
    std::cout << y << std::endl;
    line = line.substr(line.find(',') + 1);
    double z = std::stod(line);
    std::cout << z << std::endl;

    return point(x,y,z);

}
