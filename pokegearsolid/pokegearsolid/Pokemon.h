#pragma once

enum Species {
	PIKACHU,
	GRUNT,
	RATATA, 
	ZUBAT, 
	KOFFING, 
	EKANS, 
	MEWTWO
};

enum Effect {
	INCREASEATTACK,
	INCREASEDEFENSE,
	INCREASESPECATTACK,
	INCREASESPECDEFENSE,
	INCREASESPEED,
	DECREASEATTACK,
	DECREASEDEFENSE,
	DECREASESPECATTACK,
	DECREASESPECDEFENSE,
	DECREASESPEED,
	BURN,
	SLEEP,
	PARALYSIS,
	POISONED,
	FROZEN,
	CONFUSION,
	NOEFFECT
};

enum Type {
	NORMAL,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BUG,
	GHOST,
	STEEL,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK,
	FAIRY,
	QUESTIONMARK,
	NOTYPE
};

class Move {
private:
	wchar_t* name;
	Type type;
	int priority;
	bool hasaneffect;
	bool target; // true is self, false is enemy
	int damage;
	int statdamage; // 0 is attack, 1 is spec attack, 2 is no damage
	Effect effect;
	int chanceeffect;
	int currentpp, maxpp;
	int accuracyoutof100;
public:
	Move					();
	~Move					();
	Move					(wchar_t* a_name, Type a_type, int a_pri,bool a_hasaneffect,bool a_target,int a_damage,int a_attackstat,Effect a_effect,int a_chanceeffect,int a_curpp,int a_maxpp,int a_accuracy);
	wchar_t* getName		();
	Type getType			();
	int getPriority			();
	bool hasEffect			();
	bool getTarget			();
	int getDamage			();
	int getWhichStat		();
	Effect getEffect		();
	int getChanceEffect		();
	int getCurPP			();
	int getMaxPP			();
	int getAccuracy			();
	void setName			(wchar_t*);
	void setType			(Type);
	void setPriority		(int);
	void setEffectBool		(bool);
	void setTarget			(bool);
	void setDamage			(int);
	void setWhichStat		(int);
	void setEffect			(Effect);
	void setChanceEffect	(int);
	void setCurPP			(int);
	void setMaxPP			(int);
	void setAccuracy		(int);
};


class Pokemon {
private:
	wchar_t* name;
	Species species;
	Type type;
	Type type2;
	int curhp, maxhp;
	int attack;
	int defense;
	int specatt;
	int specdef;
	int speed;
	int combatstatchanges[5];
	bool statuseffects[6];
	Move movelist[4];
public:
	Pokemon();
	~Pokemon();
	Pokemon(wchar_t* a_name, Species a_species, Type a_type, Type a_type2, int a_curhp, int a_maxhp, int a_attack, int a_defense, int a_specattack, int a_specdefense, int a_speed, Move a_move1, Move a_move2, Move a_move3, Move a_move4);
	void init			(wchar_t* a_name);
	wchar_t* getName	();
	Species getSpecies	();
	Type getType		();
	Type getType2		();
	int getCurHP		();
	int getMaxHP		();
	int getAttack		();
	int getDefense		();
	int getSpecAtt		();
	int getSpecDef		();
	int getSpeed		();
	int getStatChanges	(int);
	bool getStatus		(int);
	Move getMove		(int);
	void setName		(wchar_t*);
	void setSpecies		(Species);
	void setType		(Type);
	void setType2		(Type);
	void setCurHP		(int);
	void setMaxHP		(int);
	void setAttack		(int);
	void setDefense		(int);
	void setSpecAtt		(int);
	void setSpecDef		(int);
	void setSpeed		(int);
	void setStatChanges	(int, int);
	void setStatus		(bool, int);
	void setMove		(Move, int);
	void decrementPP	(int);
};

