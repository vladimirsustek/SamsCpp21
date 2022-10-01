#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <algorithm>


/** ABOUT TEMPLATES (A BIT OF ASSING OPERATOR << OVERLOADING), (NOT ONLY STD) SEQUENCE AND ASSOCIATIVE CONTAINERS, CHAPTER 19*/
using namespace std;

constexpr int DefaultSize = 3;

/* Class to be used as a type of containers */
class Human
{
public:
    Human(): itsName("NoName"), itsAge(0){}
    Human(const string & name, int age): itsName(name), itsAge(age){}
    ~Human(){}
    Human(const Human & rhs){itsAge = rhs.itsAge;itsName = rhs.itsName;}
    Human& operator=(const Human& rhs);
    friend ostream& operator<<(ostream& os, const Human& rhs);
    string itsName;
    int itsAge;
};

Human& Human::operator=(const Human& rhs)
{
    itsName = rhs.itsName;
    itsAge = rhs.itsAge;
    return *this;
}

ostream& operator<<(ostream& os, const Human& rhs)
{
    os << rhs.itsName << " is " << rhs.itsAge << " years old\n";
    return os;
}

/* Container custom sequence template class */
template <typename T>
class MyArray
{
public:
    MyArray(int itsSize = DefaultSize);
    MyArray(const MyArray &rhs);
    ~MyArray() { delete [] pType; }

    /** operators to assign the same element types and index by [] */
    MyArray& operator=(const MyArray&);
    const T& operator[](int offSet) const { return pType[offSet]; }

    int GetSize() const { return itsSize; }

    /* friend function of when <int> type */
    friend void Intrude(MyArray<int>);

private:
    T *pType;
    int itsSize;
};

/* Non template friend function for integers only */
void Intrude(MyArray<int> theArray)
{
    cout << endl << "*** Intrude ***" << endl;
    for (int i = 0; i < theArray.itsSize; i++)
    cout << "i: " << theArray.pType[i] << endl;
    cout << endl;
}

/* Default constructor allocates a T-type array of "size" length*/
template <class T>
MyArray<T>::MyArray(int size):
    itsSize(size)
{
    pType = new T[size];
}

/* Specialized constructor for type <int> */
template<>
MyArray<int>::MyArray(int size):
    itsSize(size)
{
    pType = new int[size];
    for (int idx = 0; idx < itsSize; idx++) pType[idx] = rand();
}

/* Copy constructor to copy values into being copied rhs referrence */
template <class T>
MyArray<T>::MyArray(const MyArray &rhs)
{
    itsSize = rhs.GetSize();
    pType = new T[itsSize];
    for (int i = 0; i < itsSize; i++)
        pType[i] = rhs[i];
}

/* Assign operator */
template <class T>
MyArray<T>& MyArray<T>::operator=(const MyArray &rhs)
{
    if (this == &rhs)
        return *this;

    delete [] pType;

    itsSize = rhs.GetSize();
    pType = new T[itsSize];

    for (int i = 0; i < itsSize; i++)
        pType[i] = rhs[i];
    return *this;
}

/* General friend-template function -> (tries to) prints content regardless class type */
template <class T>
ostream& operator<< (ostream& output, const MyArray<T>& theArray)
{
    for (int i = 0; i<theArray.GetSize(); i++)
    output << "[" << i << "] " << theArray[i] << endl;
    return output;
}

template <typename T>
class PrintSingleContainerElement
{
public:
    void operator()(T & element)
    {
        cout << element << endl;
    }
};

PrintSingleContainerElement<Human> PrintHuman;
PrintSingleContainerElement<int> PrintInt;

