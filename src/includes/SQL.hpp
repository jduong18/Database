/**
 * Author: Jeffrey Duong
 * Project: SQL class
 * Purpose: Creating a class that will manage database
 * Notes: N/A
 */

#ifndef TABLE_SQL_HPP
#define TABLE_SQL_HPP
#include "Table.hpp"
#include "Parser.hpp"
#include "BPMultiMap.hpp"

#include <iostream>
#include <fstream>

//SQL CLass
class SQL{
public:
    //Default construcor to use for runs
    SQL();
    //Constructor to use to only run batch file
    SQL(std::string batchName);

    //Function to run the sql class
    //PreCondition: Requires user input
    //PostCondition: Database results printed
    void run();
private:

    //Tree for commands
    BPMultiMap<std::string, std::string> pTree;

    //Parser object to to parse commands
    Parser parser;

    //Name of file containing all tables
    std::string tableFileName;

    //Fstream object for tables
    std::fstream _tableFile;

    //Map holding table objects, names as keys
    BPMap<std::string, Table > tableMap;

    //Map holding index of tables within file object
    BPMap<std::string, int> tableIndexMap;

    //Number of tables
    int numOfTables;


    //Function to make table
    //PreCondition: Parse Tree
    //PostCondition: Table is made and added to files
    void sqlMakeTable(BPMultiMap<std::string,std::string> parse);

    //Function to insert into table
    //PreCondition: Parse Tree
    //PostCondition: Record inserted to table
    void sqlInsertIntoTable(BPMultiMap<std::string,std::string> parse);

    //Function to search table
    //PreCondition: Parse Tree
    //PostCondition: Table of search values returned
    void sqlSearchTable(BPMultiMap<std::string,std::string> parse);

    //Function to search table with conditions
    //PreCondition: Parse Tree
    //PostCondition: Table of search values returned
    void sqlSearchTableCondition(BPMultiMap<std::string,std::string> parse);


    //Function to search table for Batch
    //PreCondition: Parse Tree
    //PostCondition: Table of search values returned
    void sqlBatchSearchTable(BPMultiMap<std::string,std::string> parse, std::string fileName);

    //Function to search table with conditions for Batch
    //PreCondition: Parse Tree
    //PostCondition: Table of search values returned
    void sqlBatchSearchTableCondition(BPMultiMap<std::string,std::string> parse, std::string fileName);

    //Function to drop table
    //PreCondition: Parse Tree
    //PostCondition: Table is dropped and marked in files
    void sqlDropTable(BPMultiMap<std::string, std::string> parse);

    //Function to delete from table(all)
    //PreCondition: Parse Tree
    //PostCondition: Elements to be deleted are marked on table
    void sqlDelFromTable(BPMultiMap<std::string, std::string> parse);

    //Function to delete from table with conditions
    //PreCondition: Parse Tree
    //PostCondition: Elements to be deleted are marked on table
    void sqlDelFromTableCondition(BPMultiMap<std::string, std::string> parse);

    //Function to run batch file
    //PreCondition: Parse Tree
    //PostCondition: All commands from batch file are run
    void sqlRunBatch(std::string batchFile);

    //Function to update the number of tables
    //PreCondition: New Table inserted
    //PostCondition: File modified with new number
    void updateNumber();

    //Function to add a new table to file
    //PreCondition: New Table inserted and name
    //PostCondition: File is modified with new table name
    void addTableToFile(std::string name);

    //Function to mark a table as deleted
    //PreCondition: Table is marked for deletion in file
    //PostCondition: File is modified with mark for deleted table
    void removeTableFromFile(long recNo);
};


//Default Constructor
SQL::SQL(){
    //Initializes table
    tableFileName = "Tables.bin";
    numOfTables = 0;
    Vector<std::string>  temp;

    //Open Files
    open_fileRW(_tableFile, tableFileName.c_str());
    Record r;
    //Reads first record
    r.read(_tableFile,0);
    temp = r.get_record();
    _tableFile.close();

    //If first record has number then number of tables can be found
    if(temp[0] != ""){
        open_fileRW(_tableFile, tableFileName.c_str());
        numOfTables = std::stoi(temp[0]);

        //For remainder of tables
        //If not marked as deleted, create tables and index them
        for(int i = 1; i <= numOfTables; i++){
            r.read(_tableFile, i);
            temp = r.get_record();
            if(temp[1] != "*"){
                tableMap[temp[0]] = Table(temp[0]);
                tableIndexMap[temp[0]] = i;
            }
        }
        _tableFile.close();
    }
    else{
        //IF empty file, mark first as zero
        updateNumber();
    }

}

