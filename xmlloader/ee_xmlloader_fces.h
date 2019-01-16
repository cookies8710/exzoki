#ifndef EE_XMLLOADER_FCES_H
#define EE_XMLLOADER_FCES_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <exzoki/error/ee_error.h>

namespace EE_EXZOKI_n
{
	const std::string cS_WhiteChars = " \n\t";
	const std::string cS_AlNum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
 
	EE_CHAR_t NextChar( std::ifstream& rh_file );
 	EE_BOOL_t SkipCharIf( std::ifstream& rh_file, EE_CHAR_t c );
 	void SkipWhiteChars( std::ifstream& rh_file ); 
 	std::string ReadText( std::ifstream& rh_file, const std::string cS_stopChars = cS_WhiteChars );
 	std::string ReadTextIf( std::ifstream& rh_file, const std::string cS_goodChars = cS_AlNum );
 	EE_FLOAT_t ReadFloat( std::ifstream& rh_file );
 	EE_S32_t ReadInt( std::ifstream& rh_file );
};

#endif
