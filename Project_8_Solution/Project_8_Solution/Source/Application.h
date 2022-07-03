#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneCombate;
class SceneLevel1;
class SceneLose;
class SceneLogo;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleRender;
class ModuleFonts;
class ModuleUI;
class ModuleDestruibles;
class ScenePrevTitle;
class SceneRuta1;
class ModulePokemonInv;



class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	ModuleUI* UI = nullptr;

	SceneCombate* sceneCombate = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLose* sceneLose = nullptr;
	SceneLogo* sceneLogo = nullptr;
	ScenePrevTitle* scenePrevTitle = nullptr;
	SceneRuta1* sceneRuta1 = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePokemonInv* pokemonInv = nullptr;

	ModuleDestruibles* destruibles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__