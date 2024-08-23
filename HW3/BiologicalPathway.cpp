/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#include <iostream>
using namespace std;
#include "BiologicalPathway.h"

BiologicalPathway::BiologicalPathway(){
    pathwayHeadPtr = nullptr;
}

template<typename ItemType>
int BiologicalPathway::countItems(Node<ItemType>* headptr) const {
    int count = 0;
    Node<ItemType>* currentNode = headptr;
    while (currentNode != nullptr) {
        count++;
        currentNode = currentNode->getNext();
    }
    return count;
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName){
    int positionOfpath = findPosOfPathByID(pathwayId);
    if(positionOfpath == -1){
        
        Node<Pathways>* newNode = new Node<Pathways>(Pathways(pathwayId, pathwayName));
        
        if(pathwayHeadPtr == nullptr){
            pathwayHeadPtr = newNode; 
            cout<<"Added pathway "<<pathwayId<<"."<<endl;
        }
        else{
            Node<Pathways>* curNode = pathwayHeadPtr;
            Node<Pathways>* prevNode = nullptr;
            while(curNode != nullptr && (curNode->getItem().getIDofPath() <= newNode->getItem().getIDofPath())){
                prevNode = curNode;
                curNode = curNode->getNext();
            }
            if(curNode != nullptr){
                if(prevNode != nullptr){//ortaya bi yerlere ekleme.
                    prevNode->setNext(newNode);
                    newNode->setNext(curNode);
                }else{// curnode dolu ama bi oncesi bos yani basa ekliyorum.
                    newNode->setNext(curNode);
                    pathwayHeadPtr = newNode;
                }
            }else{// sona ekliyorum.
                prevNode->setNext(newNode);
                newNode->setNext(nullptr);
            }
            cout<<"Added pathway "<<pathwayId<<"."<<endl;
        }
    }else{
        cout<<"Cannot add pathway. There is already a pathway with ID "<<pathwayId<<"."<<endl;
    }
}

void BiologicalPathway::removePathway(const int pathwayId){
    int position = findPosOfPathByID(pathwayId);
    // if pathway does not exist
    if(position == -1){
        cout<<"Cannot remove pathway. There is no pathway with ID "<<pathwayId<<"."<<endl;
        return;
    }else{//if pathway exists scan through the list, and when id is found, remove progress

        Node<Pathways>* curPtr = nullptr;
        if(position == 1){
            curPtr = pathwayHeadPtr;
            pathwayHeadPtr = pathwayHeadPtr->getNext();
        }else{
            Node<Pathways>* prevPtr = getPathwayAt(position-1);
            curPtr = prevPtr->getNext();
            prevPtr->setNext(curPtr->getNext());
        }
        cout<<"Removed pathway "<<pathwayId<<"."<<endl;
        curPtr->setNext(nullptr);
        //releasing memories of Current path's, its proteins and each proteins' genes.
        Node<Proteins>* curPro = curPtr->getItem().ptrToProteinList;
        while (curPro != nullptr) {
            Node<Proteins>* nextPro = curPro->getNext();
            Node<Genes>* curGene = curPro->getItem().ptrToGeneList;
                while (curGene != nullptr) {
                    Node<Genes>* nextGene = curGene->getNext();
                    delete curGene;
                    curGene = nextGene; 
                }
            delete curPro; 
            curPro = nextPro;
        }
    delete curPtr;
    }
}

void BiologicalPathway::printPathways() const{
    if(pathwayHeadPtr == nullptr){
        cout<<"There are no pathways to show."<<endl;
        return;
    }
    cout<<"Pathways in the system:"<<endl;
    Node<Pathways>* curPtr = pathwayHeadPtr;
    while(curPtr != nullptr){
        const Pathways& curItem = curPtr->getItem();
        int numberOfProteins = 0;
        int totalGenes = 0;
        Node<Proteins>* proteinPtr = curItem.ptrToProteinList;
        while (proteinPtr != nullptr) {
            totalGenes += countItems(proteinPtr->getItem().ptrToGeneList);
            numberOfProteins++;
            proteinPtr = proteinPtr->getNext();
        }
        cout<<"Pathway " << curItem.getIDofPath()<<" : "<<curItem.getNameofPath()<<" ("<< numberOfProteins <<" Proteins) ("<<totalGenes<<" Genes)"<<endl;
        curPtr = curPtr->getNext();
    }
}

