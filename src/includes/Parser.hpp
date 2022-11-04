/**
 * Author: Jeffrey Duong
 * Project: Parser
 * Purpose: To parse our commands
 */

#ifndef TABLE_PARSER_HPP
#define TABLE_PARSER_HPP

#include <algorithm>
#include "STokenizer.hpp"
#include "BPMultiMap.hpp"
#include "BPMap.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"


//Enums for key words, to be used with matrix
enum keys{select = 1, from = 2, star = 3, symbol = 4, comma = 5, where = 6, comparison = 7, make = 8,
        table = 9, fields = 10, insert = 11, into = 12, values = 13, lparen = 14, rparen = 15, logic = 16, drop = 17,
        del = 18, batch = 19, period = 98, slash = 99};

const int MAXROWS = 100;
const int MAXCOLUMNS = 100;

//Class to parse command
class Parser{
private:
    //BPMultiMap to store parsed commands
    BPMultiMap<std::string,std::string> pTree;

    //Map of literals and their enums
    BPMap<std::string,keys> keywords;

    //Adjacency matrix
    int _matrix[MAXROWS][MAXCOLUMNS];

    //Queue to store our tokens
    Vector<std::string> inputQueue;

    //Function to get enum of token
    //PreCondition: Token
    //PostCondition: Int returned
    int get_column(std::string token);

    //Builds Map of keywords
    //PreCondition: Enum list
    //PostCondition: _matrix is created
    void build_keyword_list();


    //Builds adjacency matrix
    //PreCondition: 2d array
    //PostCondition: _matrix is created
    void createMatrix(int matrix[][MAXCOLUMNS]);

    //Buffer to store input string
    std::string buffer;

    //Variable to check if pTree is valid
    bool valid;




public:
    //Default Constructor
    Parser();

    //Constructor with cString parameter
    Parser(char* s);

    //Constructor with string parameter
    Parser(std::string s);

    //Function to set new string to object
    //PreCondition: cString
    //PostCondition: object has new string stored
    void set_string(char* s);

    //Function to get parse Tree
    //PreCondition: String to process
    //PostCondition: MultiMap returned
    BPMultiMap<std::string,std::string> get_parse_tree();

    //Function to check if pTree was valid
    //PreCondition: pTree
    //PostCondition: T/F returned
    bool isValid();
};

//Default constructor
Parser::Parser(){
    //Initializes everything
    valid = false;
    createMatrix(_matrix);

    build_keyword_list();

}

//Constructor with cString
Parser::Parser(char *s) {
    //Initializes everything
    valid = false;
    buffer = s;
    createMatrix(_matrix);

    build_keyword_list();

    //Sets string
    set_string(s);

}


//Constructor with string
Parser::Parser(std::string s) {
    //Initializes everything
    buffer = s;
    createMatrix(_matrix);

    build_keyword_list();

    //Sets string
    const char* temp = buffer.c_str();
    set_string(const_cast<char *>(temp));

}

//Creates adjacency matrix
void Parser::createMatrix(int matrix[][MAXCOLUMNS]){
    //Create matrix filled with -1
    Matrix::init_table(matrix);

    //Marks success states
    Matrix::mark_success(matrix, 5);
    Matrix::mark_success(matrix, 9);
    Matrix::mark_success(matrix,24);
    Matrix::mark_success(matrix,34);
    Matrix::mark_success(matrix, 42);
    Matrix::mark_success(matrix, 52);
    Matrix::mark_success(matrix, 61);


    //Marks all cells from state to state
    Matrix::mark_cells(0,matrix, select, 1);

    Matrix::mark_cells(1,matrix,star, 2);
    Matrix::mark_cells(1,matrix,symbol, 2);

    Matrix::mark_cells(2, matrix, comma, 3);
    Matrix::mark_cells(2, matrix, from, 4);

    Matrix::mark_cells(3, matrix, symbol, 2);

    Matrix::mark_cells(4, matrix, symbol, 5);

    Matrix::mark_cells(5, matrix, where, 6);

    Matrix::mark_cells(6, matrix, symbol, 7);

    Matrix::mark_cells(7, matrix, comparison, 8);

    Matrix::mark_cells(8, matrix, symbol, 9);

    Matrix::mark_cells(9, matrix, logic, 10);

    Matrix::mark_cells(10, matrix, symbol, 7);






    Matrix::mark_cells(0,matrix,make,20);

    Matrix::mark_cells(20,matrix,table,21);

    Matrix::mark_cells(21,matrix,symbol,22);

    Matrix::mark_cells(22,matrix,fields,23);

    Matrix::mark_cells(23,matrix,symbol,24);

    Matrix::mark_cells(24,matrix,comma,25);

    Matrix::mark_cells(25,matrix,symbol,24);

    Matrix::mark_cells(0,matrix,insert,30);

    Matrix::mark_cells(30,matrix,into,31);

    Matrix::mark_cells(31,matrix,symbol,32);

    Matrix::mark_cells(32,matrix,values,33);

    Matrix::mark_cells(33,matrix,symbol,34);

    Matrix::mark_cells(34,matrix,comma,35);

    Matrix::mark_cells(35,matrix,symbol,34);


    Matrix::mark_cells(0,matrix,drop,40);

    Matrix::mark_cells(40,matrix,table,41);

    Matrix::mark_cells(41,matrix,symbol,42);


    Matrix::mark_cells(0,matrix,del,50);

    Matrix::mark_cells(50,matrix,from,51);

    Matrix::mark_cells(51,matrix,symbol,52);

    Matrix::mark_cells(52,matrix,where,6);


    Matrix::mark_cells(0, matrix, batch, 60);

    Matrix::mark_cells(60, matrix, symbol, 61);


}


