
#include <string>
#include <vector>
#include <numeric>
#include <algorithm> 
#include "Table.hpp"


 CliTable::Table::Table(CliTable::Options opt,TableBody body)
            :m_opt( std::move(opt) ),m_body( std::move(body) ) {};

 void CliTable::Table::push(std::vector<std::string> elem){
    m_body.push_back( std::move(elem) );
 }

auto CliTable::Table::getHead() const -> std::vector<std::string> {
    return m_head;
}

auto CliTable::Table::getBody() const -> TableBody {
    return m_body;
}

auto CliTable::Table::getOpt() const -> CliTable::Options {
    return m_opt;
}

auto CliTable::Table::renderWithStyles(std::string& str) -> std::string&{
    // Will have an option where to set padding,truncation, colors etc.
    // As of now we can just render with some default styles
}

auto CliTable::Table::drawTopLine() -> std::string{

    auto opt = this->getOpt().m_positionChars;

    std::string lineTop = opt[CliTable::Position::TOPLEFT] ;

    for(int i(0);i< m_maxWidths.size() - 1; ++i){
         lineTop += CliTable::Utils::repeats(opt[CliTable::Position::TOP], m_maxWidths.at(i)+4);
         lineTop += opt[CliTable::Position::TOPMID];
    }
    lineTop += CliTable::Utils::repeats(opt[CliTable::Position::TOP], m_maxWidths.back() +4) ;

    lineTop += opt[CliTable::Position::TOPRIGHT];
    
    
    return lineTop;
}


auto CliTable::Table::drawBottomLine(bool isLast) -> std::string {
    auto opt = this->getOpt().m_positionChars;
       
    std::string lineBottom = [&](){ return (isLast)? opt[CliTable::Position::BOTTOMLEFT]: opt[CliTable::Position::LEFTMID]; }();
            
    for(int i(0); i < m_maxWidths.size() - 1; ++i){
        
        int maxWidth = this->m_maxWidths.at( i );
        
        int lineEndPosition = maxWidth+4 ; 

        if( isLast ){
            lineBottom += CliTable::Utils::repeats(opt[CliTable::Position::BOTTOM], m_maxWidths.at(i)+4);
            lineBottom += opt[CliTable::Position::BOTTOMMID];
        }else{
            lineBottom += CliTable::Utils::repeats(opt[CliTable::Position::BOTTOM], m_maxWidths.at(i)+4);
            lineBottom += opt[CliTable::Position::MIDMID];
        }
    }

    if( isLast ){
        lineBottom += CliTable::Utils::repeats(opt[CliTable::Position::TOP], m_maxWidths.back() +4) ;
        lineBottom += opt[CliTable::Position::BOTTOMRIGHT];
    }else{
        lineBottom += CliTable::Utils::repeats(opt[CliTable::Position::TOP], m_maxWidths.back() +4) ;
        lineBottom += opt[CliTable::Position::RIGHTMID];
    }
    
    return lineBottom;
}


auto CliTable::Table::getMaxWidth(int columnPos) -> int{

    int max = 0;
    auto tmpBody = m_body;
    // tmpBody.push_back( m_head );

    for(int i(0); i < tmpBody.size();++i){
        
        auto vecSplittedString = CliTable::Utils::split( tmpBody[i][columnPos],'\n');
        
        for( const auto& str : vecSplittedString){

            if( str.size() > max){
                max = str.size();
            }
        }
        
    }
    return max;
}

auto CliTable::Table::getMaxHeight(int rowPos, bool isHead) -> int {
    
    auto tmpBody = m_body;
    int max = 0 ;
    
    // tmpBody.push_back( m_head );

    for(int i(0); i < tmpBody[rowPos].size();++i){
         int currentElemCount = this->countEndl(tmpBody[rowPos][i]);
        if( currentElemCount > max){
            max = currentElemCount;
        }
    }
    return max;
}

auto CliTable::Table::countEndl(const std::string& str) const -> int {

    int count = std::count_if( str.begin(),str.end(), [](char c){ return c == '\n';});
    return count ;
}


