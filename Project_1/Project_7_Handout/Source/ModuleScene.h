#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	int camscene = 0;
	int Font = -1;
	int xm = 0;
	int ym = 0;
	int enemy = 0;
	float counter_Text_Disapear;
	bool once = false;
	bool check = false;
	char Text[20] = { "\0" };
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* face = nullptr;
	SDL_Texture* numbers = nullptr;

	// HUD
	Animation alive;
	Animation fase;

};

#endif