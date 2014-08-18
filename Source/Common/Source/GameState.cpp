#include <GameState.hpp>

namespace OpenBerkley
{
	GameState::~GameState( )
	{
	}

	ZED::Utility::EventRouter * const GameState::GetEventRouter( )
	{
		return m_pEventRouter;
	}
}

