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
    map<string, int> instructionType; //map that stores the type of
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
        registerMap.insert(pair<string, string>("$zero", "$0"));
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

        //sets up map that holds values for each type of instruction
        //I-type = 0, J-type = 1, R-type = 2
        instructionType.insert(pair<string, int>("add", 2));
        instructionType.insert(pair<string, int>("addi", 0));
        instructionType.insert(pair<string, int>("sub", 2));
        instructionType.insert(pair<string, int>("mult", 2));
        instructionType.insert(pair<string, int>("div", 2));
        instructionType.insert(pair<string, int>("mflo", 2));
        instructionType.insert(pair<string, int>("mfhi", 2));
        instructionType.insert(pair<string, int>("sll", 2));
        instructionType.insert(pair<string, int>("srl", 2));
        instructionType.insert(pair<string, int>("lw", 0));
        instructionType.insert(pair<string, int>("sw", 0));
        instructionType.insert(pair<string, int>("slt", 2));
        instructionType.insert(pair<string, int>("beq", 0));
        instructionType.insert(pair<string, int>("bne", 0));
        instructionType.insert(pair<string, int>("j", 1));
        instructionType.insert(pair<string, int>("jal", 1));
        instructionType.insert(pair<string, int>("jr", 2));
        instructionType.insert(pair<string, int>("jalr", 2));
        instructionType.insert(pair<string, int>("syscall", 2));

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
            //Gets rid of leading and tailing whitespace
            //Found this from https://stackoverflow.com/questions/556277/trim-remove-a-tab-t-from-a-string
            boost::trim(lines[i]); 

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

    //takes in a vector of strings and prints every element
    void printStrVector(vector<string> str) {
        cout << "The elements in your vector are: " << endl;
        for(int i = 0; i < str.size(); i++) {
            cout << str.at(i) << ' ' << endl;
            //cout << "Command type is: " << type(str.at(i)) << endl; //tests type function
        }
    }

    //returns a hard coded value to what type of instruction
    //I-type = 0, J-type = 1, R-type = 2
    int type(string str) {
        return instructionType.at(str);
    }

    //takes a reference to a vector of strings and loads commands from the file into it
    void loadCommands(vector<string> &str) {
        //For loop where we construct the string representation of the binary for each line
        for (size_t i = 0; i < lines.size(); i++) {
            string command{getCommand(lines[i])};
            str.push_back(command);
            //cout << command << endl;
        }
    }

    //returns a vector string containing each element of a command separated by whitespace
    //dont forget to remove commas, you could probably do that here
    vector<string> getLineCommand(int lineNum) {
        vector<string> lineCommand;
        string singleLine = lines[lineNum];
        stringstream check1(singleLine);
        string intermediate;

        while(getline(check1, intermediate, ' ')) {
            lineCommand.push_back(intermediate);
        }

        return lineCommand;
    }

    //function to make the add command into binary
    string make_add(vector<string> addLine) {
        string addCommand = "000000" + registerBinMap.at(addLine[2]) + registerBinMap.at(addLine[3]) + registerBinMap.at(addLine[1]) + "00000" + "100000";
        return addCommand;
    }

    string make_addi(vector<string> addiLine) {
        bitset<16> immediate = stoi(addiLine[3]);
        string addiCommand = "001000" + registerBinMap.at(addiLine[2]) + registerBinMap.at(addiLine[1]) + immediate.to_string();
        return addiCommand;
    }

    string make_sub(vector<string> subLine) {
        string addCommand = "000000" + registerBinMap.at(subLine[2]) + registerBinMap.at(subLine[3]) + registerBinMap.at(subLine[1]) + "00000" + "100010";
        return addCommand;
    }

    string make_mult(vector<string> multLine) {
        string multCommand = "000000" + registerBinMap.at(multLine[1]) + registerBinMap.at(multLine[2]) + "0000000000" + "011000";
        return multCommand;
    }

    string make_div(vector<string> divLine) {
        string divCommand = "000000" + registerBinMap.at(divLine[1]) + registerBinMap.at(divLine[2]) + "0000000000" + "011010";
        return divCommand;
    }

    //need to initialize the first two string separately otherwise it breaks with the error 
    //error: invalid operands of types ‘const char [7]’ and ‘const char [11]’ to binary ‘operator+’
    //currently works
    string make_mflo(vector<string> mfloLine) {
        string sixZeros {"000000"};
        string tenZeros {"0000000000"};
        string mfloCommand = sixZeros + tenZeros + registerBinMap.at(mfloLine[1]) + "00000" + "010010";
        return mfloCommand;
    }

    //need to initialize the first two string separately otherwise it breaks with the error 
    //error: invalid operands of types ‘const char [7]’ and ‘const char [11]’ to binary ‘operator+’
    //currently works
    string make_mfhi(vector<string> mfhiLine) {
        string sixZeros {"000000"};
        string tenZeros {"0000000000"};
        string mfhiCommand = sixZeros + tenZeros + registerBinMap.at(mfhiLine[1]) + "00000" + "010000";
        return mfhiCommand;
    }

    //makes sll string 
    string make_sll(vector<string> sllLine) {
        bitset<5> sa = stoi(sllLine[3]);
        string sixZeros {"000000"};
        string sllCommand = sixZeros + "00000" + registerBinMap.at(sllLine[2]) + registerBinMap.at(sllLine[1]) + sa.to_string() + "000000";
        return sllCommand;
    }

    string make_srl(vector<string> srlLine) {
        bitset<5> sa = stoi(srlLine[3]);
        string sixZeros {"000000"};
        string srlCommand = sixZeros + "00000" + registerBinMap.at(srlLine[2]) + registerBinMap.at(srlLine[1]) + sa.to_string() + "000010";
        return srlCommand;
    }

    //helper method for make_lw and make_sw to get offset from a string
    bitset<16> getOffset(string offset) {
        cout << "offset: " << offset << endl;
        bitset<16> offsetReturn = stoi(offset.substr(0, offset.find_first_of('(')));
        return offsetReturn;
    }

    //helper method for make_lw and make_sw to get the base from a string
    string get_base(string baseString) {
        //boost::trim(baseString); 
        //cout << "baseString: " << baseString << endl;
        size_t begin{baseString.find_first_of('(')+1};
        size_t end{baseString.size() - 1};
        //cout << begin << ' ' << end << endl;
        string baseReturn = baseString.substr(begin, end-begin);
        //string baseReturn = baseString.substr(baseString.find_first_of('(')+1, baseString.find_first_of(')')-2);
        //cout << "baseReturn: " << baseReturn << endl;
        if(registerMap.find(baseReturn) != registerMap.end()) {
            baseReturn = registerMap.at(baseReturn);

        }
        baseReturn = registerBinMap.at(baseReturn);
        return baseReturn;
    }

    string make_lw(vector<string> lwLine) {
        bitset<16> offset = getOffset(lwLine[2]);
        string base = get_base(lwLine[2]);
        string lwCommand = "100011" + base + registerBinMap.at(lwLine[1]) + offset.to_string();
        return lwCommand;
    }

    string make_sw(vector<string> swLine) {
        bitset<16> offset = getOffset(swLine[2]);
        string base = get_base(swLine[2]);
        string swCommand = "101011" + base + registerBinMap.at(swLine[1]) + offset.to_string();
        return swCommand;
    }

    string make_slt(vector<string> sltLine) {
        string sltCommand = "000000" + registerBinMap.at(sltLine[2]) + registerBinMap.at(sltLine[3]) + registerBinMap.at(sltLine[1]) + "00000" + "101010";
        return sltCommand;
    }

    string make_beq(vector<string> beqLine, int ln) {
        bitset<16> offset = labels.at(beqLine[3]) - ln - 1;
        string beqCommand = "000100" + registerBinMap.at(beqLine[1]) + registerBinMap.at(beqLine[2]) + offset.to_string();
        return beqCommand;
    }

    string make_bne(vector<string> bneLine, int ln) {
        bitset<16> offset = labels.at(bneLine[3]) - ln - 1;
        string bneCommand = "000101" + registerBinMap.at(bneLine[1]) + registerBinMap.at(bneLine[2]) + offset.to_string();
        return bneCommand;
    }

    string make_j(vector<string> jLine) {
        bitset<26> target = labels.at(jLine[1]);
        string jCommand = "000010" + target.to_string();
        return jCommand;
    }

    string make_jal(vector<string> jalLine) {
        bitset<26> target = labels.at(jalLine[1]);
        string jalCommand = "000011" + target.to_string();
        return jalCommand;
    }

    string make_jr(vector<string> jrLine) {
        string jrCommand = "000000" + registerBinMap.at(jrLine[1]) + "000000000000000" + "001000";
        return jrCommand;
    }

    string make_jalr(vector<string> jalrLine) {
        string jalrCommand;
        if(jalrLine.size() == 2) {
            jalrCommand = "000000" + registerBinMap.at("$31") + "00000" + registerBinMap.at(jalrLine[1]) + "00000" + "001001";    
        }
        else {
            jalrCommand = "000000" + registerBinMap.at(jalrLine[2]) + "00000" + registerBinMap.at(jalrLine[1]) + "00000" + "001001";            
        }
        // string jalrCommand = "000000" + registerBinMap.at(jalrLine[2]) + "00000" + registerBinMap.at(jalrLine[1]) + "00000" + "001001";
        return jalrCommand;
    }

    string make_syscall(vector<string> syscallLine) {
        //string syscallZeros{"00000000000000000000"};
        //string syscallCommand = "000000" + syscallZeros + "001100";
        string syscallCommand = "000000" + registerBinMap.at("$26") + "00000" + registerBinMap.at("$0") + "00000" + "001001";
        return syscallCommand;
    }

    //takes a line command vector as input, and checks to see if the value of each element is in the map of
    //registers. if it is, replace it with the number value, else continue
    vector<string> cleanRegisters(vector<string> lineCommand) {
        for(int i = 0; i < lineCommand.size(); i++) {
            if(registerMap.find(lineCommand[i]) == registerMap.end()) {
                continue;
            } else {
                lineCommand.at(i) = registerMap.at(lineCommand[i]);
            }
        }
        return lineCommand;
    }

    //iterates through each string in a string vector and removes any present commas
    vector<string> removeCommas(vector<string> lineCommand) {
        for(int i = 0; i < lineCommand.size(); i++) {
            while(lineCommand[i].find(',') != -1) {
                lineCommand[i].erase(lineCommand[i].find(','));
            }
        }
        return lineCommand;
    }

    //builds a binary command for second pass
    string buildCommand(string command, int lineNumber) {
        string commandTemp;
        vector<string> lineCommand = cleanRegisters(removeCommas(getLineCommand(lineNumber)));
        printStrVector(lineCommand);
        //cleanRegisters(lineCommand);
        printStrVector(lineCommand);

        if (command.compare("add") == 0) {
            return make_add(lineCommand);
        } else if (command.compare("addi") == 0) {
            return make_addi(lineCommand);
        } else if (command.compare("sub") == 0) {
            return make_sub(lineCommand);
        } else if (command.compare("mult") == 0) {
            return make_mult(lineCommand);
        } else if (command.compare("div") == 0) {
            return make_div(lineCommand);
        } else if (command.compare("mflo") == 0) {
            return make_mflo(lineCommand);
        } else if (command.compare("mfhi") == 0) {
            return make_mfhi(lineCommand);
        } else if (command.compare("sll") == 0) {
            return make_sll(lineCommand);
        } else if (command.compare("srl") == 0) {
            return make_srl(lineCommand);
        } else if (command.compare("lw") == 0) {
            return make_lw(lineCommand);
        } else if (command.compare("sw") == 0) {
            return make_sw(lineCommand);
        } else if (command.compare("slt") == 0) {
            return make_slt(lineCommand);
        } else if (command.compare("beq") == 0) {
            return make_beq(lineCommand, lineNumber);
        } else if (command.compare("bne") == 0) {
            return make_bne(lineCommand, lineNumber);
        } else if (command.compare("j") == 0) {
            return make_j(lineCommand);
        } else if (command.compare("jal") == 0) {
            return make_jal(lineCommand);
        } else if (command.compare("jr") == 0) {
            return make_jr(lineCommand);
        } else if (command.compare("jalr") == 0) {
            return make_jalr(lineCommand);
        } else if (command.compare("syscall") == 0) {
            return make_syscall(lineCommand);
        } 
        return "Not a function type";

    }

    //accepts a reference to commands and binaryRepBin, and loops through every element of commands,
    //building the command at commands
    void AlexSecondPass(vector<string> &commands, vector<string> &binaryRepBin) {
        //cout << "Number of commands " << commands.size() << endl;
        for(int i = 0; i < commands.size(); i++) {
            //cout << "command number: " << i << endl;
            binaryRepBin.push_back(buildCommand(commands.at(i),i));
        }
    }    

    //this is the actual method that starts the second pass, name needs to be changed
    vector<string> secondPassTest() {
        vector<string> binaryRepBin; //Binary output of pass two as a string
        vector<string> commands; //vector to hold every command
        loadCommands(commands);
        //cout << "commands size: " << commands.size() << endl;
        AlexSecondPass(commands, binaryRepBin);
        //printStrVector(commands);
        printStrVector(binaryRepBin);
        return binaryRepBin;
    }

};

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [input file]" << " [output file]" << endl;
        exit(0);
    }    

    vector<string> lines; //Vector containing the lines of code from the file
    string str; //used for inputting the lines into the vector

    for (int i = 1; i < argc - 1; i++) {
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
    vector<string> binaryString = test.secondPassTest();
    ofstream file;
    file.open(argv[argc-1], ios::binary);
    for(int i = 0; i < binaryString.size(); i++) {
        int toWrite = stol(binaryString[i],nullptr,2);
        file.write((char *) &toWrite, sizeof(int));
        // bitset<32> line = bitset<32>binaryString[i];
        // file.write((char *) &line, sizeof(int));
        //file << bitset<32>(binaryString[i]) << endl;
        cout << bitset<32>(binaryString[i]) << endl;
    }
    file.close();
    return 0;
}
