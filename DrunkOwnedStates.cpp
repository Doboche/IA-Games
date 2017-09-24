#include "DrunkOwnedStates.h"
#include "fsm/State.h"
#include "Drunk.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

QuenchThirstD* QuenchThirstD::Instance()
{
	static QuenchThirstD instance;
	return &instance;
}

void QuenchThirstD::Enter(Drunk* pDrunk)
{
	if (pDrunk->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Go to the saloon !";

		pDrunk->ChangeLocation(saloon);
	}
}

void QuenchThirstD::Execute(Drunk* pDrunk)
{
	pDrunk->Drink();
	pDrunk->IncreaseFatigue();
	cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Ahh nice whiskey !";

	if (pDrunk->Attack())
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "I will kick your ass !";
		pDrunk->NoAgressive();
	}

	if (pDrunk->Puke())
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "ooh it's noot good !";
		pDrunk->NoPuke();
		pDrunk->GetFSM()->ChangeState(GoHomeAndSleepTilRestedD::Instance());
	}
}

void QuenchThirstD::Exit(Drunk* pDrunk)
{
	cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": "
		<< "I go home";
}


bool QuenchThirstD::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

GoHomeAndSleepTilRestedD* GoHomeAndSleepTilRestedD::Instance()
{
	static GoHomeAndSleepTilRestedD instance;

	return &instance;
}

void GoHomeAndSleepTilRestedD::Enter(Drunk* pDrunk)
{
	if (pDrunk->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "I'm coming home !";

		pDrunk->ChangeLocation(shack);
	}
}

void GoHomeAndSleepTilRestedD::Execute(Drunk* pDrunk)
{
	if (!pDrunk->Fatigue())
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": "
			<< "All mah fatigue has drained away. Time drink!";

		pDrunk->GetFSM()->ChangeState(QuenchThirstD::Instance());
	}

	else
	{
		//sleep
		pDrunk->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "ZZZZ... ";
	}
}

void GoHomeAndSleepTilRestedD::Exit(Drunk* pDrunk)
{
}

bool GoHomeAndSleepTilRestedD::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}