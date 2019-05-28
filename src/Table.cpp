
#include <string>
#include <vector>
#include <algorithm> 
#include "Table.hpp"


 Cli::Table::Table(Cli::Options& opt, const std::vector<std::string>& head,TableBody& body)
            :m_opt(opt),m_body(body),m_head(head){};

 Cli::Table::~Table(){};
 

 void Cli::Table::push(std::vector<std::string>& elem){
    m_body.push_back(elem);
 }

std::vector<std::string> Cli::Table::getHead() const{
    return m_head;
}

TableBody Cli::Table::getBody() const {
    return m_body;
}

Cli::Options Cli::Table::getOpt() const {
    return m_opt;
}

std::string& Cli::Table::renderWithStyles(std::string& str){
    // Will have an option where to set padding,truncation, colors etc.
    // As of now we can just render with some default styles
}

std::string Cli::Table::drawTopLine(){

    auto opt = this->getOpt().m_positionChars;

    std::string lineTop = opt[Cli::Position::TOPLEFT] ;
        
    for(int i(0); i < m_head.size(); ++i){
        
        int maxWidth = this->m_maxWidths.at(i);

        int lineEndPosition = maxWidth;

        lineTop += Cli::Utils::repeats(opt[Cli::Position::TOP], lineEndPosition+ 4);
        // When we are at the corner we put the TOPRIGHT char else we put the TOPMID
        lineTop += (i!=m_head.size()-1)? opt[Cli::Position::TOPMID]: opt[Cli::Position::TOPRIGHT];
    }

    return lineTop;
}


std::string Cli::Table::drawBottomLine(bool isLast){
    auto opt = this->getOpt().m_positionChars;
       
    std::string lineBottom = [&](){ return (isLast)? opt[Cli::Position::BOTTOMLEFT]: opt[Cli::Position::LEFTMID]; }();
            
    for(int i(0); i < m_head.size(); ++i){
        
        int maxWidth = this->m_maxWidths.at( i );
        
        int lineEndPosition = maxWidth+4 ; 

        if( isLast){

            lineBottom += Cli::Utils::repeats(opt[Cli::Position::BOTTOM],lineEndPosition);

            lineBottom += (i!=m_head.size()-1)? opt[Cli::Position::BOTTOMMID] : opt[Cli::Position::BOTTOMRIGHT];
        }else{

            lineBottom += Cli::Utils::repeats(opt[Cli::Position::BOTTOM],lineEndPosition);

            lineBottom += (i!=m_head.size()-1)? opt[Cli::Position::MIDMID] : opt[Cli::Position::RIGHTMID];
        }
    }
    return lineBottom;
}


int Cli::Table::getMaxWidth(int columnPos){

    int max = 0;
    auto tmpBody = m_body;
    // tmpBody.push_back( m_head );

    for(int i(0); i < tmpBody.size();++i){
        
        auto vecSplittedString = Cli::Utils::split( tmpBody[i][columnPos],'\n');
        
        for( const auto& str : vecSplittedString){

            if( str.size() > max){
                max = str.size();
            }
        }
        
    }
    return max;
}

int Cli::Table::getMaxHeight(int rowPos, bool isHead) {
    
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

int Cli::Table::countEndl(const std::string& str) const {

    int count = std::count_if( str.begin(),str.end(), [](char c){ return c == '\n';});
    return count ;
}


void Cli::Table::generate() {

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

                    Cli::Utils::pad(stringElem, stringElem.size()+2,' ',Cli::Direction::LEFT);
                    // The remaining length to reach the end of a cell character 
                    int remaining = std::abs( static_cast<int>( maxWidths.at(i) - stringElem.size() + 4) ); 
                    Cli::Utils::pad(stringElem, stringElem.size() + remaining ,' ',Cli::Direction::RIGHT);
                    tmpStr +=  (i==0) ? opt[Cli::Position::LEFT] + stringElem + opt[Cli::Position::RIGHT]
                                        : "" + stringElem + opt[Cli::Position::RIGHT];
                    ++i;
            }
            if(  rowMatrixToPrint.size() > 1){
                tmpStr += "\n";
            }

            i = 0; // Resetting to 0 for restarting the process 
          
        }
         *out = tmpStr;
         tmpStr.clear();
        // Before moving to the next matrix, we print the current one
        

        if( j != rowsList.size()-1){
            *out = drawBottomLine(false);
            drawTop = false;
            ++j;
        }else{
            drawTop = true;
        }
    }
    *out = drawBottomLine(true);
}

std::vector<RowMatrix> Cli::Table::processCells(){

    auto opt = this->getOpt().m_positionChars;
    RowMatrix rowMatrix;

    std::vector <RowMatrix> rowsList ; 

    for(int i(0); i < m_body.size(); ++i){

        for(int j(0); j < m_body[i].size(); ++j){

                std::string currentStr(m_body[i].at(j));

                int maxWidth = this->getMaxWidth(j); // For same columns 
                int maxHeight = this->getMaxHeight(i,false); // For same rows 

                int currentStrHeight = this->countEndl( currentStr );
                auto splittedString = Cli::Utils::split(currentStr,'\n');

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


auto Cli::Table::maxColumn(int column, RowMatrix& matrix) -> int {

     int max{0};

     for(int i(0); i < matrix.size();++i){
        int size = matrix.at(i).at(column).size();
        if(  size > max){
            max = size;
        }
    }

    return max;

}

auto Cli::Table::computeMaxWidths( std::vector<RowMatrix>& rowMatrix) -> std::vector<int>{
    
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

void Cli::Table::transpose(std::vector< std::vector<std::string> >& matrix ){

    std::vector< std::vector<std::string> > trans(matrix[0].size(),std::vector<std::string>());

    for(int i(0); i < matrix.size(); ++i){

        for(int j(0); j< matrix[i].size(); ++j){

            trans[j].push_back(matrix[i][j]);
        }
    }
    matrix = trans;
}