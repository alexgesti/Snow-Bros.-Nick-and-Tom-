#ifndef __ENEMY_SPITFIRE_H__
#define __ENEMY_SPITFIRE_H__

#include "Enemy.h"
#include "p2Point.h"

class Enemy_SpitFire : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_SpitFire(float x, float y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int jumpt = (rand() % 4 + 11) * 100;
	int shoott = (rand() % 4 + 1) * 100;
	int shootcd = 0;
	bool shoot = false;
	bool shootonce = false;

private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walkLAnim;
	Animation walkRAnim;
	Animation downRAnim;
	Animation downLAnim;
	Animation Ldead;
	Animation Rdead;
	Animation JumpL;
	Animation JumpR;
	Animation shootL;
	Animation shootR;
	Animation nothing;
};

#endif // __ENEMY_RedDemon_H__