void CliTable::Table::generate() {

    auto opt = this->getOpt().m_positionChars;
    auto rowsList = this->processCells();

    std::ostream_iterator<std::string> out(std::cout,"\n");   
    std::string res ,tmpStr;

    auto maxWidths = this->computeMaxWidths( rowsList ); 
    this->m_maxWidths = maxWidths;
    bool drawTop = true;
    int i {0},j{0};

    // Matrix containing rows 

    for(auto& rowMatrixToPrint : rowsList){
        
        // Each vector of the matrix 
        if( drawTop ) {
            *out = drawTopLine();
        }

        for(auto& matrixElem : rowMatrixToPrint){
                 
            for(auto& stringElem : matrixElem ){

                    CliTable::Utils::pad(stringElem, stringElem.size()+2,' ',CliTable::Direction::LEFT);
                    // The remaining length to reach the end of a cell character 
                    int remaining = std::abs( static_cast<int>( maxWidths.at(i) - stringElem.size() + 4) ); 
                    CliTable::Utils::pad(stringElem, stringElem.size() + remaining ,' ',CliTable::Direction::RIGHT);
                    tmpStr +=  (i==0) ? opt[CliTable::Position::LEFT] + stringElem + opt[CliTable::Position::RIGHT]
                                        : "" + stringElem + opt[CliTable::Position::RIGHT];
                    ++i;
            }
            if(  rowMatrixToPrint.size() > 1){
                tmpStr += "\n";
            }

            i = 0; // Resetting to 0 for restarting the process 
          
        }
         
         if( rowMatrixToPrint.size() <= 1){
            tmpStr+="\n";
         }
         std::cout << tmpStr ;
         
         tmpStr.clear();
        // Before moving to the next matrix, we print the current one
        

        if( j != rowsList.size()-1){
            *out = drawBottomLine(false);
            drawTop = false;
            ++j;
        } 
    }
    *out = drawBottomLine(true);
}

auto CliTable::Table::processCells() -> std::vector<RowMatrix> {

    auto opt = this->getOpt().m_positionChars;
    RowMatrix rowMatrix;

    std::vector <RowMatrix> rowsList ; 

    for(int i(0); i < m_body.size(); ++i){

        for(int j(0); j < m_body[i].size(); ++j){

                std::string currentStr(m_body[i].at(j));

                int maxWidth = this->getMaxWidth(j); // For same columns 
                int maxHeight = this->getMaxHeight(i,false); // For same rows 

                int currentStrHeight = this->countEndl( currentStr );
                auto splittedString = CliTable::Utils::split(currentStr,'\n');

                int diffHeight = maxHeight - currentStrHeight;
                int k{0};
                std::string tmpStr;

                while( k < diffHeight){
                    splittedString.push_back("");
                    ++k;
                }
            
            //Checking if the last char is a "\n"

            if( currentStr.at(currentStr.size()-1) == '\n'){
                splittedString.push_back("");
            }

             rowMatrix.push_back(splittedString);
         }

        this->transpose( rowMatrix );
        rowsList.push_back( rowMatrix ); 
        rowMatrix.clear();
    }


    return rowsList;
  
}


auto CliTable::Table::maxColumn(int column, RowMatrix& matrix) -> int {

     int max{0};

     for(int i(0); i < matrix.size();++i){
        int size = matrix.at(i).at(column).size();
        if(  size > max){
            max = size;
        }
    }

    return max;

}

auto CliTable::Table::computeMaxWidths( std::vector<RowMatrix>& rowMatrix) -> std::vector<int>{
    
    int vecSize = rowMatrix[0][0].size(); 
    
    std::vector<int> widths(vecSize);

    int i{0}; // Help us to move from columns to columns 
    int max = 0 ; 
    
    while( i < vecSize ){

        for( auto& matrix : rowMatrix ){

            int currentMax = this->maxColumn(i,matrix);

            if( currentMax > max ){
                max = currentMax ;
            }
        }
        widths.at(i) = max;
        ++i;
    }

    return widths;

} 

void CliTable::Table::transpose(std::vector< std::vector<std::string> >& matrix ){

    std::vector< std::vector<std::string> > trans(matrix[0].size(),std::vector<std::string>());

    for(int i(0); i < matrix.size(); ++i){

        for(int j(0); j< matrix[i].size(); ++j){

            trans[j].push_back(matrix[i][j]);
        }
    }
    matrix = trans;
}
