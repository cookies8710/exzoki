#include <exzoki/math/ee_math_gem.h>

EE_MATH_GEM_LINE_C EE_MATH_GEM_LINE_C::operator+( const EE_MATH_GEM_LINE_C &crC_line2 ) const
{
    EE_MATH_GEM_LINE_C C_Result;
    
    EE_U32_t u32_NCoefs( co_Coefs.size() );
    
    for( EE_U32_t u32_Coef( 0 ); u32_Coef < u32_NCoefs; u32_Coef++ )
        C_Result.co_Coefs.push_back( this->co_Coefs[ u32_Coef ] + crC_line2.co_Coefs[ u32_Coef ] );
    
    C_Result.t_Result = this->t_Result + crC_line2.t_Result;
    
    return( C_Result );     
}

EE_MATH_GEM_LINE_C EE_MATH_GEM_LINE_C::operator-( const EE_MATH_GEM_LINE_C &crC_line2 ) const
{
    EE_MATH_GEM_LINE_C C_Result;
    
    EE_U32_t u32_NCoefs( co_Coefs.size() );
    
    for( EE_U32_t u32_Coef( 0 ); u32_Coef < u32_NCoefs; u32_Coef++ )
        C_Result.co_Coefs.push_back( this->co_Coefs[ u32_Coef ] - crC_line2.co_Coefs[ u32_Coef ] );
    
    C_Result.t_Result = this->t_Result - crC_line2.t_Result;
    
    return( C_Result );     
}

EE_MATH_GEM_LINE_C EE_MATH_GEM_LINE_C::operator*( EE_MATH_TYPE_t t_const ) const
{
    if( fabs( t_const ) < EE_MATH_TYPE_PRECISION )
    {
        
        EE_ERROR_C("gem","*",EE_ERROR_CODES_n::cS_Internal);
    }
    
    EE_MATH_GEM_LINE_C C_Result;
    
    EE_U32_t u32_NCoefs( co_Coefs.size() );
    
    for( EE_U32_t u32_Coef( 0 ); u32_Coef < u32_NCoefs; u32_Coef++ )
        C_Result.co_Coefs.push_back( this->co_Coefs[ u32_Coef ] * t_const );
    
    C_Result.t_Result = this->t_Result * t_const;
    
    return( C_Result );     
}

EE_BOOL_t EE_MATH_GEM_LINE_C::IsNull( void ) const
{
    EE_BOOL_t b_IsNull( 1 );
    
    if( t_Result )
        b_IsNull = 0;
    
    EE_U32_t u32_NCoefs( co_Coefs.size() );
    for( EE_U32_t u32_Coef( 0 ); u32_Coef < u32_NCoefs && b_IsNull; u32_Coef++ )
        if( fabs( co_Coefs[ u32_Coef ] ) > EE_MATH_TYPE_PRECISION )
            b_IsNull = 0;
    
    return( b_IsNull );    
}

EE_BOOL_t EE_MATH_GEM_LINE_C::HasSolution( void ) const
{
    EE_BOOL_t b_IsNull( 1 );
       
    EE_U32_t u32_NCoefs( co_Coefs.size() );
    for( EE_U32_t u32_Coef( 0 ); u32_Coef < u32_NCoefs && b_IsNull; u32_Coef++ )
        if( fabs( co_Coefs[ u32_Coef ] ) > EE_MATH_TYPE_PRECISION )
            b_IsNull = 0;  
    
    if( b_IsNull && fabs( t_Result ) > EE_MATH_TYPE_PRECISION )
        return( 0 );
    else
        return( 1 );   
}

