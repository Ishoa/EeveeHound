#pragma once
#include "Pokemon.h"


  //////////////////////////////////////////
 // Move class stuff                     //
//////////////////////////////////////////

Move::Move() {

}


Move::~Move() {

}


Move::Move(wchar_t* a_name, Type a_type, int a_pri,bool a_hasaneffect,bool a_target,int a_damage,int a_attackstat,Effect a_effect,int a_chanceeffect,int a_curpp,int a_maxpp,int a_accuracy) {
	setName(a_name);
	setType(a_type);
	setPriority(a_pri);
	setEffectBool(a_hasaneffect);
	setTarget(a_target);
	setDamage(a_damage);
	setWhichStat(a_attackstat);
	setEffect(a_effect);
	setChanceEffect(a_chanceeffect);
	setCurPP(a_curpp);
	setMaxPP(a_maxpp);
	setAccuracy(a_accuracy);
}


int Move::getPriority() {
	return priority;
}


wchar_t* Move::getName() {
	return name;
}


Type Move::getType() {
	return type;
}


bool Move::hasEffect() {
	return hasaneffect;
}


bool Move::getTarget() {
	return target;
}


int Move::getDamage() {
	return damage;
}


int Move::getWhichStat() {
	return statdamage;
}


Effect Move::getEffect() {
	return effect;
}


int Move::getChanceEffect() {
	return chanceeffect;
}


int Move::getCurPP() {
	return currentpp;
}


int Move::getMaxPP() {
	return maxpp;
}


int Move::getAccuracy() {
	return accuracyoutof100;
}


void Move::setName(wchar_t* a_name) {
	name = a_name;
}


void Move::setType(Type a_type) {
	type = a_type;
}


void Move::setPriority(int a_pri) {
	priority = a_pri;
}


void Move::setEffectBool(bool a_effect) {
	hasaneffect = a_effect;
}


void Move::setTarget(bool a_target) {
	target = a_target;
}


void Move::setDamage(int a_damage) {
	damage = a_damage;
}


void Move::setWhichStat(int a_statdamage) {
	statdamage = a_statdamage;
}


void Move::setEffect(Effect a_effect) {
	effect = a_effect;
}


void Move::setChanceEffect(int a_chance) {
	chanceeffect = a_chance;
}


void Move::setCurPP(int a_curPP) {
	currentpp = a_curPP;
}


void Move::setMaxPP(int a_maxpp) {
	maxpp = a_maxpp;
}


void Move::setAccuracy(int a_accu) {
	accuracyoutof100 = a_accu;
}


  //////////////////////////////////////////
 // Pokemon class stuff                  //
//////////////////////////////////////////

Pokemon::Pokemon() {

}


Pokemon::~Pokemon() {

}


Pokemon::Pokemon(wchar_t* a_name, Species a_species, Type a_type, Type a_type2, int a_curhp, int a_maxhp, int a_attack, int a_defense, int a_specattack, int a_specdefense, int a_speed, Move a_move1, Move a_move2, Move a_move3, Move a_move4) {
	setName(a_name);
	setSpecies(a_species);
	setType(a_type);
	setType2(a_type2);
	setCurHP(a_curhp);
	setMaxHP(a_maxhp);
	setAttack(a_attack);
	setDefense(a_defense);
	setSpecAtt(a_specattack);
	setSpecDef(a_specdefense);
	setSpeed(a_speed);
	for(int i = 0; i < 5; ++i)
		combatstatchanges[i] = 0;
	for(int i = 0; i < 6; ++i)
		statuseffects[i] = false;
	setMove(a_move1, 0);
	setMove(a_move2, 1);
	setMove(a_move3, 2);
	setMove(a_move4, 3);

}


