#include "DynamicArray.h"

int main()
{
    int t;
    Array<int> a;
    for (int i = 0; i < 100; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    for (auto it = a.iterator(); it.hasNext(); it.next())
        std::cout << it.get() << std::endl;
    
}