/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <vector>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Timer.h"

struct Vector
{
	Vector( float X, float Y )
		:
		x( X ),
		y( Y )
	{}
	Vector operator+( Vector Rhs )
	{
		return Vector( x + Rhs.x, y + Rhs.y );
	}
	Vector operator-( Vector Rhs )
	{
		return Vector( x - Rhs.x, y - Rhs.y );
	}
	Vector operator+=( Vector Rhs)
	{
		return Vector( x = x + Rhs.x, y = y + Rhs.y );
	}
	Vector operator*( float Rhs )
	{
		return Vector( x * Rhs, y * Rhs );
	}
	float GetMagnitude()
	{
		return sqrt( x * x + y * y );
	}
	Vector Normalize()
	{
		return Vector( x / GetMagnitude(), y / GetMagnitude() ) ;
	}
	float x, y;
};

struct Pressed
{
	bool space,
		 enter,
		 w,
		 a,
		 s,
		 d;
};

class Entity
{
public:
	Entity( Vector Position,
			int Width,
			int Height,
			float Hp,
			float Damage,
			float Speed = 0.f,
			Vector Heading = Vector( 0.f, 0.f ))
		:
		position( Position ),
		width( Width ),
		height( Height ),
		hp( Hp ),
		damage( Damage ),
		speed( Speed ),
		velocity( Heading * Speed )
	{}

public:
	Vector position, velocity;
	int width,
		height;
	float hp,
		  damage,
		  speed;
};

class Game
{
public:
	enum SpawnType
	{
		LASER, ENEMY
	};
	enum EntityHost
	{
		HUMAN, CPU
	};
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();

	/********** Game flow **********/
	void HandleKbdInput();
	void UpdateEntityPosition( Entity &Type );
	void UpdateEntityPosition( std::vector<Entity> &Types );
	void CheckCollision();
	bool IsColliding( Entity A, Entity B);
	bool IsCollidingScreen( Entity A );
	void SetEntityDead();
	void SpawnLaser();
	void SpawnEnemy();
	void DrawShip();
	void DrawEnemies();
	void DrawLasers();
	void DrawSquare( Vector Position, int Width, int Height );
	Vector GetMouseXY();
	/*******************************/

private:
	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;
	Graphics gfx;
	Timer timer;

	// Enums
	EntityHost host;
	SpawnType spawn_type;
	// 
	Entity ship;
	std::vector<Entity> enemies;
	std::vector<Entity> lasers;

	Pressed is_pressed;
	float frame_time;
};
