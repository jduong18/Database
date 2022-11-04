//
// Created by Jeffrey Duong on 5/17/20.
//

#ifndef BPMULTIMAP_VECTOR_HPP
#define BPMULTIMAP_VECTOR_HPP

#include <iostream>
#include <list>
#include <iomanip>
#include <assert.h>

//Class for Vector
template <class T>
class Vector{
public:
    //Default constructor
    Vector();
    //Destructor
    ~Vector();
    //Copy Constructor
    Vector(const Vector<T>& other);

    Vector(const std::list<T>& list);


    //Overloaded Assignement operator
    //PreCondiiton: Other Vector
    //PostCondition: Other vector copied into this
    Vector<T>& operator = (const Vector<T>& other){
        this->copy(other);
        return *this;
    }

    //Function to push item at end of vector
    //PreCondition:Item
    //PostCondition: Item inserted at end
    void push_back(T item);


    //Function to grab element at specific index
    //PreCondition: Index
    //PostCondition: Item at index returned
    T get(int index);

    //Function to remove and return last element
    //PreCondition: Vector
    //PostCondition: Vector is shrunk and element removed
    T pop();

    //Function to remove and return first element
    //PreCondiiton: Vector
    //PostCondition: Vector is shurnk and element removed
    T popFront();

    //Function to get size
    //PreCondition: Vector
    //PostCondition: Current size returned
    int getSize();

    //Function to get capacity
    //PreCondition: Vector
    //PostCondition: Current capacity returned
    int getCapacity();

    //Function to get size(const)
    //PreCondition: Vector
    //PostCondition: Current size returned
    int size()const;

    //Function to get capacity (const)
    //PreCondition: Vector
    //PostCondition: Current capacity returned
    int capacity()const;

    //Function to copy another vector
    //PreCondition: Vector
    //PostCondition: Other vector is copied to this
    void copy(const Vector<T>& other);

    //Function to clear vector
    //PreCondition: Vector
    //PostCondition: Vector is clear(0) elements
    void clear();

    void deleteAllAt(const T& element);


    bool empty();

    Vector<T> unionVector(const Vector<T>& vec1, const Vector<T>& vec2);

    Vector<T> intersectionVector(const Vector<T>& vec1, const Vector<T>& vec2);


    //Overloaded += operator
    //PreCondition: Other Vector
    //PostCondition: Other vector added to this
    Vector<T>& operator += (const Vector<T>& other){
        for(int i = 0; i < other._size; i++){
            this->push_back(other.arr[i]);
        }
        return *this;
    }

    //Overloaded += operator
    //PreCondition: Item
    //PostCondition: Item is added to this
    Vector<T>& operator += (const T& item){
        this->push_back(item);
        return *this;
    }

    //Overloaded insertion operator
    //PreCondition: Ostream object and vector
    //PostCondition: Vector is printed to desired location
    friend std::ostream& operator << (std::ostream& outs, const Vector<T>& print_me){
        for(int i = 0; i < print_me._size; i++){
            outs << print_me.arr[i] << std::setw(15);
        }
        return outs;
    }

    //Overloaded [] operator
    //PreCondition: Index
    //PostCondition: Item at index returned
    T& operator [] (const int& index){
        assert(index < _size);
        return arr[index];
    }

    //Overloaded [] operator
    //PreCondition: Index
    //PostCondition: Item at index returned
    T& operator [] (const int& index)const{
        assert(index < _size);
        return arr[index];
    }

private:
    //Arr for storage
    T* arr;
    //Size
    int _size;
    //Capacity
    int _capacity;
    //Function to print
    //PreCondition: Vector
    //PostCondiiton: Vector printed to console
    void print();
};


//Default Constructor
template <class T>
Vector<T>::Vector() {
    arr = new T[1];
    _capacity = 1;
    _size = 0;
}


//Destructor
template <class T>
Vector<T>::~Vector() {
    if(arr != nullptr) {
        delete[] arr;
    }

}


