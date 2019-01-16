#include <exzoki/xmlloader/ee_xmlloader_attribute.h>

EE_XMLLOADER_ATTRIBUTE_C::EE_XMLLOADER_ATTRIBUTE_C( void )
{
}

EE_XMLLOADER_ATTRIBUTE_C::EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_CCSTRING_t ccs_stringValue ): mS_Name( ccs_name )
{
	SetValue( ccs_stringValue );
}

EE_XMLLOADER_ATTRIBUTE_C::EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_S32_t s32_numberValue ): mS_Name( ccs_name )
{
	SetValue( s32_numberValue );
}

EE_XMLLOADER_ATTRIBUTE_C::EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_FLOAT_t f_floatValue ): mS_Name( ccs_name )
{
	SetValue( f_floatValue );
}

inline EE_BOOL_t EE_XMLLOADER_ATTRIBUTE_C::Load( std::ifstream& rC_file )
{
 	// Pøeskoèím bílé znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 
 	if( find( EE_EXZOKI_n::cS_AlNum.begin(),
          	  EE_EXZOKI_n::cS_AlNum.end(), 
          	  EE_EXZOKI_n::NextChar( rC_file ) ) == EE_EXZOKI_n::cS_AlNum.end() )
  		return( 0 );  
 
 	// Naètu jméno atributu
	mS_Name = EE_EXZOKI_n::ReadTextIf( rC_file );
 	// Pøeskoèím bílé znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 
  	// Pokud nenásleduje znak =, soubor je poškozen 
 	if( !EE_EXZOKI_n::SkipCharIf( rC_file, '=' ) )
  		EE_ERROR_C( "EE_XMLLOADER_ATTRIBUTE_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged );
 	// Pøeskoèím bílé znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 
 	// Pokud nenásleduje znak ", soubor je poškozen 
 	if( !EE_EXZOKI_n::SkipCharIf( rC_file, '"' ) )
  		EE_ERROR_C( "EE_XMLLOADER_ATTRIBUTE_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged ); 
 
 	// Naètu celý obsah atributu
 	mS_Value = EE_EXZOKI_n::ReadText( rC_file, std::string( "\"" ) );
 
 	// Pokud nenásleduje znak ", soubor je poškozen 
 	if( !EE_EXZOKI_n::SkipCharIf( rC_file, '"' ) )
  		EE_ERROR_C( "EE_XMLLOADER_ATTRIBUTE_C", "Load()", EE_ERROR_CODES_n::cS_FileIsDamaged ); 
               
 	return( 1 );
}

inline EE_BOOL_t EE_XMLLOADER_ATTRIBUTE_C::Write( std::ofstream& rC_file ) const
{
	// Zapíšu jméno atributu
	rC_file << mS_Name;
	
	// Zapíšu znak '='
	rC_file << "=";
	
	// Zapíšu hodnotu atributu mezi dvojité uvozovky
	rC_file << "\"" << mS_Value << "\"";
	
	// Vynutím si zápis do souboru
	rC_file.flush();
	
	return( 1 );
}

void EE_XMLLOADER_ATTRIBUTE_C::SetName( EE_CCSTRING_t ccs_name )
{
	mS_Name = ccs_name;
}

void EE_XMLLOADER_ATTRIBUTE_C::SetValue( EE_CCSTRING_t ccs_stringValue )
{
	mS_Value = ccs_stringValue;
}

void EE_XMLLOADER_ATTRIBUTE_C::SetValue( EE_S32_t s32_numberValue )
{
	EE_CHAR_t ac_Buffer[ 32 ];
	
	mS_Value = itoa( s32_numberValue, ac_Buffer, 10 );	
}

void EE_XMLLOADER_ATTRIBUTE_C::SetValue( EE_FLOAT_t f_floatValue )
{
	EE_CHAR_t ac_Buffer[ 32 ];
	
	sprintf( ac_Buffer, "%.6g", f_floatValue );
	
	mS_Value = ac_Buffer;	
}

inline std::string EE_XMLLOADER_ATTRIBUTE_C::GetName( void ) const
{
 	return( mS_Name );
}
  
inline std::string EE_XMLLOADER_ATTRIBUTE_C::GetString( void ) const
{
 	return( mS_Value );
}

inline EE_S32_t EE_XMLLOADER_ATTRIBUTE_C::GetInt( void ) const
{
 	return( atoi( mS_Value.c_str() ) );
}

inline EE_FLOAT_t EE_XMLLOADER_ATTRIBUTE_C::GetFloat( void ) const
{
 	return( atof( mS_Value.c_str() ) );
}

