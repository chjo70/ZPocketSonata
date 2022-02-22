/* main.cpp - main module of C++ demo program */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#include    "array.h"
#include    "list.h"
#include    "string.h"
#include    "allocator.h"

/* prototypes/forward references */

void staticDemo();
void stringDemo();
void simpleClassDemo();
void templateClassDemo();
void inheritanceClassDemo();
void multipleInheritanceDemo();
void largeClassDemo();
void partialTypesDemo();
void virtualBaseDemo();
void exceptionDemo();

/**********************************************************************
* Function:    main()
* Description: main driver loop for C++ Demo program
*/

int main()
{
	while (1)
	{
	    Allocator allocator;
	
	    /* Create a simple object.
	     */
	    simpleClassDemo();
	
	    /* Create inherited objects.
	     */
	    inheritanceClassDemo();
	
	    multipleInheritanceDemo();
	
	    /* Demonstrate static member variables.
	     */
	    staticDemo();
	
	    /* Demonstrate templates.
	     */
	    templateClassDemo();
	
	    /* Create a larget object.
	     */
	    largeClassDemo();
	
	    /* Create some incomplete types.
	     */
	    partialTypesDemo();
	
	    /* Demonstrate virtual base classes.
	     */
	    virtualBaseDemo();
	    
	    /* Demonstrate strings.
	     */
	    stringDemo();
	    
	    /* Demonstrate exceptions.
	     */
	    exceptionDemo();
	}
}

/**********************************************************************
* Function:    simpleClassDemo()
* Description: shows how the debugger handles creation of objects.
*/
void simpleClassDemo()
{
    /* Object construction. Please step into the constructor for IntArray.
     */
    IntArray    a(10);

    /* Now initialize it. This should go into the operator [] function.
     * This function is inline and defined in the include file.
     */
    for (unsigned i = 0; i < a.getSize(); i++)
    {
        a[i] = i;
    }

    /* Test construction and initialization.
     */
     IntArray   b(5, 0xA);
}

/**********************************************************************
* Function:    templateClassDemo()
* Description: demonstrate template classes.
*
***********************************************************************
*/

void templateClassDemo()
{
    unsigned i;

    /* We will create two arrays using template class "Array".
     * The first array will be an integer and the second array
     * will be a floating point array. Please step through the
     * next two lines to see how this is done.
     */
    Array<int>      iarray(10);
    Array<float>    farray(20);

    /* To see how the template class is initialized, please step through
     * the following two loops. The first loop will initialize the
     * array of integers and the second loop will initialize the array
     * of floating point numbers.
     */
    for (i = 0; i < iarray.getSize(); i++)
    {
        iarray[i] = i;
    }

    float f = 0.0f;
    for (i = 0; i < farray.getSize(); i++)
    {
        farray[i] = f;
        f += (float)1.1;
    }
}

/**********************************************************************
* Function:    inheritanceClassDemo()
* Description: shows inhertance.
*
*              We will create two linked lists. The first will be of
*              integers and the second will be of floats. We will also
*              create two types of lists, one where the new item is
*              added to the end of the list and the other where the
*              item is added to the list in order.
*/

/* Create some integer items to be added to the list
 */
IntListItem intItem1(1);
IntListItem intItem2(2);
IntListItem intItem3(3);
IntListItem intItem4(4);
IntListItem intItem5(5);

FloatListItem floatItem1(1.1);
FloatListItem floatItem2(2.2);
FloatListItem floatItem3(3.3);
FloatListItem floatItem4(4.4);
FloatListItem floatItem5(5.5);

