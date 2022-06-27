#include "ModulePlayer.h"

#include "Application.h"
#include "Animation.h"

#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLose.h"
#include "SceneLogo.h"
#include "SceneLevel1.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModuleDestruibles.h"
#include "SceneRuta1.h"
#include "Module.h"
#include "ModulePokemonInv.h"


#include "SDL/include/SDL_scancode.h"

#include <stdio.h>
#include <SDL/include/SDL_timer.h>
#include <SDL/include/SDL_video.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//Animaciones start

	downAnim.PushBack({ 20, 0, 22, 28 });
	downAnim.PushBack({ 0, 0, 21, 28 });
	downAnim.PushBack({ 20, 0, 22, 28 });
	downAnim.PushBack({ 42, 0, 21, 28 });

	downAnim.speed = 0.07f;
	downAnim.loop = true;


	idledownAnim.PushBack({ 21, 0, 21, 28 });
	idledownAnim.speed = 0.05f;
	idledownAnim.loop = true;


	leftAnim.PushBack({21, 28, 21, 28});
	leftAnim.PushBack({0 , 28, 21, 28 });
	leftAnim.PushBack({21 , 28, 21, 28 });
	leftAnim.PushBack({42 , 28, 21, 28 });


	leftAnim.speed = 0.07f;
	leftAnim.loop = true;

	idleleftAnim.PushBack({ 21, 28, 21, 28 });
	idleleftAnim.speed = 0.05f;
	idleleftAnim.loop = true;



	rightAnim.PushBack({ 21, 81, 21, 28 });
	rightAnim.PushBack({ 0, 81, 21, 28 });
	rightAnim.PushBack({ 21, 81, 21, 28 });
	rightAnim.PushBack({ 42, 81, 21, 28 });
	rightAnim.speed = 0.07f;
	rightAnim.loop = true;
	idlerightAnim.PushBack({ 21, 81, 21, 28 });
	idlerightAnim.speed = 0.05f;
	idlerightAnim.loop = true;


	upAnim.PushBack({ 21, 53, 21, 28 });
	upAnim.PushBack({ 0, 53, 21, 28 });
	upAnim.PushBack({ 21, 53, 21, 28 });
	upAnim.PushBack({ 42, 53, 21, 28 });
	upAnim.speed = 0.07f;
	upAnim.loop = true;
	idleupAnim.PushBack({ 21, 53, 21, 28 });
	idleupAnim.speed = 0.05f;
	idleupAnim.loop = true;


}


ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	currentAnimation = &idleupAnim;

	//Load the textures
	App->UI->iconoVida = App->textures->Load("Assets/Sprites/UI _Vidas.png"); //Icono vida
	texture = App->textures->Load("Assets/Sprites/Sprites male.png"); //Icono vida
	text_box = App->textures->Load("Assets/Sprites/caja de texto.png"); //Icono vida


	// Initiate player audios here
	weaponPickUpFx = App->audio->LoadFx("Assets/Fx/165.wav");

	//Load font
	char lookupTable[] = {"ABCDEFGHIJ,.abcdefghijKLMNOPQRST'-klmnopqrstUVWXYZ ___¡¿uvwxyz____0123456789:;_?!_________"};
	pokemonFont = App->fonts->Load("Assets/Sprites/fuentes_letras.png", lookupTable, 4);


	//Player position
	collider = App->collisions->AddCollider({ 0,0, 20,20 }, Collider::Type::BODY, this);
	collider_foot = App->collisions->AddCollider({ 0,0, 20, 10}, Collider::Type::FOOT, this);
	collider_camara =App->collisions->AddCollider({0,0, 485, 16 }, Collider::Type::NONE);
	return ret;
}

float reduce_val(bool controllerON, float v1, float min, float clamp_to) {
	if (controllerON)
	{
		float sign = v1 / fabs(v1);
		float reduced = v1 - ((fabs(v1) > min) ? sign * min : v1);
		float to_1 = reduced / (float)(SDL_MAX_SINT16);
		float reclamped = to_1 * clamp_to;
		return reclamped;
	}
	else
	{
		return 0;
	}
}

