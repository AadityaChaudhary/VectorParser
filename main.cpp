
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <istream>
#include <algorithm>
#include "parser.h"



int main() {


    std:: ifstream infile("../input.txt");
    std::string lineVal;
    parser p;
    int lineNum = 0;
    if(infile.is_open())
    {

        while(std::getline(infile, lineVal))
        {
                lineNum++;
                std::cout << lineVal << std::endl;
                if(p.readLine({lineNum,lineVal}))
                {
                    std::cout << "break" << std::endl;
                    break;
                }
        }
    }
    else
    {
        std::cout << "cannot open" << std::endl;
    }

}