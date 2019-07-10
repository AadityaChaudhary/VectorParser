//
// Created by adi on 04/07/19.
//

#ifndef VECTORPARSER_PARSER_H
#define VECTORPARSER_PARSER_H

#include <map>

struct DirVec{
    DirVec(double x, double y, double z);
    DirVec() = default;

    void printInfo();

    double x;
    double y;
    double z;
};
struct point{
    point(double x, double y, double z);
    point() = default;

    DirVec minus(point b);
    void printInfo();

    double x;
    double y;
    double z;

};

struct vec{
    vec(point a, point b);
    vec(double x, double y, double z);
    vec(DirVec dirP, point a);

    void printInfo();

    point center;
    DirVec dir;


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


    point makePoint(std::string line);
    bool addPoint(line l);

    vec makeVector(std::string l);

    DirVec makeDirVec(std::string line);

    int count(std::string l, std::string regex);

    std::map <std::string, point> points;
    std::map <std::string, DirVec> dirVecs;
    std::map <std::string, vec> vecs;
    std::map <std::string, plane> planes;

};


#endif //VECTORPARSER_PARSER_H
