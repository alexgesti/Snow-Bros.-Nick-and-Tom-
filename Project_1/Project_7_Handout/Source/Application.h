#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleSceneIntro;
class ModuleScene;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleRender;
class ModuleChangeScene;
class ModuleSceneGameOver;
class ModuleSceneWin;
class ModuleScreenFirst;
class ModuleFonts;
class ModulePoints;
class ModuleDebugInfo;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	ModuleScreenFirst* sceneFirst = nullptr;
	ModuleSceneIntro* sceneIntro = nullptr;
	ModuleScene* sceneLevel_1 = nullptr;
	ModuleSceneWin* sceneWin = nullptr;
	ModuleSceneGameOver* screenGameOver = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleRender* render = nullptr;
	ModuleChangeScene* change = nullptr;

	ModuleFonts* fonts = nullptr;
	ModulePoints* points = nullptr;
	ModuleDebugInfo* debug = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__