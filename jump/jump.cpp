#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include "view.h"
#include "SFML/Graphics.hpp"
#include <filesystem>


const sf::Vector2f gravityForce = sf::Vector2f(0.0f, 1.0f);

const float kHorizontalMaxSpeed = 10;
sf::Vector2f previousPosition;


struct Ground {
	sf::Vector2f position;
	sf::RectangleShape shape;
};


std::vector<Ground> loadObstacles(const std::string& filename)
{
	std::vector<Ground> obstacles;
	std::ifstream file(filename);
	if (file.is_open()) {
		int x;
		int y;
		int width;
		int height;
		int color_r;
		int color_g;
		int color_b;
		while (file>> x >> y >> width >> height >> color_r >> color_g >> color_b) 
		{
			Ground obstacle;
			obstacle.position.x = x;
			obstacle.position.y = y;
			obstacle.shape.setSize(sf::Vector2f(width, height));
			obstacle.shape.setFillColor(sf::Color(color_r, color_g, color_b));
			obstacle.shape.setOrigin(obstacle.shape.getSize().x / 2, obstacle.shape.getSize().y / 2);
			obstacle.shape.setPosition(obstacle.position);

			obstacles.push_back(obstacle);
		}

		file.close();
	}
	else {
		std::cout << "Echec de l'ouverture du fichier." << std::endl;
		std::cerr << "Error code: " << strerror(errno); // Get some info as to why

	}
	return obstacles;
}

int main()
{
	std::vector<Ground> grounds = loadObstacles("a.txt");



	sf::RenderWindow window(sf::VideoMode(1200, 1000), "Caca Game");
	View view(800, 600);
	
	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	// Define a Shape
	// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Shape.php
	

	sf::RectangleShape shape(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color(150, 0, 0));
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	sf::RectangleShape shape1(sf::Vector2f(50, 50));
	shape1.setFillColor(sf::Color(0, 150, 0));
	shape1.setOrigin(shape1.getSize().x / 2, shape1.getSize().y / 2);
	shape1.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);





	//Ground ground1;
	//ground1.position = sf::Vector2f(400, 500);
	//ground1.shape = sf::RectangleShape(sf::Vector2f(200, 50));
	//ground1.shape.setFillColor(sf::Color(0, 150, 0));
	//ground1.shape.setOrigin(ground1.shape.getSize().x / 2, ground1.shape.getSize().y / 2);
	//ground1.shape.setPosition(ground1.position);
	//grounds.push_back(ground1);
	//
	//Ground ground2;
	//ground2.position = sf::Vector2f(200, 400);
	//ground2.shape = sf::RectangleShape(sf::Vector2f(100, 50));
	//ground2.shape.setFillColor(sf::Color(0, 150, 0));
	//ground2.shape.setOrigin(ground2.shape.getSize().x / 2, ground2.shape.getSize().y / 2);
	//ground2.shape.setPosition(ground2.position);
	//grounds.push_back(ground2);
	//
	//
	//Ground ground3;
	//ground3.position = sf::Vector2f(600, 600);
	//ground3.shape = sf::RectangleShape(sf::Vector2f(1000, 50));
	//ground3.shape.setFillColor(sf::Color(0, 0, 150));
	//ground3.shape.setOrigin(ground3.shape.getSize().x / 2, ground3.shape.getSize().y / 2);
	//ground3.shape.setPosition(ground3.position);
	//grounds.push_back(ground3);


	sf::Vector2f speed = sf::Vector2f(0, 0);
	sf::Vector2f acceleration = sf::Vector2f(0, 0);
	sf::Vector2f jumpForce;
	sf::Vector2f moveForce;

	sf::Vector2f speed1 = sf::Vector2f(0, 0);
	sf::Vector2f acceleration1 = sf::Vector2f(0, 0);
	sf::Vector2f jumpForce1;
	sf::Vector2f moveForce1;
		

	while (window.isOpen())
	{


		sf::Event event;

		//bool isGrounded = shape.getPosition().y >= (window.getSize().y - shape.getSize().y / 2);
		bool isGrounded = false;
		bool isGrounded1 = false;
		

		for (Ground& ground : grounds) {
			if (shape.getGlobalBounds().intersects(ground.shape.getGlobalBounds())) {
				isGrounded = true;

			}
		}

		for (Ground& ground : grounds) {
			if (shape1.getGlobalBounds().intersects(ground.shape.getGlobalBounds())) {
				isGrounded1 = true;

			}
		}
		



		jumpForce = sf::Vector2f(0.0f, 0.0f);
		moveForce = sf::Vector2f(0.0f, 0.0f);

		jumpForce1 = sf::Vector2f(0.0f, 0.0f);
		moveForce1 = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2i mouse_tile_coord(mouse_pos.x / 50, mouse_pos.y / 50);



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (isGrounded1)
			{
				jumpForce1 = sf::Vector2f(0.0f, -20.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				moveForce = sf::Vector2f(-5.0f, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				moveForce = sf::Vector2f(5.0f, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				moveForce1 = sf::Vector2f(-5.0f, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				moveForce1 = sf::Vector2f(5.0f, 0.0f);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (isGrounded)
			{
				jumpForce = sf::Vector2f(0.0f, -20.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			if (isGrounded1)
			{
				shape.setPosition(shape1.getPosition());
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (isGrounded1)
			{
				shape1.setPosition(shape.getPosition());
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
		acceleration1 = sf::Vector2f(0, 0);

		if (!isGrounded)
		{
			acceleration += gravityForce;
		}
		else
		{
			speed.y = -0.5;
		}

		if (!isGrounded1)
		{
			acceleration1 += gravityForce;
		}
		else
		{
			speed1.y = -0.5;
		}

		

		acceleration += jumpForce;
		acceleration += moveForce;

		acceleration1 += jumpForce1;
		acceleration1 += moveForce1;

		
		speed += acceleration;
		speed1 += acceleration1;

		if (!isGrounded)
		{
			speed.x *= 0.75f;
		}
		else
		{
			speed.x *= 0.95f;
		}

		if (!isGrounded1)
		{
			speed1.x *= 0.75f;
		}
		else
		{
			speed1.x *= 0.95f;
		}
		previousPosition = shape.getPosition();
		previousPosition = shape1.getPosition();

		shape.setPosition(shape.getPosition() + speed);
		shape1.setPosition(shape1.getPosition() + speed1);
		
		

		

		std::cout << std::endl;
		std::cout << "is grounded ?" << isGrounded << std::endl;
		std::cout << "Acceleration : \tX=" << acceleration.x << ":\tY=" << acceleration.y << std::endl;
		std::cout << "Vitesse : \tX=" << speed.x << ":\tY=" << speed.y << std::endl;
		std::cout << "Position : \tX=" << shape.getPosition().x << ":\tY=" << shape.getPosition().y << std::endl;

		for (const Ground& ground : grounds) {
			window.draw(ground.shape);
		}

		sf::Vector2f view1 = shape1.getPosition() + shape.getPosition();
		sf::Vector2f view2;
		view2.x = view1.x / 2;
		view2.y = view1.y / 2;


		view.setCenter(view2);

		window.setView(view.getView());

		window.draw(shape);
		window.draw(shape1);
	

		window.display();
		
	

	}

	

}