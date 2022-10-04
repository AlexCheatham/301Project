//==========================================================================
//* class Simulation
//* Authors: Grant Szajda, Alex Cheatham
//* Written: 10/06/2022
//==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

using namespace std;

class Assembler {

};

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }    

    //Collects the input file and opens it 
    string inputFile = argv[1];
    ifstream myFile(inputFile);

    vector<string> lines; //Vector containing the lines of code from the file
    string str; //used for inputting the lines into the vector


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

    //Checks to make sure vector has the correct inputs
    for (size_t i = 0; i < lines.size(); i++) { 
        cout << lines[i] << endl;
    } 

    return 0;
}
