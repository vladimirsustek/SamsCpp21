#include <iostream>

using namespace std;

/** ABOUT POLYMORPHISM, VIRTUAL INHERITANCE CHAPTER 14*/

enum COLOR {BLACK, WHITE, BROWN, GREY};
typedef int HANDS;

/** Class dedicated to add just a special functionality and shall not have any data */
class TypicalMixinClass
{
public:
    HelloWorldReturning0() {cout << "----> Mixin class says Hello World! "; return 0; }
};


/** Abstract base class to show up implementation structure, all functions
    in the abstract class are intended to be pure virtual and overridden during
    declaring derived class */
class Organism
{
public:
    Organism() {cout << "Organism constructor" << endl; }
    virtual ~Organism() {cout << "Organism destructor" << endl; }
    virtual int GetAge() const = 0;
    virtual void SetAge(int age) = 0;
};

/** Base class with some "pure virtual" functions Sound() = 0, Move() = 0
    This means that the functions must be in derived class overridden
    There is also an implemented virtual function Sound() to be eventually
    used, however cannot be called without implementation in derived class */
class Animal: public Organism
{
public:
    Animal(int age):itsAge(age) {cout << "Animal constructor" << endl; }
    virtual ~Animal() {cout << "Animal destructor" << endl; }
    virtual int GetAge() const {return itsAge; }
    virtual void SetAge(int age) {itsAge = age; }
    virtual void Sound() = 0; /** Pure virtual functions */
    virtual void Move() = 0;
private:
    int itsAge;
};

void Animal::Sound()
{
    cout << "----> Animal screamed!" << endl;
}

class Horse: virtual public Animal /** Virtual inheritance ensure, that the common Animal base class will not be duplicated in next derived class*/
{
public:
    Horse(COLOR color, HANDS height, int age): Animal(age), itsColor(color), itsHeight(height) {cout << "Horse constructor" << endl; }
    virtual ~Horse() {cout << "Horse destructor" << endl; }
    virtual void Move() const {cout << "----> I can gallop" << endl; }
    virtual void Whinny() const { cout << "----> Whinny" << endl; }
    virtual HANDS GetHeight() const { return itsHeight; }
    virtual COLOR GetColor() const { return itsColor; }
    virtual void Sound() {Whinny(); Animal::Sound(); } /** Usage of pure virtual function implementation from base class */
private:
    COLOR itsColor;
    HANDS itsHeight;
};

class Bird: virtual public Animal  /** Virtual inheritance ensure, that the common Animal base class will not be duplicated in next derived class */
{
public:
    Bird(COLOR color, bool migrates, int age): Animal(age), itsColor(color), itsMigration(migrates) {cout << "Bird constructor" << endl; }
    virtual ~Bird() {cout << "Bird destructor" << endl; }
    virtual void Shirp() const {cout << "----> Shirp" << endl; }
    virtual void Move() const { cout << "----> I can fly" << endl; }
    virtual COLOR GetColor() const { return itsColor; }
    virtual bool GetMigration() const { return itsMigration; }
    virtual void Sound() {Shirp(); Animal::Sound();} /** Usage of pure virtual function implementation from base class */
private:
    COLOR itsColor;
    bool itsMigration;
};

/** Derived class which content one Horse, one Bird and only one Animal,
    as the Animal was virtually inherited. Specially is added  TypicalMixinClass */
class Pegasus: public Horse, public Bird, public TypicalMixinClass
{
public:
    Pegasus(COLOR color, HANDS height, int age):
        Animal(age),
        Horse(color, height, age),
        Bird(color, false, age)        {
            {cout << "Pegasus constructor" << endl; }
        }
    virtual ~Pegasus() {cout << "Pegasus destructor" << endl; }
    void Move() {Bird::Move(); } /** Ambiguity resolution -> inheritance of Move() from Bird */
    void Sound() {Horse::Sound(); } /** Ambiguity resolution -> inheritance of Sound() from Horse */
    COLOR GetColor() const {return Horse::GetColor(); } /** Ambiguity resolution -> inheritance of Color from Horse */
    HANDS GetHeight() const {return GetHeight(); }
};


/** On Purpose the argument is not derived, but base class of Horse */
void PrintHorseColor(Horse * pHorse)
{
    switch(pHorse->GetColor())
    {
        case BLACK: { cout << "----> The color is Black" << endl;} break;
        case WHITE: { cout << "----> The color is White" << endl;} break;
        case BROWN: { cout << "----> The color is Brown" << endl;} break;
        case GREY: { cout << "----> The color is Grey" << endl;} break;
        default : {cout << "Unspecified color" << endl; }
    }
}
int main(void)
{
    Pegasus* pPegasus = new Pegasus(BLACK, 2, 1);

    cout << "Returned: " << pPegasus->HelloWorldReturning0() << endl;

    cout << "Pegasus Move: " << endl;
    pPegasus->Move();

    cout << "Pegasus Sound: " << endl;
    pPegasus->Sound();

    PrintHorseColor(pPegasus);

    delete(pPegasus);

    return 0;
}


