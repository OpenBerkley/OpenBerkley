#ifndef __OPENBERKLEY_GAMESTATEMANAGER_HPP__
#define __OPENBERKLEY_GAMESTATEMAANGER_HPP__

#include <Game/GameStateManager.hpp>

namespace OpenBerkley
{
	class GameStateManager : public ZED::Game::GameStateManager
	{
	public:
		GameStateManager( );
		virtual ~GameStateManager( );

		virtual ZED_UINT32 Initialise( );

		static GameStateManager &GetInstance( );

	protected:
		virtual void Update( const ZED_UINT64 p_DeltaTime );
		virtual void Render( );
	};
}

#endif // __OPENBERKLEY_GAMESTATEMANAGER_HPP__

