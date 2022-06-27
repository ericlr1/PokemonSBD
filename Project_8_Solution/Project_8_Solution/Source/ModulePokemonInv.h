#ifndef __MODULE_POKEMON_INV_H__
#define __MODULE_POKEMON_INV_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;


class ModulePokemonInv : public Module
{
public:
	// Constructor
	ModulePokemonInv(bool startEnabled);

	// Destructor
	~ModulePokemonInv();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

    void setValues(const char* name, const char* nickname, int health, int attack, int defense, int speed, int specAtk, int specDef, int level, int xp, int iv);
    
    //Fight commands

    void takeDamage(int damage);

    int dealDamage(int lvl, int pow, int atk, int def);

    void defeatedPokemon(int lvl);


    //misc commands

    void heal(int heal);

    void levelUp();

    bool isAlive();

    void printStatus();

    void displayStats();

	bool CleanUp() override;


public:

	int NumOfPokemons = 0;

    const char* name;
    const char* nickname;
    int maxHealth, health, attack, defense, speed, specAtk, specDef;
    int baseHealth, baseAttack, baseDefense, baseSpeed, baseSpecAtk, baseSpecDef;
    int level, xp;
    int iv;


};

#endif //!__MODULE_PLAYER_H_