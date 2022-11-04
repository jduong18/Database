
/**
 * Author: Jeffrey Duong
 * Project: Queue Structure
 * Purpose: To create a Queue data structure for future use
 * Notes: N/A
 */

#ifndef QUEUE_QUEUE_HPP
#define QUEUE_QUEUE_HPP

#include "list.hpp"

template <class T>
class Queue{
private:
    node<T>* _head;
    node<T>* _tail;
    int _size;
public:
    Queue():_head(nullptr),_tail(nullptr),_size(0){}
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator = (const Queue<T>& rhs);

    friend ostream& operator <<(ostream& outs, const Queue& q){
        return print_list(q._head,outs);
    }

    void push(T item);
    T pop();
    bool empty();
    T front();
    int getSize();
};

//Destructor
template <class T>
Queue<T>::~Queue(){
    node<T>* temp = _head;
    //"Walks" through and individually deletes every element
    while(_head != nullptr) {
        _head = _head->_next;
        delete temp;
        temp = _head;
    }

}

//Copy Constructor
template <class T>
Queue<T>::Queue(const Queue<T>& other){
    node<T>* walker = other._head;
    _head = nullptr;
    //Individually inserts each element using another Queue
    while(walker != nullptr){
        insert_end(_head, walker->_item);
        walker = walker->_next;
        }
    _tail = walker;
    _size = other._size;
}

//Assignment Operator
template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& rhs){
    copy_list(rhs._head, _head);
    node<T>* walker = _head;
    //"Walks" to the end of the list to place marker
    while(walker->_next != nullptr){
        walker = walker->_next;
    }
    _tail = walker;
    _size = rhs._size;
    return *this;
}

//inserts new element at the end of the list
//PreCondition:Item to be added must be of the right item type
//PostCondition: Updated list with new item at the right position(end)
template <class T>
void Queue<T>::push(T item){
    //If empty list, places element in the front
    if(_head == nullptr){
        insert_head(_head, item);
        _tail = _head;
    }
    //Else places after the "_tail" marker signaling last element of list
    else{
        node<T>* temp = insert_after(_head, _tail, item);
        _tail = temp;
    }
    _size++;
}

//removes top element and returns the value stored
//PreCondition: List with elements to remove
//PostCondidtion: Value of the element removed and updated list without that element
template <class T>
T Queue<T>::pop(){
    assert(_head != nullptr);
    _size--;
    if(_size == 0){
        _tail = nullptr;
    }
    return delete_head(_head);
}

//checks the status of the list (empty or not)
//PreCondition: List of proper type
//PostCondition: Boolean expression corresponding to the status of the list
template <class T>
bool Queue<T>::empty() {
    if(_head == nullptr){
        return true;
    }
    else{
        return false;
    }

}

//returns value of the element in front of the list (does not remove)
//PreCondition: A list with elements to check
//PostCondition: Value of the first element and an unchanged list
template <class T>
T Queue<T>::front(){
    assert(_head != nullptr);
    return _head->_item;
}

template<class T>
int Queue<T>::getSize() {
    return _size;
}


#endif //QUEUE_QUEUE_HPP
