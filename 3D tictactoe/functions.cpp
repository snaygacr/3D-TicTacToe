#include <bits/stdc++.h>
//#include<Header.h>
#include "Header.h"
using namespace std;

bool checkCollinear(Coor P, Coor Q, Coor R) //Method to check if 3 points are collinear
{
    //Algorithm: will make use of 2 vectors PQ and PR. If the cosine of angle between the two is +1 or -1, it's collinear else not.
    Coor PQ, PR; //Coor struct can be used for vector purpose too.
    PQ.i = Q.i-P.i, PQ.j = Q.j-P.j, PQ.k = Q.k-P.k;
    PR.i = R.i-P.i, PR.j = R.j-P.j, PR.k = R.k-P.k;
    double val = pow((PQ.i*PR.i+PQ.j*PR.j+PQ.k*PR.k),2)/((1.0)*(PQ.i*PQ.i+PQ.j*PQ.j+PQ.k*PQ.k)*(PR.i*PR.i+PR.j*PR.j+PR.k*PR.k));
    if(val==1)
        return true;
    else
        return false;
}

//This function finds next move for the computer, in case it doesn't get to create a collinear line
//or there is no way of blocking the human player
int logicalRandom(bool movesMade[], int Cube[][3][3])
{
    if(movesMade[Cube[1][1][1]]==0)
        return Cube[1][1][1];
    else if(movesMade[Cube[0][0][0]]==0)
        return Cube[0][0][0];
    else if(movesMade[Cube[0][0][2]]==0)
        return Cube[0][0][2];
    else if(movesMade[Cube[0][2][2]]==0)
        return Cube[0][2][2];
    else if(movesMade[Cube[0][2][0]]==0)
        return Cube[0][2][0];
    else if(movesMade[Cube[2][0][0]]==0)
        return Cube[2][0][0];
    else if(movesMade[Cube[2][0][2]]==0)
        return Cube[2][0][2];
    else if(movesMade[Cube[2][2][2]]==0)
        return Cube[2][2][2];
    else if(movesMade[Cube[2][2][0]]==0)
        return Cube[2][2][0];
    else if(movesMade[Cube[0][1][1]]==0)
        return Cube[0][1][1];
    else if(movesMade[Cube[2][1][1]]==0)
        return Cube[2][1][1];
    else if(movesMade[Cube[1][0][1]]==0)
        return Cube[1][0][1];
    else if(movesMade[Cube[1][1][0]]==0)
        return Cube[1][1][0];
    else if(movesMade[Cube[1][2][1]]==0)
        return Cube[1][2][1];
    else if(movesMade[Cube[1][1][2]]==0)
        return Cube[1][1][2];
    else if(movesMade[Cube[0][0][1]]==0)
        return Cube[0][0][1];
    else if(movesMade[Cube[0][1][0]]==0)
        return Cube[0][1][0];
    else if(movesMade[Cube[0][2][1]]==0)
        return Cube[0][2][1];
    else if(movesMade[Cube[0][1][2]]==0)
        return Cube[0][1][2];
    else if(movesMade[Cube[2][0][1]]==0)
        return Cube[2][0][1];
    else if(movesMade[Cube[2][1][0]]==0)
        return Cube[2][1][0];
    else if(movesMade[Cube[2][2][1]]==0)
        return Cube[2][2][1];
    else if(movesMade[Cube[2][1][2]]==0)
        return Cube[2][1][2];
    else
    {
        while(true)
        {
            int move = rand()%27+1;
            if(movesMade[move]==0)
                return move;
        }
    }
}

//method to find whether a win is possibles. It works on the same line as the Algorithm specified in the lecture slides
int possWin(vector<int> &Moves, bool invalidTuples[][28][28], Coor M[], bool movesMade[])
{
    int N = Moves.size();
    if(N<2) //If number of moves made is less than 2, no way of finding a win.
        return 0;
    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            int newmove=42-Moves[i]-Moves[j]; //Possible third move
            if(newmove<=27&&newmove!=Moves[i]&&newmove!=Moves[j]) //This third move should fulfill basic conditions - unique, and <=27
            {
                if(!movesMade[newmove]) //Move hasn't been made
                {
                    //Making sure num1<num2<num3 for easy handling of info.
                    int num1=min(Moves[i],min(Moves[j],newmove)), num3=max(Moves[i],max(Moves[j],newmove));
                    int num2=42-num1-num3;
                    if(!invalidTuples[num1][num2][num3]) //Make sure this tuple isn't actually invalid;
                    {
                        Coor P=M[num1], Q=M[num2], R=M[num3];
                        if(checkCollinear(P,Q,R)==1) //Call collinear function
                        {
                            return newmove; //If collinear this is the winning move
                        }
                    }
                }
            }
        }
    }
    return 0;
}

