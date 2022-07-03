#include "SceneCombate.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"

SceneCombate::SceneCombate(bool startEnabled) : Module(startEnabled) {
}

SceneCombate::~SceneCombate() {}

// Load assets
bool SceneCombate::Start()
{
	bool ret = true;



	return ret;
}

Update_Status SceneCombate::Update() {
	
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCombate::PostUpdate()
{
	App->render->Blit(bgTexture, App->render->GetCameraCenterX() -112, SCREEN_HEIGHT - 1904, NULL);


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCombate::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}