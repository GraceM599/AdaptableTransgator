#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
	std::cout << "Launching TRANSGATOR SFML window...\n";

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

        window.clear(sf::Color::Black);
        window.display();
    }
}