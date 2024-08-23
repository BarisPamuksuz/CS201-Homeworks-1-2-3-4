/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 */
#ifndef __CUBICLE_
#define __CUBICLE_
#include "Node.h"
class Cubicle{
    public:
    Cubicle(int row, int column, int type);
    Cubicle();
    void addAdjacentCubicle(Cubicle& adjacentCubicule);
    void addVisitedCubicle(Cubicle& visitedCubicle);
    void clearVisitedCubicles();
    Node<Cubicle*>* visitedCubicleList;
    Node<Cubicle*>* adjacentCubicleList;
    bool isVisited;
    int rowNum;
    int columnNum;
    int typeNum;
};

#endif