#ifndef MYNAMESPACEFILE_H_INCLUDED
#define MYNAMESPACEFILE_H_INCLUDED

#include <iostream>


using std::cout;
using std::endl;

namespace PrintAndSum
{
    /* namespace Second */
    class PrintaNumClass
    {
    public:
        PrintaNumClass(int number);
        ~PrintaNumClass();
        static int existInstances;
    };

    class SumTwoNumbersClass
    {
    public:
        SumTwoNumbersClass(int first, int second);
        ~SumTwoNumbersClass();
        static int existInstances;
        int theSummedNumber;
    };

}

#endif // MYNAMESPACEFILE_H_INCLUDED
