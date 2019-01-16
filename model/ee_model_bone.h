#ifndef EE_MODEL_BONE_H
#define EE_MODEL_BONE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/base/ee_base.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>


class EE_MODEL_BONE_C: public EE_BASE_C
{
	public:
		EE_MODEL_BONE_C( void );
		
		~EE_MODEL_BONE_C( void );
		EE_MODEL_BONE_C( const EE_MODEL_BONE_C& crC_bone );
		EE_MODEL_BONE_C& operator=( const EE_MODEL_BONE_C& crC_bone );
		
		void Read( EE_SYSTEM_FILE_C& rC_file );
		
		void Draw( const EE_SYSTEM_COLOR_s &crs_headColor, 
		           const EE_SYSTEM_COLOR_s &crs_tailColor ) const;
		
		const EE_MATH_POINT_C& GetHead( void ) const;
		const EE_MATH_POINT_C& GetTail( void ) const;
		
		const std::vector< EE_U32_t >& GetVertices( void ) const; 
		
		std::string GetName( void ) const;
		
		void Clear( void );
		
		virtual EE_BYTE_t Read( std::ifstream &rC_file ){}
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const	{}		
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;
		
	private:
		void Destroy( void );
		void Create( const EE_MODEL_BONE_C& crC_bone );	
			
		// Jméno kosti
		std::string mS_Name;
		
		// ID kosti
		EE_U32_t mu32_ID;
		
		// Mateøské kosti
		EE_U32_t mu32_NParent;
		EE_PU32_t mpu32_Parents;
		
		// Dceøinné kosti
		EE_U32_t mu32_NChildren;
		EE_PU32_t mpu32_Children;
		
		// Vertexy ovlinìné kostí
		std::vector< EE_U32_t > mco_Vertices;
		
		// Pozice hlavy kosti
		EE_MATH_POINT_C mC_Head;
		// Pozice koncové èásti kosti
		EE_MATH_POINT_C mC_Tail;
		
};

#endif
