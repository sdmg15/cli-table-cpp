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

namespace CliTable {

    class Table {
    
     private:
        Options m_opt;
        std::vector<std::string> m_head;
        TableBody m_body;
        std::vector<int> m_maxWidths;

     public:

        Table(Options& opt,TableBody& body);
        
        /**
         * @brief Add a new entry to the table 
         * @param [std::string] 
         * @return void 
         **/

        void push(std::vector<std::string>& elem);

        auto getBody() const -> TableBody;

        auto getOpt() const -> Options;

        auto getHead() const -> std::vector<std::string>;

        /**
         * @brief Apply style to the given string
         * @param [std::string]
         * @return [std::string]
         **/

        auto renderWithStyles(std::string& str) -> std::string& ;

        /**
         * @brief Draw the top line with the given options
         * @return [std::string]
         **/

        auto drawTopLine() -> std::string;

        /**
         * @brief Draw the bottom line 
         * @param [bool] isLast represents whether we are drawing the last bottom line or not
         * @return [std::string]
         **/

        auto drawBottomLine(bool isLast) -> std::string;


        /**
         * @brief Generate the final table
         **/
        
        void generate();

        /** @brief Get the max width of the given table column
         *  @warning We are not taking in charge truncation as of now 
         *  @param [int] columnPos representing the column position 
         *  @return [int]
         **/

        auto getMaxWidth(int columnPos) -> int;

        /** @brief Get the max heigh of the given table row
         *  @warning We are not taking in charge truncation as of now 
         *  @param [int] rowPos representing the row position 
         *  @return [int]
         **/

        auto getMaxHeight(int rowPos,bool isHead) -> int;

        /** @brief Count the number of new lines in a given string 
         *  @param [std::string] str the given string 
         *  @return [int]
         **/

        auto countEndl(const std::string& str) const -> int;
        
        /** @brief Process the table to return a vector of rows
         *  @return [std::vector<RowMatrix>]
         **/

        auto processCells() -> std::vector<RowMatrix>;

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