#include <GameplayEvents.hpp>
#include <Utility/Events.hpp>
#include <CommonStates.hpp>
#include <Arithmetic/Arithmetic.hpp>
#include <GameplayGameState.hpp>
#include <System/Debugger.hpp>

namespace OpenBerkley
{
    GameplayInputListener::GameplayInputListener( ) :
	m_pGameplayGameState( ZED_NULL )
    {
    }

    GameplayInputListener::~GameplayInputListener( )
    {
    }

    ZED_BOOL GameplayInputListener::HandleEvent(
	const ZED::Utility::Event &p_Event )
    {
	if( p_Event.Type( ).ID( ) == ZED::Utility::ActionInputEventType.ID( ) )
	{
	    ZED::Utility::ActionInputEventData *pActionData =
		p_Event.Data< ZED::Utility::ActionInputEventData >( );

	    ZED_UINT32 Action = 0;
	    ZED_FLOAT32 ActionValue = 0.0f;

	    pActionData->GetAction( Action, ActionValue );

	    switch( Action )
	    {
		case STATE_EXIT:
		{
		    if( ZED::Arithmetic::Equal( ActionValue, 1.0f ) )
		    {
			m_pGameplayGameState->Exit( );
		    }

		    return ZED_TRUE;
		}
	    }
	}

	return ZED_FALSE;
    }

    ZED_CHAR8 *GameplayInputListener::GetName( ) const
    {
	return "Gameplay input listener";
    }

    ZED_UINT32 GameplayInputListener::SetGameplayGameState(
	GameplayGameState * const &p_pGameplayGameState )
    {
	if( p_pGameplayGameState )
	{
	    m_pGameplayGameState = p_pGameplayGameState;
	    return ZED_OK;
	}

	return ZED_FAIL;
    }
}

