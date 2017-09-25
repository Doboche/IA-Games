#ifndef DRUNK_H
#define DRUNK_H

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkOwnedStates.h"
#include "fsm/StateMachine.h"


template <class entity_type> class State;

struct Telegram;

const int TirednessThresholdD = 5;
const int PukeLevel = 8;

class Drunk : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Drunk>*  m_pStateMachine;

	location_type         m_Location;

	int m_iPuke;
	int m_iFatigue;

public:

	Drunk(int id) :m_Location(shack),
		m_iPuke(0),
		m_iFatigue(0),
		BaseGameEntity(id)

	{
		m_pStateMachine = new StateMachine<Drunk>(this);

		m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRestedD::Instance());

	}

	~Drunk() { delete m_pStateMachine; }

	void Update();

	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Drunk>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool		  Thirsty()const;
	void 		  Drink() { m_iPuke += 1; }
	bool 		  Attack()const;
	void 		  NoAgressive() { m_iFatigue = 0; }
	bool 		  Puke()const;
	void 		  NoPuke() { m_iPuke = 0; }

	bool          Fatigue()const;
	int			  LevelFatigue()const { return m_iFatigue; }
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

};

#endif