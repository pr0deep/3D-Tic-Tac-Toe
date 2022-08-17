#include "game.h"
#include <SFML/Graphics.hpp>
#include "ui.h"

using namespace std;


int main(){
    srand(time(0)); // seed it ..
    Game game(0,0,10,5); // human vs ai ? 
    vector<GameState> historyOfRounds; 
    int ptr = 0,mxptr = 5 * 5 * 5;// 0 indicates menu ..[0,len(vec) - 1];

    Menu menu;
    RoundDisplay roundDisp;
    sf :: Font font;
    font.loadFromFile("arial.ttf");
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "3D Tic Tac Toe",sf::Style :: Titlebar);
    
    bool displayMenu = true,gameOver = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf :: Event :: KeyPressed){
                if(event.key.code == sf :: Keyboard :: Q)
                    return 0;
                if(displayMenu){
                    // inside menu ..
                    if(event.key.code == sf :: Keyboard :: Num1){
                        game = Game(1,0,10,5);
                        displayMenu = false;
                        historyOfRounds.push_back(game.play());// first round played ..
                        ptr++;
                }
                    else if(event.key.code == sf :: Keyboard :: Num2){
                        game = Game(0,0,10,5);
                        displayMenu = false;
                        historyOfRounds.push_back(game.play());// first round played ..
                        ptr++;
                    }
                    else if(event.key.code == sf :: Keyboard :: Right){
                        // go out of menu;
                        displayMenu = false;
                        historyOfRounds.push_back(game.play());// first round played ..
                        ptr++;
                    }
                }
                else{
                    // not inside menu ..!
                    if(event.key.code == sf :: Keyboard :: Right){
                        if(ptr == mxptr)
                            continue;
                        ptr++;
                        if(ptr > historyOfRounds.size())
                            historyOfRounds.push_back(game.play());

                    }
                    if(event.key.code == sf :: Keyboard :: Left){
                        if(ptr > 0)
                            ptr--;
                        if(ptr == 0)
                            ptr++;
                    }
                }
            }

        }

        window.clear(sf :: Color(255,255,255));
        if(displayMenu)
	    menu.draw(window,font);
        else{
            roundDisp.draw(window,font,historyOfRounds[ptr - 1]);
        }
        window.display();
    }
    return 0;
}
