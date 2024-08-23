/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#ifndef __PROTEINS_H
#define __PROTEINS_H
#include <iostream>
#include "Genes.h"

using namespace std;

class Proteins{
public:

    Proteins(int ID);
    int getId() const;
    void setId(int newId);
    Node<Genes>* ptrToGeneList;
    int geneListLen;

private:
    int Id;
};

#endif