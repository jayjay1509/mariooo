#pragma once

#include <chrono>
#include <iostream>
#include <SFML/Audio.hpp>

#include "tilemap.h"
#include "HUD.h"

 

class Game
{
public:
	bool windowResized = false;
	bool levelediting = false;
	bool grounded;
	bool checkpoint = false;
	bool you_win = false;
	bool you_lose = false;
	bool coin = false;
	int coin_musik = 0;
	int cheakpoint_musik = 0;
	int you_dead_musik = 0;
	int you_win_musik = 0;

	Tilemap tilemap_;
	Tilemap tilemap_coin;
	sf::Vector2f player_pos_ = sf::Vector2f(1000, 949);
	sf::Vector2f player_vel_ = sf::Vector2f(0, 0);

	sf::Vector2f player_size = sf::Vector2f(20, 30);
	sf::RenderWindow window_;

	sf::RectangleShape tile_shape_;
	sf::RectangleShape cursor_shape_;
	sf::RectangleShape debug_limit_shape_vertical_;
	sf::RectangleShape debug_limit_shape_horizontal_;
	sf::RectangleShape player_box_shape_;

	sf::Sprite tile_sprite;
	sf::Texture tile_texture;

	sf::Sprite tile_sprite2;
	sf::Texture tile_texture2;

	sf::Sprite tile_sprite3;
	sf::Texture tile_texture3;

	sf::Sprite player_origin_shape_;
	sf::Sprite background;
	sf::Sprite background2;
	sf::Sprite background0;
	sf::Sprite background3;
	sf::Sprite background4;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;

	sf::Sprite drapeux_s;
	sf::Texture drapeux_t;

	sf::Sprite drapeux_true_s;
	sf::Texture drapeux_true_t;

	sf::Sprite drapeux_arrive_s;
	sf::Texture drapeux_arrive_t;

	sf::Sprite you_win_s;
	sf::Texture you_win_t;

	sf::Sprite you_lose_s;
	sf::Texture you_lose_t;

	sf::Sprite heart_full_s;
	sf::Texture heart_full_t;

	sf::Sprite heart_empty_s;
	sf::Texture heart_empty_t;

	sf::Sprite coin_s; 
	sf::Texture coin_t;

	sf::Sprite ground_s;
	sf::Texture ground_t;

	sf::Sprite spike_s;
	sf::Texture spike_t;


	//--------------------------------------------------------------------------------------------------------------
	// sound

	sf::SoundBuffer sound_jump_b; 
	sf::Sound sound_jump_s;

	sf::SoundBuffer sound_coin_b; 
	sf::Sound sound_coin_s;

	sf::SoundBuffer sound_cheakpoint_b; 
	sf::Sound sound_cheakpoint_s;

	sf::SoundBuffer sound_dead_b; 
	sf::Sound sound_dead_s;

	sf::SoundBuffer sound_you_lose_b; 
	sf::Sound sound_you_lose_s;


	sf::SoundBuffer sound_you_win_b;  
	sf::Sound sound_you_win_s;


	sf::SoundBuffer sound_main_b;  
	sf::Sound sound_main_s;

	std::chrono::high_resolution_clock::time_point frameStart;
	std::chrono::high_resolution_clock::time_point frameEnd;

	HUD hud_;
	float deltaTime_;

	void init();

	void update();

	void view();

	
};

