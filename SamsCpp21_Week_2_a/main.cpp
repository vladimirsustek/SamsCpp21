#include <iostream>

using namespace std;

/** ABOUT BASICS OF INHERITANCE AND POLYMORPHISM, CHAPTER 12*/


/** If any method in class is virtual (expected to be overridden),
    also the destructor must (should) be virtual.
    However neither constructor nor copy constructor must not be virtual */

class Mammal /** Base class */
{
public: /** Members visible for everybody, even outside of the class for direct usage (e.g. myMammal.Speak())*/
    Mammal(): itsAge(0), itsNumber(0) {cout << "Mammal constructor" << endl; }
    Mammal(int age): itsAge(age) {cout << "Overloaded Mammal constructor" << endl; } /** Overloaded */

    Mammal(const Mammal & rhs) { cout << "Mammal copy constructor" << endl; }

    /** Virtual destructor is needed when a reference to Mammal (base class) object is expected
    but derived class object is passed (e.g. Horse). In this case can happen, that the derived
    object is deleted. As the destructor is virtual, derived class's destructor ensures to also
    call base class's destructor */

    virtual ~Mammal() {cout << "Mammal destructor" << endl; }

    virtual Mammal* Clone() {return new Mammal(*this); }
    virtual void Speak(void) {cout << "Mammal sounds" << endl; }
    void SetNumber(int num) {itsNumber = num; }
    int GetAge() {return itsAge; }
    int GetNumber(void) {return itsNumber; }

protected:
    int itsAge; /** Protected variable visible only for this class and derived classes (for method implementation)*/
private:
    int itsNumber; /** Private variable visible only for this class (for method implementation implementation) */
};


class Horse: public Mammal
{
public:
    Horse():Mammal(10) {; cout << "Horse constructor" << endl;} /** Passing Argument to Base Constructor (itsAge) */
    ~Horse() {cout << "Horse destructor" << endl;}
    void SetAge(int age) {itsAge = age;}
    void Speak(void) {cout << "Whinny" << endl;};
};

class Dog: public Mammal
{
public:
    Dog():Mammal(5) {cout << "Dog constructor" << endl;} /** Passing Argument to Base Constructor (itsAge)*/
    ~Dog() {cout << "Dog constructor" << endl;}
    void SetAge(int age) {itsAge = age; }
    void Speak(void) {cout << "Woef" << endl;};
};

class Cat: public Mammal
{
public:
    Cat():Mammal(2) {cout << "Cat constructor" << endl;} /** Passing Argument to Base Constructor (itsAge)*/
    ~Cat() {cout << "Cat constructor" << endl;}
    void SetAge(int age) {itsAge = age; }
    void Speak(void) {cout << "Meow" << endl;};
};

void FunctionDeletingMammal(Mammal *Mammal)
{
    delete(Mammal);
}

void FunctionSlicingDerivedClass(Mammal Mammal)
{
    Mammal.Speak();
}

int main()
{
    Mammal * pMammal;

    Mammal *clonedArrayOfPointers[4] = {0};
    cout << "Usage of Base class pointer to create a derived\nclass instances and access it's member\n" << endl;

    for(int i = 0; i < 4 ; i++)
    {
        /** Note that this works only when reference or pointer is used */
        switch(i)
        {
        case 0 :
            {
                pMammal = new Horse;
            }
            break;
        case 1 :
            {
                pMammal = new Dog;
            }
            break;
        case 2 :
            {
                pMammal = new Cat;
            }
            break;
        default :
            {
                pMammal = new Mammal;
            }
            break;
        }

        pMammal->Speak();
        pMammal->SetNumber(i);

        cout << "Objects number is: " << pMammal->GetNumber() << " and age: " << pMammal->GetAge() << endl;

        clonedArrayOfPointers[i] = pMammal->Clone();

        FunctionDeletingMammal(pMammal);

        cout << "----------------------" << endl;

    }

    cout << "Creating a Horse object" << endl;

    Horse * pHorse = new Horse;

    cout << "----------------------" << endl;

    cout << "Slicing down Horse object by passing it into function expecting base class argument (copy argument):" << endl;

    FunctionSlicingDerivedClass(*pHorse);

    cout << "----------------------" << endl;

    cout << "Calling base class method myHorse.Mammal::Speak() using derived Horse class instance: " << endl;

    Horse myHorse = *(pHorse);
    myHorse.Mammal::Speak();

    cout << "----------------------" << endl;

    cout << "Passing pointer to Horse into function excepting pointer to Mammal (function deleting the object)" << endl;

    FunctionDeletingMammal(pHorse);

    cout << "----------------------" << endl;

    cout << "Deleting Horse object from calling myHorse.Mammal::Speak() - LOCATED ON STACK" << endl;

    return 0;
}
