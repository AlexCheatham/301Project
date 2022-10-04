//==========================================================================
//* class Simulation
//* Authors: Grant Szajda, Alex Cheatham
//* Written: 10/06/2022
//==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Assembler {

}

int main() {

    //Collects the input file and opens it 
    string inputFile = argv[1];
    ifstream myFile(inputFile);

    vector<string> lines; //Vector containing the lines of code from the fil

    //Adds lines to vector
    if (myFile.is_open()) {
        while(myFile>>a) {
            myParams.push_back(a);
        }
    }

    //Closes the input file
    myFile.close();

    return 0;
}