int DoRand(void)
{
    return rand();
}
int main(void)
{
    /** Sequence containers ------------------------------------ */

    cout << "Sequence containers: (accessed by index or const_interator)\n-list\n-vector,\n-stack,\n-queue\n-dequeue\n" << endl;
    cout << "Associative: (accessed by \"keyword\"):\n-map\n-multimap\n-set\n-multiset\n-bitset\n" << endl;

    /* Creating instance of the custom container type array */
    MyArray<int> theArray;
    /* Using assign operator to print content ass describe in
    friend ostream& operator<<(ostream& os, const Human& rhs); */
    cout << "MyArray<int> of default size= " << DefaultSize << " with default constructor (randomized) is:" << endl;
    cout << theArray;

    cout << "\nCreating instance of the STD's vector<int> theArray2(" << DefaultSize << ")" << endl;
    vector<int> theArray2(DefaultSize);

    cout << "\nCopying theArray into theArray2 \"backwards\"" << endl;
    for (int idx = 0; idx < theArray.GetSize(); idx++)
    {
        /* Copying from theArray backwards*/
        theArray2[idx] = theArray[theArray.GetSize() - idx - 1];
    }

    cout << "\nForce write operation at the end of the array of the number 7 - vector must grow" << endl;
    theArray2.push_back(7);

    cout << "\nPrint out theArray2 using for loop and theArray2.size limit";
    cout << "because << operator is not implemented\n" << endl;

    for (size_t idx = 0; idx < theArray2.size(); idx++)
    {
        cout <<"[" << idx << "] "<< theArray2[idx] << endl;
    }

    cout << "\nCreating an list<Human> growingList(" << DefaultSize << ")" << endl;
    list<Human> growingList(3);

    cout << "push_back, push_front and push_back by known Human instances\n" << endl;
    Human firstie("Julia", 29);
    Human secondie("Britney", 27);
    Human thirdie("Avril", 30);

    growingList.push_back(firstie);
    growingList.push_front(secondie);
    growingList.push_back(thirdie);

    cout << "Print out using only \"Browsing way\" - the const_interator\n" << endl;

    for (list<Human>::const_iterator ci = growingList.begin(); ci != growingList.end(); ci++)
        cout << *ci;

    cout << "\nObvious that list optimizes it's size" << endl;

    cout << "\nCreating a map<string, Human> theMap;\n" << endl;
    cout << "\nAdding already used Humans using 3x theMap[firstie.itsName] = firstie;\n" << endl;

    map<string, Human> theMap;

    theMap[firstie.itsName] = firstie;
    theMap[secondie.itsName] = thirdie;
    theMap[thirdie.itsName] = firstie;

    /** Associative containers ------------------------------------ */

    cout << "Calling: cout << theMap[\"Julia\"] = " << theMap["Julia"] << endl;

    cout << "Usage of const_iterator to print the whole theMap, however with both map parameters ci->first, ci->second\n" << endl;
    for (map<string, Human>::const_iterator ci = theMap.begin(); ci != theMap.end(); ci++)
        cout << ci->first << ": " << ci->second << endl;

    /** Algorithm overview */

    cout << "Algorithm from <algorithm> are divided into:" << endl;
    cout << "-Non-Mutating (not changing elements in list): for_each" << endl;
    cout << "-Mutating (changing elements in list): e.g. fill"  << endl;
    cout << "-Sorting and similar () e.g sort " << endl;

    cout << "\nUsage of for_each(growingList.begin(), growingList.end(), PrintHuman);\n" << endl;

    for_each(growingList.begin(), growingList.end(), PrintHuman);

    cout << "\nfor_each(theArray2.begin(), theArray2.end(), PrintInt);" << endl;

    for_each(theArray2.begin(), theArray2.end(), PrintInt);

    cout << "\nsort(theArray2.begin(), theArray2.end());" << endl;

    sort(theArray2.begin(), theArray2.end());

    for_each(theArray2.begin(), theArray2.end(), PrintInt);

    cout << "\nfill(theArray2.begin(), theArray2.end(), 0);" << endl;

    fill(theArray2.begin(), theArray2.end(), 0);

    for_each(theArray2.begin(), theArray2.end(), PrintInt);

    return 0;
}
