#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

/** ABOUT ADVANCED INHERITANCE (AGGREGATION, DELEGATION, IMPLEMENT ONE CLASS IN TERM OF OTHER), CHAPTER 16*/

class Alfa
{
public:
    Alfa() {cout << "Alfa's constructor" << endl;}
private:
    static void HelloFunction() {cout << "Alfa's Secret";}
    friend class Delta; /* This allowes Delta to touch everything what Alfa has*/
};
class Beta
{
public:
    Beta() {cout << "Beta's constructor" << endl;}
    void ItsOnlyMethod() {cout << "Beta's only method";};
    static char character;
private:
    static char privateCharacter; /* This can't be touched outside this class without having friend */

};

//string Beta::character = 'β'; // did not fit within 8-bits
char Beta::character = 'B';
char Beta::privateCharacter = 'B';

class Gamma /* The Gamma has-a Alfa, Beta and Gamma */
{
public:
    Alfa a;
    Beta b;
    Gamma() {cout << "Gamma's constructor" << endl;}
    void ItsOnlyMethod() {cout << "Gamma's only method" << endl;};
};
class Delta
{
public:
    Alfa a;
    Delta()
    {
        cout << "Delta constructor" << endl;
        cout << "Delta knows: ";
        Alfa::HelloFunction();
        cout << " because Alfa declared Delta as a friend and so can Delta\n" \
        "             access Alfa's PRIVATE static function (static = no instance needed)" << endl;
    }
};
class TheSameGamma : public Gamma /* The TheSameGama is-a Gamma*/
{
public:
    TheSameGamma() {cout << "TheSameGamma constructor" <<endl;}
};
class Epsilon : private Beta
{
public:
    Epsilon()
    {
        cout << "Epsilon constructor" << endl;
        cout << "Epsilon knows public string of Beta =\"" << Beta::character <<"\"because privately inherits" << endl;
        cout << "         from Beta and can touch anything public from Beta for Epsilon's implementation" << endl;
        cout << "         However cant touch Beta's private methods or private data's such a:\n\t\t Beta::privateCharacter" << endl;
    }
};
int main()
{
    /* Aggregation is just "has-a" relationship */
    cout << "Aggregation example:" << endl;
    Gamma g;

    cout << "\nDelegation example:" << endl;
    /* Delegation is just a "is-a" relationship */
    TheSameGamma theSameGammaInstance;
    theSameGammaInstance.ItsOnlyMethod();

    /* Implementing one class in term of another */
    cout << "\nImplementing class in term of another example using a friend class:" << endl;
    Delta d;
    cout << "\nImplementing class in term of another example private inheritance:" << endl;
    Epsilon e;

    cout << "However Epsilon does not forward any Beta's methods such as e.ItsOnlyMethod()" << endl;
    //e.ItsOnlyMethod(); // This will not work
    return 0;
}
