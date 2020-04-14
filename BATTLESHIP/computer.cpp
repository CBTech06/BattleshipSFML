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

#include "computer.hpp"

computerBoard::computerBoard():TILESIZE(32),SENSOR_SIZE(28),EMPTY(0),FILLED(1),BUSY(2),MISSED(3),HORIZONTAL(0),VERTICAL(1),COMPUTERGRID_OFFSET_X(650),COMPUTERGRID_OFFSET_Y(150),SMALL_BOAT_SIZE(2),MEDIUM_BOAT_SIZE(3),BIG_BOAT_SIZE(5),MAX_CASE(10),MAX_ROTATION(2)
{
	positionX = 0;
	positionY = 0;
	computerSquarePositionX = 30;
	computerSquarePositionY = 130;
	boat = 13;
	l = 0;
	r = 0;
	choiceX = 0;
	choiceY = 0;
	touched = false;
	isPressed = false;
	setComputerGrid();
	computerStartPosition = 0;
	computerBoatOrientation = 0;
}

void computerBoard::setComputerGrid()
{
	for(int line=0; line < computerGridArray.size(); line++)
	{
		for(int row=0; row < computerGridArray.size(); row++)
		{
			computerGridArray[line][row] = EMPTY;
		}
	}

	spawnSmallBoats();
	spawnMediumBoats();
	spawnMediumBoats();
	spawnBigBoats();
}

void computerBoard::spawn()
{
	computerStartPosition = std::rand() % MAX_CASE;
	computerBoatOrientation = std::rand() % MAX_ROTATION;
}

void computerBoard::spawnSmallBoats()
{      
	// SPAWN TWO NUMBER TO PLACE COMPUTER BOATS ON THE CARD
	spawn();

	 checkBoatLength(computerStartPosition,computerBoatOrientation,SMALL_BOAT_SIZE);
	 if(!checkCase(computerStartPosition,computerBoatOrientation,SMALL_BOAT_SIZE))
	 { 
		for(int i=0; i < SMALL_BOAT_SIZE;i++)
	 	{
			if(computerBoatOrientation == HORIZONTAL)
				fillGrid(computerBoatOrientation, computerStartPosition,
					 computerStartPosition + i, SMALL_BOAT_SIZE);
			else 
				fillGrid(computerBoatOrientation, computerStartPosition + i,
					 computerStartPosition, SMALL_BOAT_SIZE);
	 	}
	 }
	 else { spawnSmallBoats(); }
}

void computerBoard::spawnMediumBoats()
{
	spawn();

	 checkBoatLength(computerStartPosition,computerBoatOrientation,MEDIUM_BOAT_SIZE);
	 
	 // 2 X MEDIUM
	 if(!checkCase(computerStartPosition,computerBoatOrientation,MEDIUM_BOAT_SIZE))
	 { 
	 	for (int i = 0; i < MEDIUM_BOAT_SIZE;i++)
	 	{
			if(computerBoatOrientation == HORIZONTAL)
				
				fillGrid(computerBoatOrientation, computerStartPosition,
					 computerStartPosition + i, MEDIUM_BOAT_SIZE);
			else 
				fillGrid(computerBoatOrientation, computerStartPosition + i,
					 computerStartPosition, MEDIUM_BOAT_SIZE);
		}
	}
	 else { spawnMediumBoats(); }
}

void computerBoard::spawnBigBoats()
{
	spawn();

	checkBoatLength(computerStartPosition,computerBoatOrientation,BIG_BOAT_SIZE);
	if(!checkCase(computerStartPosition,computerBoatOrientation,BIG_BOAT_SIZE))
	{	
	// BIG
		for(int i = 0; i < BIG_BOAT_SIZE; i++)
		{
			if(computerBoatOrientation == HORIZONTAL)
				fillGrid(computerBoatOrientation, computerStartPosition + i,
				 computerStartPosition, BIG_BOAT_SIZE);
			else 
				fillGrid(computerBoatOrientation, computerStartPosition,
				 computerStartPosition + i, BIG_BOAT_SIZE);
		}
	}
	else { spawnBigBoats(); }
}

void computerBoard::readGridInfo(sf::RenderWindow& window,Boat& boat)
{
	for(int line=0; line < computerGridArray.size(); line++)
	{
		for(int row=0; row < computerGridArray.size(); row++)
		{

			if(computerGridArray [line][row] == EMPTY){ }
			else if(computerGridArray[line][row] == FILLED) {
				positionX = row * TILESIZE + COMPUTERGRID_OFFSET_X; 
				positionY = line * TILESIZE + COMPUTERGRID_OFFSET_Y;			
				boat.destroyed(window,positionX,positionY);
			}
			else if(computerGridArray[line][row] == MISSED){
				positionX = row * TILESIZE + COMPUTERGRID_OFFSET_X; 
				positionY = line * TILESIZE + COMPUTERGRID_OFFSET_Y;			
				boat.missed(window,positionX,positionY);				
			}
			else
			{
				positionX = row * TILESIZE + COMPUTERGRID_OFFSET_X; 
				positionY = line * TILESIZE + COMPUTERGRID_OFFSET_Y;			
			}
		}
	}
}

