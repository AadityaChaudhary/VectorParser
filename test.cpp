//
// Created by adi on 07/07/19.
//
#include <iostream>
#include <vector>
#include "parser.h"


int count(std::string l,std::string regex);
void testVector(std::string l);
point makePointT();
std::string replace(std::string newS, std::string oldS, std::string p);

int main() {

//    point* a;
//    if(true)
//    {
//        point ap = makePointT();
//        a = &ap;
//    }
//    a->printInfo();

std::string p = "vec => v{ 9 , 0, 9 }";
p = replace(""," ", p);
std::cout << p << std::endl;


}

point makePointT()
{
    return {1,0,0};
}
int count(std::string l, std::string regex) {
int x;
for(x = 0; l.find(regex) != std::string::npos; x++)
    {
        l = l.substr(l.find(regex) + regex.length());
    }
return x;
}

void testVector(std::string l)
{
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
        for(auto& p : args)
        {

        }
    }

}

