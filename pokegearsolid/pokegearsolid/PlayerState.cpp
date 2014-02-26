#include "PlayerState.h"
//number of sceens for story
#define numberSceens 2

void causeEffect(Pokemon a_effected, Effect a_effect);

void resolveMove(Pokemon& a_user, Pokemon& a_enemy, int a_move);


PlayerState::PlayerState()
{
	bool setSceen = false;

	curPos.X = 0;
	curPos.Y = 0;
	curPos.Z = 0;

	rendPos.X = 1;
	rendPos.Y = 1;
	rendPos.Z = 0;

	for(int i = 0;i<numberSceens;++i)
	{
		watchedDialogs.push_back(setSceen);
	}
	pikachu.init(L"Solid Chu");
	enemy.init(L"Solid Chu");
}

void PlayerState::setPikachu(Pokemon a_pikachu) {
	pikachu = a_pikachu;
}

Pokemon PlayerState::getPikachu() {
	return pikachu;
}

void PlayerState::setEnemy(Pokemon a_enemy) {
	pikachu = a_enemy;
}

Pokemon PlayerState::getEnemy() {
	return enemy;
}

void PlayerState::decrementPikaPP(int a_move) {
	pikachu.decrementPP(a_move);
}


void PlayerState::decrementEnemyPP(int a_move) {
	enemy.decrementPP(a_move);
}


void PlayerState::randomizeEnemy() {
	int random = rand()%4;
	if(random == 0)
		enemy.init(L"RATATA");
	else if(random == 1)
		enemy.init(L"ZUBAT");
	else if(random == 2)
		enemy.init(L"KOFFING");
	else if(random == 3)
		enemy.init(L"EKANS");
}


void PlayerState::resolveMoveInOrder(bool a_user) {
	if(a_user) {
		resolveMove(pikachu, enemy, playermove);
	}
	else
		resolveMove(enemy, pikachu, enemymove);
}


void PlayerState::initPikachu() {
	pikachu.init(L"Solid Chu");
}


void PlayerState::setPlayerMove(int a_playermove) {
	playermove = a_playermove;
}


int PlayerState::getPlayerMove() {
	return playermove;
}


void PlayerState::setEnemyMove(int a_enemymove) {
	enemymove = a_enemymove;
}


int PlayerState::getEnemyMove() {
	return enemymove;
}


bool PlayerState::setSceen(bool states[],int arraySize)
{
	int length;
	
	if(arraySize<numberSceens)
	{
		length = arraySize;
	}
	else
	{
		length = numberSceens;
	}

	for(int i = 0;i<length;++i)
	{
		watchedDialogs[i] = states[i];
	}

	if(arraySize>numberSceens)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Pos PlayerState::getPos()
{
	return curPos;
}

Pos PlayerState::getRen()
{
	return rendPos;
}

void PlayerState::setPos(int locx,int locy,int renx,int reny)
{
	curPos.X = locx;
	curPos.Y = locy;
	curPos.Z = 0;

	rendPos.X = renx;
	rendPos.Y = reny;
	rendPos.Z = -2.0f;
}


void causeEffect(Pokemon a_effected, Effect a_effect) {
	if(a_effect == BURN) {
		a_effected.setStatus(true,0);
	}
	else if(a_effect == SLEEP) {
		a_effected.setStatus(true,1);
	}
	else if(a_effect == PARALYSIS) {
		a_effected.setStatus(true,2);
	}
	else if(a_effect == POISONED) {
		a_effected.setStatus(true,3);
	}
	else if(a_effect == FROZEN) {
		a_effected.setStatus(true,4);
	}
	else if(a_effect == CONFUSION) {
		a_effected.setStatus(true,5);
	}
	else if(a_effect == INCREASEATTACK) {
		a_effected.setStatChanges(1,0);
	}
	else if(a_effect == INCREASEDEFENSE) {
		a_effected.setStatChanges(1,1);
	}
	else if(a_effect == INCREASESPECATTACK) {
		a_effected.setStatChanges(1,2);
	}
	else if(a_effect == INCREASESPECDEFENSE) {
		a_effected.setStatChanges(1,3);
	}
	else if(a_effect == INCREASESPEED) {
		a_effected.setStatChanges(1,4);
	}
	else if(a_effect == DECREASEATTACK) {
		a_effected.setStatChanges(-1,0);
	}
	else if(a_effect == DECREASEDEFENSE) {
		a_effected.setStatChanges(-1,1);
	}
	else if(a_effect == DECREASESPECATTACK) {
		a_effected.setStatChanges(-1,2);
	}
	else if(a_effect == DECREASESPECDEFENSE) {
		a_effected.setStatChanges(-1,3);
	}
	else if(a_effect == DECREASESPEED) {
		a_effected.setStatChanges(-1,4);
	}
};


void resolveMove(Pokemon& a_user, Pokemon& a_enemy, int a_move) {
	int tempdamage;
	int random = rand()%100;
	bool hitormiss = true;
	if(random > a_user.getMove(a_move).getAccuracy())// Checks if it hits or misses, true for hit, false for miss
		hitormiss = false;
	if(hitormiss) {
		if(a_user.getMove(a_move).getWhichStat() == 0)// Checks to see which stat the move needs, 0 for Attack, 1 for Spec Attack, 2 for no stat
			tempdamage = a_user.getMove(a_move).getDamage()+a_user.getAttack()/5;
		else if(a_user.getMove(a_move).getWhichStat() == 1)
			tempdamage = a_user.getMove(a_move).getDamage()+a_user.getSpecAtt()/5;
		else
			tempdamage = 0;
		if(a_user.getType() == a_user.getMove(a_move).getType()) // STAB
			tempdamage *=1.5;
		if(tempdamage >= a_enemy.getCurHP()) // If it sets the target's health below 0, it just sets it to 0.
			a_enemy.setCurHP(0);
		else
			a_enemy.setCurHP(a_enemy.getCurHP()-tempdamage);
		if(a_user.getMove(a_move).hasEffect()) {// Checks if it causes a status effect
			random = rand()%100;
			if(random <= a_user.getMove(a_move).getChanceEffect()) {// Checks if the status effect happens, 
				if(a_user.getMove(a_move).getTarget())
					causeEffect(a_user, a_user.getMove(a_move).getEffect());
				else
					causeEffect(a_enemy, a_user.getMove(a_move).getEffect());
			}

		}
		if(a_user.getMove(a_move).getName() == L"Self-Destruct")
			a_user.setCurHP(0);
	}
		
};

bool PlayerState::sceenNew(int num)
{
	if(num<watchedDialogs.size())
	{
		return !watchedDialogs[num];
	}
	return false;
}

void PlayerState::setWatched(int num)
{
	watchedDialogs[num] = true;
}