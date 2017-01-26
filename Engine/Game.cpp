/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ship( Vector( 400.f, 300.f),
		50,
		50,
		100.f,
		10.f )
{
	enemies.push_back( Entity( Vector( 20.f, 20.f ),
		50,
		50,
		100.f,
		10.f ) );
}

void Game::HandleKbdInput()
{
	if ( wnd.kbd.KeyIsPressed( VK_SPACE ) )
	{
		SpawnLaser();
		is_pressed.space = true;
	}
	else
	{
		is_pressed.space = false;
	}
}

void Game::UpdateEntityPosition( Entity &Type )
{
		Type.position += Vector( 1.f, 1.f );
}

void Game::UpdateEntityPosition( std::vector<Entity> &Types )
{
	for( auto &Type : Types )
	{
		Type.position += Type.velocity * frame_time;
	}
}

void Game::CheckCollision()
{
	// Laser vs Enemy
	for( int i = lasers.size() - 1; i >=0; --i )
	{
		for( int j = enemies.size() - 1; j >= 0; --j )
		{
			if( IsColliding( lasers[i], enemies[j] ) )
			{
				lasers.erase(lasers.begin() + i );
				enemies.erase(enemies.begin() + j );
			}
		}
	}

	// Laser vs Screen edge
	for( int i = lasers.size() - 1; i >=0; --i )
	{
		if (IsCollidingScreen( lasers[i] ) )
		{
			lasers.erase( lasers.begin() + i );
		}
	}
}

bool Game::IsCollidingScreen( Entity A )
{
	return A.position.x + A.width > 799 ||
		A.position.x < 0 ||
		A.position.y + A.height > 599 ||
		A.position.y < 0;
}

bool Game::IsColliding( Entity A, Entity B)
{
	return A.position.y > B.position.x &&
		A.position.x + A.width <
		B.position.x + B.width &&
		A.position.y > B.position.y &&
		A.position.y + A.height <
		B.position.y + B.height;
}

void Game::SetEntityDead()
{
}

Vector Game::GetMouseXY()
{
	return Vector( wnd.mouse.GetPosX(), wnd.mouse.GetPosY() );
}

void Game::SpawnLaser()
{
	Entity temp_laser( ship.position,
		4,
		4,
		100,
		10,
		100.f,
		( Vector( GetMouseXY() - ship.position ).Normalize() ) );
	lasers.push_back( temp_laser );
}

void Game::SpawnEnemy()
{
}

void Game::DrawShip()
{
	DrawSquare( ship.position, ship.width, ship.height );
}

void Game::DrawEnemies()
{
}

void Game::DrawLasers()
{
	for( auto &laser : lasers )
	{
		DrawSquare( laser.position, laser.width, laser.height );
	}
}

void Game::DrawSquare( Vector Position, int Width, int Height )
{
	for(int row = 0; row < Width; ++row)
	{
		for(int col = 0; col < Width; ++col)
		{
			gfx.PutPixel( Position.x + row, Position.y + col,
				Colors::Gray );
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// count the time between frames
	frame_time = timer.Reset();
	// Handle user input first
	HandleKbdInput();
	// Move things around
	UpdateEntityPosition( lasers );
	// See if anything touched something
	CheckCollision();
}

void Game::ComposeFrame()
{
	DrawShip();
	DrawEnemies();
	DrawLasers();
}
