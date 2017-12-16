/*
Node.h
Zi Jian Wu
CSCI 235
Assignment 3
11/8/2016
*/
#ifndef NODE_H
#define NODE_H

#include "LinkedStack.h"

template<class ItemType>
class Node {   
public:
   Node();
   // @param an_item a given item.
   // Constucts a node holding an_item and pointing to nullptr.
   Node(const ItemType& an_item);
   
   // @param an_item a given item.
   // @param next_node pointer to next_nodex
   // Constucts a node holding an_item and pointing to next_node.
   Node(const ItemType& an_item, Node<ItemType>* next_node);

   // @param an_item
   // Sets the item_ to an_item.
   void SetItem(const ItemType& an_item);

   // @param next_node pointer to next node.
   // Sets next point to next_node.
   void SetNext(Node<ItemType>* next_node);

   // @return current item.
   ItemType GetItem() const;

   // @return pointer to next node.
   Node<ItemType>* GetNext() const;

private:
   ItemType        item_; // A data item
   Node<ItemType>* next_node_; // Pointer to next node
}; // end Node
#endif  // NODE_H
