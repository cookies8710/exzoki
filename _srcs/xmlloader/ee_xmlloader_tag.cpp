#include <exzoki/xmlloader/ee_xmlloader_tag.h>

EE_XMLLOADER_TAG_C::EE_XMLLOADER_TAG_C( void ): mb_ClosingTag( 0 ), mb_SingleTag( 0 )
{
}

EE_XMLLOADER_TAG_C::EE_XMLLOADER_TAG_C( EE_CCSTRING_t ccs_name ): mb_ClosingTag( 0 ), mb_SingleTag( 0 ), mS_Name( ccs_name )
{
}

void EE_XMLLOADER_TAG_C::Write( std::ofstream& rC_file )
{
	if( mb_ClosingTag && mb_SingleTag )
		EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Write", EE_ERROR_CODES_n::cS_BadOptions, "Tag cannot be closing and single same time\nTag name = %s", mS_Name.c_str() );
	
	// Otev�rac� z�vorka
	rC_file.put( '<' );
	// Lom�tko, pokud jde o uzav�rac� tag
	if( mb_ClosingTag )
		rC_file.put( '/' );
	// Jm�no tagu
	rC_file << mS_Name;
	// Pokud nejde o uzav�rac� tag, zap�u atributy
	if( !mb_ClosingTag )
	{
		std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C >::const_iterator cI_Attribute( mco_Parameters.begin() ), 
		                                                                  cI_AttributeEnd( mco_Parameters.end() );
		while( cI_Attribute != cI_AttributeEnd )
		{
			// Vlo��m b�l� znak	
			rC_file.put( ' ' );	
			// Zap�u atribut
			cI_Attribute++->second.Write( rC_file );			
		}
	}
	
	if( mb_SingleTag )
		rC_file.put( '/' );			
	
	// Uzav�rac� z�vorka
	rC_file.put( '>' );	
	
	if( !mb_ClosingTag && !mb_SingleTag )
		rC_file << mS_Data;
	
	rC_file << std::endl;
}

void EE_XMLLOADER_TAG_C::WriteClosing( std::ofstream& rC_file )
{
	EE_BOOL_t b_OldClosingFlag = mb_ClosingTag;
	SetClosingTagFlag( 1 );
	
	Write( rC_file );
	
	SetClosingTagFlag( b_OldClosingFlag );
}

void EE_XMLLOADER_TAG_C::SetName( EE_CCSTRING_t ccs_name )
{
	mS_Name = ccs_name;
}

void EE_XMLLOADER_TAG_C::SetClosingTagFlag( EE_BOOL_t b_closingTag )
{
	mb_ClosingTag = b_closingTag;	
}

void EE_XMLLOADER_TAG_C::SetSingleTagFlag( EE_BOOL_t b_singleTag )
{
	mb_SingleTag = b_singleTag;	
}

void EE_XMLLOADER_TAG_C::AddParameter( const EE_XMLLOADER_ATTRIBUTE_C &crC_attribute )
{
	mco_Parameters[ crC_attribute.GetName() ] = crC_attribute;
}

void EE_XMLLOADER_TAG_C::SetData( EE_CCSTRING_t ccs_data )
{
	mS_Data = ccs_data;	
}

void EE_XMLLOADER_TAG_C::Clear( void )
{
	mS_Name.clear();
	mS_Data.clear();
 
	mb_ClosingTag = 0;
	mb_SingleTag = 0;
 		
  	mco_Parameters.clear();
  	mco_ChildTags.clear(); 	
}

void EE_XMLLOADER_TAG_C::DeleteAttributes( void )
{
	mco_Parameters.clear();	
}


