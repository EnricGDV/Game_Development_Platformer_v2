#pragma once

#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Module.h"

struct SDL_Texture;

struct PlayerData
{
	Animation*			current_animation;
	Animation*			current_fire;
	Animation			angel_idle;
	Animation			angel_moving;
	Animation			angel_jumping;
	Animation			angel_falling;
	Animation			angel_idle_M;
	Animation			angel_moving_M;
	Animation			angel_jumping_M;
	Animation			angel_falling_M;
	Animation			demon_idle;
	Animation			demon_moving;
	Animation			demon_jumping;
	Animation			demon_falling;
	Animation			demon_idle_M;
	Animation			demon_moving_M;
	Animation			demon_jumping_M;
	Animation			demon_falling_M;
	Animation			fire;
	Animation			fireM;
	bool				canDJump;
	bool				isDemon;
	bool				canDash;
	bool				mirror;
	bool				isJumping;
	bool				isDashing;
	bool				onFloor;
	bool                godmode = false;
	int					xDirection;
	int                 map;
	int                 savedmap;
	int					dashTime;
	float				currentDashTime;
	float				initialDashTime;
	fPoint				jumpSpeed;
	fPoint				dashSpeed;
	fPoint				acceleration;
	fPoint				maxSpeed;
	fPoint				iMaxSpeed;
	fPoint				speed;
	fPoint				iSpeed;
	fPoint				position;
	fPoint              initPosition;
	fPoint				offSet;
	j1Timer				dashTimer;
	Collider*			collider;
	SDL_Rect            colInit;

};

class j1Player : public j1Module
{
public:

	j1Player();

	//Destructor
	virtual ~j1Player();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void Draw();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;



	bool Clean();

	void DoubleJump();

	void MirrorSprite();

	void AnimChange();

	fPoint Gravity(fPoint vec);

	void SpeedUp(float dt);

	void SpeedDown(float dt);

	void ArrivesFloor();

	void Dashing(float dt);

	void StopDash();

	void PlayerMov(float dt);

	void ResetPlayer();

	void OnCollision(Collider* c1, Collider* c2);

private:

public:
	bool				leftCollider;
	bool				rightCollider;
	bool				downCollider;
	bool				upCollider;
	bool				isAlive;
	//uint				fxDeath;
	PlayerData			Player;

private:

	p2SString			spritesheetN;
	uint				fxJump;
	uint				fxDeath;
	uint				fxLand;
	uint				fxTransformation;
	p2SString			jumpFX;
	p2SString			deathFX;
	p2SString			landFX;
	p2SString			tranformationFX;
	fPoint				temp;
	SDL_Texture*		graphics = nullptr;
};





#endif // !__j1PLAYER_H__


