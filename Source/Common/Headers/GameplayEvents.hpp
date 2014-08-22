#ifndef __OPENBERKLEY_GAMEPLAYEVENTS_HPP__
#define __OPENBERKLEY_GAMEPLAYEVENTS_HPP__

#include <Utility/Event.hpp>

namespace OpenBerkley
{
    class GameplayGameState;

    class GameplayInputListener : public ZED::Utility::EventListener
    {
    public:
	GameplayInputListener( );
	virtual ~GameplayInputListener( );

	virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );
	virtual ZED_CHAR8 *GetName( ) const;

	ZED_UINT32 SetGameplayGameState(
	    GameplayGameState * const &p_pGameplayGameState );

    private:
	GameplayGameState *m_pGameplayGameState;
    };
}

#endif // __OPENBERKLEY_GAMEPLAYEVENTS_HPP__

