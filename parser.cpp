//
// Created by adi on 04/07/19.
//

#include <iostream>
#include "parser.h"

DirVec::DirVec(double x, double y, double z) : x(x), y(y), z(z) {}

point::point(double x, double y, double z) : x(x), y(y), z(z) {}
DirVec point::minus(point b)
{
    return {b.x-x, b.y - y, b.z - z};
}

vec::vec(point a, point b)
{
    center = a;
    dir = a.minus(b);
}
vec::vec(DirVec dirP, point a)
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
   // std::cout << line << std::endl;
    line = line.substr(line.find('{') + 1); //line now is ####,#####,####}
    line = line.substr(0,line.length()- 1);
    if(line.find(',') != std::string::npos)
    {
        if(points.count(line) > 0)
        {
            return points[line];
        }
    }
  //  std::cout << line << std::endl;
    double x = std::stod(line.substr(0,line.find(',')));
    //std::cout << x << std::endl;
    line = line.substr(line.find(',') + 1);
    double y = std::stod(line.substr(0, line.find(',')));
    //std::cout << y << std::endl;
    line = line.substr(line.find(',') + 1);
    double z = std::stod(line);
   // std::cout << z << std::endl;

    return {x,y,z};

}

bool parser::addPoint(line l) {
    std::string name = l.lineVal.substr(0, l.lineVal.find("=>"));
    points[name] = makePoint(l.lineVal);
}

vec parser::makeVector(std::string l) {
    int nPoints = count(l,"pt{");
    int nDV = count(l,"dv{");
    

    std::string line = l;
    line = line.substr(line.find("v{") + 2); //line now is ####,#####,####}
    line = line.substr(0,line.length()- 1);
    if(line.find(',') != std::string::npos)
    {
        if(vecs.count(line) > 0)
        {
            return vecs[line];
        }
    }


    if(nPoints == 2)
    {
        //this is for the case where a vector is created using two points. the direction vector is calculated
        point a = makePoint(line.substr(0, line.find(",pt")));
        point b = makePoint(line.substr(line.find(",pt{")));
        return {a,b};
    }
    else if( nPoints == 1 && nDV == 1)
    {


        DirVec a;
        point b;
        if(line.find(",pt") != std::string::npos)
        {

            a = makeDirVec(line.substr(0,line.find(",p")));
            b = makePoint(line.substr(line.find("pt{")));
            return {a,b};
        }
        else if(line.find(",dv") != std::string::npos)
        {
            a = makeDirVec(line.substr(line.find("dv")));
            b = makePoint(line.substr(0,line.find(",dv")));
            return {a,b};
        }

        else
        {
            //  error case
        }
    }
    else if(nDV == 1 && nPoints == 0)
    {
        //case where only a dir vector is given, so the origin is assumed to be the point
        DirVec a = makeDirVec(line);
        point b = point(0,0,0);
        return {a,b};
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

DirVec parser::makeDirVec(std::string line) {

    //std::cout << "code made it here" << std::endl;
   // std::cout << line << std::endl;
    line = line.substr(line.find('{') + 1); //line now is ####,#####,####}
    //std::cout << line << std::endl;
    line = line.substr(0,line.length()- 1);

    if(line.find(',') != std::string::npos)
    {
        if(dirVecs.count(line) > 0)
        {
            return dirVecs[line];
        }
    }
   // std::cout << line << std::endl;
    double x = std::stod(line.substr(0,line.find(',')));
   // std::cout << x << std::endl;
    line = line.substr(line.find(',') + 1);
    double y = std::stod(line.substr(0, line.find(',')));
   // std::cout << y << std::endl;
    line = line.substr(line.find(',') + 1);
    double z = std::stod(line);
  //  std::cout << z << std::endl;

    return {x,y,z};
}

void DirVec::printInfo() {
    std::cout << "{" << x << ", " << y << ", " << z << "}" << std::endl;
}
void point::printInfo() {
    std::cout << "{" << x << ", " << y << ", " << z << "}" << std::endl;
}
void vec::printInfo() {
   std::cout << "Center: ";
   center.printInfo();
   std::cout << "DirVec: ";
   dir.printInfo();
}