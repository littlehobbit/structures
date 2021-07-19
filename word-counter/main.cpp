#include <iostream>
#include <list.h>
#include <list>
#include <vector>
#include <algorithm>

int main(int argc, char **argv) {

    btl::list<int> ilist;
    ilist.push_back(10);
    ilist.push_back(15);

    auto even = std::find_if(ilist.begin(), ilist.end(), [](int el) -> bool { return el % 2 == 0; });
    if (even != ilist.end()) {
        std::cout << "Was found " << *even << std::endl;
    }

    return 0;
}
