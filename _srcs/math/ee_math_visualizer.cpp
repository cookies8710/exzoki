#include <exzoki/math/ee_math_visualizer.h>

void EE_EXZOKI_n::Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                             const EE_MATH_POINT_C &crC_point )
{
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    
    glBegin( GL_POINTS );
        glColor4ub( crs_color.b_R, crs_color.b_G, crs_color.b_B, crs_color.b_A );
        glVertex3f( crC_point.GetX(), crC_point.GetY(), crC_point.GetZ() );
    glEnd();
    
    glPopAttrib();    
}                             
                            
void EE_EXZOKI_n::Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                             const EE_MATH_VECTOR_C &crC_vector, 
                             const EE_MATH_POINT_C &crC_place )
{
    EE_MATH_POINT_C C_End( crC_place + crC_vector );
    
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    
    glBegin( GL_LINES );
        glColor4ub( crs_color.b_R, crs_color.b_G, crs_color.b_B, crs_color.b_A );
        glVertex3f( crC_place.GetX(), crC_place.GetY(), crC_place.GetZ() );
        glVertex3f( C_End.GetX(), C_End.GetY(), C_End.GetZ() );
    glEnd();
    
    glPopAttrib();    
}            
                    
void EE_EXZOKI_n::Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                             const EE_MATH_PLANE_C &crC_plane )
{
    EE_BYTE_t b_Smallest1, b_Smallest2;
    EE_MATH_VECTOR_C C_PlaneNormal( crC_plane.GetNormal() );
    
    if( C_PlaneNormal.GetX() < C_PlaneNormal.GetY() )
    {
        if( C_PlaneNormal.GetX() < C_PlaneNormal.GetZ() )
        {
            b_Smallest1 = 0;
            if( C_PlaneNormal.GetZ() < C_PlaneNormal.GetY() )
                b_Smallest2 = 2; 
            else
                b_Smallest2 = 1; 
            
        }
        else
        {
            b_Smallest1 = 2; 
            b_Smallest2 = 0;
        }
               
    } 
    else
    {
        if( C_PlaneNormal.GetY() < C_PlaneNormal.GetZ() )
        {
            b_Smallest1 = 1;
            if( C_PlaneNormal.GetZ() < C_PlaneNormal.GetX() )
                b_Smallest2 = 2; 
            else
                b_Smallest2 = 0;             
        }
        else
        {
            b_Smallest1 = 2; 
            b_Smallest2 = 1;
        }    
    }
    
    EE_FLOAT_t f_X, f_Y, f_Z;
    EE_BOOL_t b_X( 0 ), b_Y( 0 ), b_Z( 0 );
    
    if( b_Smallest1 == 0 || b_Smallest2 == 0 )
    {
        f_X = 50.0;
        b_X = 1;
    }
    if( b_Smallest1 == 1 || b_Smallest2 == 1 )
    {
        f_Y = 50.0;
        b_Y = 1;
    }
    if( b_Smallest1 == 2 || b_Smallest2 == 2 )
    {
        f_Z = 50.0;
        b_Z = 1;
    }
    
    EE_MATH_POINT_C aC_Points[ 5 ]; // 4 body jsou plocha, pátý je umístìní normály roviny
    
    for( EE_BYTE_t b_Point( 0 ); b_Point < 5; b_Point++ )
    {
        switch( b_Point )
        {
            case 0:                           
                break;
            case 1:
                if( b_X && b_Y )
                    f_X = -f_X; 
                    
                if( b_X && b_Z )
                    f_Z = -f_Z;  
                    
                if( b_Y && b_Z )
                    f_Z = -f_Z;                     
                break;
            case 2:
                if( b_X && b_Y )
                {                    
                    f_Y = -f_Y;  
                }   
                
                if( b_X && b_Z )
                {
                    f_X = -f_X;                    
                }  
                
                if( b_Y && b_Z )
                {
                    f_Y = -f_Y;
                    
                }  
                break;
            case 3:
                if( b_X && b_Y )
                    f_X = -f_X;  
                if( b_X && b_Z )
                    f_Z = -f_Z;                     
                if( b_Y && b_Z )
                    f_Z = -f_Z;  
                break;  
            case 4:
                if( b_X && b_Y )              
                    f_X = f_Y = 0.0;  
                if( b_X && b_Z )
                    f_X = f_Z = 0.0;                   
                if( b_Y && b_Z )
                    f_Y = f_Z = 0.0;  
                  
        }
        
        if( !b_X )
        {
            f_X = - ( crC_plane.GetD() + C_PlaneNormal.GetY() * f_Y + C_PlaneNormal.GetZ() * f_Z ) / C_PlaneNormal.GetX();     
        }
        else if( !b_Y )
        {
            f_Y = - ( crC_plane.GetD() + C_PlaneNormal.GetX() * f_X + C_PlaneNormal.GetZ() * f_Z ) / C_PlaneNormal.GetY();     
        }
        else if( !b_Z )
        {
            f_Z = - ( crC_plane.GetD() + C_PlaneNormal.GetX() * f_X + C_PlaneNormal.GetY() * f_Y ) / C_PlaneNormal.GetZ();     
        }
        
        aC_Points[ b_Point ].Set( f_X, f_Y, f_Z );
    }     
      
      
   
    EE_DEBUG_RTDS_C::GetRTDS( "collisiondebugger" ).UpdateInfo
("mvp1","P1 = [%.2g, %.2g, %.2g]",aC_Points[ 0 ].GetX(),aC_Points[ 0 ].GetY(),aC_Points[ 0 ].GetZ());  
    EE_DEBUG_RTDS_C::GetRTDS( "collisiondebugger" ).UpdateInfo
("mvp2","P2 = [%.2g, %.2g, %.2g]",aC_Points[ 1 ].GetX(),aC_Points[ 1 ].GetY(),aC_Points[ 1 ].GetZ());  
    EE_DEBUG_RTDS_C::GetRTDS( "collisiondebugger" ).UpdateInfo
("mvp3","P3 = [%.2g, %.2g, %.2g]",aC_Points[ 2 ].GetX(),aC_Points[ 2 ].GetY(),aC_Points[ 2 ].GetZ());  
    EE_DEBUG_RTDS_C::GetRTDS( "collisiondebugger" ).UpdateInfo
("mvp4","P4 = [%.2g, %.2g, %.2g]",aC_Points[ 3 ].GetX(),aC_Points[ 3 ].GetY(),aC_Points[ 3 ].GetZ());  
    
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    
    glBegin( GL_QUADS );
        glColor4ub( crs_color.b_R, crs_color.b_G, crs_color.b_B, crs_color.b_A );
        glVertex3f( aC_Points[ 0 ].GetX(), aC_Points[ 0 ].GetY(), aC_Points[ 0 ].GetZ() );
        glVertex3f( aC_Points[ 1 ].GetX(), aC_Points[ 1 ].GetY(), aC_Points[ 1 ].GetZ() );
        glVertex3f( aC_Points[ 2 ].GetX(), aC_Points[ 2 ].GetY(), aC_Points[ 2 ].GetZ() );
        glVertex3f( aC_Points[ 3 ].GetX(), aC_Points[ 3 ].GetY(), aC_Points[ 3 ].GetZ() );
    glEnd();
    
    // Normála
    EE_EXZOKI_n::Visualize( crs_color, C_PlaneNormal, aC_Points[ 4 ] );
    
    glPopAttrib();    
}
