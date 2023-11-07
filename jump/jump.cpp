
#include <iostream>
#include <fstream>
#include <vector>

#include "view.h"
#include "SFML/Graphics.hpp"

const sf::Vector2f gravityForce = sf::Vector2f(0.0f, 1.0f);

const float kHorizontalMaxSpeed = 10;
sf::Vector2f previousPosition;


struct Ground {
	sf::Vector2f position;
	sf::RectangleShape shape;
};

std::vector<Ground> loadObstacles(const std::string& filename) {
	std::vector<Ground> obstacles;
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		int x;
		int y;
		int width;
		int height;
		int color_r;
		int color_g;
		int color_b;
		while (file >> x >> y >> width >> height >> color_r >> color_g >> color_b) {
			Ground obstacle;
			obstacle.position.x = x;
			obstacle.position.y = y;
			obstacle.shape.setSize(sf::Vector2f(width, height));
			obstacle.shape.setFillColor(sf::Color(color_r, color_g, color_b));

			obstacles.push_back(obstacle);
		}

		file.close();
	}
	else {
		std::cout << "Echec de l'ouverture du fichier." << std::endl;

	}

	return obstacles;
}

int main()
{
	std::vector<Ground> grounds = loadObstacles("obstacles.txt");



	sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");
	View view(800, 600);

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(3000);

	// Define a Shape
	// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Shape.php
	

	sf::RectangleShape shape(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color(150, 0, 0));
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);





	Ground ground1;
	ground1.position = sf::Vector2f(400, 500);
	ground1.shape = sf::RectangleShape(sf::Vector2f(200, 50));
	ground1.shape.setFillColor(sf::Color(0, 150, 0));
	ground1.shape.setOrigin(ground1.shape.getSize().x / 2, ground1.shape.getSize().y / 2);
	ground1.shape.setPosition(ground1.position);
	grounds.push_back(ground1);

	Ground ground2;
	ground2.position = sf::Vector2f(200, 400);
	ground2.shape = sf::RectangleShape(sf::Vector2f(100, 50));
	ground2.shape.setFillColor(sf::Color(0, 150, 0));
	ground2.shape.setOrigin(ground2.shape.getSize().x / 2, ground2.shape.getSize().y / 2);
	ground2.shape.setPosition(ground2.position);
	grounds.push_back(ground2);


	Ground ground3;
	ground3.position = sf::Vector2f(600, 600);
	ground3.shape = sf::RectangleShape(sf::Vector2f(1000, 50));
	ground3.shape.setFillColor(sf::Color(0, 0, 150));
	ground3.shape.setOrigin(ground3.shape.getSize().x / 2, ground3.shape.getSize().y / 2);
	ground3.shape.setPosition(ground3.position);
	grounds.push_back(ground3);


	sf::Vector2f speed = sf::Vector2f(0, 0);
	sf::Vector2f acceleration = sf::Vector2f(0, 0);
	sf::Vector2f jumpForce;
	sf::Vector2f moveForce;

		

	while (window.isOpen())
	{
	

		sf::Event event;

		//bool isGrounded = shape.getPosition().y >= (window.getSize().y - shape.getSize().y / 2);
		bool isGrounded = false;

		for (Ground& ground : grounds) {
			if (shape.getGlobalBounds().intersects(ground.shape.getGlobalBounds())) {
				isGrounded = true;
				
			}
		}

		
		

		jumpForce = sf::Vector2f(0.0f, 0.0f);
		moveForce = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2i mouse_tile_coord(mouse_pos.x / 50, mouse_pos.y / 50);



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (isGrounded)
			{
				jumpForce = sf::Vector2f(0.0f, -20.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				moveForce = sf::Vector2f(-5.0f, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (speed.x < kHorizontalMaxSpeed)
			{
				moveForce = sf::Vector2f(5.0f, 0.0f);
			}

		}

		while (window.pollEvent(event))
		{
			sf::Vector2i newPos;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}

		}

		



		window.clear(sf::Color::Black);

	
		acceleration = sf::Vector2f(0, 0);

		if (!isGrounded)
		{
			acceleration += gravityForce;
		}
		else
		{
			speed.y = -0.5;
		}

		acceleration += jumpForce;
		acceleration += moveForce;

		
		speed += acceleration;
		if (!isGrounded)
		{
			speed.x *= 0.75f;
		}
		else
		{
			speed.x *= 0.95f;
		}
		previousPosition = shape.getPosition();

		shape.setPosition(shape.getPosition() + speed);
		
		

		

		std::cout << std::endl;
		std::cout << "is grounded ?" << isGrounded << std::endl;
		std::cout << "Acceleration : \tX=" << acceleration.x << ":\tY=" << acceleration.y << std::endl;
		std::cout << "Vitesse : \tX=" << speed.x << ":\tY=" << speed.y << std::endl;
		std::cout << "Position : \tX=" << shape.getPosition().x << ":\tY=" << shape.getPosition().y << std::endl;

		for (const Ground& ground : grounds) {
			window.draw(ground.shape);
		}
		view.setCenter(shape.getPosition());

		window.setView(view.getView());

		window.draw(shape);
	

		window.display();
	

	}



}