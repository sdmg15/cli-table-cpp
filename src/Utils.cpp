#include "Utils.hpp"
#include <algorithm>

std::string& Cli::Utils::repeats(std::string& str, const int x){
    
    for(int i(0); i< x; ++i){
        str+=str;
    }
    return str;
}

std::string& Cli::Utils::pad(std::string& str, const int len, const int pad, const Cli::Direction dir){

}

std::string& Cli::Utils::truncate(std::string& str, const int len,const std::string& chr){

}