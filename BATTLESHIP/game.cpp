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

#include "game.hpp"


Game::Game():USER(0),COMPUTER(1),STARTED(1)
{
	state = 0;
	secondHitPlayed = false;
}

bool Game::check(Board& board)
{
	if(board.getBoatInfo() == 13)
	{	
		board.messageBox("OK   THE   GAME    CAN    START.    READY    ???");
		return true;
	}
	else if( board.getBoatInfo() > 13)
	{
		board.messageBox("SET    THE    CORRECT    PLACE    OF    THE    BOAT");
	}
	else { board.messageBox("PLACE    EACH    BOATS    ON    THE    GRID");}

	return false;
}


void Game::start(sf::RenderWindow& win,Board& board,Boat& boat,computerBoard& cb)
{
	if(cb.getBoatInfo()) { board.messageBox(" COMPUTER    LOOSE" ); }
	else if(!board.checkBoatOnGrid()) { board.messageBox("YOU    LOOSE.    COMPUTER    WIN"); }

	else if(!cb.getBoatInfo() || board.checkBoatOnGrid()) {
		// USER PLAY ON COMPUTER GRID
		if(state == USER) {
			board.messageBox("YOU    CAN    PLAY    ON    THE    COMPUTER    GRID");
			if(cb.gridEvent(win)) {
				// IF THE GAME IS STARTED SET STATUS TO FALSE AND BLOCK BOAT POSITION
        			boat.setStatus(false);	
				 if(cb.returnHitInformation() && !secondHitPlayed) {	state = USER; secondHitPlayed = true; }
				else { state =	COMPUTER; secondHitPlayed = false;}
			}
		}
		else {
			// COMPUTER PLAY ON THE USER GRID
			if(cb.play(board)) { state = USER; }
			else { board.messageBox("COMPUTER    WIN.    IT    PLAYS    AGAIN"); cb.play(board);
			       state = USER;
			       	}
			board.messageBox("COMPUTER PLAYS");
		}
	}
}

