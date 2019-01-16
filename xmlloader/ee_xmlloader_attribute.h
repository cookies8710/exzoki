#ifndef E33_XMLLOADER_ATTRIBUTE_H
#define E33_XMLLOADER_ATTRIBUTE_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include <engine33/e33_error.h>
#include <engine33/xmlloader/e33_xmlloader_fces.h>

// Tøída XML atributu
class EE_XMLLOADER_ATTRIBUTE_C
{
 	public:
		EE_XMLLOADER_ATTRIBUTE_C( void );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_CCSTRING_t ccs_stringValue );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_S32_t s32_numberValue );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_FLOAT_t f_floatValue );
		
		// Naète atribut ze souboru
  		inline EE_BOOL_t Load( std::ifstream& rC_file );
  		
  		// Zapíše atribut do souboru
  		inline EE_BOOL_t Write( std::ofstream& rC_file ) const;
  
  		// Nastavení jména
  		void SetName( EE_CCSTRING_t ccs_name );
  		// Nastavení hodnoty
  		void SetValue( EE_CCSTRING_t ccs_stringValue );
  		void SetValue( EE_S32_t s32_numberValue );
  		void SetValue( EE_FLOAT_t f_floatValue );
  
  		// Vrátí jméno
  		inline std::string GetName( void ) const;
  		
  		// Vrátí hodnotu ve formátu øetìzce
  		inline std::string GetString( void ) const;
  		// Vrátí hodnotu ve formátu celého èísla
  		inline EE_S32_t GetInt( void ) const;
  		// Vrátí hodnotu ve formátu desetinného èísla
  		inline EE_FLOAT_t GetFloat( void ) const;

 	private:
		// Jméno atributu
  		std::string mS_Name;
  		// Hodnota
  		std::string mS_Value;
};

#endif