void EE_XMLLOADER_TAG_C::Load( std::ifstream& rC_file, EE_BOOL_t* pb_closing, const std::string& crS_name )
{
 	EE_BOOL_t b_DivideChar( false );
 	EE_XMLLOADER_ATTRIBUTE_C C_Parameter;
  
 	// P�esko��m b�l� znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 
 	// P�esko��m hodnoty elementu
 	EE_EXZOKI_n::ReadText( rC_file, std::string( "<" ) );
 	if( !EE_EXZOKI_n::SkipCharIf( rC_file, '<' ) )
  		EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged, "5" ); // Pokud dal�� znak nen� <, tak je to chyba
 
 	// P�esko��m b�l� znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 	// Pokud n�sleduje v�k�i�n�k a dv� poml�ky, je to koment��
 	if( EE_EXZOKI_n::SkipCharIf( rC_file, '!' ) )
 	{ 
  		if( EE_EXZOKI_n::SkipCharIf( rC_file, '-' ) )
  		{ 
   			if( EE_EXZOKI_n::SkipCharIf( rC_file, '-' ) )
   			{
    			EE_BOOL_t b_End( 0 );   
    			while( !b_End )
    			{
     				EE_EXZOKI_n::ReadText( rC_file, std::string( "-" ) );
     				EE_EXZOKI_n::SkipCharIf( rC_file, '-' );
     				if( EE_EXZOKI_n::SkipCharIf( rC_file, '-' ) )
      				if( EE_EXZOKI_n::SkipCharIf( rC_file, '>' ) )
       				b_End = 1;
    			}    
   			}
   			else  
    			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged, "1" );  
  		}
  		else
   			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged, "2" );  
  		
		return;
 	}
 	
	// Pokud n�sleduje otazn�k, je to �daj o verzi XML
 	if( EE_EXZOKI_n::SkipCharIf( rC_file, '?' ) )
 	{
  		EE_EXZOKI_n::SkipWhiteChars( rC_file );
  		std::string S_Name = EE_EXZOKI_n::ReadTextIf( rC_file );
  		if( S_Name != std::string( "xml" ) )
   			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged,"3" );
  		EE_XMLLOADER_ATTRIBUTE_C C_Version;
  		C_Version.Load( rC_file );
  		
		if( C_Version.GetName() != std::string( "version" ) ) 
   			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged,"4" );
  		
		if( C_Version.GetFloat() > 1.0f ) 
   			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_UnknownXmlVersion );
  
  		EE_EXZOKI_n::ReadText( rC_file, std::string( ">" ) );
  		EE_EXZOKI_n::SkipCharIf( rC_file, '>' );
  		
		return;
 	}
 
 	// Pokud n�sleduje lom�tko, je to uzav�rac� tag (bez parametr�)
 	if( EE_EXZOKI_n::SkipCharIf( rC_file, '/' ) )
 	{ 
  		if( pb_closing )
  		{
   			// Na�tu jm�no tagu
   			std::string S_Name = EE_EXZOKI_n::ReadTextIf( rC_file );
   			if( S_Name != crS_name )
    			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged,"6" ); // �patn� jm�no
   			else
   			{
    			*pb_closing = 1; 
    			return;
   			}
  		}
  		else
   			EE_ERROR_C( "EE_XMLLOADER_TAG_C", "Load", EE_ERROR_CODES_n::cS_FileIsDamaged,"7" ); // ��dn� tag nen� otev�en�
 	}
 
 	// Na�tu jm�no tagu
 	mS_Name = EE_EXZOKI_n::ReadTextIf( rC_file );
  
 	// P�esko��m b�l� znaky
 	EE_EXZOKI_n::SkipWhiteChars( rC_file );
 	// Dokud nenaraz�m na ukon�ovac� z�vorku, �tu parametry
 	while( !EE_EXZOKI_n::SkipCharIf( rC_file, '>' ) ) 
 	{
  		if( EE_EXZOKI_n::SkipCharIf( rC_file, '/' ) )
  		{
   			b_DivideChar = 1;
   			EE_EXZOKI_n::SkipWhiteChars( rC_file );
   			continue;
		}
  
  		if( C_Parameter.Load( rC_file ) )  
  		{
   			// je�t� kontrola, zda u� tam takov� parametr nen�
   			mco_Parameters[ C_Parameter.GetName() ] = C_Parameter;
  		}
    
  		// P�esko��m b�l� znaky
  		EE_EXZOKI_n::SkipWhiteChars( rC_file );
 	}
 
 	while( !b_DivideChar )
 	{
  		EE_XMLLOADER_TAG_C C_Tag;
  
  		C_Tag.Load( rC_file, &b_DivideChar, mS_Name );
  		if( !b_DivideChar )
   		mco_ChildTags[ C_Tag.mS_Name ].push_back( C_Tag ); 
 	}
 
 	return; 
} 

const std::string& EE_XMLLOADER_TAG_C::GetName( void ) const
{
 	return( mS_Name );
}

const std::map< std::string, std::vector< EE_XMLLOADER_TAG_C > >& EE_XMLLOADER_TAG_C::GetTags( void ) const
{
 	return( mco_ChildTags );
}

const std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C >& EE_XMLLOADER_TAG_C::GetParameters( void ) const
{
 	return( mco_Parameters );
}

const std::vector< EE_XMLLOADER_TAG_C >& EE_XMLLOADER_TAG_C::GetTags( std::string S_name ) const
{
 	std::map< std::string, std::vector< EE_XMLLOADER_TAG_C > >::const_iterator cI_Tag;
 
 	if( ( cI_Tag = mco_ChildTags.find( S_name ) ) != mco_ChildTags.end() )
  		return( cI_Tag->second );
 	else 
  		EE_ERROR_C( "EE_XMLLOADER_TAG_C", "GetTags", EE_ERROR_CODES_n::cS_TagsDontExist, S_name.c_str() ); 
}

const EE_XMLLOADER_ATTRIBUTE_C& EE_XMLLOADER_TAG_C::GetParameter( std::string S_name ) const
{
 	std::map< std::string, EE_XMLLOADER_ATTRIBUTE_C >::const_iterator cI_Parameter;
 
 	if( ( cI_Parameter = mco_Parameters.find( S_name ) ) != mco_Parameters.end() )
  		return( cI_Parameter->second );
  	else  	
		EE_ERROR_C( "EE_XMLLOADER_TAG_C", "GetParameter", EE_ERROR_CODES_n::cS_ParameterDoesntExist, S_name.c_str() );   
}

