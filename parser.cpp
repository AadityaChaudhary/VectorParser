//
// Created by adi on 04/07/19.
//

#include <iostream>
#include "parser.h"
#include <vector>


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

void parser::addPoint(std::string l) {
    std::string name = l.substr(0, l.find("=>"));
    points[name] = makePoint(l);
}

vec parser::makeVector(std::string l) {
    int nPoints = count(l,"pt{");
    int nDV = count(l,"dv{");
    

    std::string line = l;
    line = line.substr(line.find("v{") + 2); //line now is ####,#####,####}
    line = line.substr(0,line.length()- 1);

    //I'm not entirely sure what the point of this is , but I'll leave it in for now
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


        dirVec a;
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
        dirVec a = makeDirVec(line);
        point b = point(0,0,0);
        return {a,b};
    }
    else{
        //assume that
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

void dirVec::printInfo() {
    std::cout << "{" << x << ", " << y << ", " << z << "}" << std::endl;
}
void point::printInfo() {
    std::cout << "{" << x << ", " << y << ", " << z << "}" << std::endl;
}
void vec::printInfo() {
   std::cout << "Center: ";
   center.printInfo();
   std::cout << "dirVec: ";
   dir.printInfo();
}
void parser::addVector(std::string l) {
    std::string name = l.substr(0, l.find("=>"));
    vecs[name] = makeVector(l);
}
void parser::error(std::string errMsg) {
    std::cout << "error on line " << currentLineNum << std::endl;

    std::cout << "line contents: " << std::endl;
    std::cout << currentLineVal << std::endl;

    std::cout << "Error Message: " << std::endl;
    std::cout << errMsg << std::endl;

}
vec parser::makeVectorTest(std::string l) {

    std::vector<std::string> args;
    l = l.substr(l.find("v{") + 2); //line now is ####,#####,####}
    l = l.substr(0,l.length()- 1);

    int beginArg = 0;
    bool ignore = false; //for ignoring parameters in pt and dv definitions

    for(int x = 0; x < l.length(); x++)
    {
        // std::cout << x << " : " << beginArg << std::endl;
        std::string current = l.substr(x,1);
        if(current.compare("{") == 0)
        {
            ignore = true;
        }
        else if(current.compare("}") == 0)
        {
            ignore = false;
        }
        else if(current.compare(",") == 0 && !ignore)
        {
            args.push_back(l.substr(beginArg, x - beginArg));
            beginArg = x;
            //std::cout << "special" << x << " : " << beginArg << std::endl;

        }
        else
        {
            //basically any other character, we don't really care about them.
        }
        if(x == l.length() - 1)
        {
            args.push_back(l.substr(beginArg + 1,x - beginArg + 1));
            //std::cout << x << " : " << beginArg << std::endl;
        }
    }
    for(auto&& x: args)
    {
        std::cout << x << std::endl;
    }
    if(args.size() == 1)
    {
        //return {makeDirVec(args[0])};
    }
    else
    {
        point* a;
        point* b;
        dirVec* c;
        for(auto& p : args) {
            if (p.find("pt{") != std::string::npos || points.count(p))
            {
                //parameter is a point
                if(a == NULL)
                {

                }
            }
            else if(p.find("dv{") == std::string::npos || dirVecs.count(p))
            {
                //parameter is a dirVec
            }
            else
            {
                //parameter is neither and is wrong ERROR
            }
        }
    }

}
std::string parser::replace(std::string newS, std::string oldS, std::string p) {
    std::string replace(std::string newS, std::string oldS, std::string p)
    {
        while(p.find(oldS) != std::string::npos)
        {
            p = p.substr(0,p.find(oldS)) + newS + p.substr(p.find(oldS) + 1);
        }
    }
}
