#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#pragma once 

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Utils.hpp"

using TableBody = std::vector< std::vector<std::string> >;
using RowMatrix  = std::vector< std::vector<std::string> >;

namespace Cli {

    class Table {
    
     private:
        Options m_opt;
        std::vector<std::string> m_head;
        TableBody m_body;
        std::vector<int> m_maxWidths;

     public:

        Table(Options& opt,TableBody& body);
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

        /** @brief Get the max heigh of the given table row
         *  @warning We are not taking in charge truncation as of now 
         *  @param [int] rowPos representing the row position 
         *  @return [int]
         **/

        int getMaxHeight(int rowPos,bool isHead);

        /** @brief Count the number of new lines in a given string 
         *  @param [std::string] str the given string 
         *  @return [int]
         **/

        int countEndl(const std::string& str) const;
        
        /** @brief Process the table to return a vector of rows
         *  @return [std::vector<RowMatrix>]
         **/

        std::vector<RowMatrix> processCells();

        /** @brief Transpose the given matrix
         *  @param [std::vector<std::vector<std::string>> ] matrix
         **/

        void transpose(std::vector< std::vector<std::string> >& matrix); 

        /**
         * Compute the max width of the given rowList
         * @param [ std::vector<RowMatrix>]
         * @return [ std::vector<int> ]
         */

        auto computeMaxWidths(std::vector<RowMatrix>& rowMatrix) -> std::vector<int>;

        /** @brief Compute the max column width of the given table
         *  @param [int] i representing the column position 
         *  @return [int]
         **/

        auto maxColumn(int i, RowMatrix& m) -> int ;
    };
}
#endif