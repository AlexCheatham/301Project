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
#include <boost/algorithm/string.hpp> 

using namespace std;

class Assembler {

    vector<string> lines;   //Lines of assembly code, to be altered through passes to become readable
    map<string, int> labels;    //Stores all the labels and their line numbers
    map<string, string> instructionMap;   //map for storing the MIPS instructions paired with their op code as a string int pair
    map<string, string> registerMap;    //map for storing the aliases of registers as actual registers
    map<string, string> registerBinMap;    //map for storing the actual registers as a binary value
    
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
        size_t pos{line.find_first_of('#')};
        line.erase(pos, line.size()-pos);
        return line;
    }

    //Gets the command from the line and returns it
    string getCommand(string line) {
        //size_t pos{line.find_first_of(' ')};
        string command{line.substr(0, line.find(' '))};
        cout << command << endl;
        return command;
    }


public:
    
    //Constructor 
    Assembler(vector<string> input) {

        //Takes the input code and stores it 
        lines = input;

        //Sets up the map pairing registers
        registerMap.insert(pair<string, string>("$r0", "$0"));
        registerMap.insert(pair<string, string>("$at", "$1"));
        registerMap.insert(pair<string, string>("$v0", "$2"));
        registerMap.insert(pair<string, string>("$v1", "$3"));
        registerMap.insert(pair<string, string>("$a0", "$4"));
        registerMap.insert(pair<string, string>("$a1", "$5"));
        registerMap.insert(pair<string, string>("$a2", "$6"));
        registerMap.insert(pair<string, string>("$a3", "$7"));
        registerMap.insert(pair<string, string>("$t0", "$8"));
        registerMap.insert(pair<string, string>("$t1", "$9"));
        registerMap.insert(pair<string, string>("$t2", "$10"));
        registerMap.insert(pair<string, string>("$t3", "$11"));
        registerMap.insert(pair<string, string>("$t4", "$12"));
        registerMap.insert(pair<string, string>("$t5", "$13"));
        registerMap.insert(pair<string, string>("$t6", "$14"));
        registerMap.insert(pair<string, string>("$t7", "$15"));
        registerMap.insert(pair<string, string>("$s0", "$16"));
        registerMap.insert(pair<string, string>("$s1", "$17"));
        registerMap.insert(pair<string, string>("$s2", "$18"));
        registerMap.insert(pair<string, string>("$s3", "$19"));
        registerMap.insert(pair<string, string>("$s4", "$20"));
        registerMap.insert(pair<string, string>("$s5", "$21"));
        registerMap.insert(pair<string, string>("$s6", "$22"));
        registerMap.insert(pair<string, string>("$s7", "$23"));
        registerMap.insert(pair<string, string>("$t8", "$24"));
        registerMap.insert(pair<string, string>("$t9", "$25"));
        registerMap.insert(pair<string, string>("$k0", "$26"));
        registerMap.insert(pair<string, string>("$k1", "$27"));
        registerMap.insert(pair<string, string>("$gp", "$28"));
        registerMap.insert(pair<string, string>("$sp", "$29"));
        registerMap.insert(pair<string, string>("$s8", "$30"));
        registerMap.insert(pair<string, string>("$ra", "$31"));

        //sets up the map pairing registers with their binary values;
        registerBinMap.insert(pair<string, string>("$0", "00000"));
        registerBinMap.insert(pair<string, string>("$1", "00001"));
        registerBinMap.insert(pair<string, string>("$2", "00010"));
        registerBinMap.insert(pair<string, string>("$3", "00011"));
        registerBinMap.insert(pair<string, string>("$4", "00100"));
        registerBinMap.insert(pair<string, string>("$5", "00101"));
        registerBinMap.insert(pair<string, string>("$6", "00110"));
        registerBinMap.insert(pair<string, string>("$7", "00111"));
        registerBinMap.insert(pair<string, string>("$8", "01000"));
        registerBinMap.insert(pair<string, string>("$9", "01001"));
        registerBinMap.insert(pair<string, string>("$10","01010"));
        registerBinMap.insert(pair<string, string>("$11","01011"));
        registerBinMap.insert(pair<string, string>("$12","01100"));
        registerBinMap.insert(pair<string, string>("$13","01101"));
        registerBinMap.insert(pair<string, string>("$14","01110"));
        registerBinMap.insert(pair<string, string>("$15","01111"));
        registerBinMap.insert(pair<string, string>("$16","10000"));
        registerBinMap.insert(pair<string, string>("$17","10001"));
        registerBinMap.insert(pair<string, string>("$18","10010"));
        registerBinMap.insert(pair<string, string>("$19","10011"));
        registerBinMap.insert(pair<string, string>("$20","10100"));
        registerBinMap.insert(pair<string, string>("$21","10101"));
        registerBinMap.insert(pair<string, string>("$22","10110"));
        registerBinMap.insert(pair<string, string>("$23","10111"));
        registerBinMap.insert(pair<string, string>("$24","11000"));
        registerBinMap.insert(pair<string, string>("$25","11001"));
        registerBinMap.insert(pair<string, string>("$26","11010"));
        registerBinMap.insert(pair<string, string>("$27","11011"));
        registerBinMap.insert(pair<string, string>("$28","11100"));
        registerBinMap.insert(pair<string, string>("$29","11101"));
        registerBinMap.insert(pair<string, string>("$30","11110"));
        registerBinMap.insert(pair<string, string>("$31","11111"));


        //Ties instructions to their opcodes or function codes 
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
            
            //Gets rid of leading and trailing whitespace
            //Found this from https://stackoverflow.com/questions/556277/trim-remove-a-tab-t-from-a-string
            boost::trim(lines[i]); 
            
            i++; //Increments i if the entire loop finishes, and goes on to the next iteration            
        }

        //Test code to make sure first pass works properly
        /*
        for (size_t i = 0; i < lines.size(); i++) {
            cout << lines[i] << endl;
        }

        map<string, int>::iterator it;
        for (it = labels.begin(); it != labels.end(); it++) {
            cout << it->first << ' ' << it->second << endl;
        } */
        return lines;
    }  

    //second pass through code to convert to binary
    //only works if first pass has been called
    vector<string> secondPass() {

        vector<string> binaryRep; //String representation of the binary output by pass 2 

        //For loop where we construct the string representation of the binary for each line
        for (size_t i = 0; i < lines.size(); i++) {
            string command{getCommand(lines[i])};
            //cout << command << endl;
        }

        return binaryRep;
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
    test.secondPass();

    return 0;
}
