/**
 * Author: Jeffrey Duong
 * Project: Stack Structure
 * Purpose: Creating a Stack structure for future use
 * Notes: N/A
 */
#ifndef STACK_STACK_HPP
#define STACK_STACK_HPP

#include "list.hpp"
#include <assert.h>

template <class T>
class Stack{
private:
    node<T>* _top;
public:
    Stack():_top(nullptr){}
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator = (const Stack<T>& rhs);
    void push(T item);
    T pop();
    T top();
    bool empty();
    friend ostream& operator << (ostream& out, const Stack& s){
        return print_list(s._top, out);
    }

};

//Destructor
template <class T>
Stack<T>::~Stack() {
    node<T>* temp = _top;
    //walks through stack and deletes each element individually
    while(_top != nullptr){
        delete temp;
        _top = _top->_next;
        temp = _top;
    }
}

//Copy Constructor
template <class T>
Stack<T>::Stack(const Stack<T> &other) {
    node<T>* walker = other._top;
    _top = nullptr;
    //individually adds elements to new stack using given stack
    while(walker != nullptr){
        insert_end(_top, walker->_item);
        walker = walker->_next;
    }

}

//Assignment Operator
template <class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& rhs){
    copy_list(rhs._top, _top);
    return *this;
}


//inserts element into list in the proper posistion (on top)
//PreCondition: Proper data type for item
//PostCondition: Updated structure with new element
template <class T>
void Stack<T>::push(T item){
    insert_head(_top, item);
}

//removes top element and returns value
//PreCondition: List with elements to remove
//PostCondition: Updated list with the top element removed
template <class T>
T Stack<T>::pop(){
    assert(_top != nullptr);
    return delete_head(_top);
}

//returns top element value but does not remove the item from the list
//PreCondition: List with elements to check
//PostCondition: Value of top element is returned, list is not modified
template <class T>
T Stack<T>::top(){
    assert(_top != nullptr);
    return _top->_item;
}

//checks whether the list has elements in it
//PreCondition: A list of the proper type(Stack)
//PostCondition: Boolean expression corresponding with status of list
template <class T>
bool Stack<T>::empty() {
    if(_top == nullptr){
        return true;
    }
    return false;
}
#endif //STACK_STACK_HPP
