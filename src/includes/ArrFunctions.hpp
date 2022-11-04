/**
 * Author: Jeffrey Duong
 * Project: Arr Functions
 * Purpose: To create functions to manipulate arrays
 * Notes: N/A
 */

#ifndef BPTREE_ARRFUNCTIONS_HPP
#define BPTREE_ARRFUNCTIONS_HPP

#include <iostream>

//Inserts item at index and shifts
//PreCondition: Array, index, size, and item
//PostCondition: Array has item inserted
template <class T>
void insert_item(T data[],int i, int& n, T entry);

//Splits array into two and stores one in the other
//PreCondition: 2 arrays and sizes of the arrays
//PostCondition: Array 2 has half of array 1
template <class T>
void split(T data1[], int& n1, T data2[], int& n2);

//Prints array
//PreCondition: Array and size
//PostCondition: Array is printed
template <class T>
void print_array(const T data[], int n, int pos = -1);

//Gets index of first item greater or equal to input
//PreCondition: Array, size, item
//PostCondition: Index of first item >=
template <class T>
int first_ge(const T data[], int data_size,const T& entry);


//Copies array from one to another
//PreCondition: Two arrays and two sizes
//PostCondition: One array is a copy of the other.
template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size);

//Clears array by setting to default values
//PreCondition: array and size
//PostCondition: Array is filled with default
template <class T>
void clear_array(T data[], int data_size);

//Merges Two arrays together
//PreCondition: Two arrays and sizes
//PostCondition: Second array merged into first array
template <class T>
void merge(T data1[], int& n1, T data2[], int& n2);

//Deletes an element in array
//PreCondition: Array, size, index to delete, variable to hold item
//PostCondition: Item deleted, array shifted, item stored
template <class T>
void delete_item(T data[], int i, int& n, T& entry);


//Function to shuffle an array
//PreCondition: Array and size
//PostCondition: Shuffled array
template <class T>
void shuffle(T a[],int size);

//Function two swap two elements
//PreCondition: Two items to swap
//PostCondition: Values at locations swapped
template <class T>
void swap(T& a, T& b);


//Inserst items and shifts
template <class T>
void insert_item(T data[], int i, int&n, T entry){
    //Shifts array
    for(int j = n; j > i; j--){
        data[j] = data[j-1];
    }
    n++;
    data[i] = entry;
}


//Splits array in half and puts in other array
template <class T>
void split(T data1[],int& n1, T data2[], int& n2){
    //Integer division
    int data1Half = n1/2;
    int counter = n1 - data1Half;
    //Puts half of array into second
    for(int i = 0; i < data1Half; i++){
        data2[n2] = data1[counter];
        data1[counter] = T();
        n1--;
        n2++;
        counter ++;
    }
}

//Prints array
template <class T>
void print_array(const T data[], int n, int pos){
    for(int i = 0; i < n; i++){
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

//Grabs index of first item >=
template <class T>
int first_ge(T data[], int data_size,const T& entry){
    for(int i = 0; i < data_size; i++){
        if(data[i] >= entry){
            return i;
        }
    }
    return data_size;
}


//Copies one array to the other
template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){
    //Clears dest array
    for(int i = 0; i < dest_size; i++){
        dest[i] = T();
    }
    //Copies array 2 into array 1
    for(int i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
    dest_size = src_size;
}

//Clears array
template <class T>
void clear_array(T data[], int data_size){
    for(int i = 0; i < data_size; i++){
        data[i] = T();
    }
}

//Merges all of array two into end of array 1
//Changes size
template <class T>
void merge(T data1[], int& n1, T data2[], int& n2){
    for(int i = 0; i < n2; i++){
        data1[n1] = data2[i];
        n1++;
    }
    n2 = 0;
}

//Deletes an item in the array given index
//Stores deleted item in "entry" parameter
template <class T>
void delete_item(T data[], int i, int&n , T&entry){
    //Stores delement
    entry = data[i];
    //Shifts all remaining elements left
    for(int j = i; j < n-1; j++){
        data[j] = data[j+1];
    }
    //Reduces size
    n--;
}


//Shuffles array
template <class T>
void shuffle(T a[], int size){

    //Randomly switches two elements n times
    for(int i = 0; i < size*3; i++){
        int rand1 = rand()%(size-1);
        int rand2 = rand()%(size-1);
        swap(a[rand1],a[rand2]);
    }
}

//Swaps two elements
template <class T>
void swap(T& a, T &b){
    T temp = b;
    b = a;
    a = temp;
}

#endif //BPTREE_ARRFUNCTIONS_HPP
