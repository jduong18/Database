/**
 * Author: Jeffrey Duong
 * Project: Pair
 * Purpose: To create a pair object for use with map
 * Notes: N/A
 */

#ifndef BPMAP_PAIR_HPP
#define BPMAP_PAIR_HPP

#include <iostream>

//Struct for an entry
template <class K, class V>
struct Pair{
    K key;
    V value;
    //Constructor
    Pair(const K& k = K(), const V& v = V());

    //Overloaded insertion operator to output
    //PreCondition: ostream and Pair
    //PostCondition: Object printed to desired location
    friend std::ostream& operator << (std::ostream& outs, const Pair<K,V>& print_me){
        outs << print_me.key << ":" << print_me.value;
        return outs;
    }
    //Overloaded operator for ==
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator == (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key == rhs.key;
    }

    //Overloaded operator for <
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator < (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key < rhs.key;
    }


    //Overloaded operator for >
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator > (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key > rhs.key;
    }

    //Overloaded operator for <=
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator <= (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key <= rhs.key;
    }

    //Overloaded operator for >=
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator >= (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key >= rhs.key;
    }

    //Overloaded operator for !=
    //PreCondition: Two pair objects
    //PostCondition: Boolean value
    friend bool operator != (const Pair<K,V>& lhs, const Pair<K,V>& rhs){
        return lhs.key != rhs.key;
    }

    //Overloaded operator for +=
    //PreCondition: One other pair object
    //PostCondition: "This" is replaced by other
    Pair<K,V>& operator += (const Pair<K,V>& other){
        //this = other;
        value = other.value;
        return *this;
    }

};


//Constructor
template <class K, class V>
Pair<K,V>::Pair(const K& k, const V& v) {
    //Sets values if given, default if not
    key = k;
    value = v;
}


#endif //BPMAP_PAIR_HPP
