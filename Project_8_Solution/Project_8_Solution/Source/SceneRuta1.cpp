#include "SceneRuta1.h"

#include "Collider.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <SDL/include/SDL_scancode.h>
#include "ModuleInput.h"
#include "Enemy_GreenSoldier.h"
#include "Enemy_GreenSoldier2.h"
#include "ModuleDestruibles.h"
#include "ModuleFonts.h"


#define SPAWN_MARGIN 60

SceneRuta1::SceneRuta1(bool startEnabled) : Module(startEnabled)
{
	
	
}

SceneRuta1::~SceneRuta1()
{

}

// Load assets
bool SceneRuta1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->player->Enable();
	App->enemies->Enable();
	App->destruibles->Enable();
	App->collisions->Enable();
	App->audio->Enable();
	App->fonts->Enable();
	App->particles->Enable();
	App->textures->Enable();

	bgTexture = App->textures->Load("Assets/Sprites/Ruta1.png");
	pokeball = App->textures->Load("Assets/Sprites/pokeball.png");
	App->audio->PlayMusic("Assets/Fx/pallet_town_theme.ogg", 1.0f); // bgm ruta 1

	App->player->immovable = false;

	App->collisions->AddCollider({ 190, 632, 35, 10 }, Collider::Type::TOPALLETTOWN);
	colliderpokeballR = App->collisions->AddCollider({ 70, 120, 20, 20 }, Collider::Type::RECOLLECTABLE);
	colliderpokeballW = App->collisions->AddCollider({ 75, 125, 10, 10 }, Collider::Type::WALL);


	return ret;
}

Update_Status SceneRuta1::Update()
{


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRuta1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(pokeball, 75, 125, NULL);

	//App->render->Blit(destructibles, 163, 113, false);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneRuta1::CleanUp()
{
	

	return true;
}




