/**
 * Author: Jeffrey Duong
 * Project: BPTree
 * Purpose: To create a BP Tree
 * Notes: N/A
 */

#ifndef BPTREE_BPTREE_HPP
#define BPTREE_BPTREE_HPP

#include <iostream>
#include <iomanip>
#include <assert.h>
#include "ArrFunctions.hpp"


//Class to create a BTree
template <class T>
class BPTree{
public:
    //Class for an iterator for BP Tree
    class Iterator{
    public:
        friend class BPTree;
        //Constructor with default values
        Iterator(BPTree<T>* _it = nullptr, int _key_ptr = 0):it(_it),key_ptr(_key_ptr){}

        //Dereference operator
        //PreCondition: Iterator
        //PostCondition: Iterator pointer is dereferenced
        T operator *(){
            assert(it);
            return it->data[key_ptr];
        }

        //Overloaded ++ operator
        //PreCondidtion: Iterator
        //PostCondition: Iterator is moved to next element
        Iterator operator++(int un_used){
            //Moves to next data set if applicable
            if(key_ptr < it->data_count-1){
                key_ptr++;
            }
            //Else moves to next BPTree
            else {
                key_ptr = 0;
                it = it->next;
            }
            return it;
        }
        //Overloaded ++ operator
        //PreCondition: Iterator
        //PostCondition: Iterator is moved to next element
        Iterator operator++(){
            //Moves to next data set if applicable
            if(key_ptr < it->data_count-1){
                key_ptr++;
            }
            //Else moves to next BPTree
            else {
                key_ptr = 0;
                it = it->next;
            }
            return it;
        }

        //Overloaded comparison operator
        //PreCondition: 2 Iterator objects
        //PostCondition: T/F
        friend bool operator == (const Iterator& lhs, const Iterator& rhs){
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        //Overloaded comparison operator
        //PreCondition: 2 Iterator objects
        //PostCondition: T/F
        friend bool operator != (const Iterator& lhs, const Iterator& rhs){
            if(lhs.it != rhs.it){
                return true;
            }
            if(lhs.key_ptr != rhs.key_ptr){
                return true;
            }
            return false;
        }
        //Prints the value of the iterator
        //PreCondition: Iterator
        //PostCondition: Item is printed out
        void print_Iterator(){
            if(it) {
                std::cout << it->data[key_ptr];
            }
        }
        //Checks if the Iterator is null
        //PreCondition: Iterator
        //PostCondition:
        bool is_null(){return !it;}
    private:
        //Pointer
        BPTree<T>* it;
        //DataCount Pointer
        int key_ptr;
    };
    //Default Constructor
    BPTree(bool ignore = true);
    //Copy Constructor
    BPTree(const BPTree<T>& other);
    //Destructor
    ~BPTree();
    //Assignment Operator
    BPTree<T>& operator = (const BPTree<T>& RHS);


    //Inserts new entry into tree and adjusts tree
    //PreCondition: Item to insert
    //PostCondtiion: Proper tree with new item
    void insert(const T& entry);

    //Removes entry from tree and adjusts tree
    //PoreCondition: Item to remove
    //PostCondition: Proper tree with item removed
    void remove(const T& entry);

    //Function to clear the tree
    //PreCondition: Tree to clear
    //PostCondition: Proper Tree with new item
    void clear_tree();

    //Copies tree into this object
    //PreCondition: Tree to copy
    //PostCondition: This tree is a copy of other tree
    void copy_tree(const BPTree<T>& other);

    //Checks if tree contains item
    //PreCondition: Item to search for
    //PostCondition: T/F
    bool contains(const T& entry);

    //Returns item searched for, if not found, inserts
    //PreCondition: Entry to search for
    //PostCondition: Item is returned
    T& get(const T& entry);

    //Function to return pointer of value
    //PreCondition: Tree to search and value to find
    //PostCondition: Item returned or nullptr if not found
    T* findValue(const T& entry);

