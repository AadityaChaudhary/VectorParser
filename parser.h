//
// Created by adi on 04/07/19.
//

#ifndef VECTORPARSER_PARSER_H
#define VECTORPARSER_PARSER_H

#include <map>
#include <vector>

struct dirVec{
    dirVec(double x, double y, double z);
    dirVec() = default;

    void printInfo();

    double x;
    double y;
    double z;
};
struct point{
    point(double x, double y, double z);
    point() = default;

    dirVec minus(point b);
    void printInfo();

    double x;
    double y;
    double z;

};

struct vec{
    vec(point a, point b);
    //vec(double x, double y, double z);
    vec(dirVec dirP, point a);
    vec() = default;

    void printInfo();

    point center;
    dirVec dir;


};
struct plane{
    plane(point a, point ac, point c);
    plane(vec b, vec c, point a);
    plane(vec a, point b);

    point center;
    vec dir1;
    vec dir2;
};

struct line{
    line(int lineNum, std::string lineVal);

    int lineNum;
    std::string lineVal;
};


class parser {
public:
    bool readLine(line l);

private:
    point makePoint(std::string line);
    void addPoint(std::string l);

    vec makeVector(std::string l);
    void addVector(std::string line);
 //   vec makeVectorTest(std::string l);
    void addDirVec(std::string line);
    dirVec makeDirVec(std::string line);

    int count(std::string l, std::string regex);
    void error(std::string errMsg);
    std::string replace(std::string newS,std::string oldS,std::string p);
    std::vector<std::string> seperateArgs(std::string l);

    int currentLineNum;
    std::string currentLineVal;
    bool err = false;

    std::map <std::string, point> points;
    std::map <std::string, dirVec> dirVecs;
    std::map <std::string, vec> vecs;
    std::map <std::string, plane> planes;

};


#endif //VECTORPARSER_PARSER_H
