/**
 * Author: Jeffrey Duong
 * Project: BP Map
 * Purpose: To create a map to use
 * Notes: Uses BP tree as data struct
 */

#ifndef BPMAP_BPMAP_HPP
#define BPMAP_BPMAP_HPP


#include "Pair.hpp"
#include "BPTree.hpp"

//Class to create a map
template <class K, class V>
class BPMap{
public:
    typedef BPTree<Pair<K,V> > map_base;
    //Class for Iterator
    class Iterator{
    public:
        friend class BPMap;

        //Constructor
        Iterator(typename map_base::Iterator it = typename map_base::Iterator()):_it(it){}

        //Overloaded ++ operator
        //PreCondition: Iterator
        //PostCondition: Iterator is moved to next
        Iterator operator ++(int unused){
            return _it++;
        }

        //Overloaded ++ operator
        //PreCondition: Iterator
        //PostCondition: Iterator is moved to next
        Iterator operator ++(){
            return ++_it;
        }

        //Derefernce operator
        //PreCondition: Iterator
        //PostCondition: Object dereferenced
        Pair<K,V> operator *(){
            return *_it;
        }

        //Overloaded == operator
        //PreCondition: Two iterator objects
        //PostCondition: Boolean T/F
        friend bool operator == (const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }

        //Overloaded != operator
        //PreCondition: Two iterator objects
        //PostCondition: Boolean T/F
        friend bool operator != (const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }

        //Function to print object
        //PreCondition: Iterator
        //PostCondition: Object pointed at is printed
        void print_Iterator(){
            _it.print_Iterator();
        }
    private:
        typename map_base::Iterator _it;
    };

    //Default Constructor
    BPMap();

    Iterator begin();
    Iterator end();

    //Function to insert a new entry
    //PreCondition: A key and a value
    //PostCondition: Entry is inserted into map
    void insert(const K& k, const V& v);

    //Function to remove an entry
    //PreCondition: A key
    //PostCondition: Entry is removed from map
    void remove(const K& key);

    //Function to clear the map
    //PreCondition: Map to clear
    //PostCondition: Map is cleared
    void clear();

    //Function to get value in map, inserts if not found
    //PreCondition: Key of value
    //PostCondition: Value is returned
    V& get(const K& key);

    //Function to check whether key is in map
    //PreCondition: Key of value
    //PostCondition: Boolean value returned
    bool contains(const K& key);

    //Function to return value of key
    //PreCondition: Key of value
    //PostCondition: Value returned, default if not found
    V findValue(const K& key);

    Iterator find(const K& key);

    //Overloaded insertion operator
    //PreCondition: ostream and Map
    //PostCondition: Map is printed to desired location
    friend std::ostream& operator << (std::ostream& outs,BPMap<K,V>& print_me){
        print_me.printTable(print_me);
        return outs;
    }

    //Overloaded operator to access map
    //PreCondition: Key
    //PostCondition: Returns value of key, inserts if not found
    V& operator[](const K& key){
        return map.get(key).value;
    }

    //Function to print map as tree
    //PreCondition: Map
    //PostCondition: Map printed as a tree
    void printTree();

    void printTable(BPMap<K,V>& print_me);
private:
    //BTree as storage for map
    BPTree<Pair<K,V> > map;
};


//Default Constructor
template <class K, class V>
BPMap<K,V>::BPMap() {
}


//Function to insert new entry to map
template <class K, class V>
void BPMap<K,V>::insert(const K &k, const V &v) {
    //Creates Pair
    Pair<K,V> temp(k,v);
    //Inserts into map
    map.insert(temp);
}

//Function to get value of key
//Inserts if not found
template <class K, class V>
V& BPMap<K,V>::get(const K &key) {
    return map.get(key).value;
}

//Function to find value of key
//Returns default if not found
template <class K, class V>
V BPMap<K,V>::findValue(const K &key) {
    Pair<K,V>* temp = map.findValue(key);
    if (temp == nullptr){
        return V();
    }
    else{
        return temp->value;
    }
}

//Function to check if key is in map
template <class K, class V>
bool BPMap<K,V>::contains(const K &key) {
    return map.contains(key);
}

//Function to remove an entry from map
//Removes based on key
template <class K, class V>
void BPMap<K,V>::remove(const K &key) {
    map.remove(key);
}

//Function to clear the map
template <class K, class V>
void BPMap<K,V>::clear() {
    map.clear_tree();
}

//Returns iterator to beginning
template <class K, class V>
typename BPMap<K,V>::Iterator BPMap<K,V>::begin() {
    return map.begin();
}

//Returns iterator to end
template <class K, class V>
typename BPMap<K,V>::Iterator BPMap<K,V>::end() {
    return map.end();
}

//Returns iterator to desired location
template <class K, class V>
typename BPMap<K,V>::Iterator BPMap<K,V>::find(const K &key) {
    return map.find(key);
}

//Function to print map as tree
template <class K, class V>
void BPMap<K,V>::printTree() {
    map.print_tree();
}

//Function to print map as tree
template <class K, class V>
void BPMap<K,V>::printTable(BPMap<K,V>& print_me) {
    BPMap<K,V>::Iterator it;
    for(it = print_me.begin(); it != print_me.end(); it++){
        std::cout << *it << "\n";
    }

}

#endif //BPMAP_BPMAP_HPP
