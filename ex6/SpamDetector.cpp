
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "HashMap.hpp"

HashMap<std::string, int> readDataBase( std::ifstream & database ) {

  HashMap<std::string, int> ret = HashMap<std::string, int>();
  std::string key = ""; int value;
  char inpchar;

  std::cout << " reading " << '\n';

  while( !database.eof() ) {
    while(!database.eof() && database.peek() != ',') {
      inpchar = database.get();
      key += inpchar;
    }
    database >> inpchar >> value;
    ret.insert(key, value);
    key = "";

    while( database.peek() == ' ' || database.peek() == '\n' )
      database.get();

  }

  std::cout << " finish to read " << '\n';
  return ret;
}

void subSeq( std::ifstream & _stream , HashMap<std::string, int>  & _map ) {

  std::stringstream str_stream;
  str_stream << _stream.rdbuf(); //read the file
  std::string _str = str_stream.str();

  int grade = 0;
  std::string key;

  for (int i = 0; i < _str.size(); i++) {
      for (int j = 0; j < 60; j++) {
        key = _str.substr(i,j);
        if ( _map.containsKey(key) ) {
          grade += _map.at(key);
          std::cout << "error -> : " << key << '\n';
        }
      }
  }

  std::cout << "total errors : " << grade << '\n';
}

int main (int argc, char* argv[]) {
  std::ifstream database ( argv[1]);
  HashMap<std::string, int> _map =  readDataBase( database );
  database.close();

  int num = 0;
  for (auto it = _map.begin(); it != _map.end(); it++) {
    std::cout  << "|" << num << "> : " <<  "second " <<  (*it).second << "\t\t\tfirst : " << (*it).first <<'\n';
    num++;
  }


  // O(n^2) :
  std::ifstream message ( argv[2] );


  subSeq( message, _map );

  message.close();


  //
  // std::cout << "\nsize " << h.size() << '\n';
  //
  // ofstream myfile;
  // myfile.open ("example.txt");
  // myfile << "Writing this to a file.\n";
  // myfile.close();
  return 0;

}
