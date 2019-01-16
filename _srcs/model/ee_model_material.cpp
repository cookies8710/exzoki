#include <exzoki/model/ee_model_material.h>

EE_MODEL_MATERIAL_C::EE_MODEL_MATERIAL_C( void ): mb_HasTexture( false )
{
	for( EE_U32_t u32_ColorIndex( 0 ); u32_ColorIndex < 3; u32_ColorIndex++ )
  		mab_Color[ u32_ColorIndex ] = 0;   
}

EE_MODEL_MATERIAL_C::EE_MODEL_MATERIAL_C( const EE_MODEL_MATERIAL_C& crC_material )
{
 	for( EE_U32_t u32_ColorIndex( 0 ); u32_ColorIndex < 3; u32_ColorIndex++ )
  		this->mab_Color[ u32_ColorIndex ] = crC_material.mab_Color[ u32_ColorIndex ];
 	this->mb_HasTexture = crC_material.mb_HasTexture;
 	this->mS_TexturePath = crC_material.mS_TexturePath;   
}

EE_MODEL_MATERIAL_C& EE_MODEL_MATERIAL_C::operator=( const EE_MODEL_MATERIAL_C& crC_material )
{
 	if( &crC_material != this )
 	{
  		for( EE_U32_t u32_ColorIndex( 0 ); u32_ColorIndex < 3; u32_ColorIndex++ )
   		this->mab_Color[ u32_ColorIndex ] = crC_material.mab_Color[ u32_ColorIndex ];
  		this->mb_HasTexture = crC_material.mb_HasTexture;
  		this->mS_TexturePath = crC_material.mS_TexturePath;      
 	}
 	return( *this );    
}
 
void EE_MODEL_MATERIAL_C::SetColor( EE_BYTE_t b_r, EE_BYTE_t b_g, EE_BYTE_t b_b )
{
 	mab_Color[ 0 ] = b_r;    
 	mab_Color[ 1 ] = b_g;    
 	mab_Color[ 2 ] = b_b;    
}

void EE_MODEL_MATERIAL_C::SetColor( EE_BYTE_t ab_color[ 3 ] )
{
 	for( EE_U32_t u32_ColorIndex( 0 ); u32_ColorIndex < 3; u32_ColorIndex++ )
  		mab_Color[ u32_ColorIndex ] = ab_color[ u32_ColorIndex ];   
}

void EE_MODEL_MATERIAL_C::SetTexture( EE_CCSTRING_t cpc_texturePath )
{
 	SetTexture( std::string( cpc_texturePath ) );    
}

void EE_MODEL_MATERIAL_C::SetTexture( const std::string& crS_texturePath )
{
 	mb_HasTexture = true;
 	mS_TexturePath = crS_texturePath;
}
 
EE_BYTE_t EE_MODEL_MATERIAL_C::GetColor( EE_U32_t u32_index ) const
{
 	if( u32_index < 3 )
  		return( mab_Color[ u32_index ] );
 	else
		EE_ERROR_C( "EE_MODEL_MATERIAL_C", "GetColor", EE_ERROR_CODES_n::cS_BadIndex );  
}

EE_BYTE_t EE_MODEL_MATERIAL_C::HasTexture( void ) const
{
 	return( mb_HasTexture );    
}

EE_CCSTRING_t EE_MODEL_MATERIAL_C::GetTexture( void ) const
{
 	if( mb_HasTexture )
  		return( mS_TexturePath.c_str() );
 	else
  		EE_ERROR_C( "EE_MODEL_MATERIAL_C", "GetTexture", EE_ERROR_CODES_n::cS_MaterialHasNotTexture );  
}
/*
inline void EE_MODEL_MATERIAL_C::Write( EE_SYSTEM_FILE_C& rC_file ) const
{
 	rC_file.Write( (EE_PVOID_t)&mab_Color[ 0 ], sizeof( mab_Color[ 0 ] ) );   
 	rC_file.Write( (EE_PVOID_t)&mab_Color[ 1 ], sizeof( mab_Color[ 1 ] ) );   
 	rC_file.Write( (EE_PVOID_t)&mab_Color[ 2 ], sizeof( mab_Color[ 2 ] ) );
 
 	if( mS_TexturePath.size() > 255 )
  		EE_ERROR_C( "EE_MODEL_MATERIAL_C", "Write", EE_ERROR_CODES_n::cS_TextureNameIsTooLong, mS_TexturePath.c_str() );  
 	EE_BYTE_t b_Size( mS_TexturePath.size() );
 	rC_file.Write( (EE_PVOID_t)&b_Size, sizeof( b_Size ) );

 	rC_file.Write( (EE_PVOID_t)mS_TexturePath.data(), b_Size );
 
 	return;      
}
*/
inline void EE_MODEL_MATERIAL_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
 	rC_file.Read( &mab_Color[ 0 ], sizeof( mab_Color[ 0 ] ) );  
 	rC_file.Read( &mab_Color[ 1 ], sizeof( mab_Color[ 1 ] ) );     
 	rC_file.Read( &mab_Color[ 2 ], sizeof( mab_Color[ 2 ] ) ); 
  
 	EE_BYTE_t b_Size;
 	rC_file.Read( &b_Size, sizeof( b_Size ) );

 	if( b_Size == 0 )
  		mb_HasTexture = false;
 	else 
 	{
  		mb_HasTexture = true;
  
  		char ac_Buffer[ b_Size + 1 ];   
  
  		rC_file.Read( ac_Buffer, b_Size ); 
  		ac_Buffer[ b_Size ] = '\0';
  		mS_TexturePath = ac_Buffer;
 	}
 
 	return; 
}    
