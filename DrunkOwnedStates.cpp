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
//------------------------------------------------------------------------QuenchThirst
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

	

	if (pDrunk->Puke())
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "ooh it's noot good ! I go home !";
		pDrunk->NoPuke();
		pDrunk->GetFSM()->ChangeState(GoHomeAndSleepTilRestedD::Instance());
	}
}

void QuenchThirstD::Exit(Drunk* pDrunk)
{
}


bool QuenchThirstD::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_Hello:
		if (pDrunk->Attack())
		{
			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "You are dumb !";
			//send a delayed message myself so that I know when to take the stew
			//out of the oven
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,                  //time delay
				pDrunk->ID(),           //sender ID
				ent_Miner_Bob,           //receiver ID
				Msg_YouAreDumb,        //msg
				NO_ADDITIONAL_INFO);
		}
		return true;

	case Msg_Fight:

		pDrunk->GetFSM()->ChangeState(Attack::Instance());

		return true;
	}
	return false;
}
//------------------------------------------------------methods for GoHomeAndSleepTilRested
GoHomeAndSleepTilRestedD* GoHomeAndSleepTilRestedD::Instance()
{
	static GoHomeAndSleepTilRestedD instance;

	return &instance;
}

void GoHomeAndSleepTilRestedD::Enter(Drunk* pDrunk)
{
	if (pDrunk->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "It's nice to be at home !";

		pDrunk->ChangeLocation(shack);
	}
}

void GoHomeAndSleepTilRestedD::Execute(Drunk* pDrunk)
{
	if (!pDrunk->Fatigue())
	{
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": "
			<< "All mah fatigue has drained away. Time to drink!";

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

//------------------------------------------------------------------------Attack

Attack* Attack::Instance()
{
	static Attack instance;

	return &instance;
}


void Attack::Enter(Drunk* pDrunk)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Let's go to the fight";
}

void Attack::Execute(Drunk* pDrunk)
{
	
	cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Take that !";

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,                  //time delay
		pDrunk->ID(),           //sender ID
		ent_Miner_Bob,           //receiver ID
		Msg_Kick,        //msg
		(int*)pDrunk->LevelFatigue());
}

void Attack::Exit(Drunk* pDrunk)
{
}


bool Attack::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	if ((int*)pDrunk->LevelFatigue()<msg.ExtraInfo) {
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "I win";
	}
	else {
		cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "I loose";
	}
	cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "I go to home for rest";
	pDrunk->GetFSM()->ChangeState(GoHomeAndSleepTilRestedD::Instance());

	return false;
}