#ifndef EE_XMLLOADERC_H
#define EE_XMLLOADERC_H

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <exzoki/error/ee_error.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>

struct EE_XMLLOADER_TAGCOMPLEX_s
{
 	EE_XMLLOADER_TAGCOMPLEX_s::EE_XMLLOADER_TAGCOMPLEX_s(): b_HasAttribute( 0 )
 	{
 	}

 	EE_XMLLOADER_TAGCOMPLEX_s( const std::string& crS_name ): S_TagName( crS_name ), b_HasAttribute( 0 )
 	{
 	}
 
 	std::string S_TagName;
 	EE_BOOL_t b_HasAttribute;
 	EE_XMLLOADER_ATTRIBUTE_C C_Attribute;
};

class EE_XMLLOADER_C
{
 	public:
  		EE_XMLLOADER_C( void );
 
  		void Load( EE_CCSTRING_t ccs_path );
  		const EE_XMLLOADER_ATTRIBUTE_C& GetParameter( EE_CCSTRING_t ccs_path ) const;
  		const EE_XMLLOADER_TAG_C& GetRootTag( void ) const;
 	
	private:
  		EE_XMLLOADER_TAG_C mC_RootTag;
  		EE_BOOL_t mb_Loaded; 
};

#endif
