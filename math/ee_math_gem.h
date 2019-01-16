#ifndef EE_MATH_GEM_H
#define EE_MATH_GEM_H

#include <exzoki/math/ee_math_types.h>
#include <vector>

class EE_MATH_GEM_LINE_C
{
    public:
        EE_MATH_GEM_LINE_C operator+( const EE_MATH_GEM_LINE_C &crC_line2 ) const;
        EE_MATH_GEM_LINE_C operator-( const EE_MATH_GEM_LINE_C &crC_line2 ) const;
        EE_MATH_GEM_LINE_C operator*( EE_MATH_TYPE_t t_const ) const;
        EE_BOOL_t IsNull( void ) const;
        EE_BOOL_t HasSolution( void ) const;
        
        #ifdef EE_DEBUG        
        void Dump( std::ofstream &rC_out )
        {
            for( EE_U32_t u32_I( 0 ); u32_I < co_Coefs.size(); u32_I++ )
            {
                rC_out << co_Coefs[ u32_I ];
                if( u32_I != co_Coefs.size() - 1 ) 
                    rC_out << " | ";
            }
            rC_out << " = " << t_Result << endl;
        }
        #endif
    
        std::vector< EE_MATH_TYPE_t > co_Coefs;
        EE_MATH_TYPE_t t_Result;    
};

enum EE_MATH_GEM_RESULT_TYPE_e
{
    EE_MATH_GEM_RESULT_TYPE_ONE_SOLUTION = 1,
    EE_MATH_GEM_RESULT_TYPE_NO_SOLUTION = 2,
    EE_MATH_GEM_RESULT_TYPE_INFINITE_SOLUTIONS = 3    
};

struct EE_MATH_GEM_RESULT_s
{
    std::vector< EE_MATH_TYPE_t > co_Results;
    EE_MATH_GEM_RESULT_TYPE_e e_ResultType;    
};

namespace EE_EXZOKI_n
{
    EE_MATH_GEM_RESULT_s GaussEliminationMethod( std::vector< EE_MATH_GEM_LINE_C > co_matrix );    
    void ZeroCoefs( EE_U32_t u32_row, EE_U32_t u32_column, std::vector< EE_MATH_GEM_LINE_C > &rco_matrix );
};

#endif