Update_Status ModulePlayer::Update()    
{
	float fx = 0, fy = 0;

	fx += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2);
	fy += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2);
	fx += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j2_x, 10000, 2);
	fy += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j2_y, 10000, 2);

	// GAMEPAD: Triggers Count as axis, have specific values
	if (App->input->controllers[0].LT > SDL_MAX_SINT16 / 2) {
		fx *= 2;
		fy *= 2;
	}
	if (App->input->controllers[0].RT > SDL_MAX_SINT16 / 2) {
		fx *= 3;
		fy *= 3;
	}

	// GAMEPAD: Fire with any button for now to check they all work
	bool button_press = false;
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (App->input->controllers[0].buttons[i] == KEY_DOWN)
		{
			button_press = true; break;
		}
	}
	
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		return Update_Status::UPDATE_STOP;
	}

	if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN)
	{
		text_on_screen = !text_on_screen;
	}
	
	//Auto win
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 30);
	}

	//Auto kill
	if (App->input->keys[SDL_SCANCODE_J] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);
	}

	//Auto win //Creo que está mal
	if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 100);
	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN)
	{
		
		if (godMode == false)
		{
			speed += 3;
		}
		else
		{
			speed -= 3;
		}
		godMode = !godMode;
	}

	//Pokemon inv
	if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN)		
	{
		inventario = !inventario;
	}

	//Add one pokemon
	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN)
	{
		App->pokemonInv->NumOfPokemons++;
		App->pokemonInv->setValues("Pokachu", "Pokachu Gordo", 80, 30, 20, 99, 100, 110, 5, 69, 6);
	}

	//Spawning enemies menu
	if (shortcuts == true)
	{
		if (App->input->keys[SDL_SCANCODE_F9] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F10] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::TRIPLESHOT, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, position.x, position.y - 100);		//Tackler
		}

		if (App->input->keys[SDL_SCANCODE_H] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::HOSTAGE, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GRENADER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::ESPINAS, position.x, position.y - 100);
		}
	}
	

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) < 0 && immovable == false)
	{
		position.x -= speed;
		facing = 4;
		currentAnimation = &leftAnim;
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) > 0 && immovable == false)
	{
		position.x += speed;
		facing = 2;
		currentAnimation = &rightAnim;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) > 0 && immovable == false)
	{
		position.y += speed;
		facing = 3;
		currentAnimation = &downAnim;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) < 0 && immovable == false)
	{
		position.y -= speed;
		facing = 1;
		currentAnimation = &upAnim;
	}

	// Interactuar
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_B] == Key_State::KEY_DOWN)
	{
		if (text_on_screen == true)
		{
			immovable = false;
			text_on_screen = false;
			App->sceneLevel_1->cartel_metal = false;
			App->sceneLevel_1->cartel_madera = false;
		}
	}

	//Immovable a false
	if (App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_DOWN)
	{
		immovable = !immovable;
	}


	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) == 0
		&& reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0)
	{
		//Comprobación de la ultima dirección en la que ha mirado
		switch (facing)
		{
		case 1:
			currentAnimation = &idleupAnim;
			break;
						
		case 2:
			currentAnimation = &idlerightAnim;
			break;

		case 3:
			currentAnimation = &idledownAnim;
			break;

		case 4:
			currentAnimation = &idleleftAnim;
			break;
		}


	}


	//Idle del espacio
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE || button_press)
	{
		
	}
	
	collider->SetPos(position.x, position.y);
	collider_foot->SetPos(position.x, position.y + 12);


	//Posicion de los colliders conforme se mueve la camara
	currentAnimation->Update();

	CameraFollowPlayer();	

	return Update_Status::UPDATE_CONTINUE;
	
}

