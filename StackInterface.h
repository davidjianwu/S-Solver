/*
StackInterface.h
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016
*/
#ifndef STACKINTERFACE_H
#define STACKINTERFACE_H

template<class ItemType>
class StackInterface
{
public:
   /** Sees whether this stack is empty.
    @return True if the stack is empty, or false if not. */
   virtual bool IsEmpty() const = 0;
   
   /** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry is at the top of the stack.
    @param new_entry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
   virtual bool Push(const ItemType& new_entry) = 0;
   
   /** Removes the top of this stack.
    @post If the operation was successful, the top of the stack
    has been removed.
    @return True if the removal is successful or false if not. */
   virtual bool Pop() = 0;
   
   /** Returns the top of this stack.
    @pre The stack is not empty.
    @post The top of the stack has been returned, and
    the stack is unchanged.
    @return The top of the stack. */
   virtual ItemType Peek() const = 0;
}; // end StackInterface
#endif
