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
	if (pokeballruta1 == false)
	{
		colliderpokeballR = App->collisions->AddCollider({ 70, 120, 20, 20 }, Collider::Type::RECOLLECTABLE);
		colliderpokeballW = App->collisions->AddCollider({ 75, 125, 10, 10 }, Collider::Type::WALL);
	}
	//colliders de la ruta
	App->collisions->AddCollider({ 159, 226, 98, 47 }, Collider::Type::WALL); //arboles medio parte media fila derecha
	App->collisions->AddCollider({ 33, 227, 32, 49 }, Collider::Type::WALL); //arboles medio partea media arbol solitario
	App->collisions->AddCollider({ 128, 51, 32, 145 }, Collider::Type::WALL); //arboles medio arriba
	App->collisions->AddCollider({ 32, 386, 160, 46 }, Collider::Type::WALL); //arboles medio abajo izquierda
	App->collisions->AddCollider({ 0, 32, 32, 586 }, Collider::Type::WALL); //arboles izquierda
	App->collisions->AddCollider({ 353, 32, 31, 586 }, Collider::Type::WALL); //arboles derecha
	App->collisions->AddCollider({ 32, 577, 160, 41 }, Collider::Type::WALL); //valla abajo izquierda
	App->collisions->AddCollider({ 224, 577, 130, 38 }, Collider::Type::WALL); //valla abajo derecha

	App->collisions->AddCollider({ 0, 0, 162, 32 }, Collider::Type::WALL); //arboles arriba izquierda
	App->collisions->AddCollider({ 224, 0, 161, 32 }, Collider::Type::WALL); //arboles arriba derecha








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
	
	if (pokeballruta1 == false)
	{
		App->render->Blit(pokeball, 75, 125, NULL);
	}
	
	//App->render->Blit(destructibles, 163, 113, false);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneRuta1::CleanUp()
{
	

	return true;
}




