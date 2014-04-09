#ifndef DRAWER
#define DRAWER

#include "Globals.h"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "clInitFunctions.hpp"
#include <stdio.h>
#include "Food.h"
#include "Simulation.h"
#include "Helper.h"

class Drawer {

public:
	sf::Uint8* pixels;
	sf::Texture texture;
	
	sf::Sprite *sprite;

	sf::RenderWindow *window;
	sf::View *view;
	sf::RectangleShape *shapeSelection;
	sf::Font hudFont;
	Drawer();
	~Drawer();

	

	void drawHUD(Stats * stats);
    void drawStatisticText(int fontSize, sf::Color textColor, std::string statisticDescription, int statisticSize, int x, int y);
	void drawTargets(openCLinit * init, int i);
	void drawBackground();
	void drawPheromonMap (openCLinit * init);
	void drawFood (openCLinit * init, std::vector <Food*> food);
	void drawAnts (openCLinit * init, Helper * helper);
	void selectAnts (int x, openCLinit * init, sf::RectangleShape *shapeSelection, std::vector <int*> selectedAnts, bool selectionMode);
	void drawGrid (int gridSize);
	void drawSimulation(openCLinit * init, Helper * helper, Simulation *sim, Stats *stats);
	void drawEnemies(openCLinit * init, std::vector <Enemy*> enemy);

};

#endif