void BiologicalPathway::addProtein(const int proteinId, const int pathwayId){
    int positionOfSource = findPosOfPathByID(pathwayId);
    if(positionOfSource == -1){
        cout<<"Cannot add protein. There is no pathway with ID "<<pathwayId<<"."<<endl;
    }else{
        Node<Pathways>* curPtr = pathwayHeadPtr;
        while(curPtr != nullptr){
            int positionOfProtein = findPosOfProByID(proteinId, curPtr);
            if(positionOfProtein != -1){
                cout<<"Cannot add protein. There is a pathway having a protein with ID "<<proteinId<<"."<<endl;
                return;
            }
            curPtr = curPtr->getNext();
        }//if loop terminates, it mean there is no any pathway holding a protein with ID "proteinId".
        //then add it to target pathway...
        Node<Pathways>* sourceNode = getPathwayAt(positionOfSource);
        Node<Proteins>* toBeAddedNode = new Node<Proteins>(Proteins(proteinId));
        if(sourceNode->getItem().ptrToProteinList == nullptr){
            sourceNode->getItem().ptrToProteinList = toBeAddedNode;
            cout<< "Added protein "<< proteinId<<" to pathway "<< pathwayId<<"."<<endl;
        }else{
            Node<Proteins>* curNode = sourceNode->getItem().ptrToProteinList;
            Node<Proteins>* prevNode = nullptr;
            //eklenilecek yerin belirlenmesi
            while(curNode != nullptr && curNode->getItem().getId() <= toBeAddedNode->getItem().getId()){
                prevNode = curNode;
                curNode = curNode->getNext();
            }
            //ekleme islemi
            if(curNode != nullptr){
                if(prevNode != nullptr){//ortaya bir yerlere ekliyorum
                    prevNode->setNext(toBeAddedNode);
                    toBeAddedNode->setNext(curNode);
                }else{//basa ekliyorum
                    toBeAddedNode->setNext(curNode);
                    sourceNode->getItem().ptrToProteinList = toBeAddedNode;
                }
            }else{//sona ekliyorum.
                prevNode->setNext(toBeAddedNode);
                toBeAddedNode->setNext(nullptr);
            }
            cout<< "Added protein "<< proteinId<<" to pathway "<< pathwayId<<"."<<endl;
        }
    }
}

void BiologicalPathway::removeProtein(const int proteinId, const int pathwayId){
    int positionOfSource = findPosOfPathByID(pathwayId);
    if(positionOfSource == -1){
        cout<<"Cannot remove protein. There is no pathway with ID "<<pathwayId<<"."<<endl;
    }else{
        Node<Pathways>* targetPathway = getPathwayAt(positionOfSource);
        int positionOfProtein = findPosOfProByID(proteinId, targetPathway);
        if(positionOfProtein == -1){
            cout<<"Cannot remove protein. Pathway "<<pathwayId<<" does not have a protein with ID "<< proteinId<<"."<<endl;
            return;
        }
        Node<Proteins>* curPro = targetPathway->getItem().ptrToProteinList;
        if(positionOfProtein == 1){
            curPro = targetPathway->getItem().ptrToProteinList;
            targetPathway->getItem().ptrToProteinList = targetPathway->getItem().ptrToProteinList->getNext();
        }else{
            Node<Proteins>* prevPtr = getProteinAt(targetPathway,positionOfProtein-1);
            curPro = prevPtr->getNext();
            prevPtr->setNext(curPro->getNext());   
        }
        curPro->setNext(nullptr);// ama listeden once genleri(liste itemlarini) silmem gerekiyor!
        cout<<"Removed protein "<<curPro->getItem().getId()<<" from pathway "<< targetPathway->getItem().getIDofPath()<<"."<<endl; 
        Node<Genes>* curGene = curPro->getItem().ptrToGeneList;
        while(curGene != nullptr){
            Node<Genes>* nextGene = curGene->getNext();
            delete curGene;
            curGene = nextGene;
        }
        delete curPro;
        curPro = nullptr;
    }
}

