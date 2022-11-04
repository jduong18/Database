/**
 * Author: Jeffrey Duong
 * Project: Shunting Yard
 * Purpose: To convert input into rpn notation
 * Notes: N/A
 */

#ifndef TABLE_SHUNTINGYARD_HPP
#define TABLE_SHUNTINGYARD_HPP

#include "Stack.hpp"
#include "Queue.hpp"
#include "Vector.hpp"
#include "BPMap.hpp"


//Class to convert to RPN notation
class ShuntingYard{
private:
    //Stack of operators
    Stack<std::string> operations;
    //Queue for the output
    Queue<std::string> output;
    //Vector for tokens
    Vector<std::string> tokens;
    //Map of operators and precedence
    BPMap<std::string, int> operatorMap;
public:
    //Constructor that takes a vector of strings
    ShuntingYard(Vector<std::string> input);

    //Function to convert to rpn
    //PreCondition: A vector of strings from constructor
    //PostCondition: Vector of strings in proper order RPN
    Vector<std::string> getConversion();
};

//Constructor
ShuntingYard::ShuntingYard(Vector<std::string> input) {
    //Initializes
    tokens = input;
    operatorMap["<"] = 2;
    operatorMap[">"] = 2;
    operatorMap["<="] = 2;
    operatorMap[">="] = 2;
    operatorMap["="] = 2;
    operatorMap["and"] = 1;
    operatorMap["or"] = 0;
}

//Function to get conversion
Vector<std::string> ShuntingYard::getConversion() {
    //While there are tokens to process
    while(!tokens.empty()){
        std::string tempToken = tokens.popFront();
        //If the token is operator
        if(operatorMap.contains(tempToken)){
            //If operations tack is not empty and current token has higher precedence
            //Pop to output to appropriate spot
            if(!operations.empty()) {
                while (operatorMap[operations.top()] >= operatorMap[tempToken] && operations.top() != "(") {
                    output.push(operations.pop());
                    if(operations.empty()){
                        break;
                    }
                }
            }
            operations.push(tempToken);
        }

        else if(tempToken == "("){
            operations.push(tempToken);
        }
        //If token is ")" pop until "("
        else if(tempToken == ")"){
            if(!operations.empty()){
                while(operations.top() != "("){
                    output.push(operations.pop());
                }
                operations.pop();
            }

        }
        //Else just push into output
        else{
            output.push(tempToken);
        }

    }
    //Once all tokens are processed
    //Push remainder in stack into queue
    while(!operations.empty()){
        output.push(operations.pop());
    }

    Vector<std::string> rpnNotation;
    //Push everything to new vector;
    while(!output.empty()){
        rpnNotation.push_back(output.pop());
    }
    return rpnNotation;
}

#endif //TABLE_SHUNTINGYARD_HPP
