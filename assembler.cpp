//==========================================================================
//* class Assembler
//* Authors: Grant Szajda, Alex Cheatham
//* Written: 10/06/2022
//==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <iterator>
#include <map>
#include <bitset>

using namespace std;

class Assembler {

    vector<string> binaryRep; //String representation of the binary output by pass 2 
    vector<string> lines;   //Lines of assembly code, to be altered through passes to become readable
    map<string, int> labels;    //
    map<string, string> instructionMap;   //map for storing the MIPS instructions paired with their op code as a string int pair
    map<string, string> registerMap;    //map for storing the aliases of registers as actual registers
    
    //Stores the labels in a map, then extracts the label from the line and 
    //returns it    
    string labelStore(string input, size_t line) {
        string label;
        size_t pos{input.find_first_of(':')}; //Finds where the label starts

        for (size_t i = 0; i <= pos; i++) {
            label.push_back(input[0]);
            input.erase(input.begin() + 0);
        }

        //Gets rid of the colon in the label
        label.pop_back();
        
        //Stores the label into the map
        int insertline = static_cast<int>(line);
        labels.insert(pair<string, int>(label, insertline));

        //Returns the altered string 
        return input;
    }


    //Parses comments from a line
    string parseComments(string line) {
        size_t pos{ line.find_first_of('#')};
        line.erase(pos, line.size()-pos);
        return line;
    }


public:
    
    //Constructor 
    Assembler(vector<string> input) {

        //Takes the input code and stores it 
        lines = input;

        //Sets up the map pairing registers
        registerMap.insert(pair<string, string>("$0", "$r0"));
        registerMap.insert(pair<string, string>("$1", "$at"));
        registerMap.insert(pair<string, string>("$2", "$v0"));
        registerMap.insert(pair<string, string>("$3", "$v1"));
        registerMap.insert(pair<string, string>("$4", "$a0"));
        registerMap.insert(pair<string, string>("$5", "$a1"));
        registerMap.insert(pair<string, string>("$6", "$a2"));
        registerMap.insert(pair<string, string>("$7", "$a3"));
        registerMap.insert(pair<string, string>("$8", "$t0"));
        registerMap.insert(pair<string, string>("$9", "$t1"));
        registerMap.insert(pair<string, string>("$10", "$t2"));
        registerMap.insert(pair<string, string>("$11", "$t3"));
        registerMap.insert(pair<string, string>("$12", "$t4"));
        registerMap.insert(pair<string, string>("$13", "$t5"));
        registerMap.insert(pair<string, string>("$14", "$t6"));
        registerMap.insert(pair<string, string>("$15", "$t7"));
        registerMap.insert(pair<string, string>("$16", "$s0"));
        registerMap.insert(pair<string, string>("$17", "$s1"));
        registerMap.insert(pair<string, string>("$18", "$s2"));
        registerMap.insert(pair<string, string>("$19", "$s3"));
        registerMap.insert(pair<string, string>("$20", "$s4"));
        registerMap.insert(pair<string, string>("$21", "$s5"));
        registerMap.insert(pair<string, string>("$22", "$s6"));
        registerMap.insert(pair<string, string>("$23", "$s7"));
        registerMap.insert(pair<string, string>("$24", "$t8"));
        registerMap.insert(pair<string, string>("$25", "$t9"));
        registerMap.insert(pair<string, string>("$26", "$k0"));
        registerMap.insert(pair<string, string>("$27", "$k1"));
        registerMap.insert(pair<string, string>("$28", "$gp"));
        registerMap.insert(pair<string, string>("$29", "$sp"));
        registerMap.insert(pair<string, string>("$30", "$s8"));
        registerMap.insert(pair<string, string>("$31", "$ra"));

        //Ties instructions to their opcodes
        instructionMap.insert(pair<string, string>("add", "100000"));
        instructionMap.insert(pair<string, string>("addi", "001000"));
        instructionMap.insert(pair<string, string>("sub", "100010"));
        instructionMap.insert(pair<string, string>("mult", "011000"));
        instructionMap.insert(pair<string, string>("div", "011010"));
        instructionMap.insert(pair<string, string>("mflo", "010010"));
        instructionMap.insert(pair<string, string>("mfhi", "010000"));
        instructionMap.insert(pair<string, string>("sll", "000000"));
        instructionMap.insert(pair<string, string>("srl", "000010"));
        instructionMap.insert(pair<string, string>("lw", "100011"));
        instructionMap.insert(pair<string, string>("sw", "101011"));
        instructionMap.insert(pair<string, string>("slt", "101010"));
        instructionMap.insert(pair<string, string>("beq", "000100"));
        instructionMap.insert(pair<string, string>("bne", "000101"));
        instructionMap.insert(pair<string, string>("j", "000010"));
        instructionMap.insert(pair<string, string>("jal", "000011"));
        instructionMap.insert(pair<string, string>("jr", "001000"));
        instructionMap.insert(pair<string, string>("jalr", "001001"));
        instructionMap.insert(pair<string, string>("syscall", "001100"));
    }

    //Destructor
    ~Assembler() {};

    //Does the first pass on the code, removing labels and storing them,
    //as well as getting rid of comments other lines we can ignore
    vector<string> firstPass() {

        //Useful variables for setting up a while loop
        vector<string> tokens;
        size_t i{0};        

        while (i < lines.size()) {

            //Removes empty lines and lines we can ignore.
            if((lines[i].empty())
            || (lines[i].find_first_of('.') != -1)) { 
                lines.erase(lines.begin() + i); 
                continue; 
            }
            
            //Now checks for labels.
            //If a line contains only a label, then the line is removed from
            //the lines vector.
            if (lines[i].find_first_of(':') != -1) {
                lines[i] = labelStore(lines[i], i);
                if (lines[i].empty()) {
                    lines.erase(lines.begin() + i);
                    continue;
                }
            }

            //Last, we check for comments
            if (lines[i].find_first_of('#') != -1) {
                size_t found{lines[i].find_first_not_of(' ')};
                if (lines[i][found] == '#') {
                    lines.erase(lines.begin() + i);
                    continue;
                } else {
                    lines[i] = parseComments(lines[i]);
                }
            }

            i++; //Increments i if the entire loop finishes, and goes on to the next iteration            
        }

        //Test code to make sure first pass works properly
        
        for (size_t i = 0; i < lines.size(); i++) {
            cout << lines[i] << endl;
        }

        map<string, int>::iterator it;
        for (it = labels.begin(); it != labels.end(); it++) {
            cout << it->first << ' ' << it->second << endl;
        } 
        return lines;
    }  

};

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }    

    vector<string> lines; //Vector containing the lines of code from the file
    string str; //used for inputting the lines into the vector

    for (int i = 1; i < argc; i++) {
        //Collects the input file and opens it 
        string inputFile = argv[i];
        ifstream myFile(inputFile);

        //Adds lines to vector
        if (myFile.is_open()) {
            while(getline(myFile, str)) {
                if(str.size() > 0) {
                    lines.push_back(str);
                }
            }
        }

        //Closes the input file
        myFile.close();
    }

    //Checks to make sure vector has the correct inputs
    /*
    for (size_t i = 0; i < lines.size(); i++) { 
        cout << lines[i] << endl;
    } */

    //Creates the assembler
    Assembler test(lines);

    //Tests to make sure the first pass works 
    test.firstPass();

    return 0;
}
