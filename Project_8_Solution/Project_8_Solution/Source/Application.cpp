#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneCombate.h"
#include "SceneLevel1.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "SceneLose.h"
#include "SceneLogo.h"
#include "ModuleUI.h"
#include "ModuleDestruibles.h"
#include "ScenePrevTitle.h"
#include "SceneRuta1.h"
#include "ModulePokemonInv.h"



Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	UI =			new ModuleUI(false);		//UI

	modules[5] =	sceneCombate =	new SceneCombate(false);
	modules[6] =	sceneLevel_1 =	new SceneLevel1(false);
	modules[7] =	destruibles =	new ModuleDestruibles(true);
	modules[8] =	sceneLose =		new SceneLose(false);
	modules[9] =	sceneLogo =		new SceneLogo(true);
	modules[10] =	scenePrevTitle =new ScenePrevTitle(false);
	modules[11] =	sceneRuta1 =	new SceneRuta1(false);
	modules[12] =   enemies =       new ModuleEnemies(false);	
	modules[13] =	pokemonInv =	new ModulePokemonInv(false);

	modules[14] = collisions =		new ModuleCollisions(true);//Gameplay scene starts disabled
	
	modules[15] =	particles =		new ModuleParticles(true);

	modules[16] =   player =        new ModulePlayer(false);
	
	modules[17] =	fade =			new ModuleFadeToBlack(true);
	modules[18] =	fonts =			new ModuleFonts(true);

	modules[19] =	render =		new ModuleRender(true);

}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
