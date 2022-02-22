/* virtualBase.cpp - implements virtual base classes class demo */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

/**************************************************************************
 *
 * This demo will show how virtual base classes are used in a class.
 * The purpose of a virtual base class is to create 1 definition of
 * a common class.
 *
 **************************************************************************
 */
class BaseClass
{
public:
    char     baseMember;
};

class DerivedClass1 : public virtual BaseClass
{
public:
    char     derivedClass1Member;
};

class DerivedClass2 : public virtual BaseClass
{
public:
    char     derivedClass2Member;
};

class UltimateDerivedClass : public DerivedClass2, public DerivedClass1
{
};

void virtualBaseDemo()
{
    // We will create an instance of the StaticMember class. This
    // class contains only static members.
    UltimateDerivedClass ultimate;

    ultimate.derivedClass1Member = '1';
    ultimate.derivedClass2Member = '2';
    ultimate.baseMember          = 'B';

    // Try viewing the members of ultimate. There should
    // be three members, set as indicated above.
    ultimate.baseMember++;
}

