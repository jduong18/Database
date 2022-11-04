//
// Created by Jeffrey Duong on 2/20/20.
//


/**
 * Author: Jeffrey Duong
 * Project LinkedList Functions
 * Purpose: Creating a linked list using individual functions (no linked list class)
 * Notes: usage of function for "init_head" not entirely clear
 */

#ifndef LIST_LIST_HPP
#define LIST_LIST_HPP

#include <iostream>

using namespace std;

template <class T>
struct node{
    T _item;
    node<T>* _next;
    node(const T& item = T(), node<T>* next = nullptr):_item(item), _next(next){
    }
    friend ostream& operator << (ostream& out, const node<T>& print){
        out << "[" << print._item << "]";
        return out;
    }

};


//intializes head to nullptr
//PreCondition: list must not be filled as list will be lost
//Postcondition: returns pointer to nullptr signifying an empty list
template <class T>
node<T>* init_head(node<T>* &head);


//deletes all nodes in the list
//PreCondition: list exists
//PostCondition: list is deleted and head points to nullptr
template <class T>
void delete_all(node<T>*& head);


//checks whether the list is empty or not
//PreCondition: A node pointer
//PostCondition: Boolean value corresponding to status of list
template <class T>
bool empty(const node<T>* head);


//copy the content of one list into another list
//PreCondition: Two lists, ensure that the data from list to be replaced is not needed
//PostCondition: Two separate lists containing the same values
template <class T>
node<T>* copy_list(const node<T>* head, node<T>* &copy);


//inserts new element to the front of the list
//PreCondition: Valid item to put into list
//PostCondition: Updated list containing new value
template <class T>
node<T>* insert_head(node<T>* &head, const T& item);


//insert new element after specified element of preexisting list, if element not found, insert at head
//PreCondition: Valid item to put into list
//PostCondition: Updated list containing new value
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item);


//deletes the first element of list and returns the value stored
//PreCondition:Valid list with element to be removed
//PostCondition:Updated list with element removed and a return value of what was stored
template <class T>
T delete_head(node<T>* &head);


//searches list for node containing value searched for
//PreCondition: Valid list and valid item type
//PostCondition: Returns node with value or nullptr if value not found, does not delete
template <class T>
node<T>* get_node(node<T>* &head, const T& item);


//inserts new element at the end of list with value inputted
//PreCondition: Valid item to be inserted
//PostCondition: Updated list with new element
template <class T>
node<T>* insert_end(node<T>* &head, const T& item);


//returns the last node of the list
//PreCondition: Valid list
//PostCondition: Returns last node of list without deleting it
template <class T>
node<T>* get_last_node(node<T*> &head);

//prints the list in order from beginning to end
//PreCondition: Valid list
//PostCondition: Console output of list
template <class T>
ostream& print_list(const node<T>* head, ostream& out = cout);











template <class T>
node<T>* init_head(node<T>* &head){
    assert(empty(head));
    head = nullptr;
    return head;
}

template <class T>
void delete_all(node<T>*& head){
    node<T>* walker = head;
    //"Walks" list and deletes each element with each step
    while(head != nullptr){
        head = head->_next;
        delete walker;
        walker = head;
    }
}

template<class T>
bool empty(const node<T>* head){
    if(head == nullptr){
        return true;
    }
    else{
        return false;
    }
}


template<class T>
node<T>* copy_list(const node<T>* head, node<T>* &cpy){
    delete_all(cpy);
    //"walks" the original list and uses values to build the new list
    while(head != nullptr) {
        insert_end(cpy, head->_item);
        head = head->_next;
    }
    return get_last_node(cpy);
}

template<class T>
node<T>* insert_head(node<T>* &head, const T& item){
    node<T>* temp = new node<T>(item);
    temp->_next = head;
    head = temp;
    return head;
}

template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T &item){
    assert(!empty(head));
    node<T>* temp = new node<T>(item);
    node<T>* walker = head;
    //searches for "after" node
    while(walker != after){
        walker = walker->_next;
        //checks to see if end of list has been reached
        if(walker == nullptr){
            insert_head(head,item);
            return head;
        }
    }
    //inserts node and returns pointer to node
    temp->_next = walker->_next;
    walker->_next = temp;
    return temp;
}

template <class T>
T delete_head(node<T>* &head){
    //sets head pointer to next node to become new head pointer
    T temp = head->_item;
    node<T>* toDelete = head;
    head = head->_next;
    delete toDelete;
    return temp;
}

template <class T>
node<T>* get_node(node<T>* &head, const T& item){
    assert(!empty(head));
    node<T>* walker = head;
    //searches for node containing item
    while(walker != nullptr && walker->_item != item){
        walker = walker->_next;
    }
    //if node has reached the end of list without finding it
    if(walker == nullptr){
        return walker;
    }
    return walker;
}

template <class T>
node<T>* insert_end(node<T>* &head, const T& item){
    node<T> *temp = new node<T>(item);
    //if list is not empty
    if(!empty(head)) {
        node<T> *walker = head;
        //"walks" to the end of the list
        while (walker->_next != nullptr) {
            walker = walker->_next;
        }
        walker->_next = temp;
    }
    //if list is empty
    else{
        head = temp;
    }
    return temp;
}

template <class T>
node<T>* get_last_node(node<T>* &head) {
    node<T>* walker = head;
    //if list does not exist yet
    if(walker == nullptr){
        return walker;
    }
    //walks to end of list
    while(walker->_next != nullptr){
        walker = walker->_next;
    }
    return walker;
}

template <class T>
ostream& print_list(const node<T>* head, ostream& out){
    //"Walks" list and returns each element into ostream object
    while(head != nullptr) {
        out << *head;
        head = head->_next;
    }
    out << endl;
    return out;
}




#endif //LIST_LIST_HPP
