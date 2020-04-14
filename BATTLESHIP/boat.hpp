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

#ifndef BOAT_HPP
#define BOAT_HPP

#include <iostream>
#include <vector>
#include "string"
#include "array"
#include <SFML/Graphics.hpp>

#include "board.hpp"


class Boat
{
	private:
		sf::Sprite sprite;
		sf::Sprite explosion;
		sf::Sprite filledCase;
		sf::Sprite playedCase;
		sf::Texture playedTexture;
		sf::Texture explosionTexture;
		sf::Texture boatTexture;				  
		sf::Texture filledTexture;
		sf::Vector2f position;
		std::vector<sf::IntRect> textureRect;
		std::vector<sf::Vector2f> origin;
		std::vector<Boat> boat;
		std::string state;	
		std::string rotation;
		const int BOATCOUNT;
		const int HORIZONTAL;
		const int VERTICAL;
		const int MARGIN;
		const int STARTED;
		bool canSelect;
		bool status;
	public:
		Boat();											
		void initialize();						
		void setStatus(bool);					
		void select(sf::RenderWindow&,sf::Vector2i);					
		void rotate(sf::Vector2i,sf::Event&);			
		void move(sf::RenderWindow&);							 
		bool checkPositionOnGrid(sf::FloatRect& );			
		const sf::FloatRect getBoatPosition();				
		void missed(sf::RenderWindow& window, const int&,const int&);    
		void filled(sf::RenderWindow&, const int&,const int&);		
		void destroyed(sf::RenderWindow&,const int&, const int&);		
		void draw(sf::RenderWindow&);				
};
#endif
