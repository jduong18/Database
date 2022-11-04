//
// Created by Jeffrey Duong on 3/2/20.
//


#include "STokenizer.hpp"


//Table that must be reintroduced to the cpp file
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];


//Default constructor, does not accomplish must as there is no string
STokenizer::STokenizer(){
    make_table(_table);
    _pos = 0;
}

//Primary Constructor to be used, creates table and initializes the c-string
STokenizer::STokenizer(char str[]){
    for(int i = 0; i < strlen(str); i ++){
        _buffer[i] = str[i];
    }
    for(int i = strlen(str); i < strlen(_buffer); i++){
        _buffer[i] = '\0';
    }
    _pos = 0;
    _bufferLength = strlen(_buffer);
    make_table(_table);
}

//Constructor that takes in a string as an argument and creates table
STokenizer::STokenizer(std::string str){
    _bufferString = str;
    make_table(_table);
    _pos = 0;
}




//Creates state table to use
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //Marks entire table with '-1'
    init_table(_table);

    //Marks the table with success states in appropriate locations
    mark_success(_table,1);
    mark_success(_table, 10);
    mark_success(_table,12);
    mark_success(_table, 20);
    mark_success(_table, 30);

    //Marks the table with fail states in appropriate location
    mark_fail(_table, 11);

    //Creates the "machine" for the alphabet
    mark_cells(0,_table, 'A','Z',1);
    mark_cells(0,_table, 'a','z',1);
    mark_cells(1,_table,'A','Z',1);
    mark_cells(1,_table, 'a','z',1);

    //Creates the "machine" for digits and doubles
    mark_cells(0, _table, '0', '9',10);
    mark_cells(10, _table, '0', '9',10);
    mark_cells(10, _table, '.',11);
    mark_cells(11, _table, '0', '9',12);
    mark_cells(12, _table, '0', '9',12);

    //Creates the "machine" for spaces
    mark_cells(0, _table, ' ',20);

    //Creates the "machine" for punctuation
    mark_cells(0,_table,"!@#$%^&*,.?';:\'(){}[]/-_+=",30);
}


//Function that will return data for a token as well as value for success or failure
bool STokenizer::get_token(int start_state, std::string& token, int& end_state){
    if(done()){
        return false;
    }
    else {
        int endposition = -1;

        //If character is not within ASCII range, returns that character
        //Pushes position by two, as it takes up two spaces
        if (_buffer[_pos] < 0 || _buffer[_pos] > 127) {
            token += _buffer[_pos];
            _pos++;
            token += _buffer[_pos];
            _pos++;
            end_state = 0;
        }

            //If character is within ASCII range
        else {
            //Cycles through characters from the starting position to the end
            for (int i = _pos; i < strlen(_buffer); i++) {
                //If character is out of ASCII range, stops cycling
                //If the character occurs in the middle of a good input
                if (_buffer[i] < 0 || _buffer[i] > 127) {
                    break;
                }

                //Sets the state
                start_state = _table[start_state][_buffer[i]];
                //If it is a success state
                if (_table[start_state][0] == 1) {
                    //Marks as a success by updating the end position
                    endposition = i;
                    end_state = start_state;
                }
                //If it is a fail state
                if (start_state == -1) {
                    break;
                }
            }

            //If no success state was found, endposition is still -1
            //Returns that character and updates the starting position
            if (endposition == -1) {
                token = _buffer[_pos];
                _pos++;
            }

                //Returns all characters from the start position, to the last success
                //Updates position of where to start the next token
            else {
                endposition++;
                for (int i = _pos; i < endposition; i++) {
                    token += _buffer[i];
                }
                _pos = endposition;
            }
        }
        return true;
    }
}


//Checks if entire string has been processed
//If current position on where to start is > string length
bool STokenizer::done(){
    if(_pos > _bufferLength){
        return true;
    }
    else{
        return false;
    }
}




