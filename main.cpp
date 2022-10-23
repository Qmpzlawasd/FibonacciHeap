#include <iostream>
#include <vector>
#include "FibTree.h"
#include "FibTree.cc"


int main()
{
    std::vector<FibTree> v;
    unsigned int n, quer;
    std::cin >> n >> quer;
    v.resize(n);
    for (size_t i = 0; i < quer; i++)
    {
        int op, elem, setNum;
        std::cin >> op >> setNum;
        setNum--;
        switch (op)
        {
        case 1:
            std::cin >> elem;
            v[setNum].insetElem(elem);
            break;

        case 3:
            std::cin >> elem;
            elem--;
            v[setNum].merge(v[elem]);
            break;

        default:

            std::cout << v[setNum].getMax() << "\n";

            break;
        }
    }
}
