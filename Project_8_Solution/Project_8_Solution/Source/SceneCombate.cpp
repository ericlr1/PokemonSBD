#include "SceneCombate.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePokemonInv.h"
#include "SDL/include/SDL_scancode.h"

SceneCombate::SceneCombate(bool startEnabled) : Module(startEnabled) 
{
	
	
}

SceneCombate::~SceneCombate() {}

// Load assets
bool SceneCombate::Start()
{
	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Ruta1_Combat_Background.png");

	//Provisional pokemon enemigo
	App->pokemonInv->E_attack = 10;
	App->pokemonInv->E_defense = 10;
	App->pokemonInv->E_health = 10;
	App->pokemonInv->E_maxHealth = 10;
	App->pokemonInv->E_name = "Pockachu";
	App->pokemonInv->E_nickname = "Pockachu";
	App->pokemonInv->E_specAtk = 10;
	App->pokemonInv->E_specDef = 10;
	App->pokemonInv->E_speed = 10;

	if (App->pokemonInv->E_speed > App->pokemonInv->speed)
	{
		youtTurn = false;
	}
	else
	{
		youtTurn = true;
	}

	return ret;
}

Update_Status SceneCombate::Update() {
	
	// To combat screen
	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneCombate, (Module*)App->sceneLevel_1, 30);
	}

	if (youtTurn == true)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_B] == Key_State::KEY_DOWN)
		{

		}

	}
	else
	{

	}

	if (App->pokemonInv->E_health <= 0)
	{

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCombate::PostUpdate()
{
	App->render->Blit(bgTexture, -120, 0, NULL);



	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCombate::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}