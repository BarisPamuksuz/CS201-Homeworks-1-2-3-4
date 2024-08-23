/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#include <iostream>
using namespace std;
#include "Genes.h"

Genes::Genes(int ID, string name){
    this->setID(ID);
    this->setName(name);
}
void Genes::setName(string name){
    geneName = name;
}
string Genes::getName() const{
    return geneName;
}
void Genes::setID(int id){
    geneID = id;
}
int Genes::getID() const{
    return geneID;
}


