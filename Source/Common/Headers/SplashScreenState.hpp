#ifndef __OPENBERKLEY_SPLASHSCREENSTATE_HPP__
#define __OPENBERKLEY_SPLASHSCREENSTATE_HPP__

#include <Game/GameState.hpp>
#include <Renderer/Renderer.hpp>

namespace OpenBerkley
{
	class SplashScreenState : public ZED::Game::GameState
	{
	public:
		SplashScreenState( );
		virtual ~SplashScreenState( );

		virtual ZED_UINT32 Enter( );

		virtual void Render( );
		virtual void Update( const ZED_UINT64 p_DeltaTime );

		virtual ZED_UINT32 Exit( );

		virtual ZED_CHAR8 *GetName( ) const;

	private:
		ZED::Renderer::Renderer	*m_pRenderer;

		ZED_UINT64	m_ElapsedTime;

		ZED_BOOL	m_Finished;
	};
}

#endif // __OPENBERKLEY_SPLASHSCREENSTATE_HPP__

