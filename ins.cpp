#include <fstream>
#include <iostream>

using namespace std;

void instructions(){
string line;
ifstream myfile ("instructions.txt");//open fiel instructions.txt
  if (myfile.is_open()) {
   while ( getline (myfile,line) ) {//while there are more lines,
      cout << line << '\n';//show each line onto screen
   }
  myfile.close();//close file

  } else
      cout << "Unable to open file";//display error if error in opening file
 }
