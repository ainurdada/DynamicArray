#include "DynamicArray.h"
#include <iostream>

int main()
{
    //int t;
    Array<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    a.remove(3);


    auto it = a.iterator();
    std::cout << it.get() << std::endl;
    do {
        it.next();
        std::cout << it.get() << std::endl;
    } while (it.hasNext());
    
    /*for (auto it = a.iterator(); it.hasNext(); it.next())
        std::cout << it.get() << std::endl;*/
    
}