#include <exzoki/gui/ee_gui_system.h>

EE_GUI_SYSTEM_C::EE_GUI_SYSTEM_C( void ): mcpC_Mouse( 0 ), mpC_Keyboard( 0 ), 
                                          mpu32_IDs( new EE_U32_t( 0 ) ), 
                                          mu32_NIDAlocated( sizeof( EE_U32_t ) * 8 ),
                                          mpf_GuiProc( 0 ),
                                          mb_Callback( 0 )
{
}

EE_GUI_SYSTEM_C::EE_GUI_SYSTEM_C( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                                  EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard,
                                  EE_FLOAT_t f_left, EE_FLOAT_t f_right, EE_FLOAT_t f_bottom, EE_FLOAT_t f_top,
                                  EE_U32_t u32_screenWidth, EE_U32_t u32_screenHeight,
                                  EE_GUI_PROC_t pf_guiProc ): 
                                  mpu32_IDs( new EE_U32_t( 0 ) ), 
                                  mu32_NIDAlocated( sizeof( EE_U32_t ) * 8 ),
                                  mb_Callback( 0 )
                                  
{
    SetUp( cpC_mouse, pC_keyboard, f_left, f_right, f_bottom, f_top, u32_screenWidth, u32_screenHeight, pf_guiProc );    
}
                                  
EE_GUI_SYSTEM_C::~EE_GUI_SYSTEM_C( void )
{
    Clear();    
}
        
void EE_GUI_SYSTEM_C::SetUp( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                             EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard,
                             EE_FLOAT_t f_left, EE_FLOAT_t f_right, EE_FLOAT_t f_bottom, EE_FLOAT_t f_top,
                             EE_U32_t u32_screenWidth, EE_U32_t u32_screenHeight,
                             EE_GUI_PROC_t pf_guiProc )
{
    mcpC_Mouse = cpC_mouse;
    mpC_Keyboard = pC_keyboard;
    ms_ScreenRectangle.f_Left = f_left;  
    ms_ScreenRectangle.f_Right = f_right;
    ms_ScreenRectangle.f_Bottom = f_bottom;
    ms_ScreenRectangle.f_Top = f_top;
    mu32_ScreenWidth = u32_screenWidth;
    mu32_ScreenHeight = u32_screenHeight;
    mpf_GuiProc = pf_guiProc;
}
        
EE_GUI_ID_t EE_GUI_SYSTEM_C::CreateGuiElement( const EE_GUI_BASE_C &crC_guiElement )
{
    EE_U32_t u32_NGuiElements( mco_GuiElements.size() );  
    
    // Pokud by byl nov� po�et prvk� mimo po�et alokovan�ch ID, alokuju dal�� m�sto
    if( u32_NGuiElements + 1 > mu32_NIDAlocated )
    {
        // Alokuju nov� m�sto
        EE_PU32_t pu32_NewIDStore( new EE_U32_t[ mu32_NIDAlocated / ( sizeof( EE_U32_t ) * 8 ) + 1 ] );
        // Zkop�ruju star� ID
        memcpy( pu32_NewIDStore, mpu32_IDs, mu32_NIDAlocated / ( sizeof( EE_U32_t ) * 8 ) ); 
        
        // Nov� po�et alokovan�ch ID
        mu32_NIDAlocated = mu32_NIDAlocated +  sizeof( EE_U32_t ) * 8;   
        
        // Dealokace star�ho m�sta
        delete[] mpu32_IDs;
        // Nov� ukazatel
        mpu32_IDs = pu32_NewIDStore;
    }
    
    // Najdu voln� ID    
    EE_U32_t u32_NSegments( mu32_NIDAlocated / ( sizeof( EE_U32_t ) * 8 ) );
    EE_U32_t u32_ID( 0 );
    EE_BOOL_t b_Found( 0 );
    // Projdu v�echny segmenty
    EE_U32_t u32_BitMask( 1 );
    for( EE_U32_t u32_Segment( 0 ); u32_Segment < u32_NSegments && !b_Found ; u32_Segment++, u32_BitMask = 1 )
        // Projdu v�echny bity segmentu
        for( EE_BYTE_t t_Bit( 0 ); 
             t_Bit < 32 && !b_Found; 
             t_Bit++, u32_BitMask *= 2, u32_ID++ )
            // Pokud je bit = 0, id nen� obsazeno
            if( ! ( mpu32_IDs[ u32_Segment ] & u32_BitMask ) )
            {
                // Nastav�m vlajku obsazen� na 1
                mpu32_IDs[ u32_Segment ] |= u32_BitMask; 
                b_Found = 1; 
            }
                
    if( !b_Found )
        EE_ERROR_C();
        
    // Ulo��m nov� gui prvek
    EE_GUI_ELEMENT_TYPE_e e_ElementType( crC_guiElement.GetElementType() );
    switch( e_ElementType )
    {
        case EE_GUI_ELEMENT_TYPE_BUTTON:            
            mco_GuiElements[ u32_ID ] = new EE_GUI_BUTTON_C( (const EE_GUI_BUTTON_C&)crC_guiElement );   
            break;
        case EE_GUI_ELEMENT_TYPE_EDITBOX:
            mco_GuiElements[ u32_ID ] = new EE_GUI_EDITBOX_C( (const EE_GUI_EDITBOX_C&)crC_guiElement );   
            break;
        case EE_GUI_ELEMENT_TYPE_SCROLLBAR:
            mco_GuiElements[ u32_ID ] = new EE_GUI_SCROLLBAR_C( (const EE_GUI_SCROLLBAR_C&)crC_guiElement );   
            break;
        case EE_GUI_ELEMENT_TYPE_WINDOW:
            mco_GuiElements[ u32_ID ] = new EE_GUI_WINDOW_C( (const EE_GUI_WINDOW_C&)crC_guiElement );
            break;    
    }
    
             
    // Um�st�m ho na vrchol Z
    mco_GuiElementsZ.insert( mco_GuiElementsZ.begin(), u32_ID );  
    
    return( u32_ID );    
}

void EE_GUI_SYSTEM_C::DeleteGuiElement( EE_GUI_ID_t t_id )
{
    std::map< EE_GUI_ID_t, EE_GUI_BASE_C* >::iterator I_GuiElement;
    if( ( I_GuiElement = mco_GuiElements.find( t_id ) ) == mco_GuiElements.end() )
        EE_ERROR_C();
    
    
    delete I_GuiElement->second;
    mco_GuiElements.erase( I_GuiElement );
    
    // 
    mco_GuiElementsZ.erase( find( mco_GuiElementsZ.begin(), mco_GuiElementsZ.end(), t_id ) );  
    
    // Uvoln�m ID
    
    // Zjist�m segment
    EE_U32_t u32_Segment( t_id / ( sizeof( EE_U32_t ) * 8 ) );
    // Zjist�m bit
    EE_U32_t u32_Bit( t_id - u32_Segment * ( sizeof( EE_U32_t ) * 8 ) );
    // Vytvo��m bitovou masku
    EE_U32_t u32_BitMask( 1 );
    for( EE_U32_t u32_I( 0 ); u32_I < u32_Bit; u32_I++, u32_BitMask *= 2 );
    // Vynuluju vlajku pou�it� ID
    mpu32_IDs[ u32_Segment ] &= ~u32_BitMask; 
}


        
void EE_GUI_SYSTEM_C::Clear( void )
{
    // Sma�u odkaz na my� a kl�vesnici
    mcpC_Mouse = 0;
    mpC_Keyboard = 0;
    
    mpf_GuiProc = 0;
    
    // Vyma�u gui prvky
    std::map< EE_GUI_ID_t, EE_GUI_BASE_C* >::const_iterator cI_Element( mco_GuiElements.begin() ), 
                                                            cI_ElementEnd( mco_GuiElements.end() );
    while( cI_Element != cI_ElementEnd )
        delete (cI_Element++)->second;
    
    mco_GuiElements.clear();
    mco_GuiElementsZ.clear();
    // Sma�u ID
    delete[] mpu32_IDs;
    mpu32_IDs = 0;
    mu32_NIDAlocated = 0; 
    
    mb_Callback = 0;   
}

        
void EE_GUI_SYSTEM_C::GuiProc( void )
{
 	 POINT p;
	 GetCursorPos(&p);
 	 
    // Zpracuju vstup z my�i a kl�vesnice
    ms_MouseData.b_LBBefore = ms_MouseData.b_LB;
    ms_MouseData.b_LB = (GetAsyncKeyState(VK_LBUTTON))?1:0;//mcpC_Mouse->GetLeftButton();
    
    ms_MouseData.f_XBefore = ms_MouseData.f_X;
    ms_MouseData.f_X = ( (EE_FLOAT_t)p.x / mu32_ScreenWidth ) * 
                       ( ms_ScreenRectangle.f_Right - ms_ScreenRectangle.f_Left ) + ms_ScreenRectangle.f_Left;
					   /*( (EE_FLOAT_t)mcpC_Mouse->GetX() / mu32_ScreenWidth ) * 
                       ( ms_ScreenRectangle.f_Right - ms_ScreenRectangle.f_Left ) + ms_ScreenRectangle.f_Left;
    */
    ms_MouseData.f_YBefore = ms_MouseData.f_Y;
    ms_MouseData.f_Y = ( (EE_FLOAT_t)( mu32_ScreenHeight - p.y ) / mu32_ScreenHeight ) * 
                       ( ms_ScreenRectangle.f_Top - ms_ScreenRectangle.f_Bottom ) + ms_ScreenRectangle.f_Bottom;
	/*( (EE_FLOAT_t)( mu32_ScreenHeight - mcpC_Mouse->GetY() ) / mu32_ScreenHeight ) * 
                       ( ms_ScreenRectangle.f_Top - ms_ScreenRectangle.f_Bottom ) + ms_ScreenRectangle.f_Bottom;
    */
      
    if( mb_Callback )
    {
        if( mco_GuiElements[ mu32_CallbackElement ]->GuiProc( ms_MouseData, mpC_Keyboard ) != EE_GUI_SIGNAL_CALLBACK )
        {
            mb_Callback = 0;    
        }        
    }
    else
    {    
        // Proch�z�m Gui prvky od nejhorn�j��ho, pokud n�jak� prvek zareaguje, vstup je zpracov�n a ostatn�
        // prvky p�esko��m
        std::list< EE_GUI_ID_t >::iterator I_GuiElement( mco_GuiElementsZ.begin() ), 
                                           I_GuiElementEnd( mco_GuiElementsZ.end() ); 
        EE_BOOL_t b_Processed( 0 );
        while( I_GuiElement != I_GuiElementEnd && !b_Processed )
        {        
            // Na za��tku p�edpokl�d�m, �e vstup bude zpracov�n
            b_Processed = 1;
            
            EE_U32_t e_Signal( mco_GuiElements[ *I_GuiElement ]->GuiProc( ms_MouseData, mpC_Keyboard ) );
            
            switch( e_Signal  )
            {
                // My� prvek aktivovala
                case EE_GUI_SIGNAL_ACTIVATED:
                    // P�esunu prvek z aktu�ln� pozice na vrchol
                    mco_GuiElementsZ.insert( mco_GuiElementsZ.begin(), *I_GuiElement );
                    mco_GuiElementsZ.erase( I_GuiElement );
                    // Zavol� aktiva�n� fci a p�ed� ID prvku
                    mpf_GuiProc( *I_GuiElement );                
                    break; 
                // Callback vlajka -> v p��t�m vol�n� vol�m jen a pouze tento prvek dokud bude vracet callback
                case EE_GUI_SIGNAL_CALLBACK:
                    // P�esunu prvek z aktu�ln� pozice na vrchol
                    mco_GuiElementsZ.insert( mco_GuiElementsZ.begin(), *I_GuiElement );
                    mco_GuiElementsZ.erase( I_GuiElement );
                    
                    mb_Callback = 1;
                    mu32_CallbackElement = *I_GuiElement;
                    break;
                // Callbakactive -> callback + vol�n� aktiva�n� fce
                case EE_GUI_SIGNAL_ACTIVECALLBACK:
                    mpf_GuiProc( *I_GuiElement );       
                    mb_Callback = 1;
                    mu32_CallbackElement = *I_GuiElement;
                    break;
                // Prvek ��d� o odstran�n�
                case EE_GUI_SIGNAL_DELETE:
                    DeleteGuiElement( *I_GuiElement );
                    break;
                // My� klikla vedle
                case EE_GUI_SIGNAL_NOTHING:
                default:
                    // Vstup nezpracov�n prvekm
                    b_Processed = 0;
                    break;            
            }
            
            // Dal�� prvek
            I_GuiElement++;
        }
    }
    // Vykreslen� od nejzadn�j��ho po nejp�edn�j��
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    // blendfce
    std::list< EE_GUI_ID_t >::reverse_iterator cI_GuiElementReverse, 
                                               cI_GuiElementEndReverse; 
    cI_GuiElementReverse = mco_GuiElementsZ.rbegin();
    cI_GuiElementEndReverse = mco_GuiElementsZ.rend();
    while( cI_GuiElementReverse != cI_GuiElementEndReverse )
        mco_GuiElements[ *cI_GuiElementReverse++ ]->Draw();    
    
    glPopAttrib();   
}
        
const EE_GUI_BASE_C* EE_GUI_SYSTEM_C::GetGuiElement( EE_GUI_ID_t t_id ) const
{
    std::map< EE_GUI_ID_t, EE_GUI_BASE_C* >::const_iterator cI_GuiElement;
    if( ( cI_GuiElement = mco_GuiElements.find( t_id ) ) == mco_GuiElements.end() )
        EE_ERROR_C( "EE_GUI_SYSTEM_C", 
                    "GetGuiElement", 
                    EE_ERROR_CODES_n::cS_BadIndex, 
                    "Element with index %d not found", t_id );  
    else
        return( cI_GuiElement->second );
}

EE_GUI_BASE_C* EE_GUI_SYSTEM_C::GetGuiElement( EE_GUI_ID_t t_id )
{
    std::map< EE_GUI_ID_t, EE_GUI_BASE_C* >::iterator I_GuiElement;
    if( ( I_GuiElement = mco_GuiElements.find( t_id ) ) == mco_GuiElements.end() )
        return( 0 );       
    else
        return( I_GuiElement->second );
}
