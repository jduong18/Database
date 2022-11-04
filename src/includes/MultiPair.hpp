/**
 * Author: Jeffrey Duong
 * Project: MultiPair
 * Purpose: To create an object for use with BPMM
 * Notes: Uses vector
 */

#ifndef BPMULTIMAP_MULTIPAIR_HPP
#define BPMULTIMAP_MULTIPAIR_HPP

#include "Vector.hpp"

//Struct for MPair
template <class K, class V>
struct MPair{
    //Key to search for
    K key;

    //Value list as Vector
    Vector<V> value_list;

    //Default constructor
    MPair();
    //Constructor with just a key
    MPair(const K& k);
    //Constructor with key and one value
    MPair(const K& k, const V& v);
    //Constructor with key and a vector
    MPair(const K& k, const Vector<V> v);

    //Overloaded insertion operator
    //PreCondition: MPair object
    //PostCondition: MPair printed
    friend std::ostream& operator << (std::ostream& outs, const MPair<K,V>& print_me){
        outs << print_me.key << ":" << print_me.value_list;
        return outs;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator == (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key == rhs.key;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator < (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key < rhs.key;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator > (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key > rhs.key;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator <= (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key <= rhs.key;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator >= (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key >= rhs.key;
    }

    //Overloaded comparison operator
    //PreCondition: 2 MPairs
    //PostCondition: Boolean T/F
    friend bool operator != (const MPair<K,V>& lhs, const MPair<K,V>& rhs){
        return lhs.key != rhs.key;
    }

    //Overloaded += operator
    //PreCondition: Another pair object
    //PostCondition: Other value list added to current
    MPair<K,V>& operator += (const MPair<K,V>& other){
        value_list+= other.value_list;
        return *this;
    }


};

//Default constructor
template <class K, class V>
MPair<K,V>::MPair() {
    key = K();
}

//Constructor with one key
template <class K, class V>
MPair<K,V>::MPair(const K& k) {
    key = k;
}

//Constructor with key and one value
template <class K, class V>
MPair<K,V>::MPair(const K& k, const V& v) {
    key = k;
    value_list.push_back(v);
}

//Constructor with key and vector
template <class K, class V>
MPair<K,V>::MPair(const K& k, const Vector<V> v) {
    key = K();
    value_list.copy(v);
}


#endif //BPMULTIMAP_MULTIPAIR_HPP
