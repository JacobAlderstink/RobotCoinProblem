#include <iostream>
using namespace std;

void PrintOptimal(int CoinCopy[][7], int F[][7], int colSize, int rowSize);
int RobotCoinCollection(int C[][7],int colSize, int rowSize);
void Print(int C[][7],int colSize,int rowSize);
void Setup(int CoinCopy[][7],int C[][7],int colSize,int rowSize);


//Applies dynamic programming to compute the largest number of
//coins a robot can collect on an n × m board by starting at (1, 1)
//and moving right and down from upper left to down right corner
//Input: Matrix C[1..n, 1..m] whose elements are equal to 1 and 0
//for cells with and without a coin, respectively
//Output: Largest number of coins the robot can bring to cell (n, m)
int main(){
  int C[6][7];
  int CoinCopy[6][7];
  Setup(CoinCopy,C,6,7);
  Print(C,6,7);
  int x = RobotCoinCollection(C,6,7);
  cout <<"  The Largest number of coins that are possible to collect is: " << x << endl;
  cout <<"  Below is the optimal path:" <<  endl;
  PrintOptimal(CoinCopy,C,6,7);
}

 

void PrintOptimal(int CoinCopy[][7], int F[][7], int colSize, int rowSize)
{
  
  bool Path[6][7];
  for(int i = 0; i < colSize; i++)
    {
      for(int j = 0; j < rowSize; j++)
	{
	Path[i][j] = false;
      }
    }
  Path[5][6] = true;
  for(int i  = colSize-1; i > 0; i--)
    {
      for(int j = rowSize-1; j > 0; j--)
	{
	  if(j == rowSize -1 && i == colSize -1){
	    continue;
	  }
	  else if(j == rowSize-1)
	    {
	      if(Path[i+1][j] == true && (F[i+1][j] == F[i][j] || (F[i+1][j] == F[i][j]+1 && CoinCopy[i+1][j] == 1)))
		{
		  Path[i][j] = true;
		}
	    }
	  else if(i == colSize-1)
	    {
	      if(Path[i][j+1] == true && (F[i][j+1] == F[i][j] || (F[i][j+1] == F[i][j]+1 && CoinCopy[i][j+1] == 1))){
		Path[i][j] = true;
	      }
	    }
	  else{
	    if(Path[i+1][j] == true && (F[i+1][j] == F[i][j] || (F[i+1][j] == F[i][j]+1 && CoinCopy[i+1][j] == 1))){
	      Path[i][j] = true;
	    }
	      if(Path[i][j+1] == true && (F[i][j+1] == F[i][j] || (F[i][j+1] == F[i][j]+1 && CoinCopy[i][j+1] == 1))){
	      Path[i][j] = true;
	    }
	  }
	}
    }



  for(int i = 0; i < colSize; i++){
    cout << "  ";
    for(int j = 0; j < rowSize; j++){
      if(Path[i][j] == true)
	cout << 1 << "  ";
      else
	cout << 0 << "  ";
    }
    cout << endl;
  }
}
	  
void Setup(int CoinCopy[][7],int C[][7],int colSize,int rowSize){
  for(int i = 0; i < colSize; i++){
    for(int j = 0; j < rowSize; j++){
      C[i][j]=0;
      CoinCopy[i][j] = 0;
    }
  }

  CoinCopy[1][2] = -1;
  CoinCopy[2][4] = -1;
  CoinCopy[3][4] = -1;
  CoinCopy[5][1] = -1;
  CoinCopy[5][2] = -1;
  CoinCopy[5][3] = -1;
  

  CoinCopy[1][4] = 1;
  CoinCopy[2][1] = 1;
  CoinCopy[2][5] = 1;
  CoinCopy[3][2] = 1;
  CoinCopy[3][5] = 1;
  CoinCopy[4][4] = 1;
  CoinCopy[4][6] = 1;
  CoinCopy[5][5] = 1;

  
  C[1][2] = -1;
  C[2][4] = -1;
  C[3][4] = -1;
  C[5][1] = -1;
  C[5][2] = -1;
  C[5][3] = -1;
  

  C[1][4] = 1;
  C[2][1] = 1;
  C[2][5] = 1;
  C[3][2] = 1;
  C[3][5] = 1;
  C[4][4] = 1;
  C[4][6] = 1;
  C[5][5] = 1;
}

void Print(int C[][7],int colSize,int rowSize)
{
  cout << endl;
  for(int i = 0; i < colSize; i++){
    for(int j = 0; j < rowSize; j++){
      if(C[i][j] == -1)
	cout  << " " << C[i][j];
      else
	cout  << "  "<< C[i][j];
    }
    cout << endl;
  }
}

int RobotCoinCollection(int C[][7],int colSize, int rowSize){
  int F[colSize][7];
  int j;
  int i;
  //F[0][0]=C[0][0];
  for(i =0; i< colSize; i++)
    { 
      for(j = 0; j < rowSize; j++){
	F[i][j] = C[i][j];
      }
    }

  for(i =1; i< colSize; i++)
    { 
      for(j = 1; j < rowSize; j++){
	if(i == 1 && F[i][j] == -1){
	  for(int k = j; k < rowSize; k++){
	    F[i][k] = -1;
	  }
	  break;
	}
	else if(F[i-1][j] == -1 && F[i][j-1] == -1)
	  F[i][j] = -1;
      }
    }
  
  for(i =1; i< colSize; i++)
    { 
      for(j = 1; j < rowSize; j++){
	if(F[i][j] == -1)
	  continue;
	F[i][j] = max(F[i-1][j], F[i][j-1]) + F[i][j];
      }
    }
  for(i =0; i< colSize; i++)
    { 
      for(j = 0; j < rowSize; j++){
	C[i][j] = F[i][j];
      }
    }
  
  
  Print(F,6,7);
  return F[colSize-1][rowSize-1];
}
