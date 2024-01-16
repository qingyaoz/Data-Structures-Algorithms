#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
    int count = 0;
    
    List(): first(nullptr), last(nullptr){
    }
    
    List(const List & other): first(nullptr), last(nullptr) {
        copy_all(other);
    }
    ~ List() {
      clear();
    }
    
    List & operator = (const List &rhs) {
        if (this == &rhs) {
            return *this;
        }
        clear();
        copy_all(rhs);
        return *this;
    }
    
  //EFFECTS:  returns true if the list is empty
    bool empty() const {
        return first == nullptr;
    }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
    int size() const {
        return count;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
        assert(!empty());
        return first->datum;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T & back() {
        assert(!empty());
        return last ->datum;
    }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
        Node *ptr = new Node;
        ptr->datum = datum;
        ptr->prev = nullptr;
        ptr->next = first;
        if(empty()) {
           first = last = ptr;
        }
        else {
            first->prev = ptr;
            first = ptr;
        }
        count ++;
    }

  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum) {
        Node *ptr = new Node;
        ptr -> datum = datum;
        ptr -> prev = last;
        ptr -> next = nullptr;
        if(empty()) {
            first = last = ptr;
        }
        else {
            last -> next = ptr;
            last = ptr;
        }
        count ++;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        assert(!empty());
        if(count != 1){
            Node *temp = first ->next;
            delete first;
            first = temp;
            first -> prev = nullptr;
            count --;
        }
        else {
            delete first;
            first = last = nullptr;
            count --;
        }
      
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        assert(!empty());
        if (count != 1) {
            Node * temp = last-> prev;
            delete last;
            last  = temp;
            last -> next = nullptr;
            count --;
        }
        else {
            delete first;
            first = last = nullptr;
            count --;
        }
    }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other) {
        assert(empty());
        for (Node *p = other.first; p; p = p -> next) {
            push_back(p -> datum);
        }
    }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
    class Iterator {
        //OVERVIEW: Iterator interface to List
        
        // You should add in a default constructor, destructor, copy constructor,
        // and overloaded assignment operator, if appropriate. If these operations
        // will work correctly without defining these, you can omit them. A user
        // of the class must be able to create, copy, assign, and destroy Iterators.
        
        // Your iterator should implement the following public operators: *,
        // ++ (prefix), default constructor, == and !=.
    public:
        Iterator(): node_ptr(nullptr) {}
        // This operator will be used to test your code. Do not modify it.
        // Requires that the current element is dereferenceable.
        Iterator& operator--() {
            assert(node_ptr);
            node_ptr = node_ptr->prev;
            return *this;
        }
        Iterator& operator++() {
            assert(node_ptr);
            node_ptr = node_ptr->next;
            return *this;
        }
        
        T & operator*() const{
        assert(node_ptr != nullptr);
        return node_ptr->datum;
        }
        
        bool operator==(const Iterator &rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        
        bool operator!=(const Iterator&rhs) const {
            return node_ptr != rhs.node_ptr;
        }
        
        
    private:
    
    Iterator(Node *np)
      :node_ptr(np) {}
    friend class List;
        Node *node_ptr;
   //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
      return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator();
    }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        if (i.node_ptr == first) {
            pop_front();
        }
        else if (i.node_ptr == last) {
            pop_back();
        }
        else {
            (i.node_ptr ->prev) -> next = i.node_ptr ->next;
            (i.node_ptr -> next) -> prev = i.node_ptr ->prev;
            delete i.node_ptr;
        }
    }
    

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {

        if (i  == this->begin()) {
            push_front(datum);
        }
        else if (i.node_ptr == nullptr) {
            push_back(datum);
        }
        
        else {
            Node * target = new Node;
            target -> datum = datum;
            
            target->prev = i.node_ptr ->prev;
            target-> next = i.node_ptr;
            i.node_ptr -> prev = target;
            target->prev -> next=  target;
            count ++;
        }
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
