//
// Created by adi on 04/07/19.
//

#include <iostream>
#include "parser.h"

dirVec::dirVec(double x, double y, double z) : x(x), y(y), z(z) {}

point::point(double x, double y, double z) : x(x), y(y), z(z) {}
dirVec point::minus(point b)
{
    return {b.x-x, b.y - y, b.z - z};
}

vec::vec(point a, point b)
{
    center = a;
    dir = a.minus(b);
}
vec::vec(dirVec dirP, point a)
{
    dir = dirP;
    center = a;
}

line::line(int lineNum, std::string lineVal) : lineNum(lineNum), lineVal(lineVal) {}

bool parser::readLine(line l) {

    std::cout << "parsing line number " << l.lineNum << std::endl;
    std::string line = l.lineVal;
    if(line.find("=>") != std::string::npos)
    {

    }
    else{

    }

}