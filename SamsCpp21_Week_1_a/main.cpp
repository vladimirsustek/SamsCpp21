#include <iostream>
#include <string.h>
using namespace std;


/** ABOUT CONSTRUCTOR, ITS OVERLOADING, DESCRUCTOR AND COPY CONSTRUCTOR */

class Organism /** class with capital first letter, no colon : ! */
{
/** Public methods and data */
public:
    Organism(); /** constructor with several overloads (different arguments)*/
    Organism(int age);
    Organism(int age, float weight);
    Organism(int age, float weight, const char* name, int name_length);
    ~Organism(); /** destructor (no arguments)*/
    Organism(const Organism &); /** copy constructor */

    /** Some get methods */
    int GetAge() { return itsAge; } ;
    float GetWeight() { return itsWeight; };
    char *GetName() { return pItsName; };
    int GetNameLentgh() {return *pNameLength; };

    /** Some set methods */
    void SetAge(int age) {itsAge = age;};
    void SetWeight(float weight) {itsWeight = weight;};

/** Private data */
private:
    int itsAge; // 4
    float itsWeight; // 4
    char *pItsName; // 8
    int* pNameLength; // 8

};

/** Constructors ---------------------------------------------------------------------*/

/** - See allocation of data using 'new' - heap allocation
      in all the constructors is used allocation, and thus
      the pointer must be preserved in order to deallocation once
      the instance is destructed (otherwise memory leak occurs)
*/
Organism::Organism():
    itsAge(0), /** Initialization of private variable in constructor*/
    itsWeight(0) /** Initialization of private variable in constructor*/
    {
        char name[] = "Cell";

        pNameLength = new int;
        pItsName = new char[strlen(name)];

        *pNameLength = strlen(name);
        strncpy(pItsName, name, strlen(name));

        cout << name << " constructor of object: " << this << endl;
    };
Organism::Organism(int age):
    itsAge(age), /** Initialization of private variable in constructor*/
    itsWeight(0) /** Initialization of private variable in constructor*/
    {
        char name[] = "Insect";

        pNameLength = new int;
        pItsName = new char[strlen(name)];

        *pNameLength = strlen(name);
        strncpy(pItsName, name, strlen(name));

        cout << name << " constructor of object: " << this << endl;
    };
Organism::Organism(int age, float weight):
    itsAge(age), /** Initialization of private variable in constructor*/
    itsWeight(weight) /** Initialization of private variable in constructor*/
    {
        char name[] = "Fish";

        pNameLength = new int;
        pItsName = new char[strlen(name)];

        *pNameLength = strlen(name);
        strncpy(pItsName, name, strlen(name));

        cout << name << " constructor of object at: " << this << endl;
    };
Organism::Organism(int age, float weight, const char* name, int name_length):
    itsAge(age), /** Initialization of private variable in constructor*/
    itsWeight(weight) /** Initialization of private variable in constructor*/
    {
        pNameLength = new int;
        pItsName = new char[strlen(name)];

        *pNameLength = strlen(name);
        strncpy(pItsName, name, strlen(name));

        cout << name << " constructor of object at: " << this << endl;
    };

/** Copy constructors ---------------------------------------------------------------------*/

/** Always must look like void function with constant reference argument.
    The purpose is create a clone of the passed class. This means, that
    all the members must be copied and also, if there is an allocated memory
    pointer in the class, new memory must be allocated for cloned class and
    the content of the original copied into the newly allocated space.
    Note that once the constant reference is used. There is no access for class
    methods and thus, only dereference of rhs is valid way*/

Organism::Organism(const Organism & rhs)
{
    pItsName = new char[*rhs.pNameLength];
    pNameLength = new int;

    *pNameLength = *rhs.pNameLength;
    strncpy(pItsName, rhs.pItsName, *rhs.pNameLength);

    SetAge(rhs.itsAge);
    SetWeight(rhs.itsWeight);

    cout << "Copy constructor of object at: " << &rhs << " into: " << this << endl;

}

/** Destructor ---------------------------------------------------------------------*/
Organism::~Organism()
{
    cout << pItsName << " destructor of object at: " << this << endl;

    delete pItsName;
    delete pNameLength;
};

int DisplayOrganismProperties(Organism Organism)
{
    int err = -1;
    cout << "\nDisplayOrganismProperties(Organism Organism):" << endl;
    cout << "   Age=" << Organism.GetAge() << endl;
    cout << "   Weight=" << Organism.GetWeight() << endl;
    cout << "   Name=" << Organism.GetName() << "\n" << endl;

    return err;
}
void ChangeOrganismPropertiesIntoMax(Organism & rhs)
{
    rhs.SetAge(1);
    rhs.SetWeight(1);
}
void EraseOrganismProperties(Organism* pOrganism)
{
    pOrganism->SetAge(0);
    pOrganism->SetWeight(0);
}
int main()
{
    /* Class occupies as much as its data do - methods do not reflect on the size*/
    cout << "Size of instance class Organism is= " << sizeof(Organism) << "bytes\n" << endl;
    cout << "Creating an instance of Organism called Rat, 1 year old, having 500 grams\n" << endl;
    Organism Organism(5, 500, "Rat", strlen("Rat"));


    cout << "\ninfo: myOrganism.GetAge()= " << Organism.GetAge() << ", myOrganism.GetWeight()= " <<  Organism.GetWeight() << "\n" << endl;

    DisplayOrganismProperties(Organism);

    return 0;
}