void BiologicalPathway::printProteinsInPathway(const int pathwayId) const{
    int positionOfPath = findPosOfPathByID(pathwayId);
    if(positionOfPath == -1){
        cout<<"Cannot print proteins. There is no pathway with ID "<<pathwayId<<"."<<endl;
    }else{
        Node<Pathways>* targetPathway = getPathwayAt(positionOfPath);
        if(targetPathway->getItem().ptrToProteinList == nullptr){
            cout<<"There are no proteins to show in pathway "<<pathwayId<<"."<<endl;
            return;
        }
        cout<<"Proteins in pathway "<<pathwayId<<":"<<endl;
        Node<Proteins>* curNode = targetPathway->getItem().ptrToProteinList;
        while(curNode != nullptr){
            string output = "Protein ID : " + to_string(curNode->getItem().getId()) + ", Gene IDs : ";
            Node<Genes>* curGen = curNode->getItem().ptrToGeneList;
            if(curGen == nullptr){
                output+="None";
            }else{
                int id = curGen->getItem().getID();
                string toConcat = "[";
                toConcat += to_string(id);
                while(curGen->getNext() != nullptr){
                    toConcat +=", "+to_string(curGen->getNext()->getItem().getID());
                    curGen = curGen->getNext();
                }
                toConcat += "]";
                output += toConcat;
            }
            cout<<output<<endl;
            curNode = curNode->getNext();
        }
    }
}

void BiologicalPathway::addGene(const int geneId, const string geneName, const int proteinId){
    Node<Pathways>* curPath = pathwayHeadPtr;
    Node<Proteins>* targetProtein = nullptr;
    int positionOfProtein;
    if(curPath == nullptr){
        cout<< "Cannot add gene. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    while(curPath !=nullptr){
        positionOfProtein = findPosOfProByID(proteinId,curPath);
        if(positionOfProtein != -1){// liste taranirken o idli protein ile karsilasildi ve looptan cikildi.
            break;
        }
        curPath = curPath->getNext();
        if(curPath == nullptr){//butun liste tarandi ve o idli protein bulunamadi.
            cout<<"Cannot add gene. There is no protein with ID "<<proteinId<<"."<<endl;
            return;
        }
    }
    targetProtein = getProteinAt(curPath, positionOfProtein);// target proteinimizi bulduk simdi diger proteinler bu geni kapsiyor mu onu kontrol edecegim.
    Node<Pathways>* reset = pathwayHeadPtr;
    while(reset != nullptr){
        int positionOfGene = findPosOfGenByID(geneId,reset->getItem().ptrToProteinList);
        if(positionOfGene != -1){
            cout<<"Cannot add gene. Gene "<<geneId<<" is already in use."<<endl;
            return;
        }
        reset = reset->getNext();
    }
    
    Node<Genes>* curGene = targetProtein->getItem().ptrToGeneList;
    Node<Genes>* prevGene = nullptr;
    Node<Genes>* toBeAddedGene = new Node<Genes>(Genes(geneId,geneName));
    if(curGene == nullptr){
        targetProtein->getItem().ptrToGeneList = toBeAddedGene;
        cout<<"Added gene "<<geneId<<" to protein "<<proteinId<<"."<<endl;
        return;
    }
    while(curGene != nullptr && curGene->getItem().getID() <= toBeAddedGene->getItem().getID()){
        prevGene = curGene;
        curGene = curGene->getNext();
    }
    if(curGene != nullptr){
        if(prevGene != nullptr){//ortalarda bir yere ekliyorum.
            prevGene->setNext(toBeAddedGene);
            toBeAddedGene->setNext(curGene);
        }else{//curgene dolu ama prevgene bos, yani basa ekliyorum.
            toBeAddedGene->setNext(curGene);
            targetProtein->getItem().ptrToGeneList = toBeAddedGene;//o target proteinin head ptr i artik yeni nodum oldu.
        }
    }else{
        //curgene null ise listenin sonuna gelmisimdir yani sona ekleyecegim.
        prevGene->setNext(toBeAddedGene);
        toBeAddedGene->setNext(nullptr);
    }
    //ekleme islemi bitti
    cout<<"Added gene "<<geneId<<" to protein "<<proteinId<<"."<<endl;
}

