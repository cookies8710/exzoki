#ifndef EE_MATH_MATRIX4X4_H
#define EE_MATH_MATRIX4X4_H

#include <exzoki/system/ee_system_file.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/base/ee_base.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>

class EE_MATH_MATRIX4X4_C: public EE_BASE_C
{
	public:
		// Konstruktory, destruktor, pøetížený pøiøazovací operátor
		EE_MATH_MATRIX4X4_C( void );
		~EE_MATH_MATRIX4X4_C( void );
		
		EE_MATH_MATRIX4X4_C( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 );
		EE_MATH_MATRIX4X4_C& operator=( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 );
		EE_MATH_MATRIX4X4_C& operator=( const EE_FLOAT_t *cpf_matrix4x4 );
				
		// Matematické operace: sèítání, odèítání, násobení matic, násobení èíslem
		EE_MATH_MATRIX4X4_C operator+( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const;
		EE_MATH_MATRIX4X4_C operator-( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const;
		EE_MATH_MATRIX4X4_C operator*( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const;
		EE_MATH_MATRIX4X4_C operator*( EE_MATH_TYPE_t t_number ) const;
		
		EE_MATH_VECTOR_C operator*( const EE_MATH_VECTOR_C &crC_vector ) const;
		
		// Inverzní matice
		void Inverse( void );
		EE_MATH_MATRIX4X4_C GetInverse( void ) const;
		
		// Nahraje identity matici
		void LoadIdentity( void );
		
		// Translace, skalace, rotace
		void Translate( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
		void Scale( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
		void RotateX( EE_MATH_TYPE_t t_theta );
		void RotateY( EE_MATH_TYPE_t t_theta );
		void RotateZ( EE_MATH_TYPE_t t_theta );
		
		void Set( EE_BYTE_t b_row, EE_BYTE_t b_column, EE_MATH_TYPE_t t_value );
		
		EE_MATH_TYPE_t Get( EE_BYTE_t b_row, EE_BYTE_t b_column ) const;
		const EE_MATH_TYPE_t* GetMatrix( void ) const;
		
		static EE_MATH_MATRIX4X4_C TranslationMatrix( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  );
		static EE_MATH_MATRIX4X4_C ScalationMatrix( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  );
		static EE_MATH_MATRIX4X4_C RotationXMatrix( EE_MATH_TYPE_t t_theta );
		static EE_MATH_MATRIX4X4_C RotationYMatrix( EE_MATH_TYPE_t t_theta );
		static EE_MATH_MATRIX4X4_C RotationZMatrix( EE_MATH_TYPE_t t_theta );
		
		void Read( EE_SYSTEM_FILE_C& rC_file );
		
		virtual EE_BYTE_t Read( std::ifstream &rC_file );
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const;
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;
		
	private:
		void Build( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 );
		void Build( const EE_FLOAT_t *cpf_matrix4x4 );
		
		EE_FLOAT_t mat_Matrix[ 16 ];		
};

#endif
