#ifndef DRUNK_OWNED_STATES_H
#define DRUNK_OWNED_STATES_H

#include "fsm/State.h"

class Drunk;
struct Telegram;


class QuenchThirstD : public State<Drunk>
{
private:
	QuenchThirstD(){}
	QuenchThirstD(const QuenchThirstD&);
	QuenchThirstD& operator=(const QuenchThirstD&);

public:
	static QuenchThirstD* Instance();

	virtual void Enter(Drunk* drunk);

	virtual void Execute(Drunk* drunk);	

	virtual void Exit(Drunk* drunk);

	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};


class GoHomeAndSleepTilRestedD : public State<Drunk>
{
private:
	GoHomeAndSleepTilRestedD() {}
	GoHomeAndSleepTilRestedD(const GoHomeAndSleepTilRestedD&);
	GoHomeAndSleepTilRestedD& operator=(const GoHomeAndSleepTilRestedD&);

public:
	static GoHomeAndSleepTilRestedD* Instance();

	virtual void Enter(Drunk* drunk);

	virtual void Execute(Drunk* drunk);

	virtual void Exit(Drunk* drunk);

	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

class Attack : public State<Drunk>
{
private:
	Attack() {}
	Attack(const Attack&);
	Attack& operator=(const Attack&);

public:
	static Attack* Instance();

	virtual void Enter(Drunk* drunk);

	virtual void Execute(Drunk* drunk);

	virtual void Exit(Drunk* drunk);

	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};


#endif