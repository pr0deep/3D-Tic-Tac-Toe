#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

void generateUiText(sf :: Text& text,const std :: string s,sf :: Font& font,unsigned int,unsigned int);

void generateUiText(sf :: Text& text,const std :: string s,sf :: Font& font,unsigned int,unsigned int,int);
void drawCube(sf :: RenderWindow& window,sf :: Font& font,vector<vector<vector<pair<int,int>>>> grid,int plane);


class Menu{
    public :
        void draw(sf :: RenderWindow& window,sf :: Font&);
};

class RoundDisplay{
    public : 
        void draw(sf :: RenderWindow& window,sf :: Font & font,GameState game);

};

