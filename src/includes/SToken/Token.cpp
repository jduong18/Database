//
// Created by Jeffrey Duong on 3/2/20.
//

#include "Token.hpp"

//Defualt constructor, initializes everything to blank and zero
Token::Token(){
    _token = "";
    _type = 0;
}

//Constructor that will store arguments into object
Token::Token(std::string str, int type){
    _token = str;
    _type = type;
}

//Returns the int value of the type of token
int Token::type() {
    return _type;
}

//Returns the string value of the type of token
std::string Token::type_token() {
    std::string output = "";
    switch(_type){
        case 1:
            output += "ALPHA: ";
            break;
        case 10:
            output += "DIGIT: ";
            break;
        case 12:
            output += "DOUBLE: ";
            break;
        case 20:
            output += "SPACE: ";
            break;
        case 30:
            output += "PUNCT: ";
            break;
        default:
            output += "UNKNOWN: ";
            break;
    }
    return output;

}

//Returns the string stored in the token
std::string Token::token_str() {
    return _token;
}

//Updates string stored by token
void Token::set_string(std::string a) {
    _token = a;
}

//Updates type stored by token
void Token::set_num(int a) {
    _type = a;
}