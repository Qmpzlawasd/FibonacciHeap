#include "FibTree.h"

void FibTree::appendRightTo(Node *toAdd, Node *init)
{

    if (init == nullptr)
    {
        toAdd->frateDr = toAdd;
        toAdd->frateSt = toAdd;
        rootElem = toAdd;
        return;
    }

    toAdd->parinte = init->parinte;
    toAdd->frateDr = init->frateDr;
    toAdd->frateSt = init;
    init->frateDr->frateSt = toAdd;
    init->frateDr = toAdd;
    if (rootElem->valoare < toAdd->valoare)
    {
        rootElem = toAdd;
    }
}
void FibTree::deleteNodeAndPromoteToRoot(Node *del)
{

    Node *c = del->copil;
    if (c != nullptr)
    {
        c->frateSt->frateDr = del->frateDr;
        del->frateDr->frateSt = c->frateSt;
        c->frateSt = del;
        del->frateDr = c;
        c->parinte = nullptr;
    }
    del->frateSt->frateDr = del->frateDr;
    del->frateDr->frateSt = del->frateSt;

    delete del;
}

 long long FibTree::getMax()
    {
        long long asd = rootElem->valoare;
        stergereRoot();
        return asd;
    }
    void FibTree::insetElem(const long long &x)
    {
        Node *a = new Node{0, x, 0};
        appendRightTo(a, rootElem);
    }
    void FibTree::merge(FibTree &x)
    {

        rootElem->frateDr->frateSt = x.rootElem->frateSt;
        x.rootElem->frateSt->frateDr = rootElem->frateDr;
        rootElem->frateDr = x.rootElem;
        x.rootElem->frateSt = rootElem;
        if (x.rootElem->valoare > this->rootElem->valoare)
        {
            this->rootElem = x.rootElem;
        }
        x.rootElem = nullptr;
    }
    void FibTree::stergereRoot()
    {
        std::vector<Node *> v(300001, nullptr);
        Node *viataNoua = rootElem->frateDr; // recalculam radacina dupa calamitate
        if (viataNoua == rootElem)
        {
            viataNoua = rootElem->copil;
            if (viataNoua == nullptr)
            {
                rootElem = nullptr;
                return;
            }
        }
        deleteNodeAndPromoteToRoot(rootElem);
        rootElem = viataNoua;
        Node *rulaj = viataNoua->frateDr;
        Node *tinMinte = rulaj->frateDr;
        while (rulaj != viataNoua)
        {
            if (rootElem->valoare < rulaj->valoare)
            {
                rootElem = rulaj;
            }
            if (v[rulaj->grad] == nullptr)
            {
                v[rulaj->grad] = rulaj;
            }
            else
            {
                while (v[rulaj->grad] != nullptr)
                {
                    if (v[rulaj->grad]->valoare > rulaj->valoare)
                    {
                        std::swap(rulaj, v[rulaj->grad]);
                    }
                    resolveConflictBetweenTwoParties(v, rulaj, v[rulaj->grad]);
                }
                v[rulaj->grad] = rulaj;
            }

            rulaj = tinMinte;
            tinMinte = tinMinte->frateDr;
        }
        while (v[rulaj->grad] != nullptr)
        {
            if (v[rulaj->grad]->valoare > rulaj->valoare)
            {
                std::swap(rulaj, v[rulaj->grad]);
            }
            resolveConflictBetweenTwoParties(v, rulaj, v[rulaj->grad]);
        }
    }
    void FibTree::resolveConflictBetweenTwoParties(std::vector<Node *> &v, Node *a, Node *b)
    {
        b->frateSt->frateDr = b->frateDr; // scoatem nodul mai mic din viata publica
        b->frateDr->frateSt = b->frateSt;
        if (a->copil == nullptr)
        {
            a->copil = b;
            b->frateDr = b;
            b->frateSt = b;
            b->parinte = a;
        }
        else
        {
            appendRightTo(b, a->copil);
        }

        v[a->grad] = nullptr;
        a->grad++;
    }
