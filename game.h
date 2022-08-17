#pragma once
#include <bits/stdc++.h>
#include "point.h"
#include "move.h"
#include "print.h"

using namespace std;


//Player ..
//a player holds all the moves he has performed.. 
class Player{
    public:
        vector<struct move> moves;
        Player();
        // get move gets input and applies move...
        // while predict move takes in other players moves and moves accordingly
        // both return a bool indicating whether they made a line..!
        bool predictMove(set<int>&,vector<struct move>,vector<vector<vector<pair<int,int>>>>&,int,vector<vector<point>>);
        struct move getWinningMove(set<int>&,vector<vector<vector<pair<int,int>>>>,vector<struct move>,vector<vector<point>>);
        struct point getRandPoint(vector<vector<vector<pair<int,int>>>>);
        struct move getRandomMove(set<int>&,vector<vector<vector<pair<int,int>>>>&,int);
        struct move getLineFromOnePoint(set<int>&,vector<vector<vector<pair<int,int>>>>&,int,vector<struct move>,vector<vector<struct point>>);
        struct move badMove(set<int>&,vector<vector<vector<pair<int,int>>>>,int,vector<struct move>,vector<vector<struct point>>);
};

// this class holds a representable game state object so it can easily be displayed in ui..!
class GameState{
public : 
	vector<vector<vector<pair<int,int>>>> grid;
    	vector<vector<vector<struct move>>> winningMoves;
	set<int> availableNumbers;
	vector<Player> players; // an array of players .. so it can easily be extended to more players..
	vector<int> n; // number of rounds won by player 1 and player 2..
	bool IsGameOver;
        int round;
};

// game class which maintains the order and the result of each round..
class Game{
    int cubeSize;
    int p[2]; // boolean for prediction..
    vector<vector<vector<pair<int,int>>>> grid; // maintains the grid of the current game. ie.{who owns it,what value}..
    vector<vector<vector<struct move>>> winningMoves;
    vector<vector<point>> collinearPoints; // precomputed collinear points..!
    vector<vector<point>> noFacDiagCollinearLines;
    set<int> availableNumbers;
    vector<int> n; // number of rounds won by player 1 and player 2..
    int round; // if even then player 1 decides if odd player 2 decides .. 
    int mxWins; // the first to win these many games is the winner..!
    bool IsGameOver;
    vector<Player> players; // an array of players .. so it can easily be extended to more players..
    public:
        Game();
        Game(int,int,int,int);// takes in two int params 0 if human 1 if computer plays..2 if computer but random..
        bool validate(int,int,int); // method to validate the input..
        bool win(int); // check if game ends..
        struct point getInput();// human input 
        void apply(struct move,int);
        void gameLoop(); // main game loop..
        GameState play(); // simulates one game loop..
        void updateWins();
        void updateWinsHelper(int);
        void reset(); // reset and start a new game..!

};

// method to get a collinear point..
//point getCollinearPoint(point,point);
// method to generate all possible collinear points in a cube..
//vector<vector<point>> generateCollinearPoints();
