#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <iterator>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
    map<string, int> instructionMap;   //map for storing the MIPS instructions paired with their op code as a string int pair
    map<string, string> registerMap;    //map for storing the aliases of registers as actual registers
    vector<string> registerArray;
    vector<string> aliasArray;
    vector<string> assemblyInstructions;
    vector<int> OP_codes;

    //values for all the register names
    registerArray = {"$0","$1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11",
                              "$12","$13","$14","$15","$16","$17","$18","$19","$20","$21","$22",
                              "$23","$24","$25","$26","$27","$28","$29","$30","$31"};         

    //MIPS register aliases
    aliasArray =    {"r0","at","v0","v1","a0","a1","a2","a3","t0","t1","t2","t3","t4",
                              "t5","t6","t7","s0","s1","s2","s3","s4","s5","s6","s7","t8","t9",
                              "k0","k1","gp","sp","s8","ra"};                                 
    
    //MIPS instruction OP code, the order corresponds to the instruction below
    OP_codes = {100000,001000,100010,011000,011010,010010,010000,000000,000010,
                      100011,101011,101010,000100,000101,000010,000011,001000,001001,001100};

    //stores assembly instrunctions to be mapped to opcodes in a string array
    assemblyInstructions = {"add","addi","sub","mult","div","mflo","mfhi","sll","srl",
                                     "lw","sw","slt","beq","bne","j","jal","jr","jalr","syscall"}; 

    //for loop to iterate through both register arrays and add them to the register map
    for(int i=0; i < 32; i++) {
        registerMap.insert(pair<string, string>(aliasArray[i],registerArray[i]));
    }

    //for loop to iterate through assemblyInstructions and OP_codes to add them to the instruction map
    for(int i=0; i < 20; i++) {
        instructionMap.insert(pair<string, int>(assemblyInstructions[i],OP_codes[i]));
    }

    //Test code to make sure the maps contain the correct content 
    map<string, int>::iterator it;
    for (it = instructionMap.begin(); it != instructionMap.end(); it++) {
        cout << it->first << ' ' << it->second << endl;
    }

        
    map<string, string>::iterator itr;
    for (itr = registerMap.begin(); itr != registerMap.end(); itr++) {
        cout << itr->first << ' ' << itr->second << endl;
    }
    return 0;
}