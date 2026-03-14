#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "sfmlhelpers.h"

// a lot of this has been inspired by and copied from my minesweeper project - Rylee

TextureManager::TextureManager() : prefixbutton(prefixsearch), wordsearchbutton(wordsearch), gobutton(searchbar){
	if (!prefixsearch.loadFromFile("assets/images/prefixsearch.png"))
    	std::cout << "Failed to load prefixsearch" << std::endl;

	prefixbutton.setTexture(prefixsearch, true);
	prefixbutton.setScale({.5, .5});
	prefixbutton.setPosition({292, 308});

	if (!prefixsearch_pressed.loadFromFile("assets/images/prefixsearch_pressed.png"))
		std::cout << "Failed to load prefixsearch_pressed" << std::endl;

	if (!wordsearch.loadFromFile("assets/images/wordsearch.png"))
		std::cout << "Failed to load wordsearch" << std::endl;

	wordsearchbutton.setTexture(wordsearch, true);
	wordsearchbutton.setScale({.5, .5});
	wordsearchbutton.setPosition({1132, 308});

	if (!wordsearch_pressed.loadFromFile("assets/images/wordsearch_pressed.png"))
		std::cout << "Failed to load wordsearch_pressed" << std::endl;

	if (!searchbar.loadFromFile("assets/images/searchbar.png"))
		std::cout << "Failed to load searchbar" << std::endl;
	
	gobutton.setTexture(searchbar, true);
	gobutton.setScale({.5, .5});
	gobutton.setPosition({630, 160});
}

// taken from the minesweeper specs with some modifications for sfml 3.0.2
void setText(sf::Text &text, float x, float y){
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin({textRect.position.x + textRect.size.x/2.0f,
	textRect.position.y + textRect.size.y/2.0f});
	text.setPosition(sf::Vector2f(x, y));
}

void DisplayWindow::setupText(sf::Text &text, std::string message, int size, sf::Color color, std::pair<int, int> pos, bool bold){
	text.setString(message);
	text.setCharacterSize(size);
	text.setFillColor(color);
	setText(text, pos.first, pos.second);
	if (bold)
		text.setStyle(sf::Text::Bold);
}

DisplayWindow::DisplayWindow() :
	window(sf::VideoMode({1920,1080}), "TransGator", sf::Style::Close),
	title(font),
	prefixdescription(font),
	wholedescription(font),
	inputword(font),
  	trietitle(font),
  	trietime(font),
  	trieresults(font),
  	hashtitle(font),
  	hashtime(font),
  	hashresults(font){


	// load our text font
	font.openFromFile("assets/arialuni.ttf");

	// set all bools to false
	prefix_on = false;
	whole_on = false;
	perform_search = false;

	configureStaticText();
}


void DisplayWindow::configureStaticText(){
	horizontaldivider.setSize({1839.5, 2});
	horizontaldivider.setFillColor(sf::Color::Black);
	horizontaldivider.setPosition({41.5, 501.9});

	verticaldivider.setSize({2, 465});
	verticaldivider.setFillColor(sf::Color::Black);
	verticaldivider.setPosition({960, 540});

	setupText(title, "TRANSGATOR: ENGLISH TO SPANISH", 60, sf::Color::Black, {960, 80}, true);
	setupText(prefixdescription, "Search for translations\n\n\nfor the five most\n\n\ncommon words starting\n\n\nwith a given prefix.", 20, sf::Color::Black, {146, 395}, false);
	setupText(wholedescription, "Search for a direct\n\n\ntranslation of the\n\n\nentered word.", 20, sf::Color::Black, {1754, 395}, false);
	setupText(trietitle, "Trie Implementation", 50, sf::Color::Black, {490, 560}, true);
	setupText(hashtitle, "Hash Map Implementation", 50, sf::Color::Black, {1433, 560}, true);
}

// signifcant help from my minesweeper project with the name typing and checking - Rylee
void DisplayWindow::updateInputText(sf::Event &event){
	// check if text is being entered
	if (auto textEvent = event.getIf<sf::Event::TextEntered>()){

		char letter = static_cast<char>(textEvent->unicode);

		// checking the character is a valid letter
		if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')){
			if (input.size() < 26){ // arbitrary number for now until we figure out the max char
				input += letter;
			}
		}
	}

	// check if they're deleting characters or if they press enter 
	else if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()){

		// check for backspace and remove letter
		if (keyEvent->code == sf::Keyboard::Key::Backspace && input.size() > 0){
			input.pop_back();
		}
		
		// check for enter and perform the search
		if (keyEvent->code == sf::Keyboard::Key::Enter && input.size() > 0){
			perform_search = true;
		}
	}
}

void DisplayWindow::updateResults(){

}

void DisplayWindow::drawButtons(){
	window.draw(textures.prefixbutton);
	window.draw(textures.wordsearchbutton);
	window.draw(textures.gobutton);
}

void DisplayWindow::drawText(){
	window.draw(horizontaldivider);
	window.draw(verticaldivider);
	window.draw(title);
	window.draw(prefixdescription);
	window.draw(wholedescription);
	window.draw(inputword);
	window.draw(trietitle);
	window.draw(trietime);
	window.draw(trieresults);
	window.draw(hashtitle);
	window.draw(hashtime);
	window.draw(hashresults);
}

void DisplayWindow::run(){

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		drawButtons();
		
		while (auto event = window.pollEvent()){

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
	
		}
		drawText();
		window.display();
	}
}