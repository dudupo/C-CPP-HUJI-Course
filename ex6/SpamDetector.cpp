
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "HashMap.hpp"
#include <cmath>


const char  SPACE = ' ';
const char  COMMA = ',';
const char ENDLINESTR            = '\n';

const std::string INVALIDINPUT          = "Invalid input";
const std::string USAGE                 = "Usage: SpamDetector <database path> <message path> <threshold>";
const std::string SPAM                  = "SPAM";
const std::string NOTSPAM               = "NOT_SPAM";
const std::string EMPTY                 = "";




const int FAILURECODE                   = 1;
const int SUCSSESCODE                   = 0;

void exitErorr()
{
    std::cout <<  INVALIDINPUT << std::endl;
    exit(FAILURECODE);
}


int parseStringToInt( std::string str )
{

    char * p = nullptr;
    int ret = std::strtol( str.data() , &p ,10 );
    if (  p == str.data() + str.size() && ret >= 0 )
    {
        return ret;
    }
    else
    {
        exitErorr();
    }
    return FAILURECODE;
}


HashMap<std::string, int> readDataBase( std::ifstream & database, int& maxlength ) {

  HashMap<std::string, int> ret = HashMap<std::string, int>();
  std::string key = EMPTY;
  std::string value_str = EMPTY;
  int value;
  char inpchar;

  while( !database.eof() ) {
    while(!database.eof() && database.peek() != COMMA) {
        if (  database.peek() == ENDLINESTR )
        {
            exitErorr();
        }

      inpchar = database.get();
      key += inpchar;
    }

    database >> inpchar >> value_str;
    value = parseStringToInt(  value_str );

    if (key == EMPTY || value_str == EMPTY)
    {
        exitErorr();
    }

    maxlength = std::max(maxlength, (int) key.length() );

    std::transform(key.begin(), key.end(), key.begin(),
                         [](unsigned char c)
                         {

                                 return std::tolower(c);

        });

    ret.insert(key, value);
    key = EMPTY;
    value_str = EMPTY;

    while( database.peek() == SPACE || database.peek() == ENDLINESTR )
      database.get();
    if (database.peek()  == COMMA )
    {
        exitErorr();
    }



  }
  return ret;
}

int subSeq( std::ifstream & _stream , HashMap<std::string, int>  & _map, int maxlength) {

  std::stringstream str_stream;
  str_stream << _stream.rdbuf(); //read the file
  std::string _str = str_stream.str();

  std::transform(_str.begin(), _str.end(), _str.begin(),
          [](unsigned char c){

          return std::tolower(c);

  });

  int grade = 0;
  std::string key;
  for (int i = 0; i < (int) _str.length(); i++) {
      for (int j = 0; j <= std::min( maxlength, (int) _str.length() - i ) ; j++) {
        key = _str.substr(i, j);
        if ( _map.containsKey(key) ) {
          grade += _map.at(key);
        }
        key = EMPTY;
      }
  }


  return grade;
}


std::ifstream openFile( std::string filename  )
{
    std::ifstream ret ( filename );
    if ( ! ret.good() )
    {
        exitErorr();
    }
    return ret;
}

int main (int argc, char* argv[]) {

  if ( argc != 4 )
  {
      std::cout << USAGE << std::endl;
      exit(FAILURECODE);
  }
  std::ifstream database  = openFile(argv[1]);


  int maxlength = 0;
  HashMap<std::string, int> _map =  readDataBase( database, maxlength );
  database.close();

  int num = 0;
  for (auto it = _map.begin(); it != _map.end(); it++) {
    num++;
  }

  std::ifstream message  = openFile( argv[2] );
  int threshold =  parseStringToInt( argv[3] ) ;

  if (threshold == 0)
  {
      exitErorr();
  }


  int grade = subSeq( message, _map, maxlength );

  message.close();



  if ( grade >= threshold )
  {
      std::cout << SPAM << std::endl;
  }
  else
  {

      std::cout << NOTSPAM << std::endl;
  }


  return SUCSSESCODE;

}
