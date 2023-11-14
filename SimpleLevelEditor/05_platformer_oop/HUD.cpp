#include "HUD.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

void HUD::Init(sf::RenderTarget& window) {
	window_ = &window;

	if (font.loadFromFile("data/fonts/pixelated.ttf"))
	{
		chrono_text_.setFont(font);
		fps_text_.setFont(font);
		// set the string to display
		chrono_text_.setString("Hello world");
		chrono_text_.setCharacterSize(24); // in pixels, not points!
		chrono_text_.setFillColor(sf::Color::White);
		chrono_text_.setStyle(sf::Text::Bold);
		chrono_text_.setPosition(10, 10);

		

	}

}

void HUD::Update(sf::View view)
{

	UpdateChrono();

	chrono_text_.setPosition(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y - view.getSize().y / 2 + 10);


}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw
	target.draw(chrono_text_, states);
	target.draw(fps_text_, states);
}

void HUD::StartChrono()
{
	clock.restart();
	chronoFlag = true;
}

void HUD::UpdateChrono()
{

	if (chronoFlag)
	{
		chronoTime = clock.getElapsedTime();
		chrono_text_.setString(std::to_string((int)chronoTime.asSeconds()));
	}
}

void HUD::StopChrono()
{
	chronoFlag = false;
}

void HUD::FrameTime(float fps)
{
	fps_text_.setString(std::to_string(fps) + " ms");
}

