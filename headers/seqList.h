#ifndef SEQLIST_H
#define SEQLIST_H

#define INITSIZE 100

// Exception classes
class IllegalSize {};
class OutOfBound {};

template <class elemType> class SeqList {
private:
  elemType *elem;     // Pointer to the dynamic array
  int len;            // Current length of the list
  int maxSize;        // Maximum capacity of the list
  void doubleSpace(); // Function to double the capacity

public:
  SeqList(int size = INITSIZE);
  bool isEmpty() const { return (len == 0); }
  bool isFull() const { return (len == maxSize); }
  int length() const { return len; }
  elemType get(int i) const;
  int find(const elemType &e) const;

  void insert(int i, const elemType &e);
  void remove(int i, elemType &e);

  void clear() { len = 0; }
  ~SeqList();
};

/**
 * Constructor
 * Initializes a SeqList with a specified maximum size.
 * Throws IllegalSize exception if size is non-positive.
 * @param size The initial maximum size of the sequence list.
 */
template <class elemType> SeqList<elemType>::SeqList(int size) {
  if (size <= 0)
    throw IllegalSize();
  elem = new elemType[maxSize];
  maxSize = size - 1; // index 0 is used as a watcher, not to store element
  len = 0;
}

/**
 * Destructor
 * Deallocates the dynamic array.
 */
template <class elemType> SeqList<elemType>::~SeqList() { delete[] elem; }

/**
 * Doubles the maximum size of the sequence list.
 * Allocates a new array with double capacity and copies existing elements.
 */
template <class elemType> void SeqList<elemType>::doubleSpace() {
  elemType *tmp = new elemType[2 * maxSize + 1];
  if (!tmp) {
    throw IllegalSize();
  }

  for (int i = 1; i <= len; i++) {
    tmp[i] = elem[i];
  }

  delete[] elem;
  elem = tmp;
  maxSize = 2 * maxSize;
}

/**
 * Retrieves the element at index i.
 * Throws OutOfBound exception if index is invalid.
 * @param i Index of the element to retrieve.
 * @return The element at index i.
 */
template <class elemType> elemType SeqList<elemType>::get(int i) const {
  if (i < 1 || i > len)
    throw OutOfBound();
  return elem[i];
}

/**
 * Finds the index of the first occurrence of element e.
 * @param e The element to find.
 * @return The index of e if found, otherwise 0.
 */
template <class elemType> int SeqList<elemType>::find(const elemType &e) const {
  int i;
  elem[0] = e;
  for (i = len; elem[i] != e; i--)
    ;
  return i;
}

/**
 * Inserts element e at index i.
 * Throws OutOfBound exception if index is invalid.
 * Doubles the space if the list is full.
 * @param i The index at which to insert e.
 * @param e The element to insert.
 */
template <class elemType>
void SeqList<elemType>::insert(int i, const elemType &e) {
  if (i < 1 || i > len + 1)
    throw OutOfBound();
  if (len == maxSize)
    doubleSpace();
  for (int j = len + 1; j > i; --j) {
    elem[j] = elem[j - 1];
  }
  elem[i] = e;
  ++len;
}

/**
 * Removes the element at index i and stores it in e.
 * Throws OutOfBound exception if index is invalid.
 * @param i The index of the element to remove.
 * @param e Variable to store the removed element.
 */
template <class elemType> void SeqList<elemType>::remove(int i, elemType &e) {
  if (i < 1 || i > len)
    throw OutOfBound();
  e = elem[i];
  for (int j = i; j < len; ++j) {
    elem[j] = elem[j + 1];
  }
  --len;
}

#endif // SEQLIST_H