//Function to set string and tokenize into inputQueue
void Parser::set_string(char *s) {
    //Initializes
    buffer = s;
    STokenizer stk(s);
    Token token;
    stk >> token;
    while(!stk.done()){
        //If token is not whitespace
        if(token.token_str() != " " && token.token_str() != "\t"){
            //If token is " then push entire quote in as one object
            if(token.token_str() == "\""){
                std::string holder;
                stk >> token;
                while(token.token_str() != "\""){
                    holder += token.token_str();
                    stk >> token;
                }
                inputQueue.push_back(holder);
            }
            //

            else {
                //If commands are AND or OR then set to lower case
                if(token.token_str() == "AND" || token.token_str() == "OR"){
                    std::string holder = token.token_str();
                    std::transform(holder.begin(), holder.end(), holder.begin(), ::tolower);
                    inputQueue.push_back(holder);
                }
                //Else just push item in
                else {
                    inputQueue.push_back(token.token_str());
                }
            }
        }
        stk >> token;
    }

}

//Returns column value of token
int Parser::get_column(std::string token) {
    if(!keywords.contains(token)){
        return keywords["symbol"];
    }
    return keywords[token];
}

//Creates keywords map
void Parser::build_keyword_list() {
    keywords["select"] = select;
    keywords["from"] = from;
    keywords["*"] = star;
    keywords["symbol"]  = symbol;
    keywords[","] = comma;
    keywords["where"] = where;
    keywords["="] = comparison;
    keywords[">"] = comparison;
    keywords["<"] = comparison;
    keywords["<="] = comparison;
    keywords[">="] = comparison;
    keywords["make"] = make;
    keywords["table"] = table;
    keywords["fields"] = fields;
    keywords["insert"] = insert;
    keywords["into"] = into;
    keywords["values"] = values;
    keywords["drop"] = drop;
    keywords["delete"] = del;
    keywords["("] = lparen;
    keywords[")"] = rparen;
    keywords["and"] = logic;
    keywords["or"] = logic;
    keywords["batch"] = batch;
    keywords["/"] = slash;
    keywords["."] = period;
}

//Function to get the parse tree
BPMultiMap<std::string, std::string> Parser::get_parse_tree(){
    valid = true;
    pTree.clear();
    //If at any point state = -1, break, clear tree
    int state = 0;
    int queueSize = inputQueue.size();
    for(int i = 0; i < queueSize; i++){
        std::string token = inputQueue.popFront();
        state = _matrix[state][get_column(token)];
        //If at any point state = -1 then valid is false
        if(state == -1){
            pTree.clear();
            valid = false;
            break;
        }
        //Command for each state
        switch(state){
            case 1:
            case 20:
            case 30:
            case 40:
            case 50:
            case 60:
                pTree["command"] += token;
                break;
            case 2:
            case 24:
            case 34:
                pTree["fields"] += token;
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
            case 22:
            case 32:
            case 42:
            case 52:
                pTree["table"] += token;
                break;
            case 6:
                pTree["where"] += "yes";
                break;
            case 7:
            case 8:
            case 9:
            case 10:
                pTree["condition"] += token;
                break;
            case 61:
                pTree["batch"] += token;
            default:
                break;
        }
    }
    //CHecks final success state
    //If not success then valid = false
    if (!Matrix::is_success(_matrix,state)){
        pTree.clear();
        valid = false;
    }
    return pTree;
}

//Function to return valid
bool Parser::isValid() {
    return valid;
}
#endif //TABLE_PARSER_HPP
