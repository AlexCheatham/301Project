#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
  
//main program
int main() {
  int i = 5;
  ofstream file;
  file.open("test1.txt"); //Open file in default mode (ascii)
  file << i << endl; //Write to file as a decimal ascii string (0-9)
  cout << i << endl; //Also print this to terminal
  file.close();

  file.open("test2.txt"); //Open file in default mode (ascii)
  file << hex << i << endl; //Write to file as hex ascii string (0-9a-f)
  cout << hex << i << endl; //Also print this to terminal
  file.close();

  file.open("test3.txt"); //Open file in default mode (ascii)
  file << bitset<32>(i) << endl; //Write to file as 32bit binary string (0-1)
  cout << bitset<32>(i) << endl; //Also print this to terminal
  file.close();

  file.open("test4.txt",ios::binary); //Open file in binary mode
  file.write((char *) &i, sizeof(int)); //Write to file as true binary
  //Wouldn't make sense to print this to terminal.
  file.close();
  return 0;
}
