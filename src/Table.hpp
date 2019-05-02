#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#pragma once 

#include <vector>
#include <iostream>
#include <iterator>
#include "Utils.hpp"

using TableBody = std::vector< std::vector<std::string> >;

namespace Cli {

    class Table {
    
     private:
        Options m_opt;
        std::vector<std::string> m_head;
        TableBody m_body;
     public:

        Table(Options& opt,const std::vector<std::string>& head,TableBody& body);
        virtual ~Table();

        /**
         * @brief Add a new entry to the table 
         * @param [std::string] 
         * @return void 
         **/

        void push(std::vector<std::string>& elem);

        TableBody getBody() const;

        Options getOpt() const ;

        std::vector<std::string> getHead() const;

        /**
         * @brief Apply style to the given string
         * @param [std::string]
         * @return [std::string]
         **/

        std::string& renderWithStyles(std::string& str);

        /**
         * @brief Draw the top line with the given options
         * @return [std::string]
         **/

        std::string drawTopLine();

        /**
         * @brief Draw the bottom line 
         * @param [bool] isLast represents whether we are drawing the last bottom line or not
         * @return [std::string]
         **/

        std::string drawBottomLine(bool isLast);


        /**
         * @brief Generate the final table
         **/
        
        void generate();

        /** @brief Get the max width of the given table column
         *  @warning We are not taking in charge truncation as of now 
         *  @param [int] columnPos representing the column position 
         *  @return [int]
         **/

        int getMaxWidth(int columnPos);

    };
}
#endif