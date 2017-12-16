/*
LinkedStack.h
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016
*/
#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "StackInterface.h"
#include "Node.h"

template<class ItemType>
class Node;

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
 public:
  // Constructors and destructor:
  LinkedStack();                                   // Default constructor
  LinkedStack(const LinkedStack<ItemType>& a_stack);// Copy constructor 
  virtual ~LinkedStack();                          // Destructor
  
  // Stack operations:
  bool IsEmpty() const;
  bool Push(const ItemType& new_item);
  bool Pop();
  ItemType Peek() const;

 private:
  Node<ItemType>* top_ptr_; // Pointer to first node in the chain;
                           // this node contains the stack's top

}; // end LinkedStack

//#include "LinkedStack.cpp"
#endif  // LINKED_STACK_H
