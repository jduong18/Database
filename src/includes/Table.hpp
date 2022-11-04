//
// Created by Jeffrey Duong on 5/19/20.
//

#ifndef TABLE_TABLE_HPP
#define TABLE_TABLE_HPP
#include <string>
#include <fstream>
#include <stdio.h>
#include "Record.hpp"
#include "Vector.hpp"
#include "BPMultiMap.hpp"
#include "BPMap.hpp"
#include "ShuntingYard.hpp"
#include "RPN.hpp"


//Class for a Table to manage data
class Table{
public:

    Table();

    //Constructor with name, and field names vector
    Table(std::string name,Vector<std::string>& fieldNames);

    //Constructor with name, field names vector, and current file number
    Table(std::string name, Vector<std::string>& fieldnames, std::string fileNum);

    //Constructor with name of table to search for
    Table(std::string name);

    //Function to insert entry
    //PreCondition: Vector of data
    //PostCondition: Record added to table
    void insert_into(Vector<std::string> field_list);


    //Function to "delete" entry
    //PreCondition: Fields to delete
    //PostCondition: Record marked for deletion
    void remove_from(Vector<std::string> delete_fields);

    //Function to "delete" all entries
    //PreCondition: Table to delete
    //PostCondition: All records marked for deletion
    void removeAll();


    void drop_table(std::string name);

    //Function to return entire table
    //PreCondition: Table
    //PostCondition: Table with all elements returned
    Table select_all();

    //Function to search for specific fields
    //PreCondition: Vector of field list
    //PostCondition: Table returned
    Table select(Vector<std::string> field_list);

    //Function to search for specific fields with condition
    //PreCondition: Vector of field list and vector of condition statements
    Table select(Vector<std::string> field_list, Vector<std::string> search_field);


    //Function to print indices vector
    //PreCondition: Indices
    //PostCondition: Indices vector printed
    void print_indices();


    //Overloaded operator to print table
    //PreCondition: Table
    //PostCondition: Table printed to desired location in format
    friend std::ostream& operator << (std::ostream& outs,const Table& print_me) {
        //Opens file to read table
        std::fstream _file;
        open_fileRW(_file, print_me._fileName.c_str());
        Record r;

        //Prints header of table, name and number of elements
        outs << "Table name: " << print_me._name << ",\t";
        outs << "records: " << print_me._numberOfElements << "\n";

        //Prints fields of table
        outs << std::setw(8)  << print_me._fieldNames << "\n";

        //Prints records
        for (int i = 1; i < print_me._numberOfElements+1; i++){
            r.read(_file, long(i));
            outs << "[" << i << "]" << r.get_record() << "\n";
        }
        _file.close();
        return outs;
    }
private:

    //Number of elements in table
    int _numberOfElements;
    //Name of Table
    std::string _name;
    //Name of file associated with table
    std::string _fileName;
    //Name of file for search usage
    std::string _searchFileName;
    //List of fields the table contains
    Vector<std::string> _fieldNames;
    //Informational Vector for Record 0
    Vector<std::string> _tableInfo;


    //file object
    //std::fstream _file;

    //Current serial number for search purposes
    long serialNum;

    //Indices to manage data and search
    Vector<BPMultiMap<std::string,long> > indices;

    //Field table for conversion between field and index
    BPMap<std::string,long> field_table;

    //Function to update file with current information
    void updateFile();


    void indexRecord(Record r, long recNo);


    void insert_into_select(Vector<std::string> fields);

    void reinstateTable();

};

Table::Table(){

}


//Constructor with name and field names
Table::Table(std::string name,Vector<std::string>& fieldNames) {
    std::fstream _file;
    //Initializes data
    _numberOfElements = 0;
    serialNum = 1000;
    _name = name;
    _fileName = name + ".bin";
    _searchFileName = "!" + name + "_" + to_string(serialNum) + ".bin";
    _fieldNames.push_back("deleted");
    _fieldNames += fieldNames;

    _tableInfo = _fieldNames;
    _tableInfo.push_back(to_string(serialNum));
    _tableInfo.push_back(to_string(_numberOfElements));


    //Initializes Map and Vector
    for(int i = 0; i < _fieldNames.size(); i++){
        BPMultiMap<std::string,long> temp;
        indices.push_back(temp);
        field_table[_fieldNames[i]] = i;
    }
    //Create file
    open_fileW(_file, _fileName.c_str());
    //Writes table data into record zero
    Record r(_tableInfo);
    r.write(_file);
    _file.close();


}

