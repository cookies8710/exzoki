#ifndef EE_XMLLOADER_TAG_H
#define EE_XMLLOADER_TAG_H

#include <string>
#include <vector>
#include <map> 
#include <fstream>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_fces.h>

class EE_XMLLOADER_TAG_C
{	
 	public:
		EE_XMLLOADER_TAG_C( void );
		EE_XMLLOADER_TAG_C( EE_CCSTRING_t ccs_name );
		
		void Write( std::ofstream& rC_file );
		void WriteClosing( std::ofstream& rC_file );
		void SetName( EE_CCSTRING_t ccs_name );
		void SetClosingTagFlag( EE_BOOL_t b_closingTag );
		void SetSingleTagFlag( EE_BOOL_t b_singleTag );
		void AddParameter( const EE_XMLLOADER_ATTRIBUTE_C &crC_attribute );
		void SetData( EE_CCSTRING_t ccs_data );
		void Clear( void );
		void DeleteAttributes( void );
		
		// Naète tag ze souboru
  		void Load( std::ifstream& rC_file, EE_BOOL_t* pb_closing, const std::string& crS_name );
  		
  		// Vrací jméno tagu
  		const std::string& GetName( void ) const;
  		// Vrací dceøinné tagy
  		const std::map< std::string, std::vector< EE_XMLLOADER_TAG_C > >& GetTags( void ) const;
  		// Vrací parametry tagu
  		const std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C >& GetParameters( void ) const;
 
 		
  		const std::vector< EE_XMLLOADER_TAG_C >& GetTags( std::string S_name ) const;
  		const EE_XMLLOADER_ATTRIBUTE_C& GetParameter( std::string S_name ) const;
 	private:
  		std::string mS_Name;
  		std::string mS_Data;
 
 		EE_BOOL_t mb_ClosingTag;
 		EE_BOOL_t mb_SingleTag;
 		
  		std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C > mco_Parameters;
  		std::map< std::string, std::vector< EE_XMLLOADER_TAG_C > > mco_ChildTags; 
};

#endif
