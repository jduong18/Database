/**
 * Author: Jeffrey Duong
 * Project: String Tokenzier : Token
 * Purpose: To create an object that will hold necessary data
 *              Will be used by STokenizer to input data
 * Notes: Is only an object that can store data
 *          Cannot grab the data itself
 */

#ifndef STRINGTOKENIZER_TOKEN_HPP
#define STRINGTOKENIZER_TOKEN_HPP

#include <string>

class Token{
private:
    //The string that is store in the token
    std::string _token;
    //The type of token it is
        //Such as Alphabet or Number Token
    int _type;
public:

    //Default Constructor
    Token();

    //Constructor that will take in a string and type and initialize
    Token(std::string str, int type);

    //Operator that will allow to print Token object easily
    //PreCondition: A token object with a string and type
    //PostCondition: ostream that will print Token object
    friend std::ostream& operator << (std::ostream& out, const Token& t){
        std::string output ="";
        switch(t._type){
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
        output +=  "|" + t._token + "|";
        out << output;
        return out;
    }
    //Returns the type of token
    //PreCondition: Token must contain a type to return
    //PostCondition: Integer value corresponding to the type
    int type();

    //Returns the type of token as a string
    //PreCondition: Token must contain a type to return
    //PostCondition: String corresponding to the type
    std::string type_token();

    //Returns the string store in token
    //PreCondition: Token must contain a string to return
    //PostCondition: String of the token
    std::string token_str();

    //Sets the string of the token
    //PreCondition: Any valid string
    //PostCondition: Token now holds the updated string
    void set_string(std::string a);

    //Sets the type of token
    //PreCondition: Valid integer, invalid will result in unknown
    //PostCondition: Token type updated
    void set_num(int a);
};
#endif //STRINGTOKENIZER_TOKEN_HPP
