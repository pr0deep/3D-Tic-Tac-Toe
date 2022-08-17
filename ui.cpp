#include "ui.h"
#include "move.h"
void generateUiText(sf :: Text&text ,const std :: string s,sf :: Font& font,unsigned int x,unsigned int y){
        text.setFont(font);
        text.setString(s);
        text.setCharacterSize(24); // in pixels, not points!
        text.setFillColor(sf::Color::Black);
        text.setPosition(x,y);
}
void generateUiText(sf :: Text&text ,const std :: string s,sf :: Font& font,unsigned int x,unsigned int y,int size){
        text.setFont(font);
        text.setString(s);
        text.setCharacterSize(size); // in pixels, not points!
        text.setFillColor(sf::Color::Black);
        text.setPosition(x,y);

}
void drawCube(sf :: RenderWindow& window,sf :: Font& font,vector<vector<vector<pair<int,int>>>> grid,int plane,int x,int y){
        // define a 120x50 rectangle
        int cubeSize = 300 / grid.size();
        for(int i = 0;i < grid.size();i++){
            for(int j = 0;j < grid.size();j++){
                sf :: RectangleShape rect(sf :: Vector2f(cubeSize,cubeSize));
                rect.setPosition(i*cubeSize + x,j*cubeSize + y);
                rect.setOutlineColor(sf :: Color ::Black);
                rect.setOutlineThickness(1);
                if(grid[plane][i][j].first != -1){
                    if(grid[plane][i][j].first == 0) 
                    rect.setFillColor(sf :: Color :: Green);
                    else rect.setFillColor(sf :: Color :: Red);
                    window.draw(rect);
                }
                else{
                    rect.setFillColor(sf :: Color(80,80,80));
                    window.draw(rect);
                }
                sf :: Text coord;
                generateUiText(coord,"("+ to_string(plane)+","+to_string(i)+","+to_string(j)+")",font,x + i*cubeSize,y + j*cubeSize,12);
                window.draw(coord);
                sf :: Text text;
                generateUiText(text,to_string(grid[plane][i][j].second),font,x + i*cubeSize + cubeSize/2 - 10,y + j*cubeSize + cubeSize/2 - 10);
                window.draw(text);
            }
        }
}
void Menu:: draw(sf :: RenderWindow& win,sf :: Font& font){
    sf :: Text text;
    generateUiText(text,"3D - Tic Tac Toe",font,500,200,70);
    win.draw(text);
    generateUiText(text,"1 . Human vs AI",font,550,500,40);
    win.draw(text);
    generateUiText(text,"2. AI vs AI(default)",font,550,550,40);
    win.draw(text);
    
}

void RoundDisplay:: draw(sf :: RenderWindow& window,sf :: Font & font,GameState game){
            sf :: Text text;
            string round = "Round " + to_string(game.round);
            generateUiText(text,round,font,10,0);
            window.draw(text);
            // display cube..
            unsigned int cubeX = 10,cubeY = 50,offset = 350;
            for(int z = 0;z < 3;z++){
                drawCube(window,font,game.grid,z,cubeX,cubeY);
                cubeX += offset;
            }
            // winning moves ?
            for(int i = 0;i < 2;i++){
                generateUiText(text,"wl for p" + to_string(i + 1) + " : ",font,10,500 + 120 * i);
                window.draw(text);
                if(game.winningMoves[i].size() == 0){generateUiText(text,"None",font,120,500 + 120 * i);window.draw(text);}
                for(int j = 0;j < game.winningMoves[i].size();j++){
                    vector<struct move> mv = game.winningMoves[i][j];
                    ostringstream mystream;
                    mystream << "{";
                    for(struct move m : mv){
                        mystream << "{" << m.pt.x << "," << m.pt.y <<","<<m.pt.z <<","<<m.n<<"}";
                    }
                    mystream << "}";
                    if(j < 4) generateUiText(text,mystream.str(),font,120 + 310*j,500 + 120*i);
                    else if(j < 8) generateUiText(text,mystream.str(),font,120 + 310*(j - 4),560 + 120*i);

                    window.draw(text);
                }
            }
            // score
            string score = "Score : " + to_string(game.n[0]) + " - " + to_string(game.n[1]);
            generateUiText(text,score,font,10,window.getSize().y - 100);
            window.draw(text);

        }