void Pokemon::init(wchar_t* a_name) {
	if(a_name == L"Solid Chu") {
		setAttack(55);
		setCurHP(35);
		setDefense(30);
		setMaxHP(35);
		setName(a_name);
		setSpecAtt(50);
		setSpecDef(40);
		setSpeed(90);
		for(int i = 0; i < 5; ++i)
			setStatChanges(0, i);
		setSpecies(PIKACHU);
		setMove(Move(L"Thunder Shock",ELECTRIC, 0,true,false,40,1,PARALYSIS,10,30,30,100) , 0);
		setMove(Move(L"Quick Attack",NORMAL, 1,false,false,40,0,NOEFFECT,0,30,30,100) , 1);
		setMove(Move(L"Thunder Wave",ELECTRIC, 0,true,false,0,2,PARALYSIS,100,20,20,100) , 2);
		setMove(Move(L"Surf",WATER, 0,false,false,90,1,NOEFFECT,0,15,15,100) , 3);
		setType(ELECTRIC);
		setType2(NOTYPE);
	}
	else if(a_name == L"RATATA") {
		setAttack(56);
		setCurHP(30);
		setDefense(35);
		setMaxHP(30);
		setName(a_name);
		setSpecAtt(25);
		setSpecDef(35);
		setSpeed(72);
		for(int i = 0; i < 5; ++i)
			setStatChanges(0, i);
		setSpecies(RATATA);
		setMove(Move(L"Hyper Fang",NORMAL, 0,false,false,80,0,NOEFFECT,0,15,15,90) , 0);
		setMove(Move(L"Quick Attack",NORMAL, 1,false,false,40,0,NOEFFECT,0,30,30,100) , 1);
		setMove(Move(L"Tackle",NORMAL, 0,false,false,50,0,NOEFFECT,0,35,35,100) , 2);
		setMove(Move(L"Tail Whip",NORMAL, 0,true,false,0,2,DECREASEDEFENSE,100,30,30,100) , 3);
		setType(NORMAL);
		setType2(NOTYPE);
	}
	else if(a_name == L"ZUBAT") {
		setAttack(45);
		setCurHP(40);
		setDefense(35);
		setMaxHP(40);
		setName(a_name);
		setSpecAtt(30);
		setSpecDef(40);
		setSpeed(55);
		for(int i = 0; i < 5; ++i)
			setStatChanges(0, i);
		setSpecies(ZUBAT);
		setMove(Move(L"Bite",DARK, 0,false,false,60,0,NOEFFECT,0,25,25,100) , 0);
		setMove(Move(L"Wing Attack",FLYING, 0,false,false,60,0,NOEFFECT,0,35,35,100) , 1);
		setMove(Move(L"Astonish",GHOST, 0,true,false,30,1,NOEFFECT,0,15,15,100) , 2);
		setMove(Move(L"Bite",DARK, 0,false,false,60,0,NOEFFECT,0,25,25,100) , 3);
		setType(POISON);
		setType2(FLYING);
	}
	else if(a_name == L"KOFFING") { 
		setAttack(65);
		setCurHP(40);
		setDefense(95);
		setMaxHP(40);
		setName(a_name);
		setSpecAtt(60);
		setSpecDef(45);
		setSpeed(35);
		for(int i = 0; i < 5; ++i)
			setStatChanges(0, i);
		setSpecies(KOFFING);
		setMove(Move(L"Tackle",NORMAL, 0,false,false,50,0,NOEFFECT,0,35,35,100) , 0);
		setMove(Move(L"Self-Destruct",NORMAL, 0,false,false,200,0,NOEFFECT,0,5,5,100) , 1); // Make sure to have a special case in resolve move
		setMove(Move(L"Tackle",NORMAL, 0,false,false,50,0,NOEFFECT,0,35,35,100) , 2);
		setMove(Move(L"Tackle",NORMAL, 0,false,false,50,0,NOEFFECT,0,35,35,100) , 3);
		setType(POISON);
		setType2(NOTYPE);
	}
	else if(a_name == L"EKANS") {
		setAttack(60);
		setCurHP(105);
		setDefense(44);
		setMaxHP(35);
		setName(a_name);
		setSpecAtt(40);
		setSpecDef(54);
		setSpeed(55);
		for(int i = 0; i < 5; ++i)
			setStatChanges(0, i);
		setSpecies(EKANS);
		setMove(Move(L"Wrap",NORMAL, 0,false,false,15,0,NOEFFECT,0,20,20,90) , 0);
		setMove(Move(L"Poison Sting",POISON, 0,false,false,15,0,NOEFFECT,0,35,35,100) , 1);
		setMove(Move(L"Bite",DARK, 0,false,false,60,0,NOEFFECT,0,25,25,100) , 2);
		setMove(Move(L"Acid",POISON, 0,false,false,40,1,NOEFFECT,0,30,30,100) , 3);
		setType(POISON);
		setType2(NOTYPE);
	}
	//else if(a_name == L"GRUNT") { // Not done
	//	setAttack(56);
	//	setCurHP(30);
	//	setDefense(35);
	//	setMaxHP(30);
	//	setName(a_name);
	//	setSpecAtt(25);
	//	setSpecDef(35);
	//	setSpeed(72);
	//	for(int i = 0; i < 5; ++i)
	//		setStatChanges(0, i);
	//	setSpecies(RATATA);
	//	setMove(Move(L"Hyper Fang",NORMAL, 0,false,false,80,0,NOEFFECT,0,15,15,90) , 0);
	//	setMove(Move(L"Quick Attack",NORMAL, 1,false,false,40,0,NOEFFECT,0,30,30,100) , 1);
	//	setMove(Move(L"Thunder Shock3",ELECTRIC, 0,true,false,40,1,PARALYSIS,10,30,30,100) , 2);
	//	setMove(Move(L"Thunder Shock4",ELECTRIC, 0,true,false,40,1,PARALYSIS,10,30,30,100) , 3);
	//	setType(NORMAL);
	//	setType2(NOTYPE);
	//}
}


