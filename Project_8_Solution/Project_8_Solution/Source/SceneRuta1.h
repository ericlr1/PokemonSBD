#pragma once
#ifndef __SCENE_RUTA1_H__
#define __SCENE_RUTA1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneRuta1 : public Module
{
public:
	//Constructor
	SceneRuta1(bool startEnabled);

	//Destructor
	~SceneRuta1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;


	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	//Bool que controla si ya has pillado la pokeball 
	bool pokeballruta1 = false;


	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* pokeball = nullptr;
	SDL_Texture* cartelon = nullptr;

	//Colliders con nombre
	Collider* colliderpokeballW = nullptr;
	Collider* colliderpokeballR = nullptr;



	

};




#endif