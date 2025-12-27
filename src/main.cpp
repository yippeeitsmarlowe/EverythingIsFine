#include <iostream>
#include "Game.h"

int main()
{
    std::cout << "Everything is Fine! A game using SFML and C++20." << std::endl;
    std::cout << "Made by Marlowe Baker and \"Stupid Games!\"" << std::endl;
    std::cout << "You should see a window that opens as well as this writing to the console!" << std::endl;

    // Setup SFML window
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Everything Is Fine!");
    window.setFramerateLimit(60);

    // Initialise instance of Game
    Game game(window);

    if (!game.init())
    {
        std::cerr << "Failed to initialize the game." << std::endl;
        return -1;
    }

    // Clock starts counting when created
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        // Calc delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        // Process elements of game loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                game.keyPressed(event);
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        game.update(dt);
        window.clear();
        game.render();
        window.display();
    }

    return 0;
}