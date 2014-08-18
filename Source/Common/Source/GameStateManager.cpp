#include <GameStateManager.hpp>
#include <GameState.hpp>
#include <System/Time.hpp>

namespace OpenBerkley
{
	GameStateManager::GameStateManager( ) :
		m_Running( ZED_FALSE ),
		m_TotalElapsedTime( 0ULL ),
		m_pRenderer( ZED_NULL )
	{
		ZED::System::StartTime( );
		m_StartTime = ZED::System::GetTimeMiS( );
	}

	GameStateManager::~GameStateManager( )
	{
		this->Quit( );
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		m_Running = ZED_TRUE;

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Execute( )
	{
		if( m_GameStateStack.empty( ) )
		{
			this->Quit( );
			return ZED_FAIL;
		}

		static ZED_UINT64 BeginTime = ZED::System::GetTimeMiS( );
		ZED_UINT64 TimeElapsed = ZED::System::GetTimeMiS( );
		ZED_UINT64 TimeDifference = TimeElapsed - m_StartTime;
		m_TotalElapsedTime = TimeElapsed - BeginTime;
		m_StartTime = TimeElapsed;

		m_GameStateStack.top( )->Update( TimeDifference );

		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );

		m_GameStateStack.top( )->Render( );

		m_pRenderer->EndScene( );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RegisterState(
		GameState * const &p_pGameState )
	{
		if( p_pGameState == ZED_NULL )
		{
			return ZED_FAIL;
		}

		m_GameStateRegistry.insert( p_pGameState );

		zedTrace( "[Open|Berkley::GameStateManager::RegisterState] <INFO> "
			"Added %s to the registry\n", p_pGameState->GetName( ) );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::GetNumberOfStates( ) const
	{
		return m_GameStateRegistry.size( );
	}

	ZED_CHAR8 *GameStateManager::GetStateName( const ZED_UINT32 p_Index ) const
	{
		if( p_Index > m_GameStateRegistry.size( ) )
		{
			zedTrace( "[Open|Berkley::GameStateManager::GetStateName] <ERROR> "
				"Index is larger than the elements in the registry\n" );
			return "\0";
		}

		GameStateSet::const_iterator RegistryIterator =
			m_GameStateRegistry.begin( );

		for( ZED_UINT32 i = 0; i < p_Index; ++i )
		{
			++RegistryIterator;
		}

		return ( *RegistryIterator )->GetName( );
	}

	ZED_UINT32 GameStateManager::ChangeState(
		const ZED_CHAR8 *p_pGameStateName, const ZED_UINT32 p_LevelCount )
	{
		if( this->IsGameStateNameValid( p_pGameStateName ) == ZED_FALSE )
		{
			zedTrace( "[Open|Berkley::GameStateManager::ChangeState] <ERROR> "
				"Unrecognised game state name: %s\n", p_pGameStateName );

			return ZED_FAIL;
		}

		// Pop all states
		if( p_LevelCount == 0 )
		{
			while( !m_GameStateStack.empty( ) )
			{
				this->PopState( );
			}
		}
		else
		{
			ZED_UINT32 LevelCount = p_LevelCount;
			if( p_LevelCount > m_GameStateStack.size( ) )
			{
				zedTrace( "[Open|Berkley::GameStateManager::ChangeState] "
					"<WARN> Too many levels specified for clearing, using the "
					"maximum size allowed\n" );

				LevelCount = m_GameStateStack.size( );
			}

			for( ZED_UINT32 i = 0; i < LevelCount; ++i )
			{
				this->PopState( );
			}
		}

		return this->PushState( p_pGameStateName );
	}

	ZED_UINT32 GameStateManager::PushState( const ZED_CHAR8 *p_pGameStateName )
	{
		if( this->IsGameStateNameValid( p_pGameStateName ) == ZED_FALSE )
		{
			return ZED_FAIL;
		}

		GameStateSet::const_iterator RegistryIterator =
			m_GameStateRegistry.begin( );

		for( ; RegistryIterator != m_GameStateRegistry.end( );
			++RegistryIterator )
		{
			if( strncmp( ( *RegistryIterator )->GetName( ), p_pGameStateName,
				strlen( p_pGameStateName ) ) == 0 )
			{
				break;
			}
		}

		m_GameStateStack.push( ( *RegistryIterator ) );

		if( m_GameStateStack.top( )->Enter( ) != ZED_OK )
		{
			this->PopState( );
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void GameStateManager::PopState( )
	{
		if( !m_GameStateStack.empty( ) )
		{
			m_GameStateStack.pop( );
		}
	}

	ZED_UINT32 GameStateManager::SetInputBinder(
		ZED::Utility::InputBinder * const &p_pInputBinder )
	{
		if( p_pInputBinder )
		{
			// REMINDER
			// There should be an input listener here!
			return ZED_OK;
		}

		return ZED_FAIL;
	}

	void GameStateManager::Quit( )
	{
		while( !m_GameStateStack.empty( ) )
		{
			this->PopState( );
		}

		m_Running = ZED_FALSE;
	}

	ZED_BOOL GameStateManager::IsRunning( ) const
	{
		return m_Running;
	}

	ZED::Renderer::Renderer * const GameStateManager::GetRenderer( )
	{
		return m_pRenderer;
	}

	ZED_UINT32 GameStateManager::SetRenderer(
		ZED::Renderer::Renderer * const &p_pRenderer )
	{
		if( p_pRenderer )
		{
			m_pRenderer = p_pRenderer;

			return ZED_OK;
		}

		return ZED_FAIL;
	}

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;

		return Instance;
	}

	ZED_BOOL GameStateManager::IsGameStateNameValid(
		const ZED_CHAR8 *p_pGameStateName ) const
	{
		GameStateSet::const_iterator RegistryItr =
			m_GameStateRegistry.begin( );

		for( ; RegistryItr != m_GameStateRegistry.end( ); ++RegistryItr )
		{
			if( strncmp( ( *RegistryItr )->GetName( ), p_pGameStateName,
				strlen( p_pGameStateName ) ) == 0 )
			{
				return ZED_TRUE;
			}
		}

		return ZED_FALSE;
	}
}

