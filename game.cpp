#include "game.h"

int getM(int x){
   return (x * (pow(x,3) + 1))/2;
}

int madd(int i,int j,int m){
    return (i + j + m)%m;
}
void siamese_3d(vector<vector<vector<pair<int,int>>>>& grid,int i,int j,int k,int n,int mx_val){
    if(n > mx_val)
        return;
    grid[i][j][k].second = n;
    if(grid[madd(i,-1,grid.size())][j][madd(k,-1,grid.size())].second == -1)
        return siamese_3d(grid,madd(i,-1,grid.size()),j,madd(k,-1,grid.size()),n + 1,mx_val);
    if(grid[madd(i,-1,grid.size())][madd(j,-1,grid.size())][k].second == -1)
        return siamese_3d(grid,madd(i,-1,grid.size()),madd(j,-1,grid.size()),k,n + 1,mx_val);
    if(grid[madd(i,1,grid.size())][j][k].second == -1)
        return siamese_3d(grid,madd(i,1,grid.size()),j,k,n + 1,mx_val);
}

Player :: Player(){

}


struct move Player :: getRandomMove(set<int>& s,vector<vector<vector<pair<int,int>>>>& grid,int who){
    struct point randPoint = getRandPoint(grid); 
    s.erase(grid[randPoint.x][randPoint.y][randPoint.z].second);
    grid[randPoint.x][randPoint.y][randPoint.z].first = who;
    return {randPoint,grid[randPoint.x][randPoint.y][randPoint.z].second};
}

struct move Player :: getLineFromOnePoint(set<int>& s,vector<vector<vector<pair<int,int>>>>& grid,int who,vector<struct move> moves,vector<vector<point>> collinearLines){
   // fix a point .. go through all collinear lines and check if there is one which satisfies the req cond. 
   for(struct move m : moves){
       // now for all lines check if there are two empty slots and one match..
       for(vector<point> line:collinearLines){
            bool match = false;
            vector<point> emptyPoints;
            for(int i = 0;i < 3;i++){
                if(line[i] == m.pt)
                    match = true;
                else if(grid[line[i].x][line[i].y][line[i].z].first == -1)emptyPoints.push_back(line[i]);
            }
            if(!match || emptyPoints.size() < 2)
                continue;
            point emptyPoint = emptyPoints[0];
            grid[emptyPoint.x][emptyPoint.y][emptyPoint.z].first = who;
            s.erase(grid[emptyPoint.x][emptyPoint.y][emptyPoint.z].second);
            return {emptyPoint,grid[emptyPoint.x][emptyPoint.y][emptyPoint.z].second};
       }
       }
   return {-1,-1,-1,-1};
}

bool Player :: predictMove(set<int>& s,vector<struct move> opponentMoves,vector<vector<vector<pair<int,int>>>>& grid,int who,vector<vector<point>> collinearLines){
        // first try to see if there is a point which is not taken if taken wins you the round !!
        struct move winMove = getWinningMove(s,grid,moves,collinearLines);
        if(winMove.n != -1){
            cout << "This player did a winning move !" << endl;
            // this player won.. so add the move to list and return true.
            moves.push_back(winMove);
            
            grid[winMove.pt.x][winMove.pt.y][winMove.pt.z].first = who;
            s.erase(winMove.n);
            return true;
        }
        
        // grief the other guy ..!
        struct move griefMove = getWinningMove(s,grid,opponentMoves,collinearLines);
        if(griefMove.n != -1){
            cout << "This Player griefed the other Player's win" << endl;
            moves.push_back(griefMove);
            grid[griefMove.pt.x][griefMove.pt.y][griefMove.pt.z].first = who;
            s.erase( grid[griefMove.pt.x][griefMove.pt.y][griefMove.pt.z].second );
            return false; // remember you didnt win ..!
        }
        // if that is not possible aswell then pick a point such that after you pick it  you move to a state where you need one more move to win..ie pick a point st ..
        // 1. a point in moves is already present in the line
        // 2. there are 2 free points in that line .
        // 3. obviously the line is collinear..!
        struct move betterThanRandom = getLineFromOnePoint(s,grid,who,moves,collinearLines);
        if(betterThanRandom.n != -1){
            cout << "Did a better move than random.. !" << betterThanRandom.n<<  endl;
            moves.push_back(betterThanRandom);
            return false;
      }
        // if nothing worked and we have no option then random it is..!
        cout << "Random round" <<endl;
        struct move randMove = getRandomMove(s,grid,who);
        moves.push_back(randMove);
        return false;
    }

struct move Player :: getWinningMove(set<int>& s,vector<vector<vector<pair<int,int>>>> grid,vector<struct move> moves,vector<vector<point>> collinearLines){
    if(moves.size() <= 1)
        return {-1,-1,-1,-1};
    for(int i = 0;i < moves.size();i++){
        for(int j = i + 1;j < moves.size();j++){
            point newPoint = getCollinearPoint(moves[i].pt,moves[j].pt,collinearLines);
            //check if it is already visited..
            if(newPoint.x != -1 && grid[newPoint.x][newPoint.y][newPoint.z].first == -1)
                return {newPoint,grid[newPoint.x][newPoint.y][newPoint.z].second};
        }
    }
    return {-1,-1,-1,-1};
}