//Constructor with name, fieldnames and current serial number
Table::Table(std::string name, Vector<std::string>& fieldNames, std::string fileNum){
    std::fstream _file;
    //Initializes data
    _numberOfElements = 0;
    serialNum = std::stoi(fileNum);
    _name = name;
    _fileName = name;
    _searchFileName = "!" + name + "_" + to_string(serialNum) + ".bin";
    _fieldNames.push_back("deleted");
    _fieldNames += fieldNames;

    _tableInfo = fieldNames;
    _tableInfo.push_back(to_string(serialNum));
    _tableInfo.push_back(to_string(_numberOfElements));


    //Initializes Vector and Map
    for(int i = 0; i < _fieldNames.size(); i++){
        BPMultiMap<std::string,long> temp;
        indices.push_back(temp);
        field_table[_fieldNames[i]] = i;
    }
    //Creates File
    open_fileW(_file, _fileName.c_str());
    //Writes table data into record zero
    Record r(_tableInfo);
    r.write(_file);
    _file.close();
}

//Constructor
Table::Table(std::string name){
    std::fstream _file;
    //Temporary data holders
    Vector<std::string> temp;
    Record r;
    //Initializes data
    _name = name;
    _fileName = name + ".bin";
    serialNum = 1000;
    open_fileRW(_file, _fileName.c_str());
    r.read(_file, 0);
    temp = r.get_record();
    //Removes empty spaces
    temp.deleteAllAt("");

    //Saves table data
    _tableInfo = temp;
    _fieldNames = temp;
    _fieldNames.pop();
    _fieldNames.pop();



    _numberOfElements = std::stoi(_tableInfo[_tableInfo.size()-1]);
    serialNum = std::stoi(_tableInfo[_tableInfo.size()-2]);

    _searchFileName = "!" + name + "_" + to_string(serialNum) + ".bin";

    //Initializes Vector and Map
    for(int i = 0; i < _fieldNames.size(); i++){
        BPMultiMap<std::string,long> emptyMultiMap;
        indices.push_back(emptyMultiMap);
        field_table[_fieldNames[i]] = i;
    }

    reinstateTable();
    _file.close();


}


//Function to insert into table
void Table::insert_into(Vector<std::string> field_list) {
    std::fstream _file;
    long recno;
    open_fileRW(_file, _fileName.c_str());
    Vector<std::string> holder;
    holder.push_back("\t");
    holder += field_list;
    Record r(holder);
    //Open saves record number
    recno = r.write(_file);
    for(int i = 0; i < holder.size(); i++){
        //Saves record number to indices vector
        indices[i][holder[i]]+= recno;
    }
    _numberOfElements++;
    _file.close();
    updateFile();
}

//Function to delete element from table
void Table::remove_from(Vector<std::string> delete_fields) {
    std::fstream _file;
    Vector<std::string> shuntingResult;
    Vector<long> recNum;
    ShuntingYard shunt(delete_fields);
    shuntingResult = shunt.getConversion();
    RPN rpn(shuntingResult, indices,field_table);
    recNum = rpn.getRecordNums();

    open_fileRW(_file, _fileName.c_str());
    for(int i = 0; i < recNum.size(); i++){
        Record r;
        r.read(_file, recNum[i]);
        Vector<std::string> holder = r.get_record(_fieldNames.size());
        holder[0] = "   *";
        Record write(holder);
        write.write(_file, recNum[i]);
    }
    _file.close();
    updateFile();
}

void Table::removeAll() {
    std::fstream _file;
    open_fileRW(_file, _fileName.c_str());
    for(int i = 1; i <= _numberOfElements; i++){
        Record r;
        r.read(_file, long(i));
        Vector<std::string> holder = r.get_record(_fieldNames.size());
        holder[0] = "   *";
        Record write(holder);
        write.write(_file, long(i));
    }
    _file.close();
    updateFile();
}


void Table::drop_table(std::string name) {
    std::fstream _file;
    Record r;
    Vector<std::string> temp;
    int serialsToDelete;
    open_fileRW(_file, (name+".bin").c_str());
    r.read(_file,0);
    temp = r.get_record();;
    temp.deleteAllAt("");

    serialsToDelete = std::stoi(temp[temp.size()-2]);
    for(int i = 1000; i < serialsToDelete; i++){
        remove(("!"+name+"_"+to_string(i)+".bin").c_str());
    }
    remove((name+".bin").c_str());

}