bool computerBoard::checkCase(const int& startPosition,const int& orientation,const int& boatSize)
{
	for(int i = startPosition; i < startPosition + boatSize;i++)
	{
		if(orientation == HORIZONTAL) 
		{
			l = i;
			r = startPosition;
		}
		else
		{
		      l = startPosition;
		      r = i;
		}
		
		if(computerGridArray[l][r] == BUSY) {
			return true;
		}
		else return false;
	}
}

void computerBoard::checkBoatLength(const int& startCase,const int& orientation,const int& length)
{

	// THE BOAT CAN BE LOCATED ON THE HORIZONTAL POSITION
	if(computerBoatOrientation == HORIZONTAL) {	
		if (computerStartPosition + length >=  MAX_CASE)
		{
			computerStartPosition -= length; 
			computerBoatOrientation = VERTICAL;	
		}
	}
	if(computerBoatOrientation == VERTICAL)  
	{
		if(computerStartPosition + length > MAX_CASE)
		{
			computerStartPosition -= length;
			computerBoatOrientation = HORIZONTAL;
		}
	}
}

void computerBoard::fillGrid(const int& boatOrientation,const int& line, const int& row,const int& boatSize)
{	 
			 if(computerGridArray[line][row] != FILLED)
		        	computerGridArray[line][row] = BUSY;
}

void computerBoard::addSensorsToGrid()
{
	for(int i = 0; i < MAX_CASE * MAX_CASE; i++)
	{
 		if(i % (MAX_CASE) == 0)  {
			computerSquarePositionY += TILESIZE;
			computerSquarePositionX = COMPUTERGRID_OFFSET_X;
		}	

		computerGridSquare.push_back(sf::FloatRect(sf::Vector2f(computerSquarePositionX + 5,
				     computerSquarePositionY -5),sf::Vector2f(SENSOR_SIZE,SENSOR_SIZE)));
		computerSquarePositionX += TILESIZE;
		}
}

/* COLOR FLOATRECT */ 
std::vector<sf::RectangleShape> computerColoredBox;
void computerBoard::addBoxToSquare(sf::RenderWindow& win)
{
	for(int i = 0; i < computerGridSquare.size(); i++)
	{
		computerColoredBox.push_back(sf::RectangleShape(sf::Vector2f(16,16)));
		computerColoredBox.back().setPosition(computerGridSquare[i].left,computerGridSquare[i].top);
		computerColoredBox.back().setFillColor(sf::Color::Blue);
	}

	for(int i=0; i < computerColoredBox.size(); i++)
	{
		win.draw(computerColoredBox[i]);
	}
}

bool computerBoard::gridEvent(sf::RenderWindow& win)
{
	for(int i = 0; i < computerGridSquare.size(); i++)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isPressed)
		{
			if(computerGridSquare[i].contains(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y))
			{
				isPressed = true;
				hitBoat(i,FILLED);
			        //computerGridSquare[i].width = 0;
				//computerGridSquare[i].height = 0;	
				return true;
			}
		}	
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			isPressed = false;
		}
	}
	return false;

}

bool computerBoard::returnHitInformation()
{
	if(touched) return true;
	else return false;
}

bool computerBoard::hitBoat(int& idx ,const int& status)
{
				cx = 0;
				cy = idx;

				if(idx > MAX_CASE) {
					cx = std::abs(idx / MAX_CASE);
					cy = idx % MAX_CASE;
				}

				if(computerGridArray[cx][cy] == BUSY) {
					computerGridArray[cx][cy] = status; 
					boat--;
					touched = true;
				}				
				
				if(computerGridArray[cx][cy] == EMPTY) {
					computerGridArray[cx][cy] = MISSED;
					touched = false;
				}
}

bool computerBoard::getBoatInfo()
{ // IF BOAT = 0 FUNCTION RETURN TRUE AND THE COMPUTER LOST
	if(boat  > 0) 
	 {
		 return false;
	 }
	else
	{
		return true;
	}
}
void computerBoard::spawnChoice()
{
	choiceX = std::rand()% MAX_CASE;
	choiceY = std::rand()% MAX_CASE;
}

bool computerBoard::play(Board& board)
{
	spawnChoice();

	if(!board.checkComputerChoice(choiceX,choiceY)) {
		return false;
	}
	else {
		return true;
	}

}

