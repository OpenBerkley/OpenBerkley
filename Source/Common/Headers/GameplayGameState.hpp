#ifndef __OPENBERKLEY_GAMEPLAYGAMESTATE_HPP__
#define __OPENBERKELY_GAMEPLATGAMESTATE_HPP__

#include <Game/GameState.hpp>
#include <Renderer/Renderer.hpp>

namespace OpenBerkley
{
	class GameplayInputListener;

	class GameplayGameState : public ZED::Game::GameState
	{
	public:
		GameplayGameState( );
		virtual ~GameplayGameState( );

		virtual ZED_UINT32 Enter( );

		virtual void Render( );
		virtual void Update( const ZED_UINT64 p_ElapsedTime );

		virtual ZED_UINT32 Exit( );

		virtual ZED_CHAR8 *GetName( ) const;

	private:
		ZED::Renderer::Renderer	*m_pRenderer;
		GameplayInputListener	*m_pInputListener;
	};
}

#endif // __OPENBERKLEY_GAMEPLATGAMESTATE_HPP__

