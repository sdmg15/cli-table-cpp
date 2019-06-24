#include "Utils.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

auto CliTable::Utils::repeats(std::string str, const int x) -> std::string {

    std::string res;

    for(int i(0); i< x; ++i){
        res += str;
    }
    
    return res; 
}

auto CliTable::Utils::pad(std::string& str, const int len, 
                     const char padChar, const CliTable::Direction dir) -> std::string& {

    if( len >= str.size()){
        
       int paddingLen = len - static_cast<int>(str.size());

       std::string paddingVal(paddingLen,padChar);
    
        switch (dir){

            case CliTable::Direction::LEFT :
                str = paddingVal + str;
                break;
            case CliTable::Direction::RIGHT : 
                str = str + paddingVal;
                break;
            case CliTable::Direction::BOTH :
                str = paddingVal + str + paddingVal;
                break;      
            case CliTable::Direction::DEFAULT :
                [[ fallthrough ]]
            default:
                break;
        }

    }
    
    return str;

}

auto CliTable::Utils::truncate(std::string& str, const int len,const std::string& truncateStr) -> std::string&{

    if( str.size() >= len ){
        str = str.substr(0, len - truncateStr.size()) + truncateStr ; 
    }
    return str; 
}

auto CliTable::Utils::split(std::string str, const char delimiter) -> std::vector<std::string>{

    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;

}