#include "Utils.hpp"
#include <algorithm>
#include <string>
#include <iostream>

std::string& Cli::Utils::repeats(std::string& str, const int x){

    std::string res;

    for(int i(0); i< x; ++i){
        res += str;
    }
    str=res; 

    return str;
}

std::string& Cli::Utils::pad(std::string& str, const int len, const char padChar, const Cli::Direction dir){

    if( len >= str.size()){
        
       int paddingLen = len - static_cast<int>(str.size());

       std::string paddingVal(paddingLen,padChar);
    
        switch (dir){

            case Cli::Direction::LEFT :
                str = paddingVal + str;
                break;
            case Cli::Direction::RIGHT : 
                str = str + paddingVal;
                break;
            case Cli::Direction::BOTH :
                str = paddingVal + str + paddingVal;
                break;      
            case Cli::Direction::DEFAULT :
                [[ fallthrough ]]
            default:
                break;
        }

    }
    
    return str;

}

std::string& Cli::Utils::truncate(std::string& str, const int len,const std::string& truncateStr){

    if( str.size() >= len ){
        str = str.substr(0, len - truncateStr.size()) + truncateStr ; 
    }
    return str; 
}