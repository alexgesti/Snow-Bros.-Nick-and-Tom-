#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_scancode.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	fase.PushBack({ 122, 28, 12, 15 });

	alive.PushBack({ 25, 63, 8, 8 });
	alive.PushBack({ 17, 63, 7, 8 });
	alive.PushBack({ 11, 63, 5, 8 });
	alive.loop = true;
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/lvl1.png");
	face = App->textures->Load("Assets/Nick&Tom.png");
	numbers = App->textures->Load("Assets/Title_ToplanRights.png");
	App->audio->PlayMusic("Assets/(Stage 1, 3).ogg", 1.0f);

	//collider del aire para los saltos
	App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL SUELO

	App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
	App->collisions->AddCollider({ 0, 209, 87, 5 }, Collider::Type::FLOOR);				//PLAT1 B. IZQ
	App->collisions->AddCollider({ 134, 209, 85, 5 }, Collider::Type::FLOOR);			//PLAT2 B. MED
	App->collisions->AddCollider({ 266, 209, 87, 5 }, Collider::Type::FLOOR);			//PLAT3 B. DER
	App->collisions->AddCollider({ 68, 170, 217, 5 }, Collider::Type::FLOOR);			//PALT4 M. MED GRAND
	App->collisions->AddCollider({ 0, 134, 153, 5 }, Collider::Type::FLOOR);			//PLAT5 ARR. IZQ
	App->collisions->AddCollider({ 200, 134, 152, 5 }, Collider::Type::FLOOR);			//PLAT6 ARR. DER
	App->collisions->AddCollider({ 45, 96, 43, 5 }, Collider::Type::FLOOR);				//PLAT7 GRAND. IZQ
	App->collisions->AddCollider({ 88, 77, 177, 5 }, Collider::Type::FLOOR);			//PLAT9 GRAND. MEDIO
	App->collisions->AddCollider({ 265, 96, 42, 5 }, Collider::Type::FLOOR);			//PALT11 GRAND. DER


	//collider de los lados
	App->collisions->AddCollider({ 88, 84, 4, 15 }, Collider::Type::WALL);				//PALT8 GRAND. MURO IZQ
	App->collisions->AddCollider({ 261, 84, 4, 15 }, Collider::Type::WALL2);			//PLAT10 GRAND. MURO DER
	App->collisions->AddCollider({ 0, 19, 3, 245 }, Collider::Type::WALL2);				//MURO IZQ
	App->collisions->AddCollider({ 350, 19, 3, 245 }, Collider::Type::WALL);			//MURO DER

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 100, 50);
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 230, 50);
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 70, 106);
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 250, 106);
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 90, 143);

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	
	return ret;
}

update_status ModuleScene::Update()
{
	if (App->player->lives == 3 && App->player->less == true) {
		alive.Update();
		App->player->less = false;
	}
	else if (App->player->lives == 2 && App->player->less == true) {
		alive.Update();
		App->player->less = false;
	}
	else if (App->player->lives == 1 && App->player->less == true) {
		alive.Update();
		App->player->less = false;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect bgrect;
	bgrect.w = SCREEN_SIZE;
	App->render->Blit(bgTexture,0,0, NULL);

	App->render->Blit(face, 24, 20, &(fase.GetCurrentFrame()));
	App->render->Blit(numbers, 40, 23, &(alive.GetCurrentFrame()));

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();

	App->textures->Unload(bgTexture);
	App->textures->Unload(face);
	App->textures->Unload(numbers);
	App->textures->Unload(App->player->texture);
	App->enemies->CleanUp();
	App->collisions->CleanUp();
	App->audio->PlayMusic(NULL);

	return true;
}