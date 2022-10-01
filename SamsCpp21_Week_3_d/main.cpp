#include <iostream>
#include "MyNameSpaceFile.h"

using PrintAndSum::PrintaNumClass;
using PrintAndSum::SumTwoNumbersClass;

int main()
{
    cout << "Exist instances of SumTwoNumbersClass: " << SumTwoNumbersClass::existInstances << endl;
    cout << "Exist instances of PrintaNumClass: " << PrintaNumClass::existInstances << endl;

    SumTwoNumbersClass theSum(1, 2);
    PrintaNumClass thePrint(theSum.theSummedNumber);

    cout << "Exist instances of SumTwoNumbersClass: " << SumTwoNumbersClass::existInstances << endl;
    cout << "Exist instances of PrintaNumClass: " << PrintaNumClass::existInstances << endl;

    return 0;
}
