#include <iostream>

using namespace std;



/** ABOUT OPERATOR OVERLOADING **/
class Counter
{
public:
    Counter();
    Counter(int initialValue): itsVal(initialValue) {};
    ~Counter() {};
    int GetItsVal() const {return itsVal;}
    void SetItsVal(int x) {itsVal = x ;}
    const Counter & operator++ (); /** Prefix operator overloading (unary)*/
    const Counter operator++ (int PostFixDummyArg); /** Postfix operator overloading (unary)*/
    Counter operator+ (const Counter & rhs);
    Counter operator=(const Counter & rhs);
    operator unsigned int();
private:
    int itsVal;
};


Counter::Counter():
    itsVal(0)
    {}

/** Prefix operator overloading (unary)*/
const Counter& Counter::operator++()
{
    /* Nothing else than incrementing itsVal and returning
    this changed object */
    ++itsVal;
    return *this;
}

/** Postfix operator overloading (unary) */
const Counter Counter::operator++(int PostFixDummyArg)
{
    /* see that the PostFixDummyArg is used only to distinguish
    between ++op and op++, so in this case its op++*/
    /* First is needed to create an copy of current object to return*/
    Counter temp(*this);
    /* Increment the value */
    ++itsVal;
    /* An simply return the original unchanged object as is from postfix wanted*/
    return temp;
}

Counter Counter::operator+ (const Counter & rhs)
{
    return Counter(itsVal + rhs.GetItsVal());
}

Counter Counter::operator= (const Counter & rhs)
{
    /* Protection for assigment this = this
    in this case when no allocation and deallocation
    takes place in the class in this fine */
        return *this;
    /* Copying all to fullfill '=' operation */
    itsVal = rhs.GetItsVal();

    return *this;
}

Counter::operator unsigned int()
{
    return(int (itsVal));
}
int main()
{
    Counter i;

    cout << "Creating i with initial value which is " << i.GetItsVal() << endl;
    i++;
    cout << "\nThe value of i after postfix-increment: i++, is " << i.GetItsVal() << endl;
    ++i;
    cout << "The value of i after prefix-increment: ++i, is " << i.GetItsVal() << endl;
    Counter j = ++i;
    cout << "The value of j after construction using: j = ++i, is " << j.GetItsVal() << endl;
    j = i++;
    cout << "The value of j after assigning: j = i++ is " << j.GetItsVal() << endl;

    cout << "\nHowever i was postfix-incremented " << i.GetItsVal() << endl;

    Counter first(1), second(2), third(0);

    cout << "\nCreating  Counter first(1), second(2), third() " << endl;

    third = first + second;

    cout << "Operation: third = first + second; " << endl;

    cout << "First's value is " << first.GetItsVal() << endl;
    cout << "Seconds's value is " << second.GetItsVal() << endl;
    cout << "Third's value is " << third.GetItsVal() << endl;

    cout << "Operation: second = first; " << endl;

    second = first;

    cout << "Seconds's value is " << second.GetItsVal() << endl;

    cout << "\nCreating an int object with initiliazation: int intValue = third " << endl;

    int intValue = third;

    cout << "Value of intValue is " << intValue << " as third's value was " << third.GetItsVal() << endl;

    return 0;
}
