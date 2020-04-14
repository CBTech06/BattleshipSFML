/*Copyright (c) 2020 Bourgeois Christophe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.#include "boat.hpp"
*/

#include "board.hpp"

Board::Board():USERGRID_X(50),USERGRID_Y(150),SENSOR_SIZE(16),COMPUTERGRID_X(650),COMPUTERGRID_Y(150),USERGRID_OFFSET_X(50),USERGRID_OFFSET_Y(155),MAX_CASE(10),MAX_ROTATION(2),GRID_SIZE(320),TILESIZE(32),GAMESPEED(1.00),EMPTY(0),FILLED(1),DESTROYED(2),PLAYED(3),LEFT(0),RIGHT(1),UP(2),DOWN(3),NONE(-1),N(1) 
	       
{
	squarePositionX = USERGRID_OFFSET_X; 
	squarePositionY = USERGRID_OFFSET_Y;
	isPressed = false;
	/* GRID */
	gridTexture.loadFromFile("Resources/Grid.png");
	computerGrid.setTexture(gridTexture);
	computerGrid.setPosition(COMPUTERGRID_X,COMPUTERGRID_Y);
	font.loadFromFile("Resources/Komika.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color(50,50,50));
	text.setCharacterSize(20);
	text.setPosition(190,530);
	setUserGrid();
	positionX = 0;
	positionY = 0; 
	l = 0;
	r = 0;
	x = 0; 
	y = 0;
	i = 0;
	fx = 0;
	fy = 0;
	axe = NONE; 
	direction = 0;
	old_x = 0;
	old_y = 0;
	idx = 0;
	boatOnGrid = 12;
	touched = false;	
	count = 0;
}

void Board::init()
{	/* BACKGROUND */
	backgroundTexture.loadFromFile("Resources/Background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0,0);

	/* GRID */
	gridTexture.loadFromFile("Resources/Grid.png");
	userGrid.setTexture(gridTexture);
	userGrid.setPosition(USERGRID_X,USERGRID_Y);

	grid.left = USERGRID_X;
       	grid.top = USERGRID_Y;
	grid.width = GRID_SIZE;	
}

void Board::setUserGrid()
{
	for(int line=0; line < userGridArray.size(); line++)
	{
		for(int row=0; row < userGridArray.size(); row++)
		{
			userGridArray[line][row] = EMPTY;
		}
	}
}

void Board::readUserGridInfo(sf::RenderWindow& window,Boat& boat)
{
	for(int line=0; line < userGridArray.size(); line++)
	{
		for(int row=0; row < userGridArray.size(); row++)
		{
			if(userGridArray[line][row] == FILLED) { 
		       		positionX = row * TILESIZE + USERGRID_OFFSET_X; 
				positionY = line * TILESIZE + USERGRID_OFFSET_Y;	
				boat.filled(window,positionX,positionY);					
			}		
			else if(userGridArray[line][row] == PLAYED)
			{
				positionX = row * TILESIZE + USERGRID_OFFSET_X; 
				positionY = line * TILESIZE + USERGRID_OFFSET_Y;			
				boat.missed(window,positionX,positionY);
			}
			else if(userGridArray[line][row] == DESTROYED)
			{
				positionX = row * TILESIZE + USERGRID_OFFSET_X; 
				positionY = line * TILESIZE + USERGRID_OFFSET_Y;			
				boat.destroyed(window,positionX,positionY);
			}
		}
	}
}

void Board::addSensorsToGrid()
{
	for(int i = 0; i < MAX_CASE * MAX_CASE; i++)
	{
 		if(i % (MAX_CASE) == 0 && i > 0 && i <= MAX_CASE * MAX_CASE) {
			squarePositionY += TILESIZE;
			squarePositionX = USERGRID_OFFSET_X;
		}	

		gridSquare.push_back(sf::FloatRect(sf::Vector2f(squarePositionX,
				     squarePositionY),sf::Vector2f(SENSOR_SIZE,SENSOR_SIZE)));

		squarePositionX += TILESIZE;
		}
}

void Board::detectBoatOnGrid(Boat& boat)
{ // CHECK BOAT WITH SENSORS TO DEFINE EACH POSITIONS
	 
	for( int i = 0; i < gridSquare.size(); i++)
	{
			if(boat.checkPositionOnGrid(gridSquare[i]))
			{
				setBoatOnGrid(i,FILLED);
			}
		else 
			{
				setBoatOnGrid(i,EMPTY);
			}
	}
}

void Board::setBoatOnGrid(int& idx ,const int& status)
{ // TRANSFORM INDEX TO 2D ARRAY VALUES
				x = 0;
				y = idx;

				if(idx > MAX_CASE) 
				{
					x = std::abs(idx / MAX_CASE);
					y = idx % MAX_CASE;
				}
			if(userGridArray[x][y] != DESTROYED) {
			if(status == EMPTY && userGridArray[x][y] == FILLED)
			{ // CLEAR ONLY THE FILLED CASE DURING THE BOAT MOVEMENT 
				userGridArray[x][y] = status; 
			}
			else if(status == FILLED) 
			{
				userGridArray[x][y] = status;
			}
			}
}

int Board::getBoatInfo()
{ // COUNT EACH BOAT ON THE USER GRID
	count = 0;

	for(int line = 0; line < MAX_CASE; line++)
	{
		for(int row = 0; row < MAX_CASE;row++)
		{
			if(userGridArray[line][row] == FILLED || userGridArray[line][row] == DESTROYED)
			{
				count++;
			}
			
		}
	}

	return count;
}

bool Board::checkBoatOnGrid()
{
	if(boatOnGrid > -1) { return true; }
	else { return false; }
}

/* COLOR FLOATRECT */ 
std::vector<sf::RectangleShape> coloredBox;
void Board::addBoxToSquare(sf::RenderWindow& win)
{
	for(int i = 0; i < gridSquare.size(); i++)
	{
		coloredBox.push_back(sf::RectangleShape(sf::Vector2f(16,16)));
		coloredBox.back().setPosition(gridSquare[i].left,gridSquare[i].top);
		coloredBox.back().setFillColor(sf::Color::Red);
	}

	for(int i=0; i < coloredBox.size(); i++)
	{
		win.draw(coloredBox[i]);
	}
}

void Board::updateEvent(sf::RenderWindow& win,sf::Event &event,Boat& boat)
{
	// MOUSE EVENT TO SELECT AND MOVE BOARD
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		boat.select(win,sf::Mouse::getPosition(win));
	}

	if(clock.getElapsedTime().asSeconds() >= GAMESPEED) 
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			boat.rotate(sf::Mouse::getPosition(win),event);
			clock.restart();		
		}
	}
}

void Board::messageBox(const char* str)
{
	text.setString(str);
}

bool Board::checkAdjacentCase(int& x,int& y)
{
	if (axe == NONE) { fx = old_x; fy = old_y;
		direction = std::rand() %4;
	}
	else { direction = axe;}
	
	
	// LEFT 
	if(direction ==  LEFT && old_y > 0) { checkLeftCase(x,y,LEFT); return true;}
	// RIGHT
	else if (direction == RIGHT && old_y < MAX_CASE) { checkRightCase(x,y,RIGHT); return true; }
	// UP
	else if(direction == UP && old_x > 0 ) { checkUpCase(x,y,UP); return true; }
	// DOWN
	else if(direction == DOWN && old_x < MAX_CASE ) { checkDownCase(x,y,DOWN); return true;}
	
	return false;
}

void Board::restoreFirstValue()
{
	old_x = fx;
	old_y = fy;
}

void Board::checkLeftCase(int&x,int& y,const int& callingMethod)
{
	if(userGridArray[old_x][old_y - N] == FILLED) { 
	       		x = old_x; y = old_y - N;
			axe = LEFT;
     	}
	else if(userGridArray[old_x][old_y - N] == PLAYED || 
		userGridArray[old_x][old_y - N] == EMPTY)
		{
			axe = RIGHT;
			if(callingMethod != RIGHT) {	
				restoreFirstValue();
				checkRightCase(x,y,LEFT);
			}
			else if(callingMethod == RIGHT)	{
				restoreFirstValue();	
				checkUpCase(x,y,LEFT);
			}
		}
}

void Board::checkRightCase(int& x,int& y, const int& callingMethod)
{	
	if(userGridArray[old_x][old_y + N] == FILLED) { 
			x= old_x; y = old_y + N;  
			axe = RIGHT;
	}

	else if(userGridArray[old_x][old_y + N] == PLAYED || 
		userGridArray[old_x][old_y + N] == EMPTY) 
		{
			axe = LEFT;
			if(callingMethod != LEFT) {
				restoreFirstValue();       
				checkLeftCase(x,y,RIGHT);
			}
			else if(callingMethod == LEFT) {
				restoreFirstValue();
			       	checkDownCase(x,y,RIGHT);
			}
		}
}

void  Board::checkUpCase(int& x,int& y,const int& callingMethod)
{	
		
	if(userGridArray[old_x - N][old_y] == FILLED) { 
			x = old_x - N; y = old_y; 
			axe = UP;
	}
	else if(userGridArray[old_x - N][old_y] == PLAYED || 
		userGridArray[old_x - N][old_y] == EMPTY)
		{
			axe = DOWN;
			if(callingMethod != DOWN) {
				restoreFirstValue();       
				checkDownCase(x,y,UP);
			}
			else if(callingMethod == DOWN) {
				restoreFirstValue();
				checkLeftCase(x,y,UP);
			}
		}
}

void Board::checkDownCase(int& x,int& y,const int& callingMethod)
{
	if(userGridArray[old_x + N][old_y] == FILLED) { 
			x = old_x + N; y = old_y; 
	      		axe = DOWN;
	}
	else if(userGridArray[old_x + N][old_y] == PLAYED || 
		userGridArray[old_x + N][old_y] == EMPTY)
		{
			axe = UP;
			if(callingMethod != UP){
				restoreFirstValue();       
				checkUpCase(x,y,DOWN);
			}
			else if(callingMethod == UP) {
				restoreFirstValue();
				checkRightCase(x,y,DOWN);
			}
		}
}

bool Board::checkComputerChoice(int& x,int& y)
{
	if(touched) { 
		if(checkAdjacentCase(x,y)) { touched = false;}
		else { touched = false;}	       
	}

	if(userGridArray[x][y] == PLAYED)
	{
		x =  std::rand()% MAX_CASE;
		y =  std::rand()% MAX_CASE;
	       checkComputerChoice(x,y);	
	}
	else if(userGridArray[x][y] == DESTROYED)
	{
		x =  std::rand()% MAX_CASE;
		y =  std::rand()% MAX_CASE;
	        checkComputerChoice(x,y);	
	}
	else if(userGridArray[x][y] == FILLED)
	{
		userGridArray[x][y] = DESTROYED;
		touched = true;
		old_x = x;
		old_y = y;
		boatOnGrid--;
		return false;
	}
	else { userGridArray[x][y] = PLAYED; axe = NONE; return true; }
}

void Board::drawText(sf::RenderWindow& win)
{
	win.draw(text);
}

void Board::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(userGrid);
	window.draw(computerGrid);
}
