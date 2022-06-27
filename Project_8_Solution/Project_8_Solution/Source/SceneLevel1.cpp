#include "SceneLevel1.h"

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

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->player->immovable = false;

	App->player->Enable();
	App->enemies->Enable();
	App->destruibles->Enable();
	App->collisions->Enable();
	App->audio->Enable();
	App->fonts->Enable();
	App->particles->Enable();
	App->textures->Enable();

	bgTexture = App->textures->Load("Assets/Sprites/pueblo paleta.png");
	App->audio->PlayMusic("Assets/Fx/pallet_town_theme.ogg", 1.0f); //Music


	//CREACION NPCs
	
	
	//Collider salida a Ruta 1
	App->collisions->AddCollider({ 187, 0, 57, 10 }, Collider::Type::TORUTA1);

	//Colliders carteles
	collider_cartel_metal = App->collisions->AddCollider({ 296, 325, 17, 10}, Collider::Type::SIGN);
	collider_cartel_madera = App->collisions->AddCollider({ 153, 219, 16, 10}, Collider::Type::SIGN);

	//Colliders muros
	App->collisions->AddCollider({0, 0, 30, 294}, Collider::Type::WALL);	//Arboles izquierda
	App->collisions->AddCollider({0, 294, 118, 105}, Collider::Type::WALL); //arboles de abajo
	App->collisions->AddCollider({305, 355, 10, 40}, Collider::Type::WALL);
	App->collisions->AddCollider({315, 345, 120, 50}, Collider::Type::WALL);
	App->collisions->AddCollider({183, 382-6, 124, 24}, Collider::Type::WALL);

	//Casa abajo derecha
	App->collisions->AddCollider({ 251, 178, 44,83 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 314, 178, 46,83 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 295, 178, 19,66 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 246, 316, 50,20 }, Collider::Type::WALL); //Valla abajo -> lado izquierdo
	App->collisions->AddCollider({ 296,308-2, 20,22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 316,317, 47,16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 398,0, 32,345 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240,0, 158,47 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 30,0, 158,46 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 85,204, 69,25 }, Collider::Type::WALL); //valla con cartel izquierda
	App->collisions->AddCollider({ 154,198, 18,30 }, Collider::Type::WALL); //cartel madera
	App->collisions->AddCollider({ 118,293, 70,87 }, Collider::Type::WALL); //agua

	//casa izquierda
	App->collisions->AddCollider({ 124,45, 40,98 }, Collider::Type::WALL); //casa izquierda (part derecha)
	App->collisions->AddCollider({ 163,128, 6,21 }, Collider::Type::WALL); //casa izquierda pico derecha
	App->collisions->AddCollider({ 164,63, 13,72 }, Collider::Type::WALL); //casa izquierda derecha extremo
	App->collisions->AddCollider({ 82,46, 42,79 }, Collider::Type::WALL); //casa izquierda parte izquierda
	App->collisions->AddCollider({ 73,118, 18,31 }, Collider::Type::WALL); //casa izquierda buzon
	App->collisions->AddCollider({ 91,125, 13,20 }, Collider::Type::WALL); //casa izquierda hueco

	//casa derecha 
	App->collisions->AddCollider({ 299,45, 40,98 }, Collider::Type::WALL); //casa derecha (part derecha)
	App->collisions->AddCollider({ 337,128, 6,21 }, Collider::Type::WALL); //casa derecha pico derecha
	App->collisions->AddCollider({ 256,47, 43,78 }, Collider::Type::WALL); //casa derecha izq
	App->collisions->AddCollider({ 249,120, 19,27 }, Collider::Type::WALL); //casa derecha buzon
	App->collisions->AddCollider({ 267,126, 12,19 }, Collider::Type::WALL); //casa derecha hueco
	App->collisions->AddCollider({ 339,65, 15,68 }, Collider::Type::WALL); //casa derecha parte de la derecha extremo


	



	return ret;
}

Update_Status SceneLevel1::Update()
{
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->textures->Unload(bgTexture);
	App->player->Disable();
	App->enemies->Disable();
	App->destruibles->Disable();
	App->collisions->Disable();
	App->fonts->Disable();
	App->particles->Disable();
	App->textures->Disable();



	return true;
}




