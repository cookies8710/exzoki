#ifndef EE_MATH_QUATERNION_H
#define EE_MATH_QUATERNION_H

#include <exzoki/base/ee_base.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>
#include <exzoki/math/ee_math_vector.h>
#include <exzoki/math/ee_math_matrix4x4.h>

class EE_MATH_QUATERNION_C: public EE_BASE_C
{
	public:
		EE_MATH_QUATERNION_C( void );
		
	
  		EE_MATH_QUATERNION_C operator+( const EE_MATH_QUATERNION_C& crC_quaternion ) const;  	
  		EE_MATH_QUATERNION_C operator-( const EE_MATH_QUATERNION_C& crC_quaternion ) const;
  		EE_MATH_QUATERNION_C operator*( const EE_MATH_QUATERNION_C& crC_quaternion ) const;
  	//	EE_MATH_QUATERNION_C operator/( const EE_MATH_QUATERNION_C& crC_quaternion ) const;
  		EE_MATH_QUATERNION_C operator/( EE_MATH_TYPE_t t_number ) const;
  		
		void LoadMulIdentity( void ); 
		void LoadAddIdentity( void ); 
		    			
  		EE_MATH_TYPE_t GetMagnitude( void ) const;
  		void Normalize( void );
  		void Conjugate( void );
	//	void Inverse( void );
		
		EE_MATH_MATRIX4X4_C ConvertToMatrix( void ) const;
		
		void Read( EE_SYSTEM_FILE_C& rC_file );
		
		virtual EE_BYTE_t Read( std::ifstream &rC_file );
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const;
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;
	private:
		EE_MATH_VECTOR_C mC_Vector;
		EE_MATH_TYPE_t mt_W;	
};

#endif