EE_MATH_GEM_RESULT_s EE_EXZOKI_n::GaussEliminationMethod( std::vector< EE_MATH_GEM_LINE_C > co_matrix )
{
    // Kontrola matice (všechny øádky musí mít stejný poèet koeficientù)
    EE_U32_t u32_NLines( co_matrix.size() ),
             u32_NCoefs( co_matrix[ 0 ].co_Coefs.size() );
    for( EE_U32_t u32_Line( 0 ); u32_Line < u32_NLines; u32_Line++ )
        if( co_matrix[ u32_Line ].co_Coefs.size() != u32_NCoefs )
            EE_ERROR_C( "EE_EXZOKI_n", "GaussEliminationMethod", EE_ERROR_CODES_n::cS_Internal ); 
    
    EE_MATH_GEM_RESULT_s s_Result;
    
    /*o<<"gemGEMgemGEMgemGEMgemGEMgemGEMgemGEMgemGEMgemGEMgemGEM"<<endl;
    co_matrix[0].Dump(o);co_matrix[1].Dump(o);co_matrix[2].Dump(o);
    o<<"/q"<<endl<<endl<<endl;*/
    
    // Procházím maticí
    for( EE_U32_t u32_Column( 0 ), u32_Row( 0 ); 
         u32_Column < u32_NCoefs && u32_Row < co_matrix.size(); 
       )
    {
        EE_MATH_TYPE_t t_A( co_matrix[ u32_Row ].co_Coefs[ u32_Column ] );
        if( t_A == 0.0 )
        {
            // Pokud je prvek nulový, zkontroluju prvky pod ním
            EE_BOOL_t b_AllUnderAreZero( 1 );
            EE_U32_t u32_Row2( u32_Row + 1 );
            for( ; u32_Row2 < co_matrix.size() && b_AllUnderAreZero; )
                if( fabs( co_matrix[ u32_Row2 ].co_Coefs[ u32_Column ] ) > EE_MATH_TYPE_PRECISION )
                    b_AllUnderAreZero = 0;
                else
                    u32_Row2++;        
            if( b_AllUnderAreZero )
            {
                // Pokud jsou všechny nulové, pokraèuju v dalším sloupci
                u32_Column++;
                continue;    
            }
            else
            {
               /* o<<"0="<<endl;co_matrix[ 0 ].Dump(o);
                o<<"1="<<endl;co_matrix[ 1 ].Dump(o);
                o<<"2="<<endl;co_matrix[ 2 ].Dump(o);
                o<<"u32_Row="<<u32_Row<<endl;
                o<<"u32_Row2="<<u32_Row2<<endl;
                o<<"Prohazuju"<<endl;co_matrix[ u32_Row ].Dump(o);
                o<<"Za"<<endl;co_matrix[ u32_Row2 ].Dump(o);
                */// Pokud jsem našel nenulový, prohodím øádky
                EE_MATH_GEM_LINE_C C_Temp( co_matrix[ u32_Row ] );
                co_matrix[ u32_Row ] = co_matrix[ u32_Row2 ];
                co_matrix[ u32_Row2 ] = C_Temp;        
            }                    
        }
        
        // Vynuluju koeficienty v aktuálním sloupci pod prvkem A
        ZeroCoefs( u32_Row, u32_Column, co_matrix );
        
        // Odstraním nulvé øádky
        EE_U32_t u32_Row3( 0 );
        std::vector< EE_MATH_GEM_LINE_C > co_Matrix2;
        while( u32_Row3 < co_matrix.size() )
        {
            if( !co_matrix[ u32_Row3 ].IsNull() )
                co_Matrix2.push_back( co_matrix[ u32_Row3 ] );
            u32_Row3++;
        }
        
        co_matrix = co_Matrix2;
        
        u32_Row++; u32_Column++;
        
        C_DebugFile<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<endl;
        for(int i(0);i<co_matrix.size();i++)
            co_matrix[i].Dump(C_DebugFile);
        C_DebugFile<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<endl;
        
    }  
    
    // Pokud existuje nìjaký øádek, který nemá øešení, nemá soustava øešení
    for( EE_U32_t u32_Row( 0 ); u32_Row < co_matrix.size(); u32_Row++ )
        if( !co_matrix[ u32_Row ].HasSolution() )
        {
            s_Result.e_ResultType = EE_MATH_GEM_RESULT_TYPE_NO_SOLUTION;
            return( s_Result );
        }
    
    // Pokud mám ménì øádkù než koeficientù, soustava má nekoneènì mnoho øešení
    if( co_matrix.size() < co_matrix[ 0 ].co_Coefs.size() )
        s_Result.e_ResultType = EE_MATH_GEM_RESULT_TYPE_INFINITE_SOLUTIONS;
    else
    {
       /* o<< "*********************************"<<endl;
        for(int i(0);i<co_matrix.size();i++)
            co_matrix[i].Dump(o);
        o<< "*********************************"<<endl;*/
        // Jinak má soustava jedno øešení
        s_Result.e_ResultType = EE_MATH_GEM_RESULT_TYPE_ONE_SOLUTION;
        
        // Výsledky
        std::vector< EE_MATH_TYPE_t > co_ResultCoefs( co_matrix.size() );
        
        // Postupuju odespod matice        
        for( EE_S32_t s32_Coef( co_matrix.size() - 1 ); s32_Coef >= 0; s32_Coef-- )
        {
            // Aktuální koeficient
            EE_MATH_TYPE_t t_Coef( co_matrix[ s32_Coef ].co_Coefs[ s32_Coef ] );
            // Výsledek pro aktuální koeficient
            co_ResultCoefs[ s32_Coef ] = co_matrix[ s32_Coef ].t_Result / 
                                         t_Coef;
            
            // Vynuluju hodnotu koeficienty nad sebou           
            for( EE_S32_t s32_Coef2( s32_Coef - 1 ); s32_Coef2 >= 0; s32_Coef2-- )
                co_matrix[ s32_Coef2 ] = co_matrix[ s32_Coef2 ] -
                    co_matrix[ s32_Coef ] * ( co_matrix[ s32_Coef2 ].co_Coefs[ s32_Coef ] / t_Coef );    
           /* o<< "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"<<endl;
            for(int i(0);i<co_matrix.size();i++)
                co_matrix[i].Dump(o);
            o<< "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"<<endl;*/
        }
        
        s_Result.co_Results = co_ResultCoefs;
        
        /*for( EE_S32_t s32_Coef( co_matrix.size() - 1 ); s32_Coef <= 0; s32_Coef-- )
        {
            EE_MATH_TYPE_t t_Number( co_matrix[ s32_Coef ].t_Result );
            for( EE_S32_t s32_Coef2( co_matrix[ s32_Coef ].co_Coefs.size() - 1 ); 
                 s32_Coef2 > s32_Coef; s32_Coef2-- )
                t_Number -= co_matrix[ s32_Coef ].co_Coefs[ s32_Coef2 ] * 
                            co_ResultCoefs[ co_matrix[ s32_Coef ].co_Coefs.size() - s32_Coef2 - 1 ];
            
            co_ResultCoefs.push_back( t_Number / co_matrix[ s32_Coef ].co_Coefs[ s32_Coef ] );    
        }*/   
        
    }
    
    return( s_Result );     
    
} 

void EE_EXZOKI_n::ZeroCoefs( EE_U32_t u32_row, EE_U32_t u32_column, std::vector< EE_MATH_GEM_LINE_C > &rco_matrix )
{
    EE_MATH_TYPE_t t_A( rco_matrix[ u32_row ].co_Coefs[ u32_column ] );
    EE_U32_t u32_NRows( rco_matrix.size() );
    
    for( EE_U32_t u32_Row( u32_row + 1 ); u32_Row < u32_NRows; u32_Row++ )
        rco_matrix[ u32_Row ] = rco_matrix[ u32_Row ] - 
            rco_matrix[ u32_row ] * ( rco_matrix[ u32_Row ].co_Coefs[ u32_column ] / t_A );      
}      
