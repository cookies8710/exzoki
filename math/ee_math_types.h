#ifndef EE_MATH_TYPES_H
#define EE_MATH_TYPES_H

#include <exzoki/system/ee_system_types.h>

class fgg;

// Nastavení základního matematického typu
typedef EE_FLOAT_t EE_MATH_TYPE_t;
const EE_MATH_TYPE_t EE_MATH_TYPE_ZERO = 0.0f;
const EE_MATH_TYPE_t EE_MATH_TYPE_PRECISION = 1.0e-04f;
/*
class fgg
{
   
    
    public:
        fgg():d(0.0) {}
        fgg(double df){d=trunc(df*1000.0)*0.001;}
        fgg(const fgg &f) {}
               
        
        fgg operator+(const fgg &f){return(fgg(d+f.d));}
        fgg operator+(double g){return(fgg(g+d));}
        
        
        fgg operator-(const fgg &f){return(fgg(d-f.d));}
        fgg operator-(double g){return(fgg(d-g));}
                
        fgg operator*(const fgg &f){return(fgg(d*f.d));}
        fgg operator*(double g){return(fgg(g*d));}
        
        fgg operator/(const fgg &f){return(fgg(d/f.d));}
        fgg operator/(double g){return(fgg(d/g));}
        
        fgg operator=(const fgg &f){d=f.d;return(*this);}
        fgg operator=(double df){d=trunc(df*1000.0)*0.001;return(*this);}
        
        bool operator==(const fgg &f){return(fabs(d-f.d)< EE_MATH_TYPE_PRECISION);}
        bool operator!=(const fgg &f){return(!(*this==f));}
        bool operator>(const fgg &f)
        {if(*this!=f)return(f<*this);}
        bool operator<(const fgg &f){if(*this!=f)return(f>*this);}
        bool operator>=(const fgg &f){return(f<*this || *this==f);}
        bool operator<=(const fgg &f){return(f>*this || *this==f);}
        
    private:
        EE_DOUBLE_t d;    
}*/

// Konstanty
const EE_MATH_TYPE_t EE_MATH_PI = 3.14159265;  // PI
const EE_MATH_TYPE_t EE_MATH_DEGTORAD = 0.0174533; // PI / 180
const EE_MATH_TYPE_t EE_MATH_RADTODEG = 57.2957795; // 180 / PI

// Goniometrické konstanty
const EE_MATH_TYPE_t EE_MATH_GONIOMETRIC_PRECISION = 1.0e-02f;

const EE_MATH_TYPE_t EE_MATH_SINUS_PERIOD = 360.0f;
const EE_MATH_TYPE_t EE_MATH_COSINUS_PERIOD = 360.0f;
const EE_MATH_TYPE_t EE_MATH_TANGENS_PERIOD = 180.0f;
const EE_MATH_TYPE_t EE_MATH_COTANGENS_PERIOD = 180.0f;

// Jiné
enum EE_MATH_POSITION_e
{
 	EE_MATH_POSITION_BEHIND,// 0
 	EE_MATH_POSITION_SAME, // 1
 	EE_MATH_POSITION_FRONT, // 2
 	EE_MATH_POSITION_COLLISION // 3
};

#endif
