#include <iostream>
#include "../src/Table.hpp"
#include <string>

int main(){

    // Options for the table to draw
    Cli::Options opt;
    // Contructing the table structure
    TableBody content = {
                            { "value \nmultilines ?"     ,        "Nope \njust \ntesting" },
                            { "value Yes\n are you sure?" ,              "Teufy"      },
                            { "This \nis me !"         ,     "Heuh \nanother one"  },
                            { "value \nmultilines ?"     ,        "Nope \njust \ntesting" },
                            { "value Yes\n are you sure?" ,              "Teufy"      },
                        };

	content.push_back( { "This \nis me !"         ,     "Heuh \nanother one"  } );
    Cli::Table table(opt,content);
    //Generating the final table 

    table.generate();
	return 0;
}