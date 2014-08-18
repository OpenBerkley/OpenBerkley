#ifndef __OPENBERKLEY_GAMESTATEMANAGER_HPP__
#define __OPENBERKLEY_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <Renderer/Renderer.hpp>
#include <Utility/InputBinder.hpp>
#include <stack>
#include <set>

namespace OpenBerkley
{
	class GameState;

	const ZED_FLOAT64 OneOverMillion = 1.0d / 1000000.0d;

	class GameStateManager
	{
	public:
		GameStateManager( );
		~GameStateManager( );

		ZED_UINT32 Initialise( );

		ZED_UINT32 Execute( );

		ZED_UINT32 RegisterState( GameState * const &p_pGameState );
		ZED_UINT32 GetNumberOfStates( ) const;
		ZED_CHAR8 *GetStateName( const ZED_UINT32 p_Index ) const;

		ZED_UINT32 ChangeState( const ZED_CHAR8 *p_pGameStateName,
			const ZED_UINT32 p_LevelCount = 0 );

		ZED_UINT32 PushState( const ZED_CHAR8 *p_pGameStateName );
		void PopState( );

		ZED_UINT32 SetInputBinder(
			ZED::Utility::InputBinder * const &p_pInputBinder );
	
		void Quit( );

		ZED_BOOL IsRunning( ) const;

		ZED::Renderer::Renderer * const GetRenderer( );
		ZED_UINT32 SetRenderer( ZED::Renderer::Renderer * const &p_pRenderer );

		ZED_FLOAT64 GetTotalElapsedTimeAsFloat64( ) const;
		ZED_UINT32 GetTotalElapsedTimeAsUInt64( ) const;

		static GameStateManager &GetInstance( );

	private:
		typedef std::stack< GameState * > GameStateStack;
		typedef std::set< GameState * > GameStateSet;

		ZED_BOOL IsGameStateNameValid(
			const ZED_CHAR8 *p_pGameStateName ) const;

		GameStateStack	m_GameStateStack;
		GameStateSet	m_GameStateRegistry;
		ZED_BOOL		m_Running;
		ZED_UINT64		m_StartTime;
		ZED_UINT64		m_TotalElapsedTime;

		ZED::Renderer::Renderer	*m_pRenderer;
	};
}

#endif // __OPENBERKLEY_GAMESATEMANAGER_HPP__

