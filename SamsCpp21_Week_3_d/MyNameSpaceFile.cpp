#include "MyNameSpaceFile.h"

namespace PrintAndSum
{
    PrintaNumClass::PrintaNumClass(int number)
    {

        cout << "PrintaNumClass constructor. Passed number to print is: " << number << endl;
        existInstances++;
    }
    PrintaNumClass::~PrintaNumClass()
    {
        cout << "SumTwoNumbersClass destructor" << endl;
        existInstances--;
    }
    int PrintaNumClass::existInstances = 0;

    SumTwoNumbersClass::SumTwoNumbersClass(int first, int second)
    {
        existInstances++;
        cout << "SumTwoNumbersClass constructor. Doing summ of " << first << " and " << second << endl;
        SumTwoNumbersClass::theSummedNumber = first + second;
    }
    SumTwoNumbersClass::~SumTwoNumbersClass()
    {
        cout << "SumTwoNumbersClass destructor" << endl;
        existInstances--;
    }

    int SumTwoNumbersClass::existInstances = 0;
}
