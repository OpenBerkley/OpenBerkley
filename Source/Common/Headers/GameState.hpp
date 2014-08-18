#ifndef __OPENBERKLEY_GAMESTATE_HPP__
#define __OPENBERKLEY_GAMESTATE_HPP__

#include <System/DataTypes.hpp>
#include <Utility/InputBinder.hpp>
#include <Utility/EventRouter.hpp>

namespace OpenBerkley
{
	class GameState
	{
	public:
		virtual ~GameState( );

		virtual ZED_UINT32 Enter( ) = 0;
		virtual void Render( ) = 0;
		virtual void Update( const ZED_UINT32 p_ElapsedTime ) = 0;
		virtual ZED_UINT32 Exit( ) = 0;

		virtual ZED_CHAR8 *GetName( ) const = 0;

		ZED::Utility::EventRouter * const GetEventRouter( );

	protected:
		ZED::Utility::InputBinder	*m_pInputBinder;
		ZED::Utility::EventRouter	*m_pEventRouter;
	};
}

#endif // __OPENBERKLEY_GAMESTATE_HPP__
