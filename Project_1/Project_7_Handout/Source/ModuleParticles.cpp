#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Nick&Tom.png");

	// muerte
	playerdeath.anim.PushBack({16, 531, 30, 29});
	playerdeath.anim.PushBack({54, 528, 29, 32});
	playerdeath.anim.PushBack({91, 531, 30, 29});
	playerdeath.anim.PushBack({ 54, 528, 29, 32 });
	playerdeath.anim.PushBack({ 91, 531, 30, 29 });
	playerdeath.anim.PushBack({ 54, 528, 29, 32 });
	playerdeath.anim.PushBack({ 91, 531, 30, 29 });
	playerdeath.anim.PushBack({ 54, 528, 29, 32 });
	playerdeath.anim.PushBack({ 91, 531, 30, 29 });
	playerdeath.anim.PushBack({ 54, 528, 29, 32 });
	playerdeath.anim.PushBack({ 91, 531, 30, 29 });
	playerdeath.anim.PushBack({ 129, 535, 28, 25 });
	playerdeath.anim.PushBack({ 165, 539, 30, 22 });
	playerdeath.anim.PushBack({ 203, 544, 32, 16 });
	playerdeath.anim.PushBack({ 243, 547, 32, 13 });
	playerdeath.anim.PushBack({ 283, 552, 32, 8 });
	playerdeath.anim.loop = false;
	playerdeath.anim.speed = 0.3f;

	snowball1.anim.PushBack({16, 717, 20, 17});
	snowball2.anim.PushBack({44, 710, 23, 24});
	snowball3.anim.PushBack({75, 708, 25, 26});
	snowball4.anim.PushBack({108, 704, 26, 30});

	laserx.anim.PushBack({ 16, 141, 7, 11 });
	laserx.anim.PushBack({ 31, 141, 7, 11 });
	laserx.speed.x = 5;
	laserx.lifetime = 180;
	laserx.anim.speed = 0.2f;

	lasery.anim.PushBack({ 588, 191, 7, 11 });
	lasery.anim.PushBack({ 573, 191, 7, 11 });
	lasery.speed.x = -5;
	lasery.lifetime = 180;
	lasery.anim.speed = 0.2f;

	

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}