//Copy Constructor
template <class T>
Vector<T>::Vector(const Vector<T> &other) {
    arr = nullptr;
    _capacity = 1;
    _size = 0;
    this->copy(other);
}


template <class T>
Vector<T>::Vector(const std::list<T> &list) {
    arr = new T[1];
    _capacity = 1;
    _size = 0;
    for(T item:list){
        this->push_back(item);
    }
}



//Function to push back an item into vector
template <class T>
void Vector<T>::push_back(T item) {
    //Creates new array if not yet created
    if(arr == nullptr){
        arr = new T[1];
        _capacity = 1;
        _size = 0;
    }
    //If size is at capacity
    if(_size == _capacity){
        //Double capacity
        T* temp = new T [_capacity*2];
        for(int i = 0; i < _size; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        _capacity *= 2;
        arr = temp;
    }

    //Inserts item at end
    arr[_size] = item;
    //Increments size
    _size++;
}


//Function to get item at index
template <class T>
T Vector<T>::get(int index) {
    assert(index < _size);
    return arr[index];
}

//Function to return and remove last element
template <class T>
T Vector<T>::pop() {
    T item = arr[_size-1];
    _size--;
    return item;
}

template <class T>
T Vector<T>::popFront() {
    T item = arr[0];
    _size--;
    for(int i = 0; i < _size; i++){
        arr[i] = arr[i+1];
    }
    return item;
}

//Function to return size
template <class T>
int Vector<T>::getSize() {
    return _size;
}

//Function to return capacity
template <class T>
int Vector<T>::getCapacity() {
    return _capacity;
}

//Function to print vector
template <class T>
void Vector<T>::print() {
    for(int i = 0; i < _size; i++){
        std::cout << arr[i] << " ";
    }
}

//Function to copy vector
template <class T>
void Vector<T>::copy(const Vector<T> &other) {
    delete [] arr;
    arr = nullptr;
    _size = 0;
    for(int i = 0; i < other._size; i++){
        this->push_back(other.arr[i]);
    }
}

//Function to clear vector
template <class T>
void Vector<T>::clear() {
    _size = 0;
}

template <class T>
void Vector<T>::deleteAllAt(const T &element) {
    for(int i = 0; i < _size; i++){
        if(arr[i] == element) {
                _size = i;
            }
        }
}

template <class T> bool Vector<T>::empty() {
    if(_size == 0){
        return true;
    }
    return false;
}


template <class T>
Vector<T> Vector<T>::unionVector(const Vector<T> &vec1, const Vector<T> &vec2) {
    int i = 0;
    int j = 0;
    Vector<T> finalVector;
    while(i < vec1.size() && j < vec2.size()){
        if (vec1[i] == vec2[j]){
            finalVector.push_back(vec1[i]);
            i++;
            j++;
        }
        else if (vec1[i] < vec2[j]){
            finalVector.push_back(vec1[i]);
            i++;
        }
        else{
            finalVector.push_back(vec2[j]);
            j++;
        }
    }
    while(i < vec1.size()){
        finalVector.push_back(vec1[i]);
        i++;
    }
    while(j < vec2.size()){
        finalVector.push_back(vec2[j]);
        j++;
    }
    return finalVector;
}

template <class T>
Vector<T> Vector<T>::intersectionVector(const Vector<T> &vec1, const Vector<T> &vec2){
    Vector<T> finalVector;
    int i = 0;
    int j = 0;
        while(i < vec1.size() && j < vec2.size()){
            if(vec1[i] == vec2[j]){
                finalVector.push_back(vec1[i]);
                i++;
                j++;
            }
            else if(vec1[i] < vec2[j]){
                i++;
            }
            else{
                j++;
            }
        }
    return finalVector;
}

//Function to return size
template <class T>
int Vector<T>::size() const {
    return _size;
}

//Function to return capacity
template <class T>
int Vector<T>::capacity() const {
    return _capacity;
}



#endif //BPMULTIMAP_VECTOR_HPP
