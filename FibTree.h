#pragma once
#include <vector>
class Node
{
    friend class FibTree;

private:
    long long valoare;
    bool areMark;
    unsigned grad;
    Node *parinte;
    Node *copil;
    Node *frateSt;
    Node *frateDr;
    Node(bool areMark, long long valoare, unsigned grad) : areMark(areMark), valoare(valoare), grad{grad}, parinte(nullptr), copil(nullptr), frateSt(nullptr), frateDr(nullptr){};
    Node(){};
};

class FibTree
{
private:
    Node *rootElem;

    void deleteNodeAndPromoteToRoot(Node *);
    void appendRightTo(Node *, Node *);

public:
    long long getMax();
    void stergereRoot();
    void merge(FibTree &);
    void insetElem(const long long &);
    void resolveConflictBetweenTwoParties(std::vector<Node *> &, Node *, Node *);
    FibTree() : rootElem{nullptr} {}
};
