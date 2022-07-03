#ifndef __MODULE_SCENETITLE_H__
#define __MODULE_SCENETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class SceneCombate : public Module {
public:
	// Constructor
	SceneCombate(bool startEnabled);

	// Destructor
	~SceneCombate();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player, the enemies and the powerups.
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

};

#endif // __MODULE_SCENETITLE_H__
