#ifndef CLI_H_INCLUDED
#define CLI_H_INCLUDED
#pragma once

#include <string>
#include <map>
#include <vector>

namespace CliTable {

    enum class Direction{
        LEFT,
        RIGHT,
        BOTH,
        DEFAULT,
    };

    enum class Position{
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
        MIDMID,
        MIDDLE,
    };

    struct Options {

        std::map<CliTable::Position, std::string> m_positionChars;
        std::string m_truncate;
        std::vector<int> m_colWidths;
        std::vector<int> m_colAligns;

        //Initializing all default values
        Options() {
            this->init();
        }

        Options(std::map<CliTable::Position,std::string> pos, const std::string& truncate,
                std::vector<int> colWidths, 
                std::vector<int> colAligns ){
                    
                    Options();

                    mergePositionsWithDefaults(pos);
                    m_truncate = truncate;
                    m_colAligns = colAligns;
                    m_colWidths = colWidths;

                }

        Options(std::map<CliTable::Position,std::string> pos){
          
            this->init();
            mergePositionsWithDefaults(pos);
        }

        Options(std::map<CliTable::Position, std::string> pos, const std::string& truncate){

            this->init();
            mergePositionsWithDefaults(pos);
            m_truncate = truncate;
        }

        Options(std::map<CliTable::Position, std::string> pos, std::vector<int> colWidths, std::vector<int> colAligns){

                this->init();
                mergePositionsWithDefaults(pos);
                m_colWidths = colWidths;
                m_colAligns = colAligns;
        }

        ~Options(){}

        private:

            /**
             * @brief Merge user positions with defaults 
             * @param [std::map<CliTable::Position,char>] positions
             **/

            void mergePositionsWithDefaults(const std::map<CliTable::Position,std::string>& positions){
                
                for(const auto& position: positions){
                    m_positionChars[position.first] = position.second;
                }
            }

            /**
             * Initialize parameters 
             **/
            void init(){

                m_positionChars = {

                    { Position::TOP,         "─"},
                    { Position::TOPMID,      "┬"},
                    { Position::TOPLEFT,     "┌"},
                    { Position::TOPRIGHT,    "┐"},
                    { Position::BOTTOM,      "─"},
                    { Position::BOTTOMMID,   "┴"},
                    { Position::BOTTOMLEFT,  "└"},
                    { Position::BOTTOMRIGHT, "┘"},
                    { Position::LEFT,        "│"},
                    { Position::LEFTMID,     "├"},
                    { Position::MID,         "─"},
                    { Position::MIDMID,      "┼"},
                    { Position::RIGHT,       "│"},
                    { Position::RIGHTMID,    "┤"}
                };
                
                m_truncate = "...";
                m_colAligns = {};
                m_colAligns = {};
            }

    };


    namespace Utils {

        /**
         * @brief Repeats a string x times 
         * @param [int] x 
         * @param [std::string] str
         * @return [std::string]
         **/

         auto repeats(std::string str, const int x) -> std::string;

        /**
         * @brief Pads a string according to a direction
         * @param [std::string] str
         * @param [char] len, the length of the padding 
         * @param [int] padChar, the character to use for padding
         * @param [CliTable::Direction] dir, the direction of the padding
         * @return [std::string]
         **/

         auto pad(std::string& str, const int len,
                        const char padChar, const CliTable::Direction dir) -> std::string&;

        /**
         * @brief truncates the given string 
         * @param [std::string] str
         * @param [int] len
         * @param [std::string] chr, the char to put after the truncation
         * @return [std::string]
         **/
        
         auto truncate(std::string& str, const int len, const std::string& chr) -> std::string&;

         auto split(std::string str, const char delimiter) -> std::vector<std::string>; 

    } // namespace Utils

} // namespace CliTable

#endif