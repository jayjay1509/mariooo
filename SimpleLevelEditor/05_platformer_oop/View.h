#pragma once
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

class View {
public:
    View(float width, float height) {
        view.setSize(width, height);
    }

    void setCenter(sf::Vector2f center) {
        view.setCenter(center);
    }

    sf::View getView() const {
        return view;
    }
    sf::View view;

    
};