void Table::insert_into_select(Vector<std::string> fields) {
    std::fstream _file;
    long recno;
    open_fileRW(_file, _fileName.c_str());
    Record r(fields);
    recno = r.write(_file);
    for(int i = 0; i < fields.size(); i++){
        indices[i][fields[i]] += recno;
    }
    _numberOfElements++;
    _file.close();
    updateFile();
}



//Function to select all data in the table and return a table to print
Table Table::select_all(){
    std::fstream _file;
    //Pops irrelavant items

    std::string currentSerial = _tableInfo[_tableInfo.size()-2];
    //Creates new table


    Table newTable(_searchFileName, _fieldNames, currentSerial);
    open_fileRW(_file,_fileName.c_str());
    Record r;
    //Reads every record and inserts into table
    for(int i = 1; i < _numberOfElements+1; i++){
        r.read(_file, long(i));
        newTable.insert_into(r.get_record(_fieldNames.size()));
    }
    _file.close();
    serialNum ++;
    updateFile();
    return newTable;
}

//Function to select all data in the table and return a table to print
Table Table::select(Vector<std::string> field_list) {
    std::fstream _file;
    Vector<int> temp;
    Vector<std::string> constructorFields = _fieldNames;


    //If star then all fields are wanted
    if(field_list[0] == "*"){
        constructorFields.popFront();
        field_list = _fieldNames;
    }

    else{
        temp.push_back(0);
        constructorFields = field_list;
    }

    //Pushes back field numbers
    for(int i = 0; i < field_list.size(); i++){
        temp.push_back(field_table[field_list[i]]);
    }
    //Creates new table and opens current
    Table newTable(_searchFileName, constructorFields,to_string(serialNum));
    open_fileRW(_file, _fileName.c_str());
    Record r;
    //Inserts appropriate record
    for(int i = 1; i < _numberOfElements+1; i++){
        r.read(_file, long(i));
        r = r.pickFields(temp);
        newTable.insert_into_select(r.get_record(temp.size()));
    }

    _file.close();
    serialNum++;
    updateFile();
    return newTable;
}









//Function to select fields and condititions
Table Table::select(Vector<std::string> field_list, Vector<std::string> search_field) {
    std::fstream _file;
    Vector<std::string> shuntingResult;
    Vector<long> recNum;
    Vector<int> temp;

    
    ShuntingYard shunt(search_field);
    shuntingResult = shunt.getConversion();

    RPN rpn(shuntingResult, indices,field_table);
    recNum = rpn.getRecordNums();


    Vector<std::string> constructorFields = _fieldNames;
    if(field_list[0] == "*"){
        constructorFields.popFront();
        field_list = _fieldNames;
    }
    else{
        temp.push_back(0);
        constructorFields = field_list;
    }
    for (int i = 0; i < field_list.size(); i++) {
        temp.push_back(field_table[field_list[i]]);
    }

    Table newTable(_searchFileName, constructorFields, to_string(serialNum));
    open_fileRW(_file,_fileName.c_str());
    Record r;
    for(int i = 0; i < recNum.size(); i++){
        r.read(_file,recNum[i]);
        r = r.pickFields(temp);
        newTable.insert_into_select(r.get_record(temp.size()));
    }
    _file.close();
    serialNum++;
    updateFile();
    return newTable;
}


void Table::print_indices() {
    for(int i = 0; i < indices.size(); i++){
        std::cout << indices[i];
    }
}


void Table::updateFile() {
    std::fstream _file;
    open_fileRW(_file, _fileName.c_str());
    _tableInfo.pop();
    _tableInfo.pop();
    _tableInfo.push_back(to_string((serialNum)));
    _tableInfo.push_back(to_string(_numberOfElements));
    _searchFileName = "!" + _name + "_" + to_string(serialNum) + ".bin";
    Record r(_tableInfo);
    r.write(_file, 0);

    _file.close();
}


void Table::indexRecord(Record r, long recNo) {
    Vector<std::string> temp = r.get_record();
    //std::cout << temp << "\n\n";
    temp.deleteAllAt("");

    for(int i = 0; i < temp.size(); i++){
        indices[i][temp[i]] += recNo;
    }
}

void Table::reinstateTable() {
    std::fstream _file;
    Record r;
    open_fileRW(_file, _fileName.c_str());
    for(int i = 1; i <= _numberOfElements; i++){
        r.read(_file, i);
        indexRecord(r, i);
    }

    _file.close();
}

#endif //TABLE_TABLE_HPP
