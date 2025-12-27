#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game(sf::RenderWindow& window);
    ~Game();

    bool init();
    void update(float dt);
    void render();
    void keyPressed(sf::Event event);

private:
    sf::RenderWindow& window;
};

// Continue later...