    //Function to return Iterator
    //PreCondition: Tree to search and value to find
    //PostCondition: Iterator returned
    Iterator find(const T& entry);

    //Function to print tree
    //PreCondition: Tree to print, ostream
    //PostCondition: Tree printed to desired location
    void print_tree(int level = 0, std::ostream& outs = std::cout) const;


    //Function to print tree in order
    //PreCondition: Tree and level
    //PostCondition: Tree printed in order (debugging)
    void print_tree_inorder(int level = 0, std::ostream& outs = std::cout);



    //Overloaded insertion operator
    //PreCondition: ostream, and tree
    //PostCondition: Tree printed to desired location
    friend std::ostream& operator << (std::ostream& outs, const BPTree<T>& print_me){
        print_me.print_tree(0,outs);
        return outs;
    }



    //Function to return Iterator
    //PreCondition: Tree
    //PostCondition: Iterator to beginning of tree returned
    Iterator begin();

    //Function to return Iterator
    //PreCondition: Tree
    //PostCondition: Iterator to end of tree returned
    Iterator end();

    //Function to return Iterator
    //PreCondition: Tree and key
    //PostCondition: Iterator to first value >= key
    Iterator lower_bound(const T& key);

    //Function to return Iterator
    //PreCondition: Tree and key
    //PostCondition: Iterator to first value > key
    Iterator upper_bound(const T& key);


    //Function to check whether tree is valid or not
    //PreCondition: Tree to check
    //PostCondition: T/F
    bool is_valid();

private:
    //Min and MAx
    static const int MIN = 1;
    static const int MAX = 2*MIN;

    bool _ignore_dupes;

    //Data and subset arrays
    T data[MAX+1];
    BPTree* subset[MAX+2];

    BPTree* next;
    //Number of elements
    int data_count;
    int child_count;

    void copy_tree(const BPTree<T>& other, BPTree<T>*&last_leaf);

    //Checks if current node is leaf
    //PreCondition: Node to check
    //PostCondition: T/F
    bool is_leaf()const{return child_count == 0;}

    //Function to insert new item at proper leaf
    //PreCondition: item to insert
    //PostCondition: Item is inserted at leaf
    void loose_insert(const T& entry);

    //Function to fix child's excess
    //PreCondition: Index of child to check
    //PostCondition: Child is fixed
    void fix_excess(int i);

    //Function to return value
    //PreCondition: Item to search for, item must exist
    //PostCondition: Item is returned, crashes otherwise
    T& get_existing(const T& item);


    //Function to remove an item and fix up to root
    //PreCondition: Entry to remove
    //PostCondition: Element removed, tree fixed except root
    void loose_remove(const T& entry);

    //Function to replace element with largest
    //PreCondition:Variable to hold element
    //PostCondition: Largest element placed in entry
    void remove_biggest(T& entry);


    //Function to fix child's shortage
    //PreCondition: Index of child to check
    //PostCondition: Child is fixed
    void fix_shortage(int i);

    //Function to rotate elements left to fix shortage
    //PreCondition: Index of child needing fix
    //PostCondition: Elements rotated left
    void rotate_left(int i);

    //Function to rotate elements right to fix shortage
    //PreCondition: Index of child needing fix
    //PostCondition: Elements rotate right
    void rotate_right(int i);

    //Function to merge two subsets to fix shortage
    //PreCondition: Index of left subset to merge
    //PostCondition: Left subset merged with right subset
    void merge_with_next_subset(int i);

    //Function to transfer element to the right to fix shortage
    //PreCondition: Index of element
    //PostCondition: Elements transferred to the right
    void transfer_right(int i);

    //Function to transfer element to the left to fix shortage
    //PreCondition: Index of element
    //PostCondition: Elements transferred to the left
    void transfer_left(int i);

    //Function to merge two subsets to fix shortage in leaf
    //PreCondition: Index of left subset to merge
    //PostCondition: Left subset merged with right subset in leaf
    void merge_with_next_leaf(int i);

