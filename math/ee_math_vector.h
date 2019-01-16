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
		// Implicitn� konstruktor
  		EE_MATH_VECTOR_C( void );
  		// Explicitn� konstruktor - nastav� vektor
  		EE_MATH_VECTOR_C( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
  
  		// Vektorov� sou�et
  		EE_MATH_VECTOR_C operator+( const EE_MATH_VECTOR_C& crC_vector ) const;
  		
  	/*	// Vektorov� sou�et
  		EE_MATH_VECTOR_C& operator+=( const EE_MATH_VECTOR_C& crC_vector );
  		*/
  		// Vektorov� rozd�l
  		EE_MATH_VECTOR_C operator-( void ) const;
  		EE_MATH_VECTOR_C operator-( const EE_MATH_VECTOR_C& crC_vector ) const;
  		
  	/*	// Vektorov� rozd�l
  		EE_MATH_VECTOR_C& operator-=( const EE_MATH_VECTOR_C& crC_vector );
  		*/
  		// N�soben� vektoru ��slem
  		EE_MATH_VECTOR_C operator*( EE_MATH_TYPE_t t_number ) const;
  		// D�len� vektoru ��slem
  		EE_MATH_VECTOR_C operator/( EE_MATH_TYPE_t t_number ) const;
  		// Skal�rn� sou�in
  		EE_MATH_TYPE_t operator*( const EE_MATH_VECTOR_C& crC_vector ) const;
  		// Vektorov� sou�in
  		EE_MATH_VECTOR_C operator%( const EE_MATH_VECTOR_C& crC_vector ) const;
  		// Porovn�n� dvou vektor�
  		EE_BOOL_t operator==( const EE_MATH_VECTOR_C& crC_vector ) const;
  		EE_BOOL_t operator!=( const EE_MATH_VECTOR_C& crC_vector ) const;
  
  		// Nalezen� norm�ly roviny / troj�hlen�ku
  		void Normal( const EE_MATH_VECTOR_C& crC_pointA, 
               	     const EE_MATH_VECTOR_C& crC_pointB, 
               	     const EE_MATH_VECTOR_C& crC_pointC );
  		// Normalizace vetoru
  		void Normalize( void );
  		// Nastaven� d�lky vektoru p�i zachov�n� sm�ru  		
  		void SetLength( EE_MATH_TYPE_t t_length );
  		// Nastaven� vektoru
  		void Set( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
  
  		// Vrac� true, kdyz je jeden vektor nasobkem druheho
  		bool IsMultiple( const EE_MATH_VECTOR_C &crC_vector ) const;
  		// Vr�t� true, kdyz je vektor nulovy
  		bool IsNull( void ) const;
  		inline EE_MATH_TYPE_t Pow2( void ) const;
          
            
  		// Z�sk�n� sou�adnice X
  		inline EE_MATH_TYPE_t GetX( void ) const;     
  		// Z�sk�n� sou�adnice Y
  		inline EE_MATH_TYPE_t GetY( void ) const;   
  		// Z�sk�n� sou�adnice Z
  		inline EE_MATH_TYPE_t GetZ( void ) const; 
  		// Z�sk�n� d�lky vektoru    
  		EE_MATH_TYPE_t Length( void ) const;
  		// Z�sk�n� d�lky vektoru umocn�n� na druhou   
  		EE_MATH_TYPE_t LengthPow2( void ) const;
  		// Vr�t� �hel mezi 2 vektory (ten men��)
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
