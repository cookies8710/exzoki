#include <exzoki/xmlloader/ee_xmlloader.h>

EE_XMLLOADER_C::EE_XMLLOADER_C( void ): mb_Loaded( 0 )
{
}

void EE_XMLLOADER_C::Load( EE_CCSTRING_t ccs_path )
{
 	std::ifstream C_File;
 
 	C_File.open( ccs_path );
 	if( !C_File.good() )
  		EE_ERROR_C( "EE_XMLLOADER_C", "Load", EE_ERROR_CODES_n::cS_FileNotFound, ccs_path ); 
 
 	EE_XMLLOADER_TAG_C C_Version;
 	C_Version.Load( C_File, NULL, "" );
 
 	mC_RootTag.Load( C_File, NULL, "" );
 	mb_Loaded = 1;
 
 	C_File.close();  
}

const EE_XMLLOADER_ATTRIBUTE_C& EE_XMLLOADER_C::GetParameter( EE_CCSTRING_t ccs_path ) const
{
 	std::string S_Path( ccs_path ), S_Work;
 	std::string::iterator I_Char;
 	std::string::const_iterator cI_End;
 
 	std::vector< EE_XMLLOADER_TAGCOMPLEX_s > co_Tags;
 	std::string S_ParamName;
 	
	 // Rozdìlení na tagy a parametr
 	I_Char = S_Path.begin();
 	cI_End = S_Path.end();
 	while( I_Char != cI_End )
 	{
  		if( *I_Char == '.' )
  		{
   			co_Tags.push_back( EE_XMLLOADER_TAGCOMPLEX_s( S_Work ) );
   			S_Work.clear();
  		} 
  		else
   			S_Work += *I_Char;
  		I_Char++;
 	}
 	
	co_Tags.push_back( EE_XMLLOADER_TAGCOMPLEX_s( S_Work ) );

 	S_ParamName = co_Tags[ co_Tags.size() - 1 ].S_TagName;
 	co_Tags.pop_back();
 
 	// Vyhledání tagu
 	const EE_XMLLOADER_TAG_C* cpC_Tag( &mC_RootTag );
 	EE_U32_t u32_NTags( co_Tags.size() );
 	for( EE_U32_t u32_Tag( 0 ); u32_Tag < u32_NTags; u32_Tag++ )
 	{
  		std::map< std::string, std::vector< EE_XMLLOADER_TAG_C > >::const_iterator cI_Tag, cI_End;
  		cI_Tag = cpC_Tag->GetTags().begin();
  		cI_End = cpC_Tag->GetTags().end();
  		while( cI_Tag != cI_End )
  		{
   			if( cI_Tag->first == co_Tags[ u32_Tag ].S_TagName )
    			cpC_Tag = &cI_Tag->second[ 0 ];
   			cI_Tag++;
  		}
 	}
 
 	// Vyhledání parametru
 	std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C >::const_iterator cI_Param, cI_PEnd;
 	cI_Param = cpC_Tag->GetParameters().begin();
 	cI_PEnd = cpC_Tag->GetParameters().end();
 	while( cI_Param != cI_PEnd )
 	{
  		if( cI_Param->first == S_ParamName )
   			return( cI_Param->second );
  		cI_Param++;
 	}
 	
 	EE_ERROR_C( "EE_XMLLOADER_C", "GetParameter", EE_ERROR_CODES_n::cS_ParameterNotFound, S_ParamName.c_str() );
}

const EE_XMLLOADER_TAG_C& EE_XMLLOADER_C::GetRootTag( void ) const
{
 	return( mC_RootTag ); 
}
