
#include <string>
#include <vector>
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
        
        int maxWidth = this->getMaxWidth(i);
        //std::cout << "The max width of col " << i << " is " << maxWidth << "\n";
        
        std::string currentStr(m_head.at(i));

        Cli::Utils::pad(currentStr, currentStr.size() + 5,' ',Cli::Direction::LEFT);
        
        // The +2 here is because we want to have a little space after the longest line is written
        // We are constraint to always pass currentStr.size() + len due to the implementation of pad function
        // Will refactor that?
    
        int remaining =  std::abs( static_cast<int>( maxWidth - currentStr.size() + 2 ) );
        
        int lineEndPosition = (remaining==0) ? maxWidth + 4 : maxWidth+2 ; 

        Cli::Utils::pad(currentStr,currentStr.size() + remaining,' ',Cli::Direction::RIGHT);

        currentStr =  (i==0) ? opt[Cli::Position::LEFT] + currentStr + opt[Cli::Position::RIGHT]
                             : "" + currentStr + opt[Cli::Position::RIGHT];

        lineTop += Cli::Utils::repeats(opt[Cli::Position::TOP], lineEndPosition );
        
        // When we are at the corner we put the TOPRIGHT char else we put the TOPMID
        
        lineTop += (i!=m_head.size()-1)? opt[Cli::Position::TOPMID]: opt[Cli::Position::TOPRIGHT];

    }

    return lineTop;
}


std::string Cli::Table::drawBottomLine(bool isLast){
    auto opt = this->getOpt().m_positionChars;
       
    std::string lineBottom = [&](){ return (isLast)? opt[Cli::Position::BOTTOMLEFT]: opt[Cli::Position::LEFTMID]; }();
            
    for(int i(0); i < m_head.size(); ++i){
        
        int maxWidth = this->getMaxWidth(i); 
        std::string currentStr(m_head.at(i));

        Cli::Utils::pad(currentStr, currentStr.size() + 5,' ',Cli::Direction::LEFT);

        int remaining =  std::abs( static_cast<int>( maxWidth - currentStr.size()+2 ) );
        
        int lineEndPosition = (remaining==0) ? maxWidth + 4 : maxWidth+2 ; 

        if( isLast){
            currentStr =  (i == 0) ? opt[Cli::Position::LEFT] + currentStr + opt[Cli::Position::RIGHT]
                                : " " + currentStr + opt[Cli::Position::RIGHT];

            lineBottom += Cli::Utils::repeats(opt[Cli::Position::BOTTOM],lineEndPosition);

            lineBottom += (i!=m_head.size()-1)? opt[Cli::Position::BOTTOMMID] : opt[Cli::Position::BOTTOMRIGHT];
        }else{
             
            currentStr =  (i == 0) ? opt[Cli::Position::LEFTMID] + currentStr + opt[Cli::Position::RIGHTMID]
                                : " " + currentStr + opt[Cli::Position::RIGHTMID];
                                
            lineBottom += Cli::Utils::repeats(opt[Cli::Position::BOTTOM],lineEndPosition);

            lineBottom += (i!=m_head.size()-1)? opt[Cli::Position::MIDMID] : opt[Cli::Position::RIGHTMID];
        }
    }
    return lineBottom;
}


int Cli::Table::getMaxWidth(int columnPos){
    int max = m_head.at(columnPos).size();

    for(int i(0); i < m_body.size();++i){
        
        if( m_body[i][columnPos].size() > max){
            max = m_body[i][columnPos].size();
        }
    }
    return max;
}


void Cli::Table::generate() {

    auto opt = this->getOpt().m_positionChars;

    std::ostream_iterator<std::string> out(std::cout,"\n");   
    std::string res ;

    for(int i(0); i < m_head.size(); ++i){

        std::string currentStr(m_head.at(i));
        int maxWidth = this->getMaxWidth(i);

        Cli::Utils::pad(currentStr, currentStr.size()+2,' ',Cli::Direction::LEFT);

        // The remaining length to reach the end of a cell caracter 

        int remaining = std::abs( static_cast<int>( maxWidth - currentStr.size() + 2) ); 
 
        Cli::Utils::pad(currentStr, currentStr.size() + remaining ,' ',Cli::Direction::RIGHT);

        currentStr =  (i==0) ? opt[Cli::Position::LEFT] + currentStr + opt[Cli::Position::RIGHT]
                             : "" + currentStr + opt[Cli::Position::RIGHT];

        res+=currentStr;
    }

    res+="\n";
    res+= drawBottomLine(false);
    res+= "\n";

    for(int i(0); i < m_body.size(); ++i){

        for( int j(0); j < m_body[0].size(); ++j){

            int maxWidth = this->getMaxWidth(j);

            std::string currentStr(m_body[i][j]);  

            Cli::Utils::pad(currentStr, currentStr.size() + 2,' ',Cli::Direction::LEFT);

            int remaining = std::abs( static_cast<int>( maxWidth - currentStr.size() + 2) ); 

            Cli::Utils::pad(currentStr, currentStr.size() + remaining ,' ',Cli::Direction::RIGHT);

            if( j == 0 ){
                currentStr =  opt[Cli::Position::LEFT] + currentStr + opt[Cli::Position::RIGHT];
            }else{
                currentStr =  currentStr + opt[Cli::Position::RIGHT];
            }

            res+= currentStr;    

        }

            if( i != m_body.size()-1 ) {
                 res+="\n";
                 res+= drawBottomLine(false);
                 res+="\n";
            }

    }

     *out = drawTopLine();
     *out = res;
     *out = drawBottomLine(true);
     //*out = lineBottom;

}
