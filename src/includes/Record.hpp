//
// Created by Jeffrey Duong on 5/19/20.
//


//Author: Barkeshli

#ifndef TABLE_RECORD_HPP
#define TABLE_RECORD_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include "Vector.hpp"
using namespace std;

//Checks if file exists
bool file_exists(const char filename[]);

//Opens File
void open_fileRW(fstream& f, const char filename[]) throw(char*);
//Closes File
void open_fileW(fstream& f, const char filename[]);

typedef Vector<string> vectorstr;
//Class for Record
class Record{
public:
    //Empty Constructor
    Record(){
        for (int i= 0; i<MAX_ROWS; i++)
            record[i][0] = NULL;
        recno = -1;
        _num_of_fields = 0;
    }

//    Record(char str[]){
//        strcpy(record, str);
//    }

    //Constructor with vector of string
    Record(const vectorstr& v){
        for (int i= 0; i<MAX_ROWS; i++)
            record[i][0] = NULL;
        for (int i= 0; i<v.size(); i++){

            strcpy(record[i], v[i].c_str());
        }
        _num_of_fields = v.size();
    }

    //Retuns vector of record
    vectorstr get_record(){
        vectorstr v;
        //cout<<" get_record(): "<<_num_of_fields<<endl;
        for (int i = 0; i<MAX_ROWS; i++){
            v.push_back(string(record[i]));
        }
        return v;
    }

    //Returns vector of record up to specific length
    vectorstr get_record(int length){
        vectorstr v;
        for(int i = 0; i < length; i++){
            v.push_back(string(record[i]));
        }
        return v;
    }
    //Function to write to end of file
    long write(fstream& outs);
    //Function to write to specified location
    long write(fstream& outs,long recno);
    //Function to read specific record
    long read(fstream& ins, long recno);

    //Print record
    friend ostream& operator<<(ostream& outs,
                               const Record& r);

    //Returns record with only specified fields
    //PreCondition: Vector of ints relating to col
    //PostCondition: Record returned with specified fields
    Record pickFields(const Vector<int>& fieldIndicies);

private:

    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 50;
    int recno;
    int _num_of_fields;
    char record[MAX_ROWS][MAX_COLS];
};


long Record::write(fstream &outs){
    //write to the end of the file.
    outs.seekg(0, outs.end);
    long pos = outs.tellp();

    //outs.write(&record[0], sizeof(record));
    outs.write(&record[0][0], sizeof(record));

    return pos/sizeof(record);
}

long Record::write(fstream &outs,long recno){
    //write to the end of the file.
    long pos = recno * sizeof(record);
    outs.seekg(pos, ios_base::beg);
    pos = outs.tellp();

    //outs.write(&record[0], sizeof(record));
    outs.write(&record[0][0], sizeof(record));

    return pos/sizeof(record);
}

long Record::read(fstream &ins, long recno){
    long pos= recno * sizeof(record);
    ins.seekg(pos, ios_base::beg);

    ins.read(&record[0][0], sizeof(record));
    return ins.gcount();

}
ostream& operator<<(ostream& outs,
                    const Record& r){
    for (int i= 0; i<r._num_of_fields; i++){
        outs<<r.record[i]<<"|";
    }
    return outs;
}



Record Record::pickFields(const Vector<int>& fieldIndicies) {
    vectorstr temp;
    for(int i = 0; i < fieldIndicies.size(); i++){
        temp.push_back(record[fieldIndicies[i]]);
    }
    return temp;
}

//-------------------------------------------------
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
             std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists(): File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists(): File DOES exist: "<<filename<<endl;
    ff.close();
    return true;
}

void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    }
    else{
        f.open (filename,
                std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }

}
template<typename T>
ostream& operator <<(ostream& outs, const Vector<T>& v){
    for (int i = 0; i<v.size(); i++){
        outs<<v[i]<<" ";
    }
    return outs;
}

#endif //TABLE_RECORD_HPP