SQL::SQL(std::string batchName){
    //Initializes table
    tableFileName = "Tables.bin";
    numOfTables = 0;
    Vector<std::string>  temp;

    //Open Files
    open_fileRW(_tableFile, tableFileName.c_str());
    Record r;
    //Reads first record
    r.read(_tableFile,0);
    temp = r.get_record();
    _tableFile.close();

    //If first record has number then number of tables can be found
    if(temp[0] != ""){
        open_fileRW(_tableFile, tableFileName.c_str());
        numOfTables = std::stoi(temp[0]);

        //For remainder of tables
        //If not marked as deleted, create tables and index them
        for(int i = 1; i <= numOfTables; i++){
            r.read(_tableFile, i);
            temp = r.get_record();
            if(temp[1] != "*"){
                tableMap[temp[0]] = Table(temp[0]);
                tableIndexMap[temp[0]] = i;
            }
        }
        _tableFile.close();
    }
    else{
        //IF empty file, mark first as zero
        updateNumber();
    }

    sqlRunBatch(batchName);


}





//Main run function
void SQL::run(){
    //Grabs command from console
    std::string command;
    std::cout << "sql (please make sure there is a space after the arrow for every command)> ";
    std::getline(std::cin, command);

    //While command is not exit, continue running
    while (command != "exit") {
        //Grab parse tree
        parser = Parser(command);
        pTree = parser.get_parse_tree();
        //If tree is a valid command
        if (parser.isValid()) {
            //If the command is batch
            if (pTree["command"][0] == "batch"){
                sqlRunBatch(pTree["batch"][0]);
            }

            //If the command is make
            else if(pTree["command"][0] == "make"){
                sqlMakeTable(pTree);
            }

            //Checks if table exists
            //Batch and make do not require an existing table
            else if(!tableMap.contains(pTree["table"][0])){
                std::cout << "Table Does Not Exist\n";
            }

            //If the command is select
            else if(pTree["command"][0] == "select"){
                //Checks for conditions
                if(pTree.contains("where")){
                    sqlSearchTableCondition(pTree);
                }
                else {
                    sqlSearchTable(pTree);
                }
            }
            //If command is insert
            else if(pTree["command"][0] == "insert"){
                sqlInsertIntoTable(pTree);
            }
            //If command is drop
            else if(pTree["command"][0] == "drop"){
                sqlDropTable(pTree);
            }
            //If command is delete
            else if(pTree["command"][0] == "delete"){
                //Checks for conditions
                if(pTree.contains("where")){
                    sqlDelFromTableCondition(pTree);
                }
                else{
                    sqlDelFromTable(pTree);
                }
            }
        }
        //Grabs user input again
        std::cout << "sql >";
        std::cin.ignore();
        std::getline(std::cin, command);
    }
}

//Creates table
void SQL::sqlMakeTable(BPMultiMap<std::string,std::string> parse) {
    //If table already exists, print and do nothing
    if(tableMap.contains(parse["table"][0])){
        std::cout << "SQL: Make fail, table already exists\n";
    }
    else {
        //Add to tableMap
        tableMap[parse["table"][0]] = Table(parse["table"][0], parse["fields"]);
        numOfTables++;
        //Add to tableIndexMap
        tableIndexMap[parse["table"][0]] = numOfTables;
        //Update files with names
        addTableToFile(parse["table"][0]);
        updateNumber();

        std::cout << "SQL: Make Completed\nTable " << parse["table"][0] << " created\n";
    }

}

//Function to insert into table
void SQL::sqlInsertIntoTable(BPMultiMap<std::string, std::string> parse) {
    //Inserts into specified table
    tableMap[parse["table"][0]].insert_into(parse["fields"]);
    std::cout << "SQL: Insert completed\n";
    std::cout << "Record inserted\n";
}

//Funciton to search table
void SQL::sqlSearchTable(BPMultiMap<std::string, std::string> parse) {
    //Searches specified table and saves it
    Table print = tableMap[parse["table"][0]].select(parse["fields"]);
    //Prints table
    std::cout << print << "\n";
    std::cout << "SQL: Search completed\n";
}

//Function to search table with conditions
void SQL::sqlSearchTableCondition(BPMultiMap<std::string, std::string> parse) {
    //Searches specified table with conditions and saves it
    Table print = tableMap[parse["table"][0]].select(parse["fields"],parse["condition"]);
    //Print table
    std::cout << print <<"\n";
    std::cout << "SQL: Search completed\n";
}


//Funciton to search table
void SQL::sqlBatchSearchTable(BPMultiMap<std::string, std::string> parse, std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName,std::ios_base::app);
    //Searches specified table and saves it
    Table print = tableMap[parse["table"][0]].select(parse["fields"]);
    //Prints table
    std::cout << print << "\n";
    outFile << print << "\n";
    std::cout << "SQL: Search completed\n";
}

//Function to search table with conditions
void SQL::sqlBatchSearchTableCondition(BPMultiMap<std::string, std::string> parse,std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName,std::ios_base::app);
    //Searches specified table with conditions and saves it
    Table print = tableMap[parse["table"][0]].select(parse["fields"],parse["condition"]);
    //Print table
    std::cout << print <<"\n";
    outFile << print << "\n";
    std::cout << "SQL: Search completed\n";
}

