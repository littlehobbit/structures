#include <iostream>
#include <list.h>
#include <list>
#include <vector>
#include <algorithm>
#include <tree.h>
#include <set>
#include <assert.h>

int main(int argc, char **argv)
{
    btl::bst<int> tree;

    tree.insert(10);
    tree.insert(9);
    tree.insert(11);
    tree.insert(132);
    tree.insert(2);

    std::cout << tree.count(0) << std::endl;
    std::cout << tree.count(2) << std::endl;
    std::cout << tree.count(131) << std::endl;
    std::cout << tree.count(132) << std::endl;


    return 0;
}
