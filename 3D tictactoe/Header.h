#include <bits/stdc++.h>
using namespace std;

class MagicCube
{
private:
    int myCube [3][3][3];
public:
    MagicCube() //Constructor for initialization
    {
        memset(myCube, 0, sizeof(myCube));
    }
    void generateCube(int n) //Start generating cube
    {
        int i=0,j=n/2,k=n/2,num;//fixing the position of 1st number

        for(num=1; num<=n*n*n;)
        {
            myCube[i][j][k]=num++;
            i--;//decrementing row by 1
            i=wrap(n,i);//wrap works if i value becomes -1 or 3
            k--;//decrementing height by 1
            k=wrap(n,k);
            if(myCube[i][j][k]!=0) //checking if the position is already filled
            {
                j--;//decrementing column by 1
                j=wrap(n,j);
                k++;//incrementing height by 1
                k=wrap(n,k);
                if(myCube[i][j][k]!=0)
                {
                    j++;//incrementing column by 1
                    j=wrap(n,j);
                    i=i+2;//incrementing row by 2
                    i=wrap(n,i);

                }

            }
        }
    }

    int wrap(int n,int index)
    {
        if(index<0)
        {
            index= index+n;
        }
        else if(index>n-1)
        {
            index=index-n;
        }
        return index;
    }

    void printCube() //method to print the Magic Cube according to specifications
    {
        cout<<"Surfaces:"<<endl;
        cout<<endl;
        cout<<"Top Surface:"<<endl;
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                cout<<myCube[0][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

        cout<<"Middle Surface:"<<endl;
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                cout<<myCube[1][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

        cout<<"Bottom Surface:"<<endl;
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                cout<<myCube[2][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void getCube(int outCube [][3][3]) //method to return the Magic Cube
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                for(int k=0; k<3; k++)
                {
                    outCube[i][j][k]=myCube[i][j][k];
                }
            }
        }
    }
};

struct Coor //A struct to define coordinate type for better handling
{
    int i, j, k;
};

bool checkCollinear(Coor , Coor , Coor );
int logicalRandom(bool movesMade[], int Cube[][3][3]);
int possWin(vector<int> &Moves, bool invalidTuples[][28][28], Coor M[], bool movesMade[]);
bool scoredPoint(vector<int> &Moves, bool covered[][28][28], Coor M[], bool invalidTuples[][28][28]);
void printProgressCube(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3]);
void playBoard(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3], bool invalidTuples[][28][28], Coor M[]);
