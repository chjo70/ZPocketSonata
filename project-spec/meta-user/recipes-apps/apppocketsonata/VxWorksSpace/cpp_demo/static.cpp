/* static.cpp - implements static class member demo */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

/**************************************************************************
 *
 * This demo will show how static members are handled within a
 * Class. Static members are common to all instances of the class and
 * derived classes, in which the static member is defined.
 *
 * StaticClass defines a class with only static member variables. All
 * instances of StaticClass will share the static members. There will
 * be no data allocated when a new instance of StaticClass is created
 * because the static members are allocated in global memory space,
 * but only accessable from within the class.
 *
 * Classes derived from a base class with static members inherit those
 * static members. Both the base class and the derived class will
 * access the same member variables.
 *
 **************************************************************************
 */
class StaticClass
{
public:

    void    setMemberA(int m)   { a = m;    }
    int     getMemberA() const  { return a; }
    void    setMemberB(int m)   { b = m;    }
    int     getMemberB() const  { return b; }

private:
    static  int     a;
    static  int     b;
};

/* Derived class of StaticClass.
 */
class DerivedStaticClass : public StaticClass
{
public:
    static void    setMemberC(int m) { c = m;    }
    static int     getMemberC()      { return c; }

private:
    static  int     c;
};

int StaticClass::a = 0;
int StaticClass::b = 0;
int DerivedStaticClass::c = 0;

void staticDemo()
{
    // We will create an instance of the StaticClass class. This
    // class contains only static members.
    StaticClass        static1;
    DerivedStaticClass static2;

    // Try viewing the members of both these classes. They should all
    // be zero 0.

    // We will set the values of the members so we can see that the
    // values changed for the base class and the derived class. If
    // you look at these member 'a' should be 1, 'b' should be 2 and
    // 'c' should be 3. The derived class should also show these
    // values.
    static1.setMemberA(1);
    static1.setMemberB(2);
    static2.setMemberC(3);

    // Now we will change all the value from the derived class. Notice
    // how the values for 'a' and 'b' in the base class reflect the
    // values changed in the derived class. This is because the
    // instances of both the base class and the derived class share
    // the members 'a' and 'b'.
    static2.setMemberA(3);
    static2.setMemberB(2);
    static2.setMemberC(1);

} /* staticDemo */

