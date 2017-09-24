#include "Drunk.h"

bool Drunk::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Drunk::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Drunk::Attack()const
{
	if (m_iAttack >= AttackLevel) { return true; }

	return false;
}

bool Drunk::Fatigue()const
{
	if (m_iFatigue > 0)
	{
		return true;
	}

	return false;
}

bool Drunk::Puke()const
{
	if (m_iPuke >= PukeLevel) { return true; }

	return false;
}