    //Function to find smallest element in tree
    //PreCondition: Tree
    //PostCondition: Smallest index returned
    T findSmallest();
};


//Default constructor
template <class T>
BPTree<T>::BPTree(bool ignore) {
    //Initalizes everything to default
    data_count = 0;
    child_count = 0;
    _ignore_dupes = ignore;
    next = nullptr;
    for(int i = 0; i < MAX+1; i++){
        data[i] = T();
    }
    for(int i = 0; i < MAX+2; i++){
        subset[i] = nullptr;
    }
}

//Destructor
template <class T>
BPTree<T>::~BPTree() {
    this->clear_tree();
}

//Copy Constructor
template <class T>
BPTree<T>::BPTree(const BPTree<T> &other) {
    //Initializes
    child_count = 0;
    data_count = 0;
    next = nullptr;
    for(int i = 0; i < MAX+1; i++){
        data[i] = T();
    }
    for(int i = 0; i < MAX+2; i++){
        subset[i] = nullptr;
    }
    //Copies
    this->copy_tree(other);
}

//Assignment operator
template <class T>
BPTree<T>& BPTree<T>::operator =(const BPTree<T>& RHS){
    //Clears
    this->clear_tree();
    //Copies
    this->copy_tree(RHS);
    return *this;
}

//Function to find an item
template <class T>
T* BPTree<T>::findValue(const T &entry) {
    bool found;
    //Finds index where it should be
    int i = first_ge(data, data_count, entry);
    if(i == data_count){
        found = false;
    }
    else {
        found = (data[i] == entry);
    }
    if(is_leaf() && found){
        return &data[i];
    }
    //If found, return item;
    if(found && !is_leaf()){
        subset[i+1]->findValue(entry);
    }
    //If at leaf, return nullptr
    if(!found && is_leaf()){
        return nullptr;
    }
    //Searches appropriate subtree
    return subset[i]->findValue(entry);
}

//Function to print tree
template <class T>
void BPTree<T>::print_tree(int level, std::ostream &outs) const {
    int i = 0;
    //If not a leaf
    if(!is_leaf()){
        //Cycles through each subset
        for(i = data_count; i >= 0; i--){
            subset[i]->print_tree(level+1);
            //Print data
            if(i>0){
                std::cout << std::setw(4*level) << " " << data[i-1];
            }
            std::cout << std::endl;
        }
    }
        //If leaf print data
    else{
        std::cout << std::setw(4*level) << " ";
        for(int i = data_count-1; i >= 0; i--){
            std::cout << data[i] << std::endl;
            std::cout << std::setw(4 * level) << " ";
        }
        std::cout << std::endl;
    }
}

//Function to insert and fix excess up to root
template <class T>
void BPTree<T>::loose_insert(const T &entry) {
    //Find appropriate spot
    bool found;
    int index = first_ge(data, data_count, entry);
    if(index == data_count){
        found = false;
    }
    else {
        found = (data[index] == entry);
    }

    //Inserts if leaf and not found
    if(is_leaf() && !found){
        insert_item(data, index, data_count, entry);
    }
        //If not a leaf but item is found
        //Replace
    else if(!is_leaf() && found){
        if(_ignore_dupes){

        }
        else {
            data[index] += entry;
            subset[index+1]->loose_insert(entry);
            fix_excess(index);
        }
    }
        //If it is a leaf and item is found
        //Replace
    else if(is_leaf() && found){
        if(_ignore_dupes){

        }
        else {
            data[index] += entry;
        }
    }
        //Else continue down tree to appropriate spot
    else{
        subset[index]->loose_insert(entry);
        fix_excess(index);
    }
}

//Function to fix excess
template <class T>
void BPTree<T>::fix_excess(int i) {
    //If child is larger than it should be
    if(subset[i]->data_count > MAX){
        //New node
        BPTree<T>* temp = new BPTree<T>;
        //Splits data and subset into new node
        split(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);
        split(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);

        //Grabs the last element in subchild after split and places into own data
        T item = subset[i]->data[subset[i]->data_count-1];
        int insertIndex = first_ge(data, data_count, item);
        insert_item(data, insertIndex, data_count, item);

        //Adjust child data count
        subset[i]->data_count --;

        //Inserts new node into subset
        insert_item(subset, i+1,child_count, temp);

        if(subset[i]->is_leaf()){
            insert_item(subset[i+1]->data,0,subset[i+1]->data_count,item);
            subset[i+1]->next = subset[i]->next;
            subset[i]->next = subset[i+1];
        }
    }
}

//Function to insert item and fully adjust ree
template <class T>
void BPTree<T>::insert(const T &entry) {
    //Inserts and adjusts all the way up to root
    loose_insert(entry);
    //If root is too large
    if(data_count > MAX){
        //Create new node
        BPTree<T>* temp = new BPTree<T>;
        //Copy data and subset
        copy_array(temp->data, data, temp->data_count, data_count);
        copy_array(temp->subset, subset, temp->child_count, child_count);

        //Copy root of information
        clear_array(subset, child_count);
        child_count = 0;
        data_count = 0;

        //Insert new node as child of root
        insert_item(subset, 0, child_count, temp);

        //Fix child
        fix_excess(0);
    }
}

//Function to copy tree
template <class T>
void BPTree<T>::copy_tree(const BPTree<T> &other) {
    BPTree<T>* temp = nullptr;
   copy_tree(other, temp);

}

//Function to clear tree
template <class T>
void BPTree<T>::clear_tree() {
    //Cycle through all children
    for (int i = 0; i < child_count; i++) {
        subset[i]->clear_tree();
        //delete node
        delete subset[i];
        //set to nullptr
        subset[i] = nullptr;
    }
    //Set child count to 0
    child_count = 0;
    //Set data to 0
    clear_array(data,data_count);
    data_count = 0;
}

//Checks to see if tree contains item
template <class T>
bool BPTree<T>::contains(const T& entry) {
    bool found;
    //Finds index where it should be
    int i = first_ge(data, data_count, entry);
    if(i == data_count) {
        found = false;
    }
    else{
        found = (data[i] == entry);
    }

    //Returns boolean if found
    if(found && is_leaf()){
        return found;
    }
    //Returns boolean if at leaf
    if(!found && is_leaf()){
        return found;
    }
    if(found && !is_leaf()){
        return subset[i+1]->contains(entry);
    }
    //Searches in tree more if not found yet
    return subset[i]->contains(entry);
}

//Function to search for item
//Inserts item if not found
template <class T>
T& BPTree<T>::get(const T &entry) {
    //If not found, insert
    if(!contains(entry)){
        insert(entry);
    }
    //return item
    return get_existing(entry);
}

//Returns reference to object
//Very similar to find
template <class T>
T& BPTree<T>::get_existing(const T &item) {
    bool found;
    //Finds index where it should be
    int i = first_ge(data, data_count, item);

    if (i == data_count){
        found = false;
    }
    else{
        found = (data[i] == item);
    }

    //If found, return item
    if(found && !is_leaf()){
        return subset[i+1]->get_existing(item);
    }
    if(found && is_leaf()){
        return data[i];
    }
    //Assert, should not be leaf
    assert(!is_leaf());
    return subset[i]->get_existing(item);
}

//Removes the largest element in a tree
//PreCondition: Variable to hold largest
//PostCondition: Largest element is deleted and stored
template <class T>
void BPTree<T>::remove_biggest(T& entry){
    if(is_leaf()){
        entry = data[data_count-1];
        data_count--;
    }
    else{
        subset[child_count-1]->remove_biggest(entry);
        fix_shortage(child_count-1);
    }
}

//Function to remove and fix tree up to root
template <class T>
void BPTree<T>::loose_remove(const T& entry){
    T item;
    //Finds index
    int index = first_ge(data, data_count, entry);
    bool found;

    //Previously deleted data may be within capacity
    if(index == data_count){
        found = false;
    }
    else {
        found = (data[index] == entry);
    }

    //If is a leaf and not found
    if(is_leaf() && !found){
        //return false
    }
    //If is a leaf and found
    if(is_leaf() && found){
        delete_item(data, index, data_count, item);
        //return true;
    }
    //If not a leaf and not found
    if(!is_leaf() && !found){
        //Recursive call into subtree
        subset[index]->loose_remove(entry);
        //Fixes elements as they come up
        fix_shortage(index);
    }
    //If not a leaf and found
    if(!is_leaf() && found){
        subset[index+1]->loose_remove(entry);
        data[index] = subset[index+1]->findSmallest();
        fix_shortage(index+1);
        data[index] = subset[index+1]->findSmallest();
    }
}

//Function to rotate elements to the right
template <class T>
void BPTree<T>::rotate_right(int i) {
    T item;
    BPTree<T>* temp;
    //Brings data element down
    delete_item(data, i-1, data_count, item);
    insert_item(subset[i]->data,0, subset[i]->data_count,item);
    //Moves data element from left subtree into data
    delete_item(subset[i-1]->data,subset[i-1]->data_count-1, subset[i-1]->data_count,item);
    insert_item(data,i-1, data_count,item);
    //Moves children if applicable
    if(!(subset[i-1]->is_leaf())){
        delete_item(subset[i-1]->subset, subset[i-1]->child_count-1, subset[i-1]->child_count, temp);
        insert_item(subset[i]->subset, 0, subset[i]->child_count, temp);
    }
}

//Function to rotate elements to the left
template <class T>
void BPTree<T>::rotate_left(int i){
    T item;
    BPTree<T>* temp;
    //Brings data element down
    delete_item(data, i, data_count, item);
    insert_item(subset[i]->data, subset[i]->data_count, subset[i]->data_count,item);
    //Moves data element from right subtree into data
    delete_item(subset[i+1]->data,0,subset[i+1]->data_count,item);
    insert_item(data,i, data_count,item);
    //Moves children if applicable
    if(!(subset[i+1]->is_leaf())){
        delete_item(subset[i+1]->subset,0,subset[i+1]->child_count, temp);
        insert_item(subset[i]->subset,subset[i]->child_count,subset[i]->child_count, temp);
    }
}


//Merges subtree with next subtree
template <class T>
void BPTree<T>::merge_with_next_subset(int i) {
    T item;
    BPTree<T>* temp;
    //Brings data element down into subset
    delete_item(data,i,data_count, item);
    insert_item(subset[i]->data, subset[i]->data_count, subset[i]->data_count, item);
    //Merges subset with next subset
    merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data,subset[i+1]->data_count);
    merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset, subset[i+1]->child_count);
    //Deletes next subset
    delete subset[i+1];
    //Shifts remaining subsets left
    delete_item(subset,i+1, child_count,temp);
}

//Function to transfer elements to the right(fixing shortages)
template <class T>
void BPTree<T>::transfer_right(int i) {
    T item;
    delete_item(subset[i-1]->data,subset[i-1]->data_count-1, subset[i-1]->data_count, item);
    insert_item(subset[i]->data,0, subset[i]->data_count, item);
    data[i-1] = item;
}

//Function to transfer elements to the left(fixing shortages)
template <class T>
void BPTree<T>::transfer_left(int i) {
    T item;
    delete_item(subset[i+1]->data,0, subset[i+1]->data_count, item);
    insert_item(subset[i]->data,subset[i]->data_count, subset[i]->data_count, item);
    data[i] = subset[i+1]->data[0];
}

//Function to merge with the next leaf
template <class T>
void BPTree<T>::merge_with_next_leaf(int i) {
    T item;
    BPTree<T>* temp;
    delete_item(data,i, data_count, item);
    merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
    subset[i]->next = subset[i+1]->next;
    delete subset[i+1];
    delete_item(subset,i+1, child_count,temp);
}

//Function to find the smallest element in a tree
template <class T>
T BPTree<T>::findSmallest() {
    if(is_leaf()){
        if (data_count > 0) {
            return data[0];
        }
        else{
            return T();
        }
    }
    else{
        return subset[0]->findSmallest();
    }
}

//Fixes childs shortage
template <class T>
void BPTree<T>::fix_shortage(int i) {
    //If child needs fixing
    if(subset[i]->data_count < MIN){
        if(subset[i]->is_leaf()){
            if( i == 0){
                if(subset[i+1]->data_count > MIN){
                    transfer_left(i);
                }
                else{
                    merge_with_next_leaf(i);
                }
            }
            else if (i == child_count -1){
                if(subset[i-1]->data_count > MIN){
                    transfer_right(i);
                }
                else{
                    merge_with_next_leaf(i-1);
                }
            }
            else{
                if(subset[i-1]->data_count > MIN){
                    transfer_right(i);
                }
                else if(subset[i+1]->data_count > MIN){
                    transfer_left(i);
                }
                else{
                    merge_with_next_leaf(i);
                }
            }
        }
        else {
            //If left most child
            if (i == 0) {
                //If rotate left can be used
                if (subset[i + 1]->data_count > MIN) {
                    rotate_left(i);
                } else {
                    merge_with_next_subset(i);
                }
            }
                //If right most child
            else if (i == child_count - 1) {
                //If rotate right can be used
                if (subset[i - 1]->data_count > MIN) {
                    rotate_right(i);
                } else {
                    merge_with_next_subset(i - 1);
                }
            }
                //If child has neighbors left and right
            else {
                //Checks if rotate right can be used
                if (subset[i - 1]->data_count > MIN) {
                    rotate_right(i);
                }
                    //Checks if rotate left can be used
                else if (subset[i + 1]->data_count > MIN) {
                    rotate_left(i);
                }
                    //If not, merges
                else {
                    merge_with_next_subset(i);
                }
            }
        }
    }
}

//Function to remove and complete fix tree
template <class T>
void BPTree<T>::remove(const T &entry) {
    //Removes and fixes up to root
    loose_remove(entry);
    //If parent is in shortage
    if (data_count < MIN && child_count == 1) {
        //Create new node
        BPTree<T> *temp = new BPTree<T>;
        //Copy child into temp node
        copy_array(temp->data, subset[0]->data, temp->data_count, subset[0]->data_count);
        copy_array(temp->subset, subset[0]->subset, temp->child_count, subset[0]->child_count);
        //Delete child
        subset[0]->child_count = 0;
        delete subset[0];
        //Copy data and subset of "child" into root
        copy_array(data, temp->data, data_count, temp->data_count);
        copy_array(subset, temp->subset,child_count,temp->child_count);
        temp->child_count = 0;
        temp->data_count = 0;
    }
}

//Function to print tree inorder
template <class T>
void BPTree<T>::print_tree_inorder(int level, std::ostream &outs){
    if(!is_leaf()){
        for(int i = 0; i < child_count; i++){
            subset[i]->print_tree_inorder(level);
            if(i < data_count) {
                std::cout << data[i] << " ";
            }
        }
    }
    else{
        for(int i = 0; i < data_count; i++){
            std::cout << data[i] << " ";
        }
    }
}

//Function to find Iterator based in key
template <class T>
typename BPTree<T>::Iterator BPTree<T>::find(const T &entry) {
    bool found;
    //Finds index where it should be
    int i = first_ge(data, data_count, entry);

    if(i == data_count){
        found = false;
    }
    else{
        found = (data[i] == entry);
    }

    if(is_leaf() && found){
        return Iterator(this,i);
    }
    //If found, return item;
    if(found && !is_leaf()){
        return subset[i+1]->find(entry);
    }
    //If at leaf, return nullptr
    if(!found && is_leaf()){
        return Iterator();
    }
    //Searches appropriate subtree
    return subset[i]->find(entry);
}

//Function to return the begining of the tree
template <class T>
typename BPTree<T>::Iterator BPTree<T>::begin() {
    if(!is_leaf()){
        return subset[0]->begin();
    }
    else{
        if(data_count > 0) {
            return Iterator(this, 0);
        }
        else{
            return Iterator();
        }
    }
}
//Function to return the end of the tree
template <class T>
typename BPTree<T>::Iterator BPTree<T>::end() {
    return Iterator();
}

//Function to return Iterator to first element >=  key
template <class T>
typename BPTree<T>::Iterator BPTree<T>::lower_bound(const T &key) {
    bool found;
    //Finds index where it should be
    int i = first_ge(data, data_count, key);

    if(i == data_count && !is_leaf()){
        return subset[i]->lower_bound(key);
    }
    if(i == data_count && is_leaf()){
        return Iterator();
    }
    if(data[i] == key && !is_leaf()){
         if(subset[i]->contains(key)){
             return subset[i]->lower_bound(key);
         }
         else {
             return subset[i + 1]->lower_bound(key);
         }
    }
    if(data[i] > key && !is_leaf()){
        if(subset[i]->contains(key)){
            return subset[i]->lower_bound(key);
        }
        else {
            return subset[i + 1]->lower_bound(key);
        }
    }
    if(data[i] >= key && is_leaf()){
        return Iterator(this, i);
    }
}



//Function to return Iterator to first element > key
template <class T>
typename BPTree<T>::Iterator BPTree<T>::upper_bound(const T& key){
        bool found;
        //Finds index where it should be
        int i = first_ge(data, data_count, key);

        if(i == data_count && !is_leaf()){
            return subset[i]->upper_bound(key);
        }
         if(data[i] == key){
            i++;
         }
    if(i == data_count && !is_leaf()){
        return subset[i]->upper_bound(key);
    }
        if(i == data_count && is_leaf()){
            return Iterator();
        }
         if(data[i] > key && !is_leaf()){
             if (subset[i]->data[subset[i]->data_count-1] > key){
                 return subset[i]->upper_bound(key);
             }
             else {
                 return subset[i + 1]->upper_bound(key);
             }
         }
         if(data[i] > key && is_leaf()){
             return Iterator(this,i);
         }



}


//Function to copy tree
template <class T>
void BPTree<T>::copy_tree(const BPTree<T> &other, BPTree<T> *&last_leaf) {
    //Copy data
    copy_array(data, other.data, data_count, other.data_count);
    if(!other.is_leaf()) {
        //For each subset
        for (int i = 0; i < other.child_count; i++) {
            //New Node
            subset[i] = new BPTree<T>;
            //Copy Data
            subset[i]->copy_tree(*other.subset[i],last_leaf);
            //Update Child
            child_count++;
        }
    }
    else{
        if(last_leaf != nullptr){
            last_leaf->next = this;
        }
        last_leaf = this;
    }

}


//Function to test if tree is valid
template <class T>
bool BPTree<T>::is_valid() {
    //Checks every data[i]<data[i+1]
    for(int i = 0; i < data_count-1; i++){
        if(data[i] < data[i+1]){

        }
        else{
            return false;
        }
    }
    if(is_leaf()){
        return true;
    }
    //data[data_count-1] must be less than or equal to
    //every subset[child_count-1]->data[]
    for(int i = 0; i < subset[child_count-1]->data_count; i++) {
        if (data[data_count-1] <= subset[child_count - 1]->data[i]){

        }
        else {
            return false;
        }
    }
    //Every data[i] is greater than every subset[i]->data[]
    for(int i = 0; i < data_count; i++){
        for(int j = 0; j < subset[i]->data_count; j++){
            if(data[i] >= subset[i]->data[j]){

            }
            else{
                return false;
            }
        }
    }
    //Recursively checks subset
    for(int i = 0; i < child_count; i++){
        subset[i]->is_valid();
    }

    return true;
}
#endif //BPTREE_BPTREE_HPP
