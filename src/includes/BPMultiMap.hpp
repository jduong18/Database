/**
 * Author: Jeffrey Duong
 * Project: BPMultiMap
 * Purpose: To create a multi map
 * Notes: Uses a BPTree struct
 */

#ifndef BPMULTIMAP_BPMULTIMAP_HPP
#define BPMULTIMAP_BPMULTIMAP_HPP

#include <iostream>

#include "BPTree.hpp"
#include "MultiPair.hpp"

//Class for a MultiMap
template <class K, class V>
class BPMultiMap{
public:
    //Template name
    typedef BPTree<MPair<K,V> > map_base;
    //Iterator class for MultiMap
    class Iterator{
    public:
        friend class BPMultiMap;
        //Constructor
        Iterator(typename map_base::Iterator it = typename map_base::Iterator()):_it(it){}

        //Overloaded ++ operator
        //PreCondition: Iterator
        //PostCondition: Iterator is incremented
        Iterator operator ++(int unused){
            return _it++;
        }
        //Overloaded ++ operator
        //PreCondition: Iterator
        //PostCondition: Iterator is incremented
        Iterator operator ++(){
            return ++_it;
        }

        //Dereference operator
        //PreCondition: Iterator
        //PostCondition: Object at Iterator returned
        MPair<K,V> operator*(){
            return *_it;
        }

        //Overloaded == operator
        //PreCondition: Two Iterators
        //PostCondition: Boolean returned T/F
        friend bool operator == (const Iterator& lhs, const Iterator &rhs){
            return lhs._it == rhs._it;
        }

        //Overloaded != operator
        //PreCondition: Two Iterators
        //PostCondition: Boolean returned T/F
        friend bool operator != (const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }

        //Function to print iterator
        //PreCondition: Iterator
        //PostCondition: Iterator is printed to console
        void print_Iterator(){
            _it.print_Iterator();
        }
    private:
        //Pointer
        typename map_base::Iterator _it;
    };
    //Default Constructor
    BPMultiMap();

    //Function to insert
    //PreCondition: Key and value
    //PostCondition: Map updated with value
    void insert(const K& k, const V& v);

    //Function to erase
    //PreCondition: Key
    //PostCondiiton: Map updated with removed value
    void erase(const K& key);

    //Function to clear map
    //PreCondition: Map
    //PostCondition: Map is cleared
    void clear();

    //Function to "get" value at key,inserts if not found
    //PreCondition: Key
    //PostCondition: Value list returned at key,
    Vector<V>& get(const K& key);

    //Function to find if map contains key
    //PreCondition: Key
    //PostCondition: Boolean returned T/F
    bool contains(const K& key);

    //Function to find key
    //PreCondition: Key
    //PostCondition: Value list returned
    Vector<V> findValue(const K& key);

    //Function to get iterator of key
    //PreCondition: Key
    //PostCondition: Iterator returned
    Iterator find(const K& key);

    //Function to set iterator at beginning of map
    //PreCondition: Map
    //PostCondition: Iterator returned
    Iterator begin();

    //Function to set Iterator at end of map
    //PreCondition: Map
    //PostCondition: Iterator returned
    Iterator end();

    //Function to set iterator to first that goes not before
    //PreCondition: Key
    //PostCondition: Iterator
    Iterator lower_bound(const K& key);

    //Function to set iterator to first that goes after
    //PreCondition: Key
    //PostCondition: Iterator
    Iterator upper_bound(const K& key);


    //Function to set iterator to first that goes not before
    //PreCondition: Key
    //PostCondition: Iterator
    Iterator lower_bound_inclusive(const K& key);

    //Function to set iterator to first that goes after
    //PreCondition: Key
    //PostCondition: Iterator
    Iterator upper_bound_inclusive(const K& key);


    //Overloaded insertion operator to print
    //PreCondition: Ostream object and MultiMap
    //PostCondition: Map printed to desired location
    friend std::ostream& operator << (std::ostream& outs, BPMultiMap<K,V>& print_me){
        print_me.printTable(print_me);
        return outs;
    }

    //Overloaded [] operator
    //PreCondition: Key
    //PostCondition: Value returned at key
    Vector<V>& operator [] (const K& key){
        return map.get(key).value_list;
    }

    //Function to print Map
    //PreCondition: Map
    //PostCondition:Map printed
    void printTable(BPMultiMap<K,V>& print_me);

private:
    //BPlus Tree as structure
    BPTree<MPair<K,V> > map;
};


//Default constructor
template <class K, class V>
BPMultiMap<K,V>::BPMultiMap():map(false) {

}

//Function to insert into map
template <class K, class V>
void BPMultiMap<K,V>::insert(const K &k, const V &v) {
    MPair<K,V> temp(k,v);
    map.insert(temp);
}


//Function to remove from map
template <class K, class V>
void BPMultiMap<K,V>::erase(const K &key) {
    map.remove(key);
}

//Function to clear map
template <class K, class V>
void BPMultiMap<K,V>::clear() {
    map.clear_tree();
}

//Function to get value at key, inserts if not found
template <class K, class V>
Vector<V>& BPMultiMap<K,V>::get(const K &key) {
    return map.get(key).value_list;
}


//Function to check if key is in map
template <class K, class V>
bool BPMultiMap<K,V>::contains(const K &key) {
    return map.contains(key);
}

//Function to return value at key
template <class K, class V>
Vector<V> BPMultiMap<K,V>::findValue(const K &key) {
    MPair<K,V>* temp = map.findValue(key);
    if(temp == nullptr){
        return Vector<V>();
    }
    else{
        return temp->value_list;
    }
}

//Sets iterator to beginning of map
template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::begin() {
    return map.begin();
}

//Sets iterator to end of map
template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::end() {
    return map.end();
}

template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::lower_bound(const K &key) {
    return map.lower_bound(key);
}

template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::upper_bound(const K &key) {
    return map.upper_bound(key);
}

template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::lower_bound_inclusive(const K &key){
    return map.lower_bound_inclusive(key);
}

template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::upper_bound_inclusive(const K &key){
    return map.upper_bound_inclusive(key);
}

//Finds iterator at key
template <class K, class V>
typename BPMultiMap<K,V>::Iterator BPMultiMap<K,V>::find(const K &key) {
    return map.find(key);
}

//Function to print table as tree
template <class K, class V>
void BPMultiMap<K,V>::printTable(BPMultiMap<K, V> &print_me) {
    BPMultiMap<K,V>::Iterator it;
    for(it = print_me.begin(); it != print_me.end();it++){
        std::cout << *it << "\n";
    }
}

#endif //BPMULTIMAP_BPMULTIMAP_HPP
