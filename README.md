# cli-table-cpp
Pretty unicode tables for the CLI with CPP

I was looking for a simple and beautiful unicode table for the CLI for a toy 
project written in C++ but didn't found one that satisfy my needs then I build one :smile:
Base on this [JavaScript project](https://github.com/Automattic/cli-table) .

# Compiling and Running the tests 

  ## Requirements 

  - CMAKE 3.10 or greater
  - Clang or G++ 7.3.0 (That supports C++17)
  - Conan - C++ package manager
  
## Compiling 

If all requirements are met then you can build using cmake :

Create a build directory and change to it : 

`mkdir build && cd build`


Then install dependencies that are located in the `conanfile.txt` by running 

`conan install ..`

Then run the command according to the targetted OS 

```s
(win)
$ cmake .. -G "Visual Studio 15 Win64"
$ cmake --build . --config Release

(linux, mac)
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
$ cmake --build ..

```

The resulting binary will be the located in the `bin` folder.

To run test with **make**

```
make build run clean
``` 

## Basics usage 

You need first to include the header files `Table.hpp` and `Utils.hpp`.

```cpp

    #include <iostream>
    #include "Table.hpp"
    #include <string>

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
    // Or you can use the push_back() method 
    content.push_back( { "This \nis me !"         ,     "Heuh \nanother one"  } );

    Cli::Table table(opt,content);
    //Generating the final table 

    table.generate();
    
```

     
# Result after running binary

Here is the result in image of what you can get after running the tests or after your own customization: 

![Result](images/example_one.png)

![Result Multilines](images/example_two.png)
  
# Contributing 

If you found a bug or want to add a new feature, create a new branch and work on it 
after when it's ready open a pull request and after reviewing the branch will be merge into the master 
branch.
