//
// Created by davidponar on 03/01/2020.
//

#include "Fractal.h"
#include <boost/tokenizer.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>
#include <algorithm>
#include <boost/filesystem.hpp>

const std::string INVALIDINPUT =  "Invalid input";
const std::string USAGE  = "Usage: FractalDrawer <file path>";
const char * NEWLINEASSTRING = "\n";
const char *  COMMA = ",";
const int LOWEBOUNDRECURSION = 1;
const int HIGHBOUNDRECURSION = 6;
const int LOWEBOUNDFRACTAL = 1;
const int HIGHBOUNDFRACTAL = 3;
const int FAILURECODE = 1;
const int SUCSSESCODE = 0;
const char ZERODIGIT = '0';
const char NINEDIGIT = '9';
const int ZERO = 0;
const int ONE = 1;
const int PAIRARGS = 2;


/**
 *  exitErorr responsible to print an informative message and than exit
 *  from the program.
 */
void exitErorr()
{
    std::cout <<  INVALIDINPUT << std::endl;
    exit(FAILURECODE);
}
/**
 * checking that the given string is a number of single digit.
 * @param str the given string.
 * @return true if the string is contains a single digit. false otherwise.
 */
bool checkNumber( const std::basic_string<char>& str )
{
    int num = ZERO;
    for (char c : str )
    {
        if ( c < ZERODIGIT || c >  NINEDIGIT )
        {
            return false;
        }
        num++;
    }
    if ( num > ONE)
    {
        return false;
    }
    return true;
}


/**
 * main - the main function, paring the csv file, checking the validity of the input.
 * than calling calling to the drawing function with asked fractal.
 * @param argc - the number of the parameters the program got.
 * @param argv - the given parameters.
 * @return
 */
int main( int argc, char * argv [])
{


    if (argc != PAIRARGS)
    {
        std::cout << USAGE << std::endl;
        exit(FAILURECODE);
    }


    if ( boost::filesystem::exists(argv[1]) )
    {

        std::ifstream ifnput_stream(argv[1]);
        std::string data;

        ifnput_stream.seekg(ZERO, std::ios::end);
        data.reserve(ifnput_stream.tellg());
        ifnput_stream.seekg(ZERO, std::ios::beg);

        data.assign((std::istreambuf_iterator<char>(ifnput_stream)),
                   std::istreambuf_iterator<char>());



        std::reverse(data.begin(), data.end());


        int inpfrac, inpdeep;
        typedef boost::tokenizer <boost::char_separator<char>> tokenizer;
        boost::char_separator<char> line_sep {  NEWLINEASSTRING };
        boost::char_separator<char> sep {COMMA};
        tokenizer lines { data, line_sep };
        for (auto & line  : lines )
        {

            tokenizer  params { line , sep };
            auto it = params.begin();

            try
            {

                if ( it == params.end() ||  (!checkNumber(  *it )) )
                {
                    exitErorr();
                }

                inpdeep = stoi(  (*it) ); it++;

                if ( it == params.end() || (!checkNumber( *it )))
                {
                    exitErorr();
                }
                inpfrac = stoi(  (*it) ); it++;

                if ( it != params.end() )
                {
                    exitErorr();
                }

            }
            catch(std::exception const & e)
            {
                exitErorr();
            }

            if ( inpfrac > HIGHBOUNDFRACTAL || inpfrac < LOWEBOUNDFRACTAL ||
            inpdeep > HIGHBOUNDRECURSION  || inpdeep < LOWEBOUNDRECURSION  )
            {
                exitErorr();
            }
            Fractal::draw(fractals[inpfrac-ONE], inpdeep);
            std::cout << std::endl << std::endl ;
        }

    }
    else
    {
        exitErorr();
    }
    return SUCSSESCODE;

}
