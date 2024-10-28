#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <stdexcept>

// Exception class for out-of-bound errors
class OutOfBound {};

// Forward declaration of LinkList
template <class elemType> class LinkList;

// Node class definition
template <class elemType> class Node {
  friend class LinkList<elemType>;

private:
  elemType data; // Data stored in the node
  Node *next;    // Pointer to the next node

public:
  Node() : next(nullptr) {}
  Node(const elemType &e, Node *n = nullptr) : data(e), next(n) {}
};

// LinkList class definition
template <class elemType> class LinkList {
private:
  Node<elemType> *head; // Pointer to the head (dummy) node

public:
  LinkList();
  bool isEmpty() const;
  bool isFull() const { return false; }
  int length() const;
  elemType get(int i) const;
  int find(const elemType &e) const;
  void insert(int i, const elemType &e);
  void remove(int i, elemType &e);
  void reverse();
  void clear();
  ~LinkList();
};

/**
 * Constructor
 * Initializes an empty linked list with a dummy head node.
 */
template <class elemType> LinkList<elemType>::LinkList() {
  head = new Node<elemType>(); // Create dummy head node
}

/**
 * Destructor
 * Clears the list and deletes the head node to free memory.
 */
template <class elemType> LinkList<elemType>::~LinkList() {
  clear();
  delete head;
}

/**
 * Checks if the list is empty.
 * @return True if the list is empty, false otherwise.
 */
template <class elemType> bool LinkList<elemType>::isEmpty() const {
  return head->next == nullptr;
}

/**
 * Returns the number of elements in the list.
 * @return The length of the list.
 */
template <class elemType> int LinkList<elemType>::length() const {
  int len = 0;
  Node<elemType> *p = head->next;
  while (p != nullptr) {
    len++;
    p = p->next;
  }
  return len;
}

/**
 * Retrieves the element at index i.
 * Throws OutOfBound exception if index is invalid.
 * @param i Index of the element to retrieve.
 * @return The element at index i.
 */
template <class elemType> elemType LinkList<elemType>::get(int i) const {
  if (i < 0)
    throw OutOfBound();

  Node<elemType> *p = head->next;
  int idx = 0;
  while (p != nullptr && idx < i) {
    p = p->next;
    idx++;
  }
  if (p == nullptr)
    throw OutOfBound();
  return p->data;
}

/**
 * Finds the index of the first occurrence of element e.
 * @param e The element to find.
 * @return The index of e if found, otherwise -1.
 */
template <class elemType>
int LinkList<elemType>::find(const elemType &e) const {
  Node<elemType> *p = head->next;
  int idx = 0;
  while (p != nullptr) {
    if (p->data == e)
      return idx;
    p = p->next;
    idx++;
  }
  return -1;
}

/**
 * Inserts element e at index i.
 * Throws OutOfBound exception if index is invalid.
 * @param i The index at which to insert e.
 * @param e The element to insert.
 */
template <class elemType>
void LinkList<elemType>::insert(int i, const elemType &e) {
  if (i < 0)
    throw OutOfBound();

  Node<elemType> *p = head;
  int idx = 0;
  while (p != nullptr && idx < i) {
    p = p->next;
    idx++;
  }
  if (p == nullptr)
    throw OutOfBound();

  Node<elemType> *newNode = new Node<elemType>(e, p->next);
  p->next = newNode;
}

/**
 * Removes the element at index i and stores it in e.
 * Throws OutOfBound exception if index is invalid.
 * @param i The index of the element to remove.
 * @param e Variable to store the removed element.
 */
template <class elemType> void LinkList<elemType>::remove(int i, elemType &e) {
  if (i < 0)
    throw OutOfBound();

  Node<elemType> *p = head;
  int idx = 0;
  while (p->next != nullptr && idx < i) {
    p = p->next;
    idx++;
  }
  if (p->next == nullptr)
    throw OutOfBound();

  Node<elemType> *q = p->next;
  p->next = q->next;
  e = q->data;
  delete q;
}

/**
 * Reverses the linked list.
 */
template <class elemType> void LinkList<elemType>::reverse() {
  Node<elemType> *prev = nullptr;
  Node<elemType> *current = head->next;
  while (current != nullptr) {
    Node<elemType> *nextNode = current->next;
    current->next = prev;
    prev = current;
    current = nextNode;
  }
  head->next = prev;
}

/**
 * Clears the list by deleting all nodes except the head.
 */
template <class elemType> void LinkList<elemType>::clear() {
  Node<elemType> *p = head->next;
  Node<elemType> *q;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head->next = nullptr;
}

#endif // LINKLIST_H
