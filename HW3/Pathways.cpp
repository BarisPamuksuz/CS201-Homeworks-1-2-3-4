/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#include <iostream>
#include "Pathways.h"
using namespace std;

Pathways::Pathways(int Id, string name){
    this->setIDofPath(Id);
    this->setNameOfPath(name);
    this->ptrToProteinList = nullptr;
}
void Pathways::setNameOfPath(string name){
    this->namePath = name;
}
string Pathways::getNameofPath() const{
    return this->namePath;
}
void Pathways::setIDofPath(int id){
    this->IdPath = id;
}
int Pathways::getIDofPath() const{
    return this->IdPath;
}
