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

using namespace std;

class Assembler {

    vector<string> lines;
    map<string, int> labels;
    
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
        lines = input;
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
