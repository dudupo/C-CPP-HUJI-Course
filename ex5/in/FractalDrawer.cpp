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

void exit_eror( )
{
    std::cout <<  "Invalid input" << std::endl;
    exit(1);
}

bool check_number(  const std::basic_string<char>& str )
{
    int num = 0 ;
    for (char c : str )
    {
        if ( c < '0' || c > '9' )
        {
            return false;
        }
        num++;
    }
    if ( num > 1)
    {
        return false;
    }

    return true;
}



int main( int argc, char * argv []) {


    if (argc != 2){
        std::cout << "Usage: FractalDrawer <file path>" << std::endl;
        exit(1);
    }


    if ( boost::filesystem::exists(argv[1]) )
    {

        std::ifstream t(argv[1]);
        std::string data;

        t.seekg(0, std::ios::end);
        data.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        data.assign((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());



        std::reverse(data.begin(), data.end());


        int inpfrac, inpdeep;
        typedef boost::tokenizer <boost::char_separator<char>> tokenizer;
        boost::char_separator<char> line_sep { "\n"};
        boost::char_separator<char> sep {","};
        tokenizer lines { data, line_sep };
        for (auto & line  : lines ){

            tokenizer  params { line , sep };
            auto it = params.begin();

            try {

                if ( it == params.end() ||  (!check_number(  *it )) )
                {
                    exit_eror();
                }

                inpdeep = stoi(  (*it) ); it++;

                if ( it == params.end() || (!check_number( *it )))
                {
                    exit_eror();
                }
                inpfrac = stoi(  (*it) ); it++;

                if ( it != params.end() )
                {
                    exit_eror();
                }

            }
            catch(std::exception const & e)
            {
                exit_eror();
            }

            if ( inpfrac > 3 || inpfrac <= 0 || inpdeep > 6  || inpdeep < 1  )
            {
                exit_eror();
            }
            Fractal::draw(fractals[inpfrac-1], inpdeep);
            std::cout << std::endl << std::endl ;
        }

    }
    else {
        exit_eror();
    }
    return 0;

}
