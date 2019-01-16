#include <exzoki/xmlloader/ee_xmlloader_fces.h>

EE_CHAR_t EE_EXZOKI_n::NextChar( std::ifstream& rh_file )
{
 	EE_CHAR_t c;
 
	c = rh_file.get();
 	rh_file.unget();
 	return( c );
}

EE_BOOL_t EE_EXZOKI_n::SkipCharIf( std::ifstream& rh_file, EE_CHAR_t c )
{
 	if( EE_EXZOKI_n::NextChar( rh_file ) == c )
  		rh_file.get();
	else
  		return( 0 );
 	
	 return( 1 );
}

void EE_EXZOKI_n::SkipWhiteChars( std::ifstream& rh_file )
{
 	while( find( cS_WhiteChars.begin(), 
              	 cS_WhiteChars.end(), 
              	 EE_EXZOKI_n::NextChar( rh_file ) ) != cS_WhiteChars.end() )
  	
	rh_file.get();
 	
	return;
}
 
std::string EE_EXZOKI_n::ReadText( std::ifstream& rh_file, 
                                   const std::string cS_stopChars )
{
 	EE_CHAR_t *pc_Text = new EE_CHAR_t[ 256 ];
 	EE_U32_t u32_Memory = 256;
 	EE_U32_t u32_Counter = 0;
 
	while( find( cS_stopChars.begin(), 
              	 cS_stopChars.end(), 
              	 EE_EXZOKI_n::NextChar( rh_file ) ) == cS_stopChars.end() )
 	{
		if( u32_Counter >= u32_Memory )
		{
			EE_CHAR_t* pc_Temp;
			pc_Temp = new EE_CHAR_t[ u32_Memory *= 2 ];
			memcpy( pc_Temp, pc_Text, u32_Memory );
			delete[] pc_Text;
		   	pc_Text = pc_Temp;
		}
		pc_Text[ u32_Counter++ ] = rh_file.get();
	}
 
	if( u32_Counter >= u32_Memory )
	{
		EE_CHAR_t* pc_Temp;
		pc_Temp = new EE_CHAR_t[ u32_Memory *= 2 ];
		memcpy( pc_Temp, pc_Text, u32_Memory );
		delete[] pc_Text;
		pc_Text = pc_Temp;
	}
 	
	 pc_Text[ u32_Counter ] = '\0';
 
 	return( std::string( pc_Text ) );
}

std::string EE_EXZOKI_n::ReadTextIf( std::ifstream& rh_file, const std::string cS_goodChars )
{
 	EE_CHAR_t *pc_Text = new EE_CHAR_t[ 256 ];
 	EE_U32_t u32_Memory = 256;
 	EE_U32_t u32_Counter = 0;
 
 	while( find( cS_goodChars.begin(), 
              	 cS_goodChars.end(), 
              	 EE_EXZOKI_n::NextChar( rh_file ) ) != cS_goodChars.end() )
 	{
  		if( u32_Counter >= u32_Memory )
  		{
   			EE_CHAR_t* pc_Temp;
	   		pc_Temp = new EE_CHAR_t[ u32_Memory *= 2 ];
	   		memcpy( pc_Temp, pc_Text, u32_Memory );
	   		delete[] pc_Text;
	   		pc_Text = pc_Temp;
  		}
  		pc_Text[ u32_Counter++ ] = rh_file.get();
 	}
 
 	if( u32_Counter >= u32_Memory )
 	{
  		EE_CHAR_t* pc_Temp;
  		pc_Temp = new EE_CHAR_t[ u32_Memory *= 2 ];
  		memcpy( pc_Temp, pc_Text, u32_Memory );
  		delete[] pc_Text;
  		pc_Text = pc_Temp;
 	}
 	
	pc_Text[ u32_Counter ] = '\0';
 
 	return( std::string( pc_Text ) );
}

EE_FLOAT_t EE_EXZOKI_n::ReadFloat( std::ifstream& rh_file )
{
	EE_FLOAT_t f_Output;
 
 	rh_file >> f_Output;
 
 	return( f_Output );
}

EE_S32_t EE_EXZOKI_n::ReadInt( std::ifstream& rh_file )
{
 	EE_S32_t s32_Output;
 
 	rh_file >> s32_Output;
 
 	return( s32_Output );
}

