#include "ModulePokemonInv.h"

#include "Application.h"
#include "ModulePlayer.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/include/SDL_timer.h>
#include <SDL/include/SDL_video.h>
#include <time.h>



//Pokemon
ModulePokemonInv::ModulePokemonInv(bool startEnabled) : Module(startEnabled) 
{
	/*name = "Missing No.";
	nickname = "Missing No.";
	maxHealth = 10;
	health = 10;
	attack = 10;
	defense = 10;
	specDef = 10;
	specAtk = 10;
	level = 1;
	xp = 0;
	baseHealth = health;
	baseAttack = attack;
	baseDefense = defense;
	baseSpecAtk = specAtk;
	baseSpecDef = specDef;
	srand(time(NULL));
	iv = rand() % 16;*/
}

void ModulePokemonInv::setValues(const char* name, const char* nickname, int health, int attack, int defense, int speed, int specAtk, int specDef, int level, int xp, int iv)
{
	App->pokemonInv->name = name;
	App->pokemonInv->nickname = nickname;
	App->pokemonInv->maxHealth = health;
	App->pokemonInv->health = health;
	App->pokemonInv->attack = attack;
	App->pokemonInv->defense = defense;
	App->pokemonInv->specDef = specDef;
	App->pokemonInv->specAtk = specAtk;
	App->pokemonInv->level = level;
	App->pokemonInv->xp = xp;
	App->pokemonInv->baseHealth = health;
	App->pokemonInv->baseAttack = attack;
	App->pokemonInv->baseDefense = defense;
	App->pokemonInv->baseSpecAtk = specAtk;
	App->pokemonInv->baseSpecDef = specDef;
	App->pokemonInv->iv = iv;
}

//Fight commands
void ModulePokemonInv::takeDamage(int damage) {
	health -= damage;
}

int ModulePokemonInv::dealDamage(int lvl, int pow, int atk, int def) {
	int damage = ((2 * lvl / 5 + 2) * pow * atk / def) / 50 + 2;
	return damage;
}

void ModulePokemonInv::defeatedPokemon(int lvl) {
	int xpGain = lvl / 7 + 1;
	xp += xpGain;
	if (xp >= (level ^ 3)) {
		levelUp();
	}
}

//misc commands

void ModulePokemonInv::heal(int heal) {
	health += heal;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void ModulePokemonInv::levelUp() {
	int hpGain = (2 * baseHealth + iv) * level / 100 + 5;
}

bool ModulePokemonInv::isAlive() {
	if (health > 0) {
		return true;
	}
	else {
		return false;
	}
}

void ModulePokemonInv::printStatus() {

}

void ModulePokemonInv::displayStats() {

}




//ModulePokemonInv



ModulePokemonInv::~ModulePokemonInv()
{

}

bool ModulePokemonInv::Start()
{
	bool ret = true;

	
	return ret;
}

Update_Status ModulePokemonInv::Update()
{

	return Update_Status::UPDATE_CONTINUE;

}

Update_Status ModulePokemonInv::PostUpdate()
{

	return Update_Status::UPDATE_CONTINUE;
}


bool ModulePokemonInv::CleanUp() {
	
	return true;
}
