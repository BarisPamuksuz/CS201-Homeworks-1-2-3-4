/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#ifndef __BIOLOGICALPATHWAY_H
#define __BIOLOGICALPATHWAY_H
#include <string>
#include "Pathways.h"
using namespace std;

class BiologicalPathway {
public:

    BiologicalPathway();
    ~BiologicalPathway();

    void addPathway(const int pathwayId, const string pathwayName);
    void removePathway( const int pathwayId);
    void printPathways() const;

    void addProtein( const int proteinId, const int pathwayId);
    void removeProtein( const int proteinId, const int pathwayId);
    void printProteinsInPathway( const int pathwayId ) const;

    void addGene( const int geneID, const string geneName, const int proteinId);
    void removeGene( const int geneID, const int proteinId);
    void printGenesOfProtein( const int proteinId) const;
    
    int findPosOfProByID(int proteinId, Node<Pathways>* source) const;
    int findPosOfGenByID(int genId, Node<Proteins>* source ) const;
    int findPosOfPathByID(int pathwayId) const;

    Node<Pathways>* getPathwayAt(int position) const;
    Node<Proteins>* getProteinAt(Node<Pathways>* sourcePathway, int position) const;
    Node<Genes>* getGeneAt(Node<Proteins>* sourceProtein, int position) const; 

    
    template<class ItemType>
    int countItems(Node<ItemType>* headptr) const;

    Node<Pathways>* pathwayHeadPtr;
};

#endif