/**
 * Author: Jeffrey Duong
 * Project: STokenizer: TableFunctions
 * Purpose: Functions to be used to create state table
 * Notes: Is only used to help in the creation of the state table
 */

#ifndef STRINGTOKENIZER_TABLE_HPP
#define STRINGTOKENIZER_TABLE_HPP

#include <iostream>
#include <assert.h>

//Const size of the table
const int MAX_COLUMNTABLE = 128;
const int MAX_ROWTABLE = 100;


//Initializes the table to be filled with -1
//PreCondition: Table of appropriate size
//PostCondition: Table with all values set to -1
inline void init_table(int _table[][MAX_COLUMNTABLE]){
    for(int i = 0; i < MAX_ROWTABLE; i++){
        for(int j = 0; j < MAX_COLUMNTABLE; j++){
            _table[i][j] = -1;
        }
    }
}

//Marks a success state on the table
//PreCondition: Table of appropriate size and state to set
//PostCondition: Table with updated value indicating success
inline void mark_success(int _table[][MAX_COLUMNTABLE], int state){
    _table[state][0] = 1;
}

//Marks a fail state on the table
//PreCondition: Table of appropriate size and state to set
//PostCondition: Table with updated value indicating fail
inline void mark_fail(int _table[][MAX_COLUMNTABLE], int state){
    _table[state][0] = 0;
}


//Checks if the state is a success or not
//PreCondition: Table of appropriate size, state must be in range
//PostCondition: Boolean value showing success or not
inline bool is_success(int _table[][MAX_COLUMNTABLE], int state){
    assert(state <= MAX_ROWTABLE);
    if(_table[state][0] == 1){
        return true;
    }
    else{
        return false;
    }
}

//Marks a range of cells to a desired state
//PreCondition: Table of appropriate size, all values must be in range
//PostCondition: Updated table with marked cells
inline void mark_cells(int row, int _table[][MAX_COLUMNTABLE], int from, int to, int state){
    for(int i = from; i <= to; i++){
        _table[row][i] = state;
    }
}

//Marks a range of cells using ASCI value of c-string chars as columns
//PreCondition: Table of appropriate size, all values must be in range
//PostCondition: Updated table with marked cells
inline void mark_cells(int row, int _table[][MAX_COLUMNTABLE], const char columns[], int state){
    for(int i = 0; i < strlen(columns); i++){
        _table[row][columns[i]] = state;
    }
}

//Marks a specific cell to desired state
//PreCondition: Table of appropriate size, values must be in range
//PostCondition: Updated table with marked cell
inline void mark_cells(int row, int _table[][MAX_COLUMNTABLE], int column, int state){
    _table[row][column] = state;
}

//Prints Table
//PreCondition: Table to be printed
//PostCondition: Table is printed in console
inline void print_table(int _table[][MAX_COLUMNTABLE]){
    for(int i = 0; i < MAX_ROWTABLE; i++){
        for(int j = 0; j < MAX_COLUMNTABLE; j++){
            std::cout << _table[i][j] << "      ";
        }
        std::cout << std::endl;
    }
}


#endif //STRINGTOKENIZER_TABLE_HPP