//Function to drop a table
void SQL::sqlDropTable(BPMultiMap<std::string, std::string> parse) {
    //Drops specified table
    Table print;
    print.drop_table(parse["table"][0]);
    //Removes from all elements
    removeTableFromFile(tableIndexMap[parse["table"][0]]);
    tableMap.remove(parse["table"][0]);
    tableIndexMap.remove(parse["table"][0]);
    updateNumber();

    std::cout << "SQL: Drop completed\n";
    std::cout << "Table Dropped\n";
}

//Delete elements from table
void SQL::sqlDelFromTable(BPMultiMap<std::string, std::string> parse) {
    //Deletes all elements in specified table
    tableMap[parse["table"][0]].removeAll();
    //Saves and prints new table
    Table print = tableMap[parse["table"][0]];
    std::cout << print;
    std::cout << "SQL: Delete completed\n";
    std::cout << "All elements deleted from table\n";

}

//Deletes elements from table with conditions
void SQL::sqlDelFromTableCondition(BPMultiMap<std::string, std::string> parse) {
    //Deletes elements form specified table
    tableMap[parse["table"][0]].remove_from(parse["condition"]);
    //Saves and prints new table
    Table print = tableMap[parse["table"][0]];
    std::cout << print;
    std::cout << "SQL: Search completed\n";
    std::cout << "Elements deleted from table\n";
}


//Function to update tableFile with number of tables
void SQL::updateNumber(){
    //Opens files
    std::fstream _file;
    open_fileRW(_file,tableFileName.c_str());

    //Pushes current number of tables to vector
    Vector<std::string> temp;
    temp.push_back(to_string(numOfTables));
    temp.push_back(" ");

    //Create record and write into file
    Record r(temp);
    r.write(_file,0);

    _file.close();
}

//Function to add table to file
void SQL::addTableToFile(std::string name){
    //Opens table file
    std::fstream _file;
    open_fileRW(_file,tableFileName.c_str());

    //Creates vector with name and empty space for deletion mark
    Vector<std::string> temp;
    temp.push_back(name);
    temp.push_back(" ");

    //Create record and write into file
    Record r(temp);
    r.write(_file);
    _file.close();
}

//Function to remove a table from the file
void SQL::removeTableFromFile(long recno) {
    //Opens file
    std::fstream _file;
    open_fileRW(_file,tableFileName.c_str());
    //Reads specified record
    Record r;
    r.read(_file, recno);

    //Marks record for deletion
    Vector<std::string> temp = r.get_record();
    temp[1] = "*";

    //Rewrites record
    Record r2(temp);
    r2.write(_file, recno);
    _file.close();
}

//Function to run a batch file
void SQL::sqlRunBatch(std::string batchFile) {
    //Opens file
    std::cout << "Batch file: " << batchFile << std::endl;
    std::fstream in(batchFile, ios::in);
    
    std::ofstream outPut;
    std::string outputBatch = batchFile+".txt";
    outPut.open(outputBatch);
    assert(in);
    assert(outPut);
    std::string batchInput;
    int commandCounter = 0;


    std::cout << batchInput;

    //Grabs every line in file
    while (std::getline(in, batchInput)) {
        //Parses command
        parser = Parser(batchInput);
        pTree = parser.get_parse_tree();
        //If Parse was valid
        if (parser.isValid()) {
            //Print command number and command itself
            std::cout << "\n\n|" << commandCounter << "|" + batchInput << "\n\n";
            outPut << "\n\n|" << commandCounter << "|" + batchInput << "\n\n";
            outPut.close();
            //If command is make
            if (pTree["command"][0] == "make") {
                sqlMakeTable(pTree);
            }
            //Checks if table exists, previous function does not require
            //an existing table
            else if (!tableMap.contains(pTree["table"][0])) {
                std::cout << "Table Does Not Exist\n";
            }

            //If command is select
            else if (pTree["command"][0] == "select") {
                //Checks for conditions
                if (pTree.contains("where")) {
                    sqlBatchSearchTableCondition(pTree,outputBatch);
                } else {
                    sqlBatchSearchTable(pTree,outputBatch);
                }
            }

            //If command is insert
            else if (pTree["command"][0] == "insert") {
                sqlInsertIntoTable(pTree);
            }

            //If command is drop
            else if (pTree["command"][0] == "drop") {
                sqlDropTable(pTree);
            }

            //If command is delete
            else if (pTree["command"][0] == "delete") {
                //Checks for conditions
                if (pTree.contains("where")) {
                    sqlDelFromTableCondition(pTree);
                } else {
                    sqlDelFromTable(pTree);
                }
            }
            //Increments command number
            commandCounter++;
            outPut.open(outputBatch,std::ios_base::app);
        }
        else {
            //If not command, print the line
            std::cout << batchInput << "\n\n";
            outPut << batchInput << "\n\n";
        }
    }
    in.close();
    outPut.close();
}



#endif //TABLE_SQL_HPP
