#include <exzoki/model/ee_model_vertex.h>

EE_MODEL_VERTEX_C::EE_MODEL_VERTEX_C( void )
{
}

EE_MODEL_VERTEX_C::EE_MODEL_VERTEX_C( EE_FLOAT_t f_x, EE_FLOAT_t f_y, EE_FLOAT_t f_z ): mf_X( f_x ),
                                                                                        mf_Y( f_y ),
                                                                                        mf_Z( f_z )
{
}
		
void EE_MODEL_VERTEX_C::Set( EE_FLOAT_t f_x, EE_FLOAT_t f_y, EE_FLOAT_t f_z )
{
	mf_X = f_x;
	mf_Y = f_y;
	mf_Z = f_z;
}

EE_MATH_POINT_C EE_MODEL_VERTEX_C::GetPosition( void ) const
{
	return( EE_MATH_POINT_C( mf_X, mf_Y, mf_Z ) );
}

EE_FLOAT_t EE_MODEL_VERTEX_C::GetX( void ) const
{
	return( mf_X );	
}

EE_FLOAT_t EE_MODEL_VERTEX_C::GetY( void ) const
{
	return( mf_Y );	
}

EE_FLOAT_t EE_MODEL_VERTEX_C::GetZ( void ) const
{
	return( mf_Z );	
}
		
void EE_MODEL_VERTEX_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	rC_file.Read( &mf_X, sizeof( mf_X ) );	
	rC_file.Read( &mf_Y, sizeof( mf_Y ) );	
	rC_file.Read( &mf_Z, sizeof( mf_Z ) );
}
/*
void EE_MODEL_VERTEX_C::Write( EE_SYSTEM_FILE_C& rC_file ) const
{
	rC_file.Write( (EE_PVOID_t)&mf_X, sizeof( mf_X ) );	
	rC_file.Write( (EE_PVOID_t)&mf_Y, sizeof( mf_Y ) );	
	rC_file.Write( (EE_PVOID_t)&mf_Z, sizeof( mf_Z ) );
}*/

