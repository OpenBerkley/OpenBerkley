#include <SplashScreenState.hpp>
#include <GameStateManager.hpp>
#include <Utility/EventRouter.hpp>

namespace OpenBerkley
{
	SplashScreenState::SplashScreenState( ) :
		m_pRenderer( ZED_NULL ),
		m_ElapsedTime( 0ULL ),
		m_Finished( ZED_FALSE )
	{
		m_pEventRouter = new ZED::Utility::EventRouter( "Splash Screen",
			ZED_TRUE, 2 );
	}

	SplashScreenState::~SplashScreenState( )
	{
	}

	ZED_UINT32 SplashScreenState::Enter( )
	{
		ZED::Utility::SetGlobalEventRouter( this->m_pEventRouter );

		// Dreamcast boot logo background colour is 192, 192, 192
		ZED_FLOAT32 Colour = 192.0f / 255.0f;
		GameStateManager::GetInstance( ).GetRenderer( )->ClearColour(
			Colour, Colour, Colour );

		return ZED_OK;
	}

	void SplashScreenState::Render( )
	{
	}

	void SplashScreenState::Update( const ZED_UINT64 p_DeltatTime )
	{
		m_ElapsedTime += p_DeltatTime;

		if( m_ElapsedTime > 1000000ULL )
		{
			GameStateManager::GetInstance( ).ChangeState( "Gameplay" );
		}
	}

	ZED_UINT32 SplashScreenState::Exit( )
	{
		return ZED_OK;
	}

	ZED_CHAR8 *SplashScreenState::GetName( ) const
	{
		return "Splash Screen";
	}
}

