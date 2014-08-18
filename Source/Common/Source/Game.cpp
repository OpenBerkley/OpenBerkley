#include <Game.hpp>
#include <cstring>
#include <System/Memory.hpp>
#include <GitVersion.hpp>
#include <unistd.h>

namespace OpenBerkely
{
	Game::Game( )
	{
		m_pWindow = ZED_NULL;
		m_pRenderer = ZED_NULL;
		m_pInputManager = ZED_NULL;

		memset( &m_Canvas, 0, sizeof( m_Canvas ) );
		m_Running = ZED_FALSE;
	}

	Game::~Game( )
	{
		zedSafeDelete( m_pInputManager );
		zedSafeDelete( m_pRenderer );
		zedSafeDelete( m_pWindow );
	}

	ZED_UINT32 Game::Initialise( )
	{
		if( this->PreInitialise( ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		m_GameConfiguration.Read( );

		ZED_SINT32 X = 0, Y = 0;
		ZED_UINT32 Width = 0, Height = 0;
		ZED_UINT32 WindowStyle = ZED_WINDOW_STYLE_MINIMISE |
			ZED_WINDOW_STYLE_CLOSE | ZED_WINDOW_STYLE_TITLEBAR |
			ZED_WINDOW_STYLE_MOVE;
		ZED_SINT32 DisplayNumber = 0, ScreenNumber = 0;

		X = m_GameConfiguration.GetXPosition( );
		Y = m_GameConfiguration.GetYPosition( );
		Width = m_GameConfiguration.GetWidth( );
		Height = m_GameConfiguration.GetHeight( );
		DisplayNumber = m_GameConfiguration.GetDisplayNumber( );
		ScreenNumber = m_GameConfiguration.GetScreenNumber( );

		if( m_pWindow->Create( X, Y, Width, Height, DisplayNumber,
			ScreenNumber, WindowStyle ) != ZED_OK )
		{
			zedTrace( "[Open|Berkely::Game::Initialise] <ERROR> "
				"Failed to create window\n" );

			return ZED_FAIL;
		}

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.ColourFormat( ZED_FORMAT_ARGB8 );
		m_Canvas.DepthStencilFormat( ZED_FORMAT_D24S8 );

		if( m_pRenderer->Create( m_Canvas, ( *m_pWindow ) ) != ZED_OK )
		{
			zedTrace( "[Open|Berkely::Game::Initialise] <ERROR> "
				"Failed to create renderer\n" );
			
			return ZED_FAIL;
		}

		// 247 191 11 - Shenmue.com website background colour
		// 60 112 192 -  European Dreamcast Blue

		ZED_FLOAT32 Red = 247.0f / 255.0f;
		ZED_FLOAT32 Green = 191.0f / 255.0f;
		ZED_FLOAT32 Blue = 11.0f / 255.0f;

		m_pRenderer->ClearColour( Red, Green, Blue );
		m_pRenderer->RenderState( ZED_RENDERSTATE_CULLMODE,
			ZED_CULLMODE_NONE );
		m_pRenderer->RenderState( ZED_RENDERSTATE_DEPTH, ZED_ENABLE );

		ZED::System::WINDOWDATA WindowData = m_pWindow->WindowData( );

		if( m_pInputManager->Initialise( WindowData ) != ZED_OK )
		{
			zedTrace( "[Open|Berkely::Game::Initialise] <ERROR> "
				"Failed to set window data for the new input manager\n" );

			return ZED_FAIL;
		}

		m_Keyboard.SetIndividual( );
		m_pInputManager->AddDevice( &m_Keyboard );

		ZED_CHAR8 *pTitle = new ZED_CHAR8[ 1024 ];

		sprintf( pTitle, "Open|Berkley - Version %s [%s]", GIT_BUILD_VERSION,
			GIT_TAG_NAME );
		m_pWindow->Title( pTitle );

		zedSafeDeleteArray( pTitle );

		return ZED_OK;
	}

	ZED_UINT32 Game::Execute( )
	{
		m_Running = ZED_TRUE;

		while( m_Running )
		{
			m_pWindow->Update( );
			m_pInputManager->Update( );
			m_pWindow->FlushEvents( ZED_WINDOW_FLUSH_NONE );

			if( m_pWindow->Resized( ) )
			{
				m_GameConfiguration.SetWidth( m_pWindow->GetWidth( ) );
				m_GameConfiguration.SetHeight( m_pWindow->GetHeight( ) );
			}

			if( m_pWindow->Moved( ) )
			{
				m_GameConfiguration.SetXPosition( m_pWindow->GetXPosition( ) );
				m_GameConfiguration.SetYPosition( m_pWindow->GetYPosition( ) );
			}

			if( m_Keyboard.IsKeyDown( ZED_KEY_ESCAPE ) )
			{
				m_Running = ZED_FALSE;
			}
			
			this->Update( 16667ULL );
			this->Render( );
		}

		m_GameConfiguration.Write( );

		return ZED_OK;
	}

	void Game::Update( const ZED_UINT64 p_MicroSeconds )
	{
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_pRenderer->EndScene( );
	}
}

