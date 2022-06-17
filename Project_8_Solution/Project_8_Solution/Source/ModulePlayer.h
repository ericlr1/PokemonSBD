#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	
	bool CleanUp() override;

	void CameraFollowPlayer();


public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The number related to the orientation of the player
	int facing;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* text_box = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation deadAnim, deadfootAnim;											//Muerte Player

	Animation invisibleAnim, invisibleUpAnim;									//Invisible para cuando mueres

	Animation idleupAnim, idleupfootAnim;										//Quieto-Arriba
	Animation idledownAnim, idledownfootAnim;									//Quieto-Abajo
	Animation idlerightAnim, idlerightfootAnim;									//Quieto-Derecha
	Animation idleleftAnim, idleleftfootAnim;									//Quieto-Izquierda

	Animation idlerightupAnim, idlerightupfootAnim;								//Quieto-Derecha-Arriba
	Animation idlerightdownAnim, idlerightdownfootAnim;							//Quieto-Derecha-Abajo
	Animation idleleftupAnim, idleleftupfootAnim;								//Quieto-Izquierda-Arriba
	Animation idleleftdownAnim, idleleftdownfootAnim;							//Quieto-Izquierda-Abajo

	Animation upAnim, upfootAnim;												//Arriba
	Animation downAnim, downfootAnim;											//Abajo
	Animation leftAnim, leftfootAnim;											//Izquierda
	Animation rightAnim, rightfootAnim;											//Derecha
	Animation rightupAnim, rightupfootAnim;										//Derecha-Arriba
	Animation rightdownAnim, rightdownfootAnim;									//Derecha-Abajo
	Animation leftupAnim, leftupfootAnim;										//Izquierda-Arriba
	Animation leftdownAnim, leftdownfootAnim;									//Izquierda-Abajo
	

	// The player's collider
	Collider* collider = nullptr;
	Collider* collider_foot = nullptr;
	Collider* collider_camara = nullptr; //Creo que sobra

	// Font score index
	int pokemonFont = -1;
	char demoText[10] = { "\0" };	

	//God mode
	bool godMode = false;
	bool shortcuts = false;

	// Spawn point where it needs to spawn
	int spawnPoint;

	// Variable to calculate seconds
	int t1 = 0;

	//Music & FX
	uint shotFx = 0;
	uint playerDeadFx = 0;
	uint heavyRifleFx = 0;
	uint weaponPickUpFx = 0;
	uint throwGrenadeFx = 0;

	//Immovable variable
	bool immovable = false;

	//Destroyed variable
	bool destroyed = false;

	//In conversation/text variable
	bool text_on_screen = false;

	int variable = 0;
};

#endif //!__MODULE_PLAYER_H_