#include <iostream>
#include "list.hpp"
#include "heap.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    heap<int> a;
    a.insert(5);
    a.print();
    cout <<endl;
    a.insert(8);
    a.print();
    cout <<endl;
    a.insert(7);
    a.print();
    cout <<endl;
    return 0;
}
