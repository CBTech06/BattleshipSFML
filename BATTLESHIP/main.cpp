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

#include "main.hpp"

void Battleship::init()
{
	win.create(sf::VideoMode(1024,610),"SFML GameDev");
}

void Battleship::loop()
{
	std::srand(time(NULL));
	Board board;
	computerBoard computer;
	board.init();
	
	Boat boat;
	boat.initialize();
	
	Game game;

	board.addSensorsToGrid();
	computer.addSensorsToGrid();	

	while(win.isOpen()) {
		sf::Event event;
		while(win.pollEvent(event))
		{
			if(event.type == event.KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
			   		win.close();
			}
			
			if(event.type == sf::Event::Closed)
					win.close();	
		}
		
		win.clear(sf::Color::White);
		board.draw(win);
		board.updateEvent(win,event,boat);
		if(game.check(board)) { game.start(win,board,boat,computer);	}
		board.detectBoatOnGrid(boat); 
		// computer.addBoxToSquare(win);
		// board.addBoxToSquare(win);
		computer.readGridInfo(win,boat);
		boat.draw(win);
		board.readUserGridInfo(win,boat);
		board.drawText(win);
		win.display();
	}

}

int main(int argc,char *argv[])
{
	Battleship battleship;
	battleship.init();
	battleship.loop();
}
