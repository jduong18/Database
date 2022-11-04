//
// Created by Jeffrey Duong on 5/27/20.
//

#ifndef TABLE_MATRIX_HPP
#define TABLE_MATRIX_HPP

#include <iostream>
#include <assert.h>

namespace Matrix {
//Const size of the table
    const int MAX_ROW = 100;
    const int MAX_COLUMN = 100;


//Initializes the table to be filled with -1
//PreCondition: Table of appropriate size
//PostCondition: Table with all values set to -1
    void init_table(int _table[][MAX_COLUMN]) {
        for (int i = 0; i < MAX_ROW; i++) {
            for (int j = 0; j < MAX_COLUMN; j++) {
                _table[i][j] = -1;
            }
        }
    }

//Marks a success state on the table
//PreCondition: Table of appropriate size and state to set
//PostCondition: Table with updated value indicating success
    void mark_success(int _table[][MAX_COLUMN], int state) {
        _table[state][0] = 1;
    }

//Marks a fail state on the table
//PreCondition: Table of appropriate size and state to set
//PostCondition: Table with updated value indicating fail
    void mark_fail(int _table[][MAX_COLUMN], int state) {
        _table[state][0] = 0;
    }


//Checks if the state is a success or not
//PreCondition: Table of appropriate size, state must be in range
//PostCondition: Boolean value showing success or not
    bool is_success(int _table[][MAX_COLUMN], int state) {
        assert(state <= MAX_ROW);
        if (_table[state][0] == 1) {
            return true;
        } else {
            return false;
        }
    }

//Marks a range of cells to a desired state
//PreCondition: Table of appropriate size, all values must be in range
//PostCondition: Updated table with marked cells
    void mark_cells(int row, int _table[][MAX_COLUMN], int from, int to, int state) {
        for (int i = from; i <= to; i++) {
            _table[row][i] = state;
        }
    }

//Marks a range of cells using ASCI value of c-string chars as columns
//PreCondition: Table of appropriate size, all values must be in range
//PostCondition: Updated table with marked cells
    void mark_cells(int row, int _table[][MAX_COLUMN], const char columns[], int state) {
        for (int i = 0; i < strlen(columns); i++) {
            _table[row][columns[i]] = state;
        }
    }

//Marks a specific cell to desired state
//PreCondition: Table of appropriate size, values must be in range
//PostCondition: Updated table with marked cell
    void mark_cells(int row, int _table[][MAX_COLUMN], int column, int state) {
        _table[row][column] = state;
    }

//Prints Table
//PreCondition: Table to be printed
//PostCondition: Table is printed in console
    void print_table(int _table[][MAX_COLUMN]) {
        for (int i = 0; i < MAX_ROW; i++) {
            for (int j = 0; j < MAX_COLUMN; j++) {
                std::cout << _table[i][j] << "      ";
            }
            std::cout << std::endl;
        }
    }

}

#endif //TABLE_MATRIX_HPP
