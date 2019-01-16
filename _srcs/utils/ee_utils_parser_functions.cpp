#include <exzoki/utils/ee_utils_parser_functions.h>

std::vector< std::string > EE_EXZOKI_n::CutString( std::string S_src, EE_CHAR_t cc_divider )
{
    std::vector< std::string > co_Result;
    EE_U32_t u32_Position;
    while( ( u32_Position=S_src.find( cc_divider ) ) < S_src.size() )
    {
        co_Result.push_back( S_src.substr( 0, u32_Position ) );
        S_src = S_src.substr( u32_Position + 1, S_src.size() );    
    }
    
    if( S_src.size() && S_src != std::string( " " ) )
        co_Result.push_back( S_src ); 
        
    return( co_Result );        
}

