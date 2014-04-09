#include "Drawer.h"

Drawer::Drawer (){
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hey");
	window->setFramerateLimit(FPS);
	shapeSelection = new sf::RectangleShape;
	
	hudFont.loadFromFile("/Users/chris/Desktop/coolvetica.ttf");
	pixels  = new sf::Uint8[800*800*4];
	texture.create(800,800); 
	sprite = new sf::Sprite(texture);
	view = new sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	
}
Drawer::~Drawer(){
	delete shapeSelection;
	delete window;
	

}
void Drawer::drawHUD(Stats * stats){

	int spaceFromLeft = 290;
	sf::RectangleShape hudBG;
	hudBG.setSize(sf::Vector2f(325, WINDOW_HEIGHT));
	hudBG.setPosition( WINDOW_WIDTH-spaceFromLeft-25, 0);
	hudBG.setFillColor(sf::Color(30,30,30,255));
	window->draw(hudBG);

	Drawer::drawStatisticText(22, sf::Color::White, "Possible Ants: ", ARRAY_SIZE, WINDOW_WIDTH-spaceFromLeft, 10);
	Drawer::drawStatisticText(22, sf::Color::White, "Ants: ", stats->stats_number_of_living_ants, WINDOW_WIDTH-spaceFromLeft, 50);

	Drawer::drawStatisticText(22, sf::Color(159,217,0,255), "Food-Catching: ", stats->foodCatchingAnts, WINDOW_WIDTH-spaceFromLeft, 90);
	Drawer::drawStatisticText(22, sf::Color(159,217,0,255), "Collected Food: ", stats->earnedFood, WINDOW_WIDTH-spaceFromLeft, 130);
	Drawer::drawStatisticText(22, sf::Color(0,170,217,255), "Pheromon-Searching: ", stats->pheromonSearching, WINDOW_WIDTH-spaceFromLeft, 170);
	Drawer::drawStatisticText(22, sf::Color(224,112,181,255), "Killed Ants: ", stats->killedAnts, WINDOW_WIDTH-spaceFromLeft, 210);

	Drawer::drawStatisticText(22, sf::Color (250,223,22,255), "Breed: ", stats->breed , WINDOW_WIDTH-spaceFromLeft, 300);
	Drawer::drawStatisticText(22, sf::Color (225,245,168,255), "Eggs: ", stats->eggs, WINDOW_WIDTH-spaceFromLeft, 340);
	Drawer::drawStatisticText(22, sf::Color (225,241,133,255), "Grubs: ", stats->grubs, WINDOW_WIDTH-spaceFromLeft, 380);
	Drawer::drawStatisticText(22, sf::Color (225,237,102,255), "Puppets: ", stats->puppets, WINDOW_WIDTH-spaceFromLeft, 420);
	Drawer::drawStatisticText(22, sf::Color (225,223,70,255), "Imagos: ", stats->imagos, WINDOW_WIDTH-spaceFromLeft, 460);


	Drawer::drawStatisticText(22, sf::Color::White,  "Day: ", stats->days, WINDOW_WIDTH-spaceFromLeft, 510);
	Drawer::drawStatisticText(22, sf::Color::White, "Month: ", stats->months, WINDOW_WIDTH-spaceFromLeft, 550);
	Drawer::drawStatisticText(22, sf::Color::White, "Years: ", stats->years, WINDOW_WIDTH-spaceFromLeft, 590);



	Drawer::drawStatisticText(22, sf::Color::White, "Speed: ", stats->avgSpeed, WINDOW_WIDTH-spaceFromLeft, 650);
	Drawer::drawStatisticText(22, sf::Color(58,193,247,255), "FPS: ", stats->fps, WINDOW_WIDTH-spaceFromLeft, 690);

}
void Drawer::drawStatisticText(int fontSize, sf::Color textColor, std::string statisticDescription, int statisticSize, int x, int y){
	sf::Text text;

	
	

	text.setFont(hudFont);
	text.setCharacterSize(fontSize);
	text.setColor(textColor);

	std::stringstream sstm;
	sstm << statisticDescription << statisticSize;

	text.setString(sstm.str());
	text.setPosition(x, y);
	window->draw(text);

}

void Drawer::drawTargets(openCLinit * init, int i){
	if (init->lifeStadium[i] != 0){
		sf::RectangleShape shape2(sf::Vector2f(3,3));
		shape2.setFillColor(sf::Color(255,0,0,200));
		shape2.setPosition(init->targetX[i],init->targetY[i]);
		window->draw(shape2);
	}
}


void Drawer::drawBackground(){
	// draw Anthill
	int circleRadius = 20;
	sf::CircleShape circle (circleRadius);
	circle.setFillColor(sf::Color(201,119,30));
	circle.setPosition(STARTPOSX-circleRadius,STARTPOSY-circleRadius);
	circle.setOutlineThickness(10);
	circle.setOutlineColor(sf::Color(156,92,23));
	window->draw(circle);

	circle.setPosition(ENDEPOSX-circleRadius,ENDEPOSY-circleRadius);
	window->draw(circle);

}

void Drawer::drawGrid (int gridSize){
	for (int y = 0; y < HEIGHT; y+= gridSize){
		for (int x = 0; x < WIDTH; x += gridSize){
			sf::RectangleShape shape(sf::Vector2f(gridSize,gridSize));
			shape.setOutlineColor(sf::Color(255,255,255,10));
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1);
			shape.setPosition(x,y);
			window->draw(shape);
		}
	}
}



void Drawer::drawPheromonMap (openCLinit * init){
	
	int x = 0;
	int y = 0;
	sf::VertexArray lines(sf::Points, ARRAY_SIZE);

	for (int i = 0; i < WIDTH*HEIGHT; i++){
		
		//int linn = 0;
		if (init->pheromonMap[i] > 0){
			int phColor;
			sf::CircleShape pheromon;
			pheromon.setRadius(3);
			if (init->pheromonMap[i]/4 >= 255)
				phColor = 255;
			else 
				phColor = init->pheromonMap[i]/4;
			
			pheromon.setFillColor(sf::Color(0,0,255,phColor));

			if (init->pheromonMap[i] == 100000)
				pheromon.setFillColor(sf::Color(0,0,0,0));

			pheromon.setPosition(x,y);

			window->draw(pheromon);
			
			/*lines[linn].position = sf::Vector2f(x, y);
			lines[linn].color = sf::Color(255,0,0,100);

			linn++;*/



		}

		if (i%WIDTH == 0){
			y++;
			x = 0;
		}


		x++;
	}

	window->draw(lines);


}


void Drawer::drawFood (openCLinit * init, std::vector <Food*> food){


	for (Food * thisFood : food){
		if (thisFood->volume > 1){
			sf::RectangleShape pheromon(sf::Vector2f(1,1));
			sf::RectangleShape pheromonRadius(sf::Vector2f(20,20));
			//sf::RectangleShape pheromon(sf::Vector2f(thisFood->volume/10,thisFood->volume/10));
			pheromon.setFillColor(sf::Color(255,196,0,255));
			pheromonRadius.setFillColor(sf::Color(190,255,10,thisFood->volume/FOOD_FACTOR));
			pheromon.setPosition(thisFood->x,thisFood->y);
			pheromonRadius.setPosition(thisFood->x-10,thisFood->y-10);
			window->draw(pheromon);
			window->draw(pheromonRadius);
		}
	}


}

void Drawer::selectAnts (int x, openCLinit * init, sf::RectangleShape *shapeSelection, std::vector <int*> selectedAnts, bool selectionMode){
	int countSelections = 0;
	// Ant zwischen X-Bereich
	// @TODO:: Ant Selection nach beendigung des Modus löschen
	if (selectionMode){
		// Wenn die Ant in dem Selection-Bereich ist 
		if ( 
			((init->antX[x] >shapeSelection->getPosition().x) && ( init->antX[x] < shapeSelection->getPosition().x+shapeSelection->getSize().x)) 
			&&
			((init->antY[x] >shapeSelection->getPosition().y) && ( init->antY[x] < shapeSelection->getPosition().y+shapeSelection->getSize().y))
			){

				// is ant already in Vector???
				for (int *that : selectedAnts){
					// Ant existiert noch nicht im  Selection Vector
					if (*that == x){
						countSelections++;
						//std::cout << "\n\nANT IN VECTOR::::" << x;
					}
				}
				// No! add it
				if(countSelections == 0){
					selectedAnts.push_back(new int(x));
					init->color[x] = 1;
				}

				countSelections = 0;
		}
	}

}

//
//
//
//
void Drawer::drawAnts (openCLinit * init, Helper * helper){
	sf::VertexArray m_vertices(sf::Quads, 4);

	for (int antid = 0; antid < ARRAY_SIZE; antid++){
		sf::RectangleShape antShape(sf::Vector2f(SIZEOFANANT,SIZEOFANANT));
		// Do this only for Living Ants
		if (init->lifeStadium[antid] == 1){
			// Selection Mode
			
			////////////////////////////////////////////////////////Drawer::selectAnts(antid, targetMode);
			Drawer::selectAnts( antid, init, shapeSelection, helper->selectedAnts, helper->selectionMode);

			switch (init->color[antid]){
				case 0:
					m_vertices[0].color = sf::Color(255,255,255,255); break;
				case 1:
					m_vertices[0].color = sf::Color::Yellow;break;
				case 3:
					m_vertices[0].color = sf::Color::Green;break;
				case 5:
					m_vertices[0].color = sf::Color(247,165,58,255);break;
				case 33:
					m_vertices[0].color = sf::Color::Magenta;break;
			}


			if (helper->viewRadiusMode){
				sf::CircleShape radius;
				int transparency;
				BOOST ? transparency =255 : transparency = 25;
				init->isCarryingFood[antid] ? radius.setFillColor(sf::Color(0,255,0,transparency)) : radius.setFillColor(sf::Color(255,0,0,transparency));
				
				radius.setRadius(ANT_VIEWRADIUS+(SIZEOFANANT*2));
				radius.setPosition(init->antX[antid]-(ANT_VIEWRADIUS+(SIZEOFANANT*2)),init->antY[antid]-(ANT_VIEWRADIUS+(SIZEOFANANT*2)));
				window->draw(radius);
			}

			antShape.setPosition(init->antX[antid],init->antY[antid]);
			m_vertices[0].position.x = init->antX[antid];
			m_vertices[0].position.y =	init->antY[antid];

			m_vertices[1].position.x = init->antX[antid]+SIZEOFANANT;
			m_vertices[1].position.y =	init->antY[antid];

			m_vertices[2].position.x = init->antX[antid]+SIZEOFANANT;
			m_vertices[2].position.y =	init->antY[antid]+SIZEOFANANT;

			m_vertices[3].position.x = init->antX[antid];
			m_vertices[3].position.y =	init->antY[antid]+SIZEOFANANT;

			//m_vertices[antid].color = sf::Color::White;
			


			if (helper->targetMode){
				Drawer::drawTargets(init, antid);

				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(init->antX[antid], init->antY[antid])),
					sf::Vertex(sf::Vector2f(init->targetX[antid], init->targetY[antid]))
				};

				window->draw(line, 2, sf::Lines);

			}


			// Check 

			window->draw(m_vertices);

		}


	}
	



}

void Drawer::drawSimulation(openCLinit * init, Helper * helper, Simulation *sim, Stats *stats){
	/*
	*
	* DRAWING
	* 
	*/

	/**
	VIEW !!!
	**/
	
	window->setView(*view);
	*view = window->getDefaultView();
	view->zoom(init->viewSize);
	view->move(init->moveX, init->moveY);
	window->setView(*view);
	



	// clear the window with black color
	window->clear(sf::Color::Black);

	drawBackground();
	// Draws Grid
	if (helper->gridMode){
		Drawer::drawGrid(50);
	}


	BOOST ? drawPheromonMap(init) :
		drawFood(init, sim->food);	
	if (helper->pheromonMode){
		drawPheromonMap(init);
	}

	drawEnemies(init, sim->enemy);

	// Draws Ants
	drawAnts(init, helper);
	//std::cout << "\nANTDRAW " << clcl.getElapsedTime().asMilliseconds();
	drawHUD(stats);



	window->display();
}

void Drawer::drawEnemies(openCLinit * init, std::vector <Enemy*> enemy){

	for (Enemy * thisEnemy : enemy){

			sf::CircleShape enemy(1);
			sf::CircleShape enemyRadius(thisEnemy->attackRadius);
			//sf::RectangleShape pheromon(sf::Vector2f(thisFood->volume/10,thisFood->volume/10));
			enemy.setFillColor(sf::Color(245,60,180,255));
			if (thisEnemy->ableToAttack){
				enemyRadius.setFillColor(sf::Color(245,60,180,50));
			}
			else {
				enemyRadius.setFillColor(sf::Color(100,100,100,50));
			}
			enemy.setPosition(thisEnemy->x,thisEnemy->y);
			enemyRadius.setPosition(thisEnemy->x - thisEnemy->attackRadius,thisEnemy->y - thisEnemy->attackRadius);
			window->draw(enemy);
			window->draw(enemyRadius);
		
	}
}