//This method is mainly for the human player, in case he/she is able to score a win.
bool scoredPoint(vector<int> &Moves, bool covered[][28][28], Coor M[], bool invalidTuples[][28][28])
{
    int N=Moves.size();
    if(N<3)
        return 0; //If N<3 no point scored
    //Finding whether a point has been scored, and marking down the tuple which scored a point
    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            for(int k=j+1; k<N; k++)
            {
                if(Moves[i]+Moves[j]+Moves[k]==42) //Sum must be 42
                {
                    //Again num1<num2<num3.
                    int num1=min(Moves[i],min(Moves[j],Moves[k])), num3=max(Moves[i],max(Moves[j],Moves[k]));
                    int num2=42-num1-num3;
                    if(!invalidTuples[num1][num2][num3]) //Tuple shouldn't be invalid
                    {
                        Coor P=M[num1], Q=M[num2], R=M[num3];
                        if(checkCollinear(P,Q,R)==1&&!covered[num1][num2][num3]) //Collinear and tuple not covered yet.
                        {
                            covered[num1][num2][num3]=1; //if tuple covered no need to look for anymore. In fact, it's guaranteed that this is the only tuple which hasn't been marked down yet
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void printProgressCube(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3])
{
    cout<<"Surfaces:"<<endl;
    cout<<endl;
    cout<<"Top Surface:"<<endl;
    for(int j=0; j<3; j++)
    {
        for(int k=0; k<3; k++)
        {
            int elem = Cube[0][j][k];
            if(find(HMoves.begin(), HMoves.end(), elem) != HMoves.end())
            {
                cout<<"H"<<" ";
            }
            else if(find(CMoves.begin(), CMoves.end(), elem) != CMoves.end())
            {
                cout<<"C"<<" ";
            }
            else
                cout<<elem<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Middle Surface:"<<endl;
    for(int j=0; j<3; j++)
    {
        for(int k=0; k<3; k++)
        {
            int elem = Cube[1][j][k];
            if(find(HMoves.begin(), HMoves.end(), elem) != HMoves.end())
            {
                cout<<"H"<<" ";
            }
            else if(find(CMoves.begin(), CMoves.end(), elem) != CMoves.end())
            {
                cout<<"C"<<" ";
            }
            else
                cout<<elem<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Bottom Surface:"<<endl;
    for(int j=0; j<3; j++)
    {
        for(int k=0; k<3; k++)
        {
            int elem = Cube[2][j][k];
            if(find(HMoves.begin(), HMoves.end(), elem) != HMoves.end())
            {
                cout<<"H"<<" ";
            }
            else if(find(CMoves.begin(), CMoves.end(), elem) != CMoves.end())
            {
                cout<<"C"<<" ";
            }
            else
                cout<<elem<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

//Human has the first move always
void playBoard(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3], bool invalidTuples[][28][28], Coor M[])
{
    int countH=0, countC=0;
    bool movesMade[28]= {};
    bool covered[28][28][28]= {}; //Collinear tuples covered
    int move;
    for(int i=1; i<=28; i++) //28th move is there for convenience of code, doesn't affect the functionality
    {
        if(i%2==1)//This is human move
        {
            cout<<"Enter the move you want to play: ";
            cin>>move;
            while(movesMade[move] || (move<1 || move>27))
            {
                if(move<1 || move>27) //Invalid move
                    cout<<"Invalid entry. Select Another: ";
                else //Already finished move
                    cout<<"This space has already been filled. Select another: ";
                cin>>move;
            }
            HMoves.push_back(move); //Store the move
            movesMade[move]=1; //Move marked
            if(scoredPoint(HMoves, covered, M, invalidTuples))
            {
                countH++; //If a point is scored, update counter for human
                if(countH >= 3)
                    break;
            }
        }
        else //This is computer Move
        {
            if(i==28);
            else if(i/2<2) //Both computer and human haven't made enough moves for computer to try/block a point
            {
                int move=logicalRandom(movesMade, Cube); //Make a move
                CMoves.push_back(move); //Store the move
                movesMade[move]=1; //Move marked
            }
            else
            {
                //Priority order: Check Computer Win > Block Human Win > logiacalRandom
                int win=possWin(CMoves, invalidTuples, M, movesMade);
                if(win>0&&!movesMade[win]) //If winning move for computer exists, and that move hasn't been made yet
                {
                    CMoves.push_back(win); //Make that move and score the point
                    movesMade[win]=1; //Move marked
                    scoredPoint(CMoves, covered, M, invalidTuples);
                    countC++;
                    if(countC >= 3)
                        break;
                }
                else
                {
                    win=possWin(HMoves, invalidTuples, M, movesMade);
                    if(win&&!movesMade[win]) //If winning move for human exists and it hasn't been played yet (probably need not check this part) then block the move!
                    {
                        CMoves.push_back(win); //Play the move blocking a point for human
                        movesMade[win]=1; //Move marked
                    }
                    else
                    {
                        move=logicalRandom(movesMade, Cube); //If can't do anything, find a move using logicalRandom() method
                        CMoves.push_back(move);
                        movesMade[move]=1;
                    }
                }
            }
            //Printing moves of humans and computers after every even move
            cout<<"Your moves: [ ";
            for(int k=0; k<HMoves.size(); k++)
            {
                cout<<HMoves[k]<<" ";
            }
            cout<<"]"<<endl;
            cout<<"Computer's moves: [ ";
            for(int k=0; k<CMoves.size(); k++)
            {
                cout<<CMoves[k]<<" ";
            }
            cout<<"]"<<endl;
            printProgressCube(HMoves, CMoves, Cube);
        }
    }
    //method which declares who won
    cout<<"Game Over! Your score is "<<countH<<" and Computer's score is "<<countC<<endl;
    if(countH>countC && countH >= 3)
        cout<<"You win!"<<endl;
    else if(countC>countH && countC >= 3)
        cout<<"Computer wins!"<<endl;
    else
        cout<<"It's a tie!"<<endl;
}