Update_Status ModulePlayer::PostUpdate()
{
	
	SDL_Rect rect;
	SDL_Rect rect2;

	rect = currentAnimation->GetCurrentFrame();
		
	if (text_on_screen == true)
	{
		App->render->Blit(text_box, App->render->GetCameraCenterX() - 120, App->render->GetCameraCenterY() + 110);
		text_on_screen = false;
	}


	App->render->Blit(texture, position.x, position.y + 30, &rect2);
	App->render->Blit(texture, position.x, position.y, &rect);

	if (App->sceneRuta1->IsEnabled() == true)
	{
		App->render->Blit(App->sceneRuta1->cartelon, 178, 704, NULL);
	}
	

	//UI
	App->render->Blit(App->UI->uiTexture, App->render->GetCameraCenterX() - 100, App->render->GetCameraCenterY() - 110, NULL, 1.0, false);
	App->render->Blit(App->UI->limites, App->render->GetCameraCenterX()-450, App->render->GetCameraCenterY()-200, NULL, 1.0, false);
	

	// Draw UI (score) --------------------------------------
	//Set de las variables
	sprintf_s(demoText, 10, "%5d", variable);
	//Variables del pokemon en el inventario
	sprintf_s(health, 10, "%5d", App->pokemonInv->health);
	sprintf_s(attack, 10, "%5d", App->pokemonInv->attack);
	sprintf_s(defense, 10, "%5d", App->pokemonInv->defense);
	sprintf_s(specAtk, 10, "%5d", App->pokemonInv->specAtk);
	sprintf_s(specDef, 10, "%5d", App->pokemonInv->specDef);

	//Blit the text of UI

	App->fonts->BlitText((SCREEN_WIDTH / 2) + 110, (SCREEN_HEIGHT / 2) - 140, pokemonFont, "DEMO");

	//Inventario
	if (inventario == true)
	{
		App->fonts->BlitText(10, 40, pokemonFont, "Inventario:");
		if (App->pokemonInv->NumOfPokemons > 0)
		{
			//Printar valores
			App->fonts->BlitText(10, 55, pokemonFont, health);
			App->fonts->BlitText(10, 70, pokemonFont, attack);
			App->fonts->BlitText(10, 85, pokemonFont, defense);
			App->fonts->BlitText(10, 100, pokemonFont, specAtk);
			App->fonts->BlitText(10, 115, pokemonFont, specDef);
		}
	}
	else
	{

	}

	if (App->collisions->debug == true)
	{
		App->fonts->BlitText(10, 25, pokemonFont, demoText);

		if (godMode == true)
		{
			App->fonts->BlitText(10, 300, pokemonFont, "GodMode: ON");
		}
		else
		{
			App->fonts->BlitText(10, 300, pokemonFont, "GodMode: OFF");
		}

		if (immovable == false)
		{
			App->fonts->BlitText(10, 10, pokemonFont, "Immovable: FALSE");
		}
		else
		{
			App->fonts->BlitText(10, 10, pokemonFont, "Immovable: TRUE");
		}

		


		//Camera movment

		int camerax = App->render->GetCameraCenterX();
		int cameray = App->render->GetCameraCenterY();

		App->render->DrawQuad({ camerax, cameray }, { 10, 10 }, 255, 0, 0, 255);

		int moveCameraUp = cameray - 35;
		int moveCameraDown = cameray + 35;
		int moveCameraRight = camerax + 35;
		int moveCameraLeft = camerax - 35;

		App->render->DrawQuad({ camerax, moveCameraUp }, { 10, 5 }, 255, 255, 0, 255);
		App->render->DrawQuad({ camerax, moveCameraDown }, { 10, 5 }, 255, 0, 255, 255);
		App->render->DrawQuad({ moveCameraRight, cameray }, { 5, 10 }, 255, 255, 0, 255);
		App->render->DrawQuad({ moveCameraLeft, cameray }, { 5, 10 }, 255, 0, 255, 255);
		
	}
	
	//Carteles
	if (App->sceneLevel_1->cartel_metal == true)
	{
		App->player->text_on_screen = true;
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 110, (SCREEN_HEIGHT / 2) + 150, App->player->pokemonFont, "PUEBLO PALETA");
		App->player->immovable = true;
		waiting_to_skip_text = true;

	}

	if (App->sceneLevel_1->cartel_madera == true)
	{
		App->player->text_on_screen = true;
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) + 135, App->player->pokemonFont, "TIPS PARA NUEVOS ENTRENADORES");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) + 150, App->player->pokemonFont, "-Utiliza W,A,S,D para moverte");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) + 165, App->player->pokemonFont, "-Utiliza SPACE para interactuar");
		App->player->immovable = true;
		waiting_to_skip_text = true;

	}


	return Update_Status::UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed)
	{
		return;
	}

	if (c1 != collider_foot && c1 != collider)
	{
		return;
	}

	bool isNonWalkable = c1->type == Collider::Type::FOOT && 
		(c2->type == Collider::Type::WALL || c2->type == Collider::Type::DESTRUIBLE);

	if (isNonWalkable)
	{
		int to_push_x;
		int to_push_y;
		Collider::ColliderSide side = c1->GetSideToPush(c2->rect, to_push_x, to_push_y);

		LOG("%d", side);

		switch (side)
		{
		case Collider::ColliderSide::UP:
			App->player->position.y += to_push_y;
			break;
		case Collider::ColliderSide::DOWN:
			App->player->position.y += to_push_y;
			break;
		case Collider::ColliderSide::RIGHT:
			App->player->position.x += to_push_x;
			break;
		case Collider::ColliderSide::LEFT:
			App->player->position.x += to_push_x;
			break;
		default:
			break;
		}
	}

	//Reset anim al salir de la hierba alta
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESET_ANIM_WATER)
	{
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			switch (facing)
			{
			case 0:
				currentAnimation = &upfootAnim;
				break;

			case 1:
				currentAnimation = &rightupfootAnim;
				break;
			case 2:
				currentAnimation = &rightfootAnim;
				break;
			case 3:
				currentAnimation = &rightdownfootAnim;
				break;
			case 4:
				currentAnimation = &downfootAnim;
				break;
			case 5:
				currentAnimation = &leftdownfootAnim;
				break;
			case 6:
				currentAnimation = &leftfootAnim;
				break;
			case 7:
				currentAnimation = &leftupfootAnim;
				break;
			}
		}

	}

	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::TORUTA1)
	{
		immovable = true;
		App->player->position.x = 225;
		App->player->position.y = 850;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneRuta1, 30);
	}

	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::TOPALLETTOWN)
	{
		immovable = true;
		App->player->position.x = 200;
		App->player->position.y = 35;
		App->fade->FadeToBlack((Module*)App->sceneRuta1, (Module*)App->sceneLevel_1, 30);
	}

	//Control de recolectables
	if ((c1->type == Collider::Type::FOOT) && (c2->type == Collider::Type::RECOLLECTABLE) && ((App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN 
		|| App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_B] == Key_State::KEY_DOWN)))
	{
		
		//Pokeball ruta1
		if (c2 = App->sceneRuta1->colliderpokeballR)
		{
			//FAlta hacer desaparecer el sprite
			App->sceneRuta1->colliderpokeballR->pendingToDelete = true;
			App->sceneRuta1->colliderpokeballW->pendingToDelete = true;
			App->sceneRuta1->pokeballruta1 = true;
			//Dar item
			variable++;
		}

	}

	//Collider cartel
	if ((c1->type == Collider::Type::FOOT) && (c2->type == Collider::Type::SIGN) && (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN 
		|| App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_B] == Key_State::KEY_DOWN))
	{
		if (c2 == App->sceneLevel_1->collider_cartel_metal)
		{
			App->sceneLevel_1->cartel_metal = true;
		}

		if (c2 == App->sceneLevel_1->collider_cartel_madera)
		{
			App->sceneLevel_1->cartel_madera = true;
		}
	}
	
}



void ModulePlayer::CameraFollowPlayer()
{
	
	int camerax = App->render->GetCameraCenterX();
	int cameray = App->render->GetCameraCenterY();

	int moveCameraUp = cameray - 35;
	int moveCameraDown = cameray + 35;
	int moveCameraRight = camerax + 35;
	int moveCameraLeft = camerax - 35;

	if (position.y <= moveCameraUp)
	{
		cameray = position.y + 35;
	}

	if (position.y >= moveCameraDown - 64)
	{
		cameray = position.y - 35 + 64;

	}

	if (position.x >= moveCameraRight - 32)
	{
		camerax = position.x - 35 + 32;

	}

	if (position.x <= moveCameraLeft)
	{
		camerax = position.x + 35;

	}

	App->render->SetCameraCenter(camerax, cameray);
	
}



bool ModulePlayer::CleanUp() {
	//App->fonts->Disable();
	App->textures->Unload(texture);
	App->audio->UnloadFx(shotFx);
	App->audio->UnloadFx(playerDeadFx);
	App->audio->UnloadFx(heavyRifleFx);
	App->audio->UnloadFx(throwGrenadeFx);
	App->fonts->UnLoad(pokemonFont);
	return true;
}
