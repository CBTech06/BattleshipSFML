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

#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "boat.hpp" 

class Boat;
class Board;

class computerBoard 
{
	private:
		const int TILESIZE;
		const int EMPTY;
		const int MISSED;
		const int FILLED;
		const int BUSY;
		const int HORIZONTAL;
		const int VERTICAL;
		const int SMALL_BOAT_SIZE;
		const int MEDIUM_BOAT_SIZE;
		const int BIG_BOAT_SIZE;
		const int COMPUTERGRID_OFFSET_X;
		const int COMPUTERGRID_OFFSET_Y;
		const int MAX_CASE;
		const int MAX_ROTATION;
		const int SENSOR_SIZE;
		int boat;
		int computerBoatOrientation;
		int computerStartPosition;
		int positionX;
		int positionY;
		int computerSquarePositionX;
		int computerSquarePositionY;
		int l;
		int r;
		int cx;
		int cy;
		int choiceX;
		int choiceY;
		bool touched;
		bool isPressed;
		std::vector<sf::FloatRect> computerGridSquare;
		std::array<std::array<int,10>,10> computerGridArray;
	public:
		computerBoard();							
		void setComputerGrid();						 
		void spawn();								 
		void spawnSmallBoats();							
		void spawnMediumBoats();					
		void spawnBigBoats();						
		void readGridInfo(sf::RenderWindow&,Boat&);				
		bool checkCase(const int&,const int&,const int&);		 
		void checkBoatLength(const int&,const int&,const int&);			
		void fillGrid(const int&,const int&, const int&,const int& );		
		void addSensorsToGrid();						
		void addBoxToSquare(sf::RenderWindow&);				
		bool gridEvent(sf::RenderWindow&);					
		bool hitBoat(int&, const int&);					 
		bool returnHitInformation();						
		bool getBoatInfo();							
		void spawnChoice();							
		bool play(Board&);						
		void drawPlayedCase(sf::RenderWindow&,const int&, const int&);		
};

#endif