wchar_t* Pokemon::getName() {
	return name;
}


Species Pokemon::getSpecies() {
	return species;
}


Type Pokemon::getType() {
	return type;
}


Type Pokemon::getType2() {
	return type2;
}


int Pokemon::getCurHP() {
	return curhp;
}


int Pokemon::getMaxHP() {
	return maxhp;
}


int Pokemon::getAttack() {
	return attack;
}


int Pokemon::getDefense() {
	return defense;
}


int Pokemon::getSpecAtt() {
	return specatt;
}


int Pokemon::getSpecDef() {
	return specdef;
}


int Pokemon::getSpeed() {
	return speed;
}


int Pokemon::getStatChanges(int a_stat) {// 0 attack, 1 defense, 2 specattack, 3 specattack, 4 speed
	return combatstatchanges[a_stat];
}


bool Pokemon::getStatus(int a_status) {// 0 Burn, 1 Sleep, 2 Paralysis, 3 Poison, 4 Frozen, 5 Confusion 
	return statuseffects[a_status];
}


Move Pokemon::getMove(int a_index) {
	return movelist[a_index];
}


void Pokemon::setName(wchar_t* a_name) {
	name = a_name;
}


void Pokemon::setSpecies(Species a_species) {
	species = a_species;
}


void Pokemon::setType(Type a_type) {
	type = a_type;
}


void Pokemon::setType2(Type a_type2) {
	type2 = a_type2;
}


void Pokemon::setCurHP(int a_curhp) {
	curhp = a_curhp;
}


void Pokemon::setMaxHP(int a_maxhp) {
	maxhp = a_maxhp;
}


void Pokemon::setAttack(int a_attack) {
	attack = a_attack;
}


void Pokemon::setDefense(int a_defense) {
	defense = a_defense;
}


void Pokemon::setSpecAtt(int a_specatt) {
	specatt = a_specatt;
}


void Pokemon::setSpecDef(int a_specdef) {
	specdef = a_specdef;
}


void Pokemon::setSpeed(int a_speed) {
	speed = a_speed;
}


void Pokemon::setStatChanges(int a_level, int a_stat) {// 0 attack, 1 defense, 2 specattack, 3 specdefense, 4 speed
	int tempcheck = a_level+getStatChanges(a_stat);
	if(tempcheck < -6)
		combatstatchanges[a_stat] = -6;
	else if(tempcheck > 6)
		combatstatchanges[a_stat] = 6;
	else
		combatstatchanges[a_stat] = tempcheck;
}


void Pokemon::setStatus(bool a_status, int a_statuschoice) {// 0 Burn, 1 Sleep, 2 Paralysis, 3 Poison, 4 Frozen, 5 Confusion 
	statuseffects[a_statuschoice] = a_status;
}


void Pokemon::setMove(Move a_move, int a_index) {
	movelist[a_index] = a_move;
}


void Pokemon::decrementPP(int a_whichmove) {
	if(movelist[a_whichmove].getCurPP() > 0)
		movelist[a_whichmove].setCurPP(movelist[a_whichmove].getCurPP()-1);
}