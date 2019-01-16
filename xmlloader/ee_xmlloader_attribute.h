#ifndef E33_XMLLOADER_ATTRIBUTE_H
#define E33_XMLLOADER_ATTRIBUTE_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include <engine33/e33_error.h>
#include <engine33/xmlloader/e33_xmlloader_fces.h>

// T��da XML atributu
class EE_XMLLOADER_ATTRIBUTE_C
{
 	public:
		EE_XMLLOADER_ATTRIBUTE_C( void );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_CCSTRING_t ccs_stringValue );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_S32_t s32_numberValue );
		EE_XMLLOADER_ATTRIBUTE_C( EE_CCSTRING_t ccs_name, EE_FLOAT_t f_floatValue );
		
		// Na�te atribut ze souboru
  		inline EE_BOOL_t Load( std::ifstream& rC_file );
  		
  		// Zap�e atribut do souboru
  		inline EE_BOOL_t Write( std::ofstream& rC_file ) const;
  
  		// Nastaven� jm�na
  		void SetName( EE_CCSTRING_t ccs_name );
  		// Nastaven� hodnoty
  		void SetValue( EE_CCSTRING_t ccs_stringValue );
  		void SetValue( EE_S32_t s32_numberValue );
  		void SetValue( EE_FLOAT_t f_floatValue );
  
  		// Vr�t� jm�no
  		inline std::string GetName( void ) const;
  		
  		// Vr�t� hodnotu ve form�tu �et�zce
  		inline std::string GetString( void ) const;
  		// Vr�t� hodnotu ve form�tu cel�ho ��sla
  		inline EE_S32_t GetInt( void ) const;
  		// Vr�t� hodnotu ve form�tu desetinn�ho ��sla
  		inline EE_FLOAT_t GetFloat( void ) const;

 	private:
		// Jm�no atributu
  		std::string mS_Name;
  		// Hodnota
  		std::string mS_Value;
};

#endif
