/**
 * Author: Jeffrey Duong
 * Project: String Tokenizer : STokenzier
 * Purpose: To grab all available tokens when given a string
 * Notes: Unknown characters has not been completely implemented
 *          Chinese characters will print two unknown tokens
 *          Other characters such as spanish have been implemented
 *              but will break a word up
*/

#ifndef STRINGTOKENIZER_STOKENIZER_HPP
#define STRINGTOKENIZER_STOKENIZER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include "SToken/Token.hpp"
#include "SToken/Table.hpp"

//Constant sizes of table and input string
const int MAX_COLUMNS = 128;
const int MAX_ROWS = 100;;
const int MAX_BUFFER = 500;

//Main class that will grab tokens given a string
class STokenizer{
private:
    //Variables to hold the string to tokenize
    std::string _bufferString;
    char _buffer[MAX_BUFFER];

    //Stores current position within the string
    int _pos;

    //Stores the length of the string
    int _bufferLength;

    //Table to use for internal states
    static int _table[MAX_ROWS][MAX_COLUMNS];

    //Function to initialize the table holding the states
    //PreCondition: A table of appropriate size
    //PostCondition: A table properly initialized with states
    void make_table(int _table[][MAX_COLUMNS]);

    //Main function of the class, retrieves a token
    //PreCondition: A string to tokenize, a start state(0), and an end state(0)
    //PostCondition: Boolean value showing whether a token was retrieved or not
    //                    data for a single token, and updated position
    bool get_token(int start_state, std::string& token, int& end_state );
public:

    //Default constructor
    STokenizer();

    //Constructor that will take a c-string to be tokenized
    STokenizer(char str[]);

    //Constructor that will take a string to be tokenized
    STokenizer(std::string str);

    //Function that will check whether the entire string has been tokenized
    //PreCondition: A properly constructed object with a string to be tested
    //PostCondition: Boolean value showing if string has been processed
    bool done();

    //Operator that will allow for STokenizer to insert a token into a Token object
    //PreCondition: A Token object to insert
    //PostCondition: Object has been inserted with appropriate values needed
    friend STokenizer& operator >> (STokenizer&s, Token& t){
        //Empty String to add too
        std::string temp = "";
        int endstate = 0;
        //Calls the function to get a single token
        s.get_token(0,temp, endstate);
        //Sets the token retrieved to an object
        t.set_string(temp);
        //sets the type of token to an object
        t.set_num(endstate);
        return s;
    }

};

#endif //STRINGTOKENIZER_STOKENIZER_HPP
