#include <iostream>

using namespace std;

/** ABOUT STATIC CLASS VARIABLES, CLASS STATIC FUNCTIONS, POINTERS TO CLASS FUNCTION, CHAPTER 15*/


class CountedClass
{
public:
    CountedClass() {cout << "CountedClass constructor, exists instances : " << ++existInstances << endl; itsNumber = existInstances - 1;}
    virtual ~CountedClass() {cout << "CountedClass destructor, exists instances : " << --existInstances << endl;}
    HelloWorldReturnNumber();
    virtual void GetNum() = 0;
    static GetNumberOfExisting() {return existInstances; } /** A declaration of static function which does not have THIS pointer and cannot access any non-static variables */
    static int existInstances; /** A static variable declaration */
protected:
    int itsNumber;
};

int CountedClass::existInstances = 0; /** Necessary definition and initilization of the static variable */


/** Some derived classes to show class function pointer usage, default destructor and constructor*/
class CzechCountedClass : public CountedClass
{
    void GetNum() {cout << "CZECH: Cislo je: " << itsNumber << endl;}
};

class GermanCountedClass : public CountedClass
{
    void GetNum() {cout << "DEUTSCH: Die Nummer ist: " << itsNumber << endl;}
};

class EnglishCountedClass : public CountedClass
{
    void GetNum() {cout << "ENGLISH: The number is: " << itsNumber << endl;}
};

CountedClass::HelloWorldReturnNumber()
{
    cout << "Hello World!" << endl;
    return itsNumber;
}
int main(void)
{
    /** Class member function must contain class type, return type and arguments and also
        can be used only to point into functions of the same class type or derived ancestors */
    void (CountedClass::*pFn)(void) = 0;

    CountedClass * arrOfPointers[10] = {0};
    for(int i = 0; i < 10; i++)
    {
        switch(i%3)
        {
            case 0 : arrOfPointers[i] = new CzechCountedClass; break;
            case 1 : arrOfPointers[i] = new GermanCountedClass; break;
            default : arrOfPointers[i] = new EnglishCountedClass; break;
        }

        pFn = CountedClass::GetNum;

        cout << "\nCalling an assigned function pointer pFnNoArgRetInt()" << endl;

        /** Call the function using pointer (of base class type), picking up to pointer from array of pointers */
        (arrOfPointers[i]->*pFn)();

        cout << endl;

        /** Just use static out-of-class access into static variable and function */
        if (5 == i)
        {
            cout << "Outside of the class, accessed static variable CountedClass::existInstances: " << CountedClass::existInstances << endl;
            cout << "Outside of the class, accessed static variable CountedClass::GetNumberOfExisting() " << CountedClass::GetNumberOfExisting() << endl;
            cout << endl;
        }

    }

    for(int i = 0; i < 10; i++)
    {
        delete arrOfPointers[i];
    }

    /** Just use static out-of-class access into static variable and function - here no instance of class exists */
    cout << "\nOutside of the class, accessed static variable CountedClass::existInstances: " << CountedClass::existInstances << endl;
    cout << "Outside of the class, accessed static variable CountedClass::GetNumberOfExisting() " << CountedClass::GetNumberOfExisting() << endl;

    return 0;
}


