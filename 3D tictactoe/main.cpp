#include <bits/stdc++.h>
#include "Header.h"
using namespace std;

int main()
{
    int Cube[3][3][3]; //intializing cube array and option variable
    cout<<"Generating and printing Magic Cube"<<endl;
    MagicCube MC; //Object of class MagicCube. Member functions explained above
    MC.generateCube(3);
    MC.printCube();
    MC.getCube(Cube);

    Coor M[28]; //Stores the coordinates corresponding to a number in [1,27];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                Coor P;
                P.i=i, P.j=j, P.k=k;
                M[Cube[i][j][k]]=P;//Storing the coordinates
            }
        }
    }
    //Generate all the tuples that add up to 42 but aren't collinear
    bool check[28][28][28]= {}; //Check if a tuple has already been generated and checked or not.
    bool invalidTuples[28][28][28]= {}; //If a tuple is a valid one (add upto 42) and isn't collinear, then the value is to be marked 1.
    // cout<<"Generating non collinear numbers that add upto 42"<<endl;
    for(int a=1; a<=27; a++)
    {
        for(int b=a+1; b<=27; b++)
        {
            int c=42-a-b;
            if(c>0&&c<=27&&c!=a&&c!=b) //Generating valid numbers (a,b,c) that denotes a tuple.
            {
                int num1=min(a,min(b,c)), num3=max(a,max(b,c));
                int num2=42-num1-num3; //sequencing (a,b,c) s.t. a<=b<=c
                if(!check[num1][num2][num3]) //If tuple hasn't been checked yet.
                {
                    check[num1][num2][num3]=1;
                    Coor P = M[num1], Q=M[num2], R=M[num3];
                    if(!checkCollinear(P,Q,R)) //If tuple isn't collinear
                    {
                        // cout<<num1<<" "<<num2<<" "<<num3<<endl;
                        invalidTuples[num1][num2][num3]=1; //We keep track of non collinear valid tuples
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    vector<int> HMoves, CMoves;
    playBoard(HMoves, CMoves, Cube, invalidTuples, M);
}