struct point Player :: getRandPoint(vector<vector<vector<pair<int,int>>>> grid){
    // find a point that is not visited yet..!
    int x = rand()%3,y = rand()%3,z = rand()%3;
    while(grid[x][y][z].first != -1){
        x = rand()%3;
        y = rand()%3;
        z = rand()%3;
    }
    return {x,y,z};
}

// Game definitions ..

Game :: Game(){}

Game :: Game(int pi1,int pi2,int mx,int size){
    p[0] = pi1;
    p[1] = pi2;
    mxWins = mx;
    for(int i = 0;i < 2;i++){
        players.push_back(Player());
        n.push_back(0);
    }
    winningMoves.resize(2);
    round = 0;
    for(int i = 1;i <= size * size * size;i++)
        availableNumbers.insert(i);

    grid.resize(size);
    for(int i = 0;i < size;i++)
        grid[i].resize(size);
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            grid[i][j].resize(size);
    fill(grid.begin(),grid.end(),vector<vector<pair<int,int>>>(size,vector<pair<int,int>>(size,{-1,-1})));
    siamese_3d(grid,0,0,0,1,size * size * size);
    collinearPoints = generateCollinearPoints();
    vector<point> corners = {{0,0,0},{0,cubeSize - 1,0},{0,0,cubeSize - 1},{cubeSize - 1,0,0},{cubeSize -1,cubeSize - 1,0},{0,cubeSize - 1,cubeSize - 1},{cubeSize - 1,0,cubeSize - 1},{cubeSize -1,cubeSize - 1,cubeSize - 1}};
    fillLines(collinearPoints,corners,noFacDiagCollinearLines);
    cout << "size : " << noFacDiagCollinearLines.size() << endl;
}

bool Game :: validate(int x,int y,int z){
    if(grid[x][y][z].first != -1)
        return false;
    return true;
}

struct point Game :: getInput(){
            int x,y,z;        
            // human input ..
            cout << "(x,y,z) : ";
            cin >> x >> y >> z;
            while(!validate(x,y,z)){
                cout << "Invalid input try again(x,y,z) : " << endl;
                cout << "(x,y,z) : ";
                cin >> x >> y >> z;
            }
            return {x,y,z};
}

void Game :: apply(struct move m,int who){
    availableNumbers.erase(m.n);
    grid[m.pt.x][m.pt.y][m.pt.z] = {who,m.n}; 
}

bool Game :: win(int mx){
    if(round < mx)
        return false;
    if(n[0] > n[1]){
        cout << "player 1 won..!";
    }
    else if(n[1] > n[0])
        cout << "player 2 won .. !";
    else
        cout << "draw" << endl;
    cout << endl;
    return true;
}

void Game :: updateWinsHelper(int c){
        for(int i = 0;i < players[c].moves.size();i++){
        for(int j = i + 1;j < players[c].moves.size();j++){
            // get the winning move .. check if it already exists in the current set..!
            struct point colPoint = getCollinearPoint(players[c].moves[i].pt,players[c].moves[j].pt,collinearPoints);
            if(colPoint.x == -1)
                continue;
            // for this to be winning we need MAGIC - (i.n + j.n) as the value..
            struct move winMove = {colPoint,getM(cubeSize) - (players[c].moves[i].n + players[c].moves[j].n)};
            // check if it exists here..
            bool exists = false;
            for(int k = j + 1;k < players[c].moves.size();k++)
                if(players[c].moves[k] == winMove)
                    exists = true;
            if(exists){
                n[c]++;
                winningMoves[c].push_back({players[c].moves[i],players[c].moves[j],winMove});
            }
    }
}
}

void Game :: updateWins(){
    n[0] = n[1] = 0;
    winningMoves[0].clear(); winningMoves[1].clear();
    updateWinsHelper(0);updateWinsHelper(1);
}


GameState Game :: play(){	
 	int context = round % 2;
        if(p[context] == 1){
            struct point inpPoint = getInput();
            struct move inpMove = {inpPoint,grid[inpPoint.x][inpPoint.y][inpPoint.z].second};
            players[context].moves.push_back(inpMove);
            apply(inpMove,context);
        }
        else if(p[context] == 2){
            struct move randMove = players[context].getRandomMove(availableNumbers,grid,context); 
            players[context].moves.push_back(randMove);
        }
        else if(p[context] == 3){

        }
        else{
            players[context].predictMove(availableNumbers,players[1 - context].moves,grid,context,noFacDiagCollinearLines);
        }
        round++; // round progress..
        
        updateWins();
        GameState roundInfo;
        roundInfo.IsGameOver = win(cubeSize * cubeSize * cubeSize);
        roundInfo.availableNumbers = availableNumbers;
        roundInfo.winningMoves = winningMoves;
        roundInfo.grid = grid;
        roundInfo.players = players;
        roundInfo.n = n;
        roundInfo.round = round;
        return roundInfo;
}
