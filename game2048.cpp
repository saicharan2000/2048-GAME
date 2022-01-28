#include<bits/stdc++.h>
using namespace std;

int board[4][4];
int dirrow[]={1,0,-1,0}; // mapping directions ==[ 0-D, 1-R , 2-U, 3-L ]
int dircol[]={0,1,0,-1};

pair<int,int> unoccupied()
{
    int occupied=1;
    int row,col;
    while(occupied)
    {
        row = rand()%4;
        col = rand()%4;
        if(board[row][col]==0)
        {
            occupied=0;
        }
    }
    return make_pair(row,col);
}

void addpiece()
{
    pair<int,int> pos = unoccupied();
    board[pos.first][pos.second]=2;
}

void newgame()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            board[i][j]=0;
        }
    }
    addpiece();
}

bool win()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(board[i][j]==2048)
            {
                return true;
            }
        }
    }
    return false;
}

void print()
{
    system("cls");      // CLEAR screen
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(board[i][j]==0)
            {
                cout << setw(4) << ".";
            }
            else
            {
                cout << setw(4) << board[i][j];
            }
        }
        cout << endl;
    }
    cout << "n : NEW GAME , a : LEFT , d : RIGHT , w : UP , s : DOWN , q : QUIT" << endl;
}

bool canmove(int r,int c,int nextr,int nextc)
{
    if(nextr<0 || nextc<0 || nextr>=4 || nextc>=4 || (board[r][c]!=board[nextr][nextc]&&board[nextr][nextc]!=0))
        return false;
    return true;
}

void applydir(int dir)
{
    int strtrow=0, strtcol=0,rowstep=1,colstep=1;
    if(dir==0)
    {
        strtrow=3;
        rowstep=-1;
    }
    if(dir==1)
    {
        strtcol=3;
        colstep=-1;
    }
    int movepossible,canaddpiece=0;

    while(movepossible)
    {
        movepossible=0;
        for(int i=strtrow;i>=0 && i<4;i+=rowstep)
        {
            for(int j=strtcol;j>=0 && j<4;j+=colstep)
            {
                int nexti=i+dirrow[dir], nextj=j+dircol[dir];
                if(board[i][j]!=0 && canmove(i,j,nexti,nextj))
                {
                    board[nexti][nextj]+=board[i][j];
                    board[i][j]=0;
                    movepossible=canaddpiece=1;
                }
            }
        }
        print();
        if(win())
        {
            cout << "CONGRATS !! You Won";
        }
    }
    if(canaddpiece!=1)
    {
        cout << "GameOver";    }
    if(canaddpiece)
    {
        addpiece();
    }
}

int main()
{
    srand(time(0));
    char ctodir[128];
    ctodir['s']=0;
    ctodir['d']=1;
    ctodir['w']=2;
    ctodir['a']=3;
    newgame();
    while(true)
    {
        print();
        char c;     // Input command --> new game,quit....
        cin >> c;
        if(c=='n')
        {
            newgame();
        }
        else if(c=='q')
        {
            cout << "quit the game" << endl;
            break;
        }
        else
        {
            int currdir = ctodir[c];
            applydir(currdir);
        }
    }
    return 0;
}
