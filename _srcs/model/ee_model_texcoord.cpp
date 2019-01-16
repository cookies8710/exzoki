#include <exzoki/model/ee_model_texcoord.h>

EE_MODEL_TEXCOORD_C::EE_MODEL_TEXCOORD_C( void )
{
}

EE_MODEL_TEXCOORD_C::EE_MODEL_TEXCOORD_C( EE_FLOAT_t f_u, EE_FLOAT_t f_v )
{
	Set( f_u, f_v );	
}

		
void EE_MODEL_TEXCOORD_C::Set( EE_FLOAT_t f_u, EE_FLOAT_t f_v )
{
	mf_U = f_u;
	mf_V = f_v;	
	
	return;
}

void EE_MODEL_TEXCOORD_C::SetU( EE_FLOAT_t f_u )
{
	mf_U = f_u;
		
	return;
}

void EE_MODEL_TEXCOORD_C::SetV( EE_FLOAT_t f_v )
{
	mf_V = f_v;	
	
	return;
}

		
EE_FLOAT_t EE_MODEL_TEXCOORD_C::GetU( void ) const
{
	return( mf_U );	
}

EE_FLOAT_t EE_MODEL_TEXCOORD_C::GetV( void ) const
{
	return( mf_V );	
}
		
void EE_MODEL_TEXCOORD_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	rC_file.Read( &mf_U, sizeof( mf_U ) );	
	rC_file.Read( &mf_V, sizeof( mf_V ) );	
		
	return;
}
/*
void EE_MODEL_TEXCOORD_C::Write( EE_SYSTEM_FILE_C& rC_file ) const
{
	rC_file.Write( (EE_PVOID_t)&mf_U, sizeof( mf_U ) );	
	rC_file.Write( (EE_PVOID_t)&mf_V, sizeof( mf_V ) );	
		
	return;
}*/
