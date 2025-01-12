#include "ModuleDebugInfo.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include <stdio.h>

ModuleDebugInfo::ModuleDebugInfo(bool startEnabled) : Module(startEnabled)
{
	name = "debug";
}

ModuleDebugInfo::~ModuleDebugInfo()
{

}

bool ModuleDebugInfo::Start()
{
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	debugFont = App->fonts->Load("Assets/Fonts/Fonts_1.png", lookupTable, 2);

	return true;
}

bool ModuleDebugInfo::CleanUp()
{
	//TODO: Unload debug font!
	App->fonts->UnLoad(debugFont);

	return true;
}

update_status ModuleDebugInfo::Update()
{
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
		debugMemLeaks = !debugMemLeaks;

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
		inspectedModule = (Module*)App->player;

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN)
		inspectedModule = (Module*)App->sceneIntro;

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN)
		inspectedModule = (Module*)App->sceneLevel_1;

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_DOWN)
		inspectedModule = nullptr;


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDebugInfo::PostUpdate()
{
	if(debugMemLeaks)
	{
		App->fonts->BlitText(10, 1, debugFont, "press f4 to close mem leaks debug info");

		App->fonts->BlitText(10, 20, debugFont, "total loaded resources");

		// Display total textures loaded
		sprintf_s(debugText, 150, "textures  %i", App->textures->GetTexturesCount());
		App->fonts->BlitText(20, 35, debugFont, debugText);

		// Display total audio files loaded
		sprintf_s(debugText, 150, "audio fx  %i", App->audio->GetFxCount());
		App->fonts->BlitText(20, 50, debugFont, debugText);

		// Display total font files loaded
		sprintf_s(debugText, 150, "fonts     %i", App->fonts->GetFontsCount());
		App->fonts->BlitText(20, 65, debugFont, debugText);

		// Display total colliders loaded
		sprintf_s(debugText, 150, "colliders %i", App->collisions->GetColliderCount());
		App->fonts->BlitText(20, 80, debugFont, debugText);

		// Display total particles loaded
		sprintf_s(debugText, 150, "particles %i", App->particles->GetParticlesCount());
		App->fonts->BlitText(20, 95, debugFont, debugText);

		App->fonts->BlitText(10, 120, debugFont, "press f5 to f7 to display specific modules");

		if (inspectedModule != nullptr)
		{
			DrawModuleResources(inspectedModule);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleDebugInfo::DrawModuleResources(Module* module)
{
	sprintf_s(debugText, 150, "module %s", module->name);
	App->fonts->BlitText(20, 140, debugFont, debugText);

	sprintf_s(debugText, 150, "active  total");
	App->fonts->BlitText(155, 140, debugFont, debugText);

	sprintf_s(debugText, 150, "textures          %i      %i", module->activeTextures, module->totalTextures);
	App->fonts->BlitText(30, 155, debugFont, debugText);

	sprintf_s(debugText, 150, "audio fx          %i      %i", module->activeFx, module->totalFx);
	App->fonts->BlitText(30, 170, debugFont, debugText);

	sprintf_s(debugText, 150, "fonts             %i      %i", module->activeFonts, module->totalFonts);
	App->fonts->BlitText(30, 185, debugFont, debugText);

	sprintf_s(debugText, 150, "colliders         %i      %i", module->activeColliders, module->totalColliders);
	App->fonts->BlitText(30, 200, debugFont, debugText);
}