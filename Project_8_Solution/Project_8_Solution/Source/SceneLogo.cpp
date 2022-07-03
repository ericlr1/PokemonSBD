
#include "SceneLogo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneCombate.h" 
#include "ModulePlayer.h"
#include "SceneLevel1.h"


SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneLogo::~SceneLogo()
{

}

// Load assets
bool SceneLogo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/capybara.png");
	introFX = App->audio->LoadFx("Assets/Fx/Ok_I_pull_up.wav");
	App->audio->PlayFx(introFX);

	return ret;
}

Update_Status SceneLogo::Update()
{
	bool button_press = false;
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		if (App->input->controllers[0].buttons[i] == KEY_DOWN)
		{
			button_press = true; break;
		}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || button_press)
	{
		
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		App->player->position.x = 200;
		App->player->position.y = 200;
		


	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLogo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}