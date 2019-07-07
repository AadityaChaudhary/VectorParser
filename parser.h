//
// Created by adi on 04/07/19.
//

#ifndef VECTORPARSER_PARSER_H
#define VECTORPARSER_PARSER_H

#include <map>

struct dirVec{
    dirVec(double x, double y, double z);
    dirVec() = default;
    double x;
    double y;
    double z;
};
struct point{
    point(double x, double y, double z);
    point() = default;
    dirVec minus(point b);
    double x;
    double y;
    double z;

};

struct vec{
    vec(point a, point b);
    vec(double x, double y, double z);
    vec(dirVec dirP, point a);

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


    std::map <std::string, point> points;
    std::map <std::string, vec> vecs;
    std::map <std::string, plane> planes;

};


#endif //VECTORPARSER_PARSER_H
