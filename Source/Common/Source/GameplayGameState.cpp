#include <GameplayGameState.hpp>
#include <GameplayEvents.hpp>
#include <GameStateManager.hpp>
#include <System/Debugger.hpp>
#include <System/Memory.hpp>
#include <Utility/InputBinder.hpp>
#include <Utility/EventRouter.hpp>
#include <Utility/Events.hpp>
#include <CommonStates.hpp>

namespace OpenBerkley
{
	GameplayGameState::GameplayGameState( ) :
		m_pRenderer( ZED_NULL ),
		m_pInputListener( new GameplayInputListener( ) )
	{
		m_pInputBinder = new ZED::Utility::InputBinder( );
		m_pEventRouter = new ZED::Utility::EventRouter( "Gameplay", ZED_TRUE,
			2 );
	}

	GameplayGameState::~GameplayGameState( )
	{
		zedSafeDelete( m_pEventRouter );
		zedSafeDelete( m_pInputBinder );
	}

	ZED_UINT32 GameplayGameState::Enter( )
	{
		m_pRenderer = GameStateManager::GetInstance( ).GetRenderer( );

		ZED_FLOAT32 Red = 247.0f / 255.0f;
		ZED_FLOAT32 Green = 191.0f / 255.0f;
		ZED_FLOAT32 Blue = 11.0f / 255.0f;

		m_pRenderer->ClearColour( Red, Green, Blue );

		m_pInputBinder->BindKey( ZED_KEY_ESCAPE, STATE_EXIT );

		m_pInputListener->SetGameplayGameState( this );

		GameStateManager::GetInstance( ).SetInputBinder(
			m_pInputBinder );

		m_pEventRouter->Add( m_pInputListener,
			ZED::Utility::ActionInputEventType );

		return ZED_OK;
	}

	void GameplayGameState::Render( )
	{
	}

	void GameplayGameState::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	ZED_UINT32 GameplayGameState::Exit( )
	{
		GameStateManager::GetInstance( ).PopState( );

		return ZED_OK;
	}


	ZED_CHAR8 *GameplayGameState::GetName( ) const
	{
		return "Gameplay";
	}
}
