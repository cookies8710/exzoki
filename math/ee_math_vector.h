#ifndef EE_MATH_VECTOR_H
#define EE_MATH_VECTOR_H

#include <math.h>
#include <exzoki/base/ee_base.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>

class EE_MATH_VECTOR_C: public EE_BASE_C
{
 	public:
		// Implicitní konstruktor
  		EE_MATH_VECTOR_C( void );
  		// Explicitní konstruktor - nastaví vektor
  		EE_MATH_VECTOR_C( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
  
  		// Vektorový souèet
  		EE_MATH_VECTOR_C operator+( const EE_MATH_VECTOR_C& crC_vector ) const;
  		
  	/*	// Vektorový souèet
  		EE_MATH_VECTOR_C& operator+=( const EE_MATH_VECTOR_C& crC_vector );
  		*/
  		// Vektorový rozdíl
  		EE_MATH_VECTOR_C operator-( void ) const;
  		EE_MATH_VECTOR_C operator-( const EE_MATH_VECTOR_C& crC_vector ) const;
  		
  	/*	// Vektorový rozdíl
  		EE_MATH_VECTOR_C& operator-=( const EE_MATH_VECTOR_C& crC_vector );
  		*/
  		// Násobení vektoru èíslem
  		EE_MATH_VECTOR_C operator*( EE_MATH_TYPE_t t_number ) const;
  		// Dìlení vektoru èíslem
  		EE_MATH_VECTOR_C operator/( EE_MATH_TYPE_t t_number ) const;
  		// Skalární souèin
  		EE_MATH_TYPE_t operator*( const EE_MATH_VECTOR_C& crC_vector ) const;
  		// Vektorový souèin
  		EE_MATH_VECTOR_C operator%( const EE_MATH_VECTOR_C& crC_vector ) const;
  		// Porovnání dvou vektorù
  		EE_BOOL_t operator==( const EE_MATH_VECTOR_C& crC_vector ) const;
  		EE_BOOL_t operator!=( const EE_MATH_VECTOR_C& crC_vector ) const;
  
  		// Nalezení normály roviny / trojúhleníku
  		void Normal( const EE_MATH_VECTOR_C& crC_pointA, 
               	     const EE_MATH_VECTOR_C& crC_pointB, 
               	     const EE_MATH_VECTOR_C& crC_pointC );
  		// Normalizace vetoru
  		void Normalize( void );
  		// Nastavení délky vektoru pøi zachování smìru  		
  		void SetLength( EE_MATH_TYPE_t t_length );
  		// Nastavení vektoru
  		void Set( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
  
  		// Vrací true, kdyz je jeden vektor nasobkem druheho
  		bool IsMultiple( const EE_MATH_VECTOR_C &crC_vector ) const;
  		// Vrátí true, kdyz je vektor nulovy
  		bool IsNull( void ) const;
  		inline EE_MATH_TYPE_t Pow2( void ) const;
          
            
  		// Získání souøadnice X
  		inline EE_MATH_TYPE_t GetX( void ) const;     
  		// Získání souøadnice Y
  		inline EE_MATH_TYPE_t GetY( void ) const;   
  		// Získání souøadnice Z
  		inline EE_MATH_TYPE_t GetZ( void ) const; 
  		// Získání délky vektoru    
  		EE_MATH_TYPE_t Length( void ) const;
  		// Získání délky vektoru umocnìné na druhou   
  		EE_MATH_TYPE_t LengthPow2( void ) const;
  		// Vrátí úhel mezi 2 vektory (ten menší)
		EE_MATH_TYPE_t GetAngle( const EE_MATH_VECTOR_C& crC_vector );
 
  		virtual EE_BYTE_t Read( std::ifstream &rC_file );
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const;
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;
 	private:
  		EE_MATH_TYPE_t mt_X;
  		EE_MATH_TYPE_t mt_Y;
  		EE_MATH_TYPE_t mt_Z;
};

#endif
