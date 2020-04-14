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

#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "boat.hpp"
#include "computer.hpp"

class Boat;
class computerBoard;

class Board 
{
	private:
		sf::Sprite background;
		sf::Texture backgroundTexture;
		sf::Sprite computerGrid;
		sf::Texture gridTexture;
		sf::Sprite userGrid;
		sf::Clock clock;
		sf::Font font;
		sf::Text text;
		const int GAMESPEED;
		const int USERGRID_X;
		const int USERGRID_Y;
	       	const int USERGRID_OFFSET_X;
		const int USERGRID_OFFSET_Y;
		const int COMPUTERGRID_X;
		const int COMPUTERGRID_Y;
		const int SENSOR_SIZE;
		const int MAX_CASE;
		const int MAX_ROTATION;
		const int GRID_SIZE;	
		const int TILESIZE;
		const int EMPTY;
		const int PLAYED;
		const int FILLED;
		const int DESTROYED;
		const int LEFT;
		const int RIGHT;
		const int UP;
		const int DOWN;
		const int NONE;
		int axe;
		int N;
		int fx;
		int fy;
		int squarePositionX;
		int squarePositionY;
		int boatIDX;
		int positionX;
		int positionY;
		int i;
		int l;
		int r;
		int x;
		int y;
		int count;
		int old_x;
		int old_y;
		int direction;
		int idx;
		int boatOnGrid;
		sf::FloatRect grid;
		bool touched;
		bool isPressed;
		char* status;
		std::vector<sf::FloatRect> gridSquare;
		std::array<std::array<int,10>,10> userGridArray;
	public:
		Board();								
		void init();								
		void setUserGrid();							
		void readUserGridInfo(sf::RenderWindow&,Boat& );			
		void addSensorsToGrid();						 
		void detectBoatOnGrid(Boat&);						
		void setBoatOnGrid(int& ,const int&);					
		int getBoatInfo();							
		void addBoxToSquare(sf::RenderWindow&);					
		void updateEvent(sf::RenderWindow&, sf::Event&,Boat& boat);	 
		void messageBox(const char*);						
		bool checkAdjacentCase(int&,int&);
		void restoreFirstValue();						
		void checkLeftCase(int&, int&, const int&);				
		void checkRightCase(int&, int&, const int&);				
		void checkUpCase(int&, int&, const int&);			
		void checkDownCase(int&, int&, const int&);				
		bool checkComputerChoice(int&,int&);				 
		bool checkBoatOnGrid();						
		void drawText(sf::RenderWindow&);				
		void draw(sf::RenderWindow&);					
};

#endif
