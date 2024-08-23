/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 */
#include <iostream>
using namespace std;
#include "Cubicle.h"
#include "Node.h"
Cubicle::Cubicle(int row, int column, int type){
    adjacentCubicleList = nullptr;
    visitedCubicleList = nullptr;
    isVisited = false;
    rowNum = row;
    columnNum = column;
    typeNum = type;
}
Cubicle::Cubicle():rowNum(0), columnNum(0), typeNum(0), isVisited(false){}
void Cubicle::addAdjacentCubicle(Cubicle& adjacentCubicle){
    Node<Cubicle*>* newNode = new Node<Cubicle*>(&adjacentCubicle);//node item olarak cubicle adresi tutuyor, getItemi deref ettigimde original adjacentCubicle'a erisecegim.
    if(adjacentCubicleList == nullptr){
        adjacentCubicleList = newNode;
    }else{
        Node<Cubicle*>* prevPtr = nullptr;
        Node<Cubicle*>* currPtr = adjacentCubicleList;
        while(currPtr != nullptr && (adjacentCubicle.rowNum > currPtr->getItem()->rowNum || (adjacentCubicle.rowNum == currPtr->getItem()->rowNum && adjacentCubicle.columnNum > currPtr->getItem()->columnNum))){
            prevPtr = currPtr;
            currPtr = currPtr->getNext();
        }
        if(currPtr != nullptr){
            if(prevPtr == nullptr){//put beginning
                newNode->setNext(currPtr);
                adjacentCubicleList = newNode;
            }else{//put somehwre in middle
                prevPtr->setNext(newNode);
                newNode->setNext(currPtr);
            }
        }else{// put last
            prevPtr->setNext(newNode);
        }
    }
}
void Cubicle::addVisitedCubicle(Cubicle& visitedCubicle) {
    Node<Cubicle*>* newNode = new Node<Cubicle*>(&visitedCubicle);
    if (!visitedCubicleList) {
        visitedCubicleList = newNode;
    } else {
        Node<Cubicle*>* currPtr = visitedCubicleList;
        while (currPtr->getNext() != nullptr) {
            currPtr = currPtr->getNext();
        }
        currPtr->setNext(newNode);
    }
}
void Cubicle::clearVisitedCubicles() {
    Node<Cubicle*>* current = visitedCubicleList;
    while (current != nullptr) {
        Node<Cubicle*>* toDelete = current;
        current = current->getNext();
        delete toDelete;
    }
    visitedCubicleList = nullptr;
}

    