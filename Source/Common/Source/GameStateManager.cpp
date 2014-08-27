#include <GameStateManager.hpp>
#include <System/Debugger.hpp>

namespace OpenBerkley
{
	GameStateManager::GameStateManager( )
	{
	}

	GameStateManager::~GameStateManager( )
	{
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		if( ZED::Game::GameStateManager::Initialise( ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void GameStateManager::Update( const ZED_UINT64 p_DeltaTime )
	{
		ZED::Game::GameStateManager::Update( p_DeltaTime );
	}

	void GameStateManager::Render( )
	{
		ZED::Game::GameStateManager::Render( );
	}

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;
		return Instance;
	}
}

