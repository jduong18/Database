/**
 * Author: Jeffrey Duong
 * Project: RPN
 * Purpose: To process the rpn notation given to recnums
 */

#ifndef TABLE_RPN_HPP
#define TABLE_RPN_HPP

#include "Vector.hpp"
#include "BPMap.hpp"
#include "BPMultiMap.hpp"
#include "Stack.hpp"


//Class for RPN
class RPN{
private:
    //RPN vector
    Vector<std::string> rpnVector;

    //Vector of MultiMaps representing the table
    Vector<BPMultiMap<std::string,long> > indices;

    //Map for fields
    BPMap<std::string, long> fieldMap;

    //Map for tokens
    BPMap<std::string, int> tokenMap;

    //Function to perform a comparison between two conditions
    //PreCondition: Token of operator and Stack
    //PostCondition: Vector of long returned
    Vector<long> comparisonOperator(std::string token, Stack<std::string>& stringStack);

    //Function to perform a operator comparison between two conditions
    //PreCondition: Token of operator and Stack of record numbers
    Vector<long> logicOperator(std::string token, Stack<Vector<long> >& recoNumStack);


public:
    //Default constructor
    //Takes in, rpn notation input, indices of recNums from table, and fieldTable
    RPN(Vector<std::string> input,Vector<BPMultiMap<std::string,long> > searchIndices,
            BPMap<std::string,long> fieldTable);

    //Function to get final list of record numbers
    //PreCondition: Properly build object
    //PostCondition: Vector of longs returned
    Vector<long> getRecordNums();
};

//Constructor
RPN::RPN(Vector<std::string> input, Vector<BPMultiMap<std::string,long> > searchIndices,
        BPMap<std::string,long> fieldTable) {



    
    //Initializes
    rpnVector = input;
    indices = searchIndices;
    fieldMap = fieldTable;


    tokenMap["and"] = 0;
    tokenMap["or"] = 0;

    tokenMap["<"] = 1;
    tokenMap[">"] = 1;
    tokenMap["<="] = 1;
    tokenMap[">="] = 1;
    tokenMap["="] = 1;
}


//Function to get vector of record numbers
Vector<long> RPN::getRecordNums() {
    //Initializes
    std::string token;
    Stack<std::string> stringStack;
    Stack<Vector<long> > recoNumStack;
    Vector<long> finalVector;

    
    //While rpnNotation vector still hs elements
    while(!rpnVector.empty()){
        token = rpnVector.popFront();

        if(tokenMap.contains(token)){
            //If token is an operator
            //If token is a logic operator
            if(tokenMap[token] == 0){
                recoNumStack.push(logicOperator(token, recoNumStack));
                std::cout << recoNumStack << std::endl;
            }
            //If token is a comparison operator
            else{
                recoNumStack.push(comparisonOperator(token, stringStack));
            }
        }
        //If not an operator push into stack 
        else{
            stringStack.push(token);
            std::cout << stringStack << std::endl;
        }

        
    }




    finalVector = recoNumStack.pop();
    return finalVector;
}

//Function to compare using comparison opeartors
Vector<long> RPN::comparisonOperator(std::string token, Stack<std::string>& stringStack) {
    //Initializes
    Vector<long> recoNums;

    BPMultiMap<std::string, long>::Iterator it;
    MPair<std::string, long> mPair;


    std::string fieldValue = stringStack.pop();
    std::string fieldToSearch = stringStack.pop();

    //Checks each possible case for comparison
    //lowerbound >=
    //higherbound >
    //Gets Equal
    if(token == "="){
        recoNums = indices[fieldMap[fieldToSearch]][fieldValue];
    }
    //Gets from beginning to first >=
    else if (token == "<"){
        for(it = indices[fieldMap[fieldToSearch]].begin(); it != indices[fieldMap[fieldToSearch]].lower_bound(fieldValue); it++){
            mPair = *it;
            recoNums += mPair.value_list;
        }
    }
    //Gets from > to end
    else if (token == ">"){
        for(it = indices[fieldMap[fieldToSearch]].upper_bound(fieldValue); it != indices[fieldMap[fieldToSearch]].end(); it++){
            if(it != indices[fieldMap[fieldToSearch]].end()) {
                mPair = *it;
                recoNums += mPair.value_list;
            }
        }
    }
    //Gets from beginning to first >
    else if (token == "<="){
        for(it = indices[fieldMap[fieldToSearch]].begin(); it != indices[fieldMap[fieldToSearch]].upper_bound(fieldValue); it++){
            mPair = *it;
            recoNums += mPair.value_list;
        }
    }
    //Gets from >= to end
    else{
        for(it = indices[fieldMap[fieldToSearch]].lower_bound(fieldValue); it != indices[fieldMap[fieldToSearch]].end(); it++){
            mPair = *it;
            recoNums += mPair.value_list;
        }
    }
    return recoNums;
}

//Function for logic operator
Vector<long> RPN::logicOperator(std::string token, Stack<Vector<long> >& recoNumStack){
    //Initializes
    Vector<long> finalVector;

    Vector<long> vec1 = recoNumStack.pop();
    Vector<long> vec2 = recoNumStack.pop();

    //If token is and, get intersection
    if(token == "and"){
        finalVector = finalVector.intersectionVector(vec1, vec2);
    }
    //If token is or, get union
    if(token == "or"){
        finalVector = finalVector.unionVector(vec1, vec2);
    }
    return finalVector;
}




#endif //TABLE_RPN_HPP