void inheritanceClassDemo()
{
    ListItem *item;

    /* Lets see how the items are created. Please use step into the
     * see how the next instruction creates an element.
     */
    IntListItem intItem0(0);

    /* Now lets see it create a different type of item. Please use
     * step into the see this go to the FloatListItem constructor.
     */
    FloatListItem floatItem0(1.0);

    /* Now we will start adding items to lists. We will create one
     * list that may contain either Integers or Floats.
     */
    List    linkedList;

    /* Let's start adding to the list. Items will be added to the end
     * of the list.
     */
    linkedList.add(intItem0);
    linkedList.add(intItem1);
    linkedList.add(intItem2);
    linkedList.add(floatItem0);
    linkedList.add(floatItem1);
    linkedList.add(floatItem2);

    /* Display the contents of the linked list. Notice a mixture of integers
     * and floating numbers are inserted into the list. The "displayValue"
     * function for these items will be resolved at runtime since "item" is a
     * pointer to the base class ListItem.
     */

    for (item = linkedList.getFirst();
	 item != 0;
	 item = item->getNext())
    {
        item->displayValue();
    }

    /* Remove the items from the list.
     */
    while (linkedList.getFirst() != 0)
    {
        linkedList.remove(*(linkedList.getFirst()));
    }

    /* If you stepped into during the adds, you would have seen how
     * that the member function "add" for List was called. Now we will
     * create another list that is sorted using SortedList which
     * derives from List, but changes the add function to sort the
     * list.
     *
     * NOTE: We will be using the overridded member function "compare"
     *       in the ListItem for each of the derived classes
     *       "IntListItem" and "FloatListItem". Since these cannot be
     *       compared between each other we will create two classes;
     *       one for integers and one for floats.
     */
    SortedList  intList;
    SortedList  floatList;

    /* Add the first items. Please step into the next instructions to
     * see how the "compare" member function get called for
     * IntListItem and FloatListItem. Also notice how the "add" member
     * function get called in the SortedList Class.
     */
    intList.add(intItem1);
    floatList.add(floatItem1);

    /* Now lets add something to the front of the list.
     */
    intList.add(intItem0);
    floatList.add(floatItem0);

    /* Now to the end of the list.
     */
    intList.add(intItem3);
    floatList.add(floatItem3);

    /* Now in the middle.
     */
    intList.add(intItem2);
    floatList.add(floatItem2);

    /* Display the contents of the sorted integer linked list.
     */
    for (item = intList.getFirst();
         item != 0;
         item = item->getNext())
    {
        item->displayValue();
    }

    /* Display the contents of the sorted floating linked list.
     */
    for (item = floatList.getFirst();
         item != 0;
         item = item->getNext())
    {
        item->displayValue();
    }

}

/**********************************************************************
* Function:    stringDemo()
* Description: string manipulation routine
*/

void stringDemo()
{
    String  s1 = "Wind River ";  // String Constructor, initialized to a
                                 // string value

    String  s1copy = s1;         // Copy construstor

    String  s2;                  // Create a blank string

    s2 = s1;                     // Overload the "=" operator

    String  s3 = "String ";
    String  s4 = "Simulation";

    String  s5 = s1 + s3 + s4;   // Demo the + overload

    			                 // Object destructors execute when
}                                // going out of scope


/**********************************************************************
* Function:    largeClassDemo()
* Description: shows how debugger handles large structures:
*               - enumerations
*/

class LargeEnum
{
    enum PARMS {
        RATE = 1,
        RSP,
        AR1_S,
        AR1_D,
        AR1_M,
        CV1_M,
        IC1_M,
        LA1_M,
        LV1_S,
        LV1_D,
        LV1_M,
        P1_S,
        P1_D,
        P1_M,
        PA1_S,
        PA1_D,
        PA1_M,
        RA1_M,
        RV1_S,
        RV1_D,
        RV1_M,
        AR2_S,
        AR2_D,
        AR2_M,
        CV2_M,
        IC2_M,
        LA2_M,
        LV2_S,
        LV2_D,
        LV2_M,
        P2_S,
        P2_D,
        P2_M,
        PA2_S,
        PA2_D,
        PA2_M,
        RA2_M,
        RV2_S,
        RV2_D,
        RV2_M,
        NBP_S,
        NBP_D,
        NBP_M,
        SPO2,
        SPO2_PPR,
        T1,
        T2,
        TOP_PARM = RATE,
        MAX_PARM = T2
    };

    int     data1;

public:
    LargeEnum();
};

LargeEnum::LargeEnum()
  : data1(0)
{
}

void largeClassDemo()
{
    LargeEnum   DemoObj;
}

class  UnknownIncompleteClass  *unknownClassPtr;
struct UnknownIncompleteStruct *unknownStructPtr;
union  UnknownIncompleteUnion  *unknownUnionPtr;
union  UnknownIncompleteEnum   *unknownEnumPtr;

void partialTypesDemo()
{
  /* Incomplete types are valid, examine the pointer
   * and what they point to.
   */
  unknownClassPtr  = 0;
  unknownStructPtr = 0;
  unknownUnionPtr  = 0;
  unknownEnumPtr   = 0;
}

