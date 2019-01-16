#ifndef EE_BASE_H
#define EE_BASE_H

#include <fstream>
#include <string>
#include <exzoki/system/ee_system_types.h>

class EE_BASE_C
{
	public:			
		virtual EE_BYTE_t Read( std::ifstream &rC_file ){}
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const	{}		
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const = 0;
		
		void SetComment( EE_CCSTRING_t ccs_comment, ... ) 
		{ 			
			va_list p_Argument;
 			EE_CHAR_t ac_OutputString[ 1024 ]; // 1024 ?
 
 			va_start( p_Argument, ccs_comment );
     		vsprintf( ac_OutputString, ccs_comment, p_Argument );
     		va_end( p_Argument ); 
    		
    		mS_Comment = ac_OutputString;
		}
		
		void SetComment( std::string S_comment ) { mS_Comment = S_comment; }
		
	protected:	
		std::string mS_Comment;
};

#endif