void BiologicalPathway::removeGene(const int geneId, const int proteinId){
    Node<Pathways>* curPath = pathwayHeadPtr;
    int positionOfPro;
    int positionOfGene;
    if(curPath == nullptr){
        cout<<"Cannot remove gene. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    while(curPath != nullptr){// o idli proteini bulmaya calisiyorum, yoksa hata yazisi verdirecegim
        positionOfPro = findPosOfProByID(proteinId, curPath);
        if(positionOfPro != -1){// eger o idli proteinin bulursam looptan cikacagim.
            break;
        }
        curPath = curPath->getNext();
        if(curPath == nullptr){//butun listeyi taradim ama o idli proteini bulamadim. Hata verdiriyorum.
            cout<<"Cannot remove gene. There is no protein with ID "<<proteinId<<"."<<endl;
            return;
        }
    }//asagidaki statementlar sadece break durumunda yani o idli protein bulundugunda cikabilir.
    Node<Proteins>* sourceProtein = getProteinAt(curPath, positionOfPro);//o idli proteine erisiyorum.
    positionOfGene = findPosOfGenByID(geneId, sourceProtein);
    if(positionOfGene == -1){//kaynak protein dahilinde hedef gen yoksa
        cout<<"Cannot remove gene. There is no gene "<<geneId<<" encoding protein "<<sourceProtein->getItem().getId()<<"."<<endl;
        return;
    }// varsa cikarma islemine basla...
    Node<Genes>* curPtr = nullptr;
    if(positionOfGene == 1){
        curPtr = sourceProtein->getItem().ptrToGeneList;
        sourceProtein->getItem().ptrToGeneList = sourceProtein->getItem().ptrToGeneList->getNext();
    }else{
        Node<Genes>* prevPtr = getGeneAt(sourceProtein,positionOfGene-1);
        curPtr = prevPtr->getNext();
        prevPtr->setNext(curPtr->getNext());
    }
    cout<<"Removed gene "<<curPtr->getItem().getID()<<" from protein "<<sourceProtein->getItem().getId()<<"."<<endl;
    curPtr->setNext(nullptr);
    delete curPtr;
}

void BiologicalPathway::printGenesOfProtein(const int proteinId)const{
    Node<Pathways>* curPath = pathwayHeadPtr;
    int positionOfPro;
    
    if(curPath == nullptr){
        cout<<"Cannot print genes. There is no protein with ID "<<proteinId<<"."<<endl;
        return;
    }
    while(curPath != nullptr){// o idli proteini bulmaya calisiyorum, yoksa hata yazisi verdirecegim
        positionOfPro = findPosOfProByID(proteinId, curPath);
        if(positionOfPro != -1){// eger o idli proteinin bulursam looptan cikacagim.
            break;
        }
        curPath = curPath->getNext();
        if(curPath == nullptr){//butun listeyi taradim ama o idli proteini bulamadim. Hata verdiriyorum.
            cout<<"Cannot print genes. There is no protein with ID "<<proteinId<<"."<<endl;
            return;
        }
    }
    //looptan cikabilirsem o idli proteini bulmusumdur. 
    //eger o idli proteinin gen havuzu bossa hata verdirecegim.
    Node<Proteins>* sourceProtein = getProteinAt(curPath, positionOfPro);
    Node<Genes>* curGene = sourceProtein->getItem().ptrToGeneList;
    if(curGene == nullptr){
        cout<<"There are no genes to show in protein "<<proteinId<<"."<<endl;
        return;
    }
    cout<<"Genes in protein "<<proteinId<<":"<<endl;
    while(curGene != nullptr){
        cout<<"GENE "<< curGene->getItem().getID() << " : "<< curGene->getItem().getName()<<endl;
        curGene = curGene->getNext();
    }
}

Node<Pathways>* BiologicalPathway::getPathwayAt(int position) const{
    Node<Pathways>* curPtr = pathwayHeadPtr;
    for(int skip = 1; skip < position; skip++){
        curPtr = curPtr->getNext();
    }
    return curPtr;
}
Node<Proteins>* BiologicalPathway::getProteinAt(Node<Pathways>* sourcePathway, int position) const{
    Node<Proteins>* curPtr = sourcePathway->getItem().ptrToProteinList; 
    for(int skip = 1; skip < position; skip++){
        curPtr = curPtr->getNext();
    }
    return curPtr;
}
Node<Genes>* BiologicalPathway::getGeneAt(Node<Proteins>* sourceProtein, int position) const{
    Node<Genes>* curPtr = sourceProtein->getItem().ptrToGeneList;
    for(int skip = 1; skip < position; skip++){
        curPtr = curPtr->getNext();
    }
    return curPtr;
}
int BiologicalPathway::findPosOfGenByID(int geneId, Node<Proteins>* source) const{
    if(source == nullptr || source->getItem().ptrToGeneList == nullptr){
        return -1;
    }
    int position = 1;
    Node<Genes>* curPtr = source->getItem().ptrToGeneList;

    while(curPtr != nullptr){
        if(curPtr->getItem().getID() == geneId){
            return position;
        }
        curPtr = curPtr->getNext();
        position++;
    }
    return -1;
}
int BiologicalPathway::findPosOfProByID(int proteinId, Node<Pathways>* source) const{
    if (source == nullptr || source->getItem().ptrToProteinList == nullptr) {
        return -1;
    }//kaynak ya da kaynagin protein listesi bossa -1 dondur
    int position = 1;
    Node<Proteins>* curPtr = source->getItem().ptrToProteinList;

    while (curPtr != nullptr) {
        if (curPtr->getItem().getId() == proteinId) {
            return position;
        }
        curPtr = curPtr->getNext();
        position++;
    }
    return -1;// kaynak doluysa ama hedef id li protein yoksa -1 dondur
}
int BiologicalPathway::findPosOfPathByID(int pathwayId) const{
    if(pathwayHeadPtr == nullptr){
        return -1;
    }
    int position = 1;
    Node<Pathways>* curPtr = pathwayHeadPtr;
    while(curPtr != nullptr){
        if(curPtr->getItem().getIDofPath() == pathwayId){
            return position;
        }
        curPtr = curPtr->getNext();
        position++;
    }
    return -1;
}
BiologicalPathway::~BiologicalPathway(){
    Node<Pathways>* curPath = pathwayHeadPtr;
    while(curPath != nullptr){
        Node<Pathways>* nextPath = curPath->getNext();
        Node<Proteins>* curPro = curPath->getItem().ptrToProteinList;
        while(curPro != nullptr){
            Node<Proteins>* nextProtein = curPro->getNext();
            Node<Genes>* curGene = curPro->getItem().ptrToGeneList;
            while(curGene != nullptr){
                Node<Genes>* nextGene = curGene->getNext();
                delete curGene;
                curGene = nextGene;
            }
            delete curPro;
            curPro = nextProtein;
        }
        delete curPath;
        curPath = nextPath;
    }
}



