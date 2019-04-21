#ifndef CLI_H_INCLUDED
#define CLI_H_INCLUDED
#pragma once

#include <string>
#include <map>
#include <vector>

namespace Cli {

    enum Direction{
        LEFT,
        RIGHT,
        BOTH,
        DEFAULT,
    };

    enum Position{
        TOP,
        TOPMID,
        TOPLEFT,
        TOPRIGHT,
        BOTTOM,
        BOTTOMMID,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        LEFT,
        LEFTMID,
        MID,
        RIGHT,
        RIGHTMID,
        MIDDLE,
    };

    struct Options {

        std::map<Cli::Position, char> m_positionChars;
        std::string m_truncate;
        std::vector<int> m_colWidths;
        std::vector<int> m_colAligns;

        Options(std::map<Cli::Position,char> pos, const std::string& truncate,
                std::vector<int> colWidths, 
                std::vector<int> colAligns );

        Options(std::map<Cli::Position,char> pos);

        Options(std::map<Cli::Position, char> pos, const std::string& truncate);

        Options(std::map<Cli::Position, char> pos, std::vector<int> colWidths, std::vector<int> colAligns);

        ~Options(){}
    };


    class Utils {

        /**
         * @brief Repeats a string x times 
         * @param [int] x 
         * @param [std::string] str
         * @return [std::string]
         **/

        std::string& repeats(std::string& str, const int x);

        /**
         * @brief Pads a string according to a direction
         * @param [std::string] str
         * @param [int] len 
         * @param [int] pad
         * @param [Cli::Direction] dir
         * @return [std::string]
         **/

        std::string& pad(std::string& str, const int len,const int pad, const Cli::Direction dir);

        /**
         * @brief truncates the given string 
         * @param [std::string] str
         * @param [int] len
         * @param [std::string] chr, the char to put after the truncation
         * @return [std::string]
         **/

        std::string& truncate(std::string& str, int len, const std::string& chr);

    };

} // namespace Cli

#endif