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
        if(line.find("point{") != std::string::npos)
        {
            addPoint(l);
            return true;
        }
    }
    else{

    }

}

point parser::makePoint(std::string line)
{
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

    return {x,y,z};

}

bool parser::addPoint(line l) {
    std::string name = l.lineVal.substr(0, l.lineVal.find("=>"));
    points[name] = makePoint(l.lineVal);
}

vec parser::makeVector(std::string l) {
    int nPoints = count(l,"point{");
    int nDV = count(l,"dv{");

    std::string line = l;
    line = line.substr(line.find("vector{") + 7); //line now is ####,#####,####}
    line = line.substr(0,line.length()- 1);

    if(nPoints == 2)
    {
        //this is for the case where a vector is created using two points. the direction vector is calculated
        point a = makePoint(line.substr(0, line.find(",point")));
        point b = makePoint(line.substr(line.find(",point{")));
        return {a,b};
    }
    else if( nPoints == 1 && nDV == 1)
    {
        //this is for the case where a dirvector and point is given.
        dirVec a;
        point b;
        if(line.find(",p") != std::string::npos)
        {
            a = makeDirVec(l.substr(0,l.find(",p")));
            b = makePoint(l.substr(l.find("p")));
            return {a,b};
        }
        else if(line.find(",dv") != std::string::npos)
        {
            a = makeDirVec(l.substr(l.find("dv")));
            b = makePoint(l.substr(l.find("p")));
            return {a,b};
        }
    }
    else if(nDV == 1 && nPoints == 0)
    {
        //case where only a dir vector is given, so the origin is assumed to be the point
    }
    else{
        //error case
    }

}

int parser::count(std::string l, std::string regex) {

    int x = 0;
    for(; l.find(regex) != std::string::npos; x++)
    {
        l = l.substr(l.find(regex) + regex.length());
    }
    return x;
}

dirVec parser::makeDirVec(std::string line) {

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

    return {x,y,z};
}