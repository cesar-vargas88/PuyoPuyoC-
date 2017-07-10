// PuyoPuyo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//////////////////////////////////
//			Puyo Puyo			//
//////////////////////////////////

///////////////////////////////
//	     Puyo Parameters	 //
///////////////////////////////

int DrawPuyo[2] = {1,2};
int Color[16][2] =  {{1,1},{1,2},{1,3},{1,4},
					 {2,1},{2,2},{2,3},{2,4},
					 {3,1},{3,2},{3,3},{3,4},
					 {4,1},{4,2},{4,3},{4,4}}; 
int RamColor = 0;
int PuyoRotation	= 0;
int PuyoImpact[2]	= {0,0};
int PilaPuyo[16][2];
int ContPila = 0;

/////////////////////
//		Board	   //
/////////////////////

int Board [6][12];
int WidthBoard	= 36;
int LengthBoard	= 48;
int PuyoBoardPosition[2][2];
int i;
int j;

/////////////////////
//	   Others	   //
/////////////////////

int push1		= 0;
int push		= 0;
int nCount		= 0;
int Game_Over	= 0;
int Refresh		= 0;
int appIsRunning = 0;

//////////////////////
//	   Constant		//
//////////////////////

#define right 0
#define left  1
#define up    2
#define down  3

//struct POINT A,B;

//////////////////////
//		Cubos		//
//////////////////////
/*
rom unsigned char SpriteBlanco[8]=
{
	0x0,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF
};
rom unsigned char SpriteCubo1[8]=
{
	0xFF,
	0x81,
	0x81,
	0x99,
	0x99,
	0x81,
	0x81,
	0xFF
};
rom unsigned char SpriteCubo2[8]=
{
	0xFF,
	0xC3,
	0xA5,
	0x99,
	0x99,
	0xA5,
	0xC3,
	0xFF
};
rom unsigned char SpriteCubo3[8]=
{
	0xFF,
	0x81,
	0x81,
	0x81,
	0x81,
	0x81,
	0x81,
	0xFF
};
rom unsigned char SpriteCubo4[8]=
{
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};
rom unsigned char SpriteNegro[8]=
{
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};
*/
/////////////////////
//	   Methods	   //
/////////////////////

void DrawBoard()
{
	/*PORTD = 0x00;
	TRISD = 0x00;
	
	//Establecer las tintas de brocha (relleno) y pluma (filete)
	g_GLCDBrush=GLCD_BLACK;
	
	//////////////////////////////////////
	//			Dibujamos Marco			//
	//////////////////////////////////////
	
	A.x=15;
	A.y=7;
	B.x=113;
	B.y=7;	
	ATGLine(&A,&B);
	
	A.x=112;
	A.y=8;
	B.x=112;
	B.y=56;	
	ATGLine(&A,&B);
	
	A.x=112;
	A.y=56;
	B.x=15;
	B.y=56;	
	ATGLine(&A,&B);
	
	A.x=15;
	A.y=56;
	B.x=15;
	B.y=7;	
	ATGLine(&A,&B);
	
	//Establecer las tintas de brocha (relleno) y pluma (filete)
	g_GLCDBrush=GLCD_WHITE;
	
	for(j=0;j<6;j++)
	{
		for(i=0;i<12;i++)
		{
			g_GLCDX=(i*8)+16;
			g_GLCDY=(j*8)+8;
			
			switch(Board[j][i])
			{
				case 0:					//Cubo blanco
				{
					ATGWriteCombineNx8Sprite(SpriteBlanco,8);	
					break;
				}
				case 1:					//Cubo 1
				{
					ATGWriteCombineNx8Sprite(SpriteCubo1,8);	
					break;
				}
				case 2:					//Cubo 2
				{
					ATGWriteCombineNx8Sprite(SpriteCubo2,8);
					break;
				}
				case 3:					//Cubo 3
				{
					ATGWriteCombineNx8Sprite(SpriteCubo3,8);
					break;
				}
				case 4:					//Cubo 4
				{
					ATGWriteCombineNx8Sprite(SpriteCubo4,8);
					break;
				}
				case 10:				//Cubo negro
				{
					ATGWriteCombineNx8Sprite(SpriteNegro,8);
					break;
				}
			}	
			ESS_Delay(10);
		}
	}*/
}
void GameOver()
{
	Game_Over = 1;
	//ESS_Delay(1000);
	// Clean the board

	for (i = 0 ; i < 6 ; i++)
	{
		for (j = 0; j < 12 ; j++)
		{
			Board [i][j] = 10;									// Fill all with 0
		} 
	}
}

void NewPuyo()
{
	PuyoImpact[0] = 0;	// Indicate that puyo isn´t crashed
	PuyoImpact[1] = 0;	// Indicate that puyo isn´t crashed

	PuyoRotation = 1;

	if (RamColor < 15)  RamColor++;
	else				RamColor=0;

	DrawPuyo[0] = Color[RamColor][0];
	DrawPuyo[1] = Color[RamColor][1];
	
	PuyoBoardPosition[0][0] = 2;		// Set xPosition of new Puyo
	PuyoBoardPosition[0][1] = 0;		// Set yPosition of new Puyo

	PuyoBoardPosition[1][0] = 2;		// Set xPosition of new Puyo
	PuyoBoardPosition[1][1] = 1;		// Set yPosition of new Puyo

	if (Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] == 0 )  // If the new Puyo have problems with the board Puyos, the game ends
	{
		Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
	}
	else					
	{
		Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
		GameOver();
	}
}

void NewGame()
{
	// Clean the board
	for (i = 0 ; i < 6 ; i++)
	{
		for (j = 0; j < 12 ; j++)
		{
			Board [i][j] = 0;									// Fill all with 0
		} 
	}
//	ESS_Delay(100);
	PuyoImpact[0] = 1;
	PuyoImpact[1] = 1;
	Game_Over = 0;
	PuyoRotation = 1;
}
void Moving(void)
{
	for (j = 11 ; j > 0 ; j --)
	{
		for (i = 0 ; i < 5 ; i++)
		{
			if (Board[i][j] == 0)
			{
				int cont = j;
				while (cont > 1)
				{
					if (Board[i][cont] != 0 )
					{
						Board[i][j] = Board[i][cont];
						Board[i][cont] = 0;
						cont = 0;
					}
					cont--;
				}
			}
		}
	}
}
void Clear()
{
	int x = 0;
	do
	{
		Board [PilaPuyo[x][0]] [PilaPuyo[x][1]] = 0;
		x++;
	}
	while(x < ContPila);
}

void floodfillrec(int x, int y, int origen)
{
	int permiso = 1;
	int cont;
	
	if(ContPila>0)
	{
		for(cont = 0 ; cont < ContPila-1 ; cont++)
		{
			if(PilaPuyo[cont][0] == x && PilaPuyo[cont][1] == y)
			{
				permiso = 0;
			}
		}
	}

	if (permiso)
	{
		//if square match at right
		if (x < 5 && Board[x+1][y] == Board[x][y] && origen != left)
		{
			if(ContPila == 0)
			{
				PilaPuyo[ContPila][0] = x;
				PilaPuyo[ContPila][1] = y;
				ContPila++;
			}
			PilaPuyo[ContPila][0] = x+1;
			PilaPuyo[ContPila][1] = y;
			ContPila++;
			floodfillrec(x+1,y,right);
		}
		//left
		if (x > 0 && Board[x-1][y] == Board[x][y] && origen!= right)
		{
			if(ContPila == 0)
			{
				PilaPuyo[ContPila][0] = x;
				PilaPuyo[ContPila][1] = y;
				ContPila++;
			}
			PilaPuyo[ContPila][0] = x-1;
			PilaPuyo[ContPila][1] = y;
			ContPila++;
			floodfillrec(x-1,y,left);
		}
		//up
		if (y > 0 && Board[x][y] == Board[x][y-1] && origen!= down)
		{
			if(ContPila == 0)
			{
				PilaPuyo[ContPila][0] = x;
				PilaPuyo[ContPila][1] = y;
				ContPila++;
			}
			PilaPuyo[ContPila][0] = x;
			PilaPuyo[ContPila][1] = y-1;
			ContPila++;
			floodfillrec(x,y-1,up);
		}
		//down
		if (y < 11 && Board[x][y] == Board[x][y+1] && origen!= up)
		{
			if(ContPila == 0)
			{
				PilaPuyo[ContPila][0] = x;
				PilaPuyo[ContPila][1] = y;
				ContPila++;
			}
			PilaPuyo[ContPila][0] = x;
			PilaPuyo[ContPila][1] = y+1;
			ContPila++;
			floodfillrec(x,y+1,down);
		}
	}
}
int floodfill()
{
	int erased = 0;

	for (j = 11 ; j >= 0 ; j--)
	{
		for (i = 0 ; i < 5 ; i++)
		{
			if (Board[i][j] != 0)
			{
				floodfillrec(i, j, -1);
				if (ContPila > 3)
				{
					Clear();
					Moving();
					erased = 1;
				}
				ContPila = 0;
			}
		}
	}

	return erased;
}
void MoveLeft()
{
	if (push == 2)
	{	
		Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
		Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = 0;					// Clear Puyo 2

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		if ((PuyoRotation == 1 || PuyoRotation == 3) && PuyoBoardPosition[0][0] > 0)
		{	
			if ( Board [PuyoBoardPosition[0][0] - 1] [PuyoBoardPosition[0][1]] == 0 &&
				 Board [PuyoBoardPosition[1][0] - 1] [PuyoBoardPosition[1][1]] == 0 &&
				 PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
			{						
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] - 1;							// Forward y position of Puyo 1
				PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] - 1;							// Forward y position of Puyo 2
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 2 on Board
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			}
			else
			{							
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			}
		}
		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		if (PuyoRotation == 2 && PuyoBoardPosition[0][0] > 0 && 
			Board [PuyoBoardPosition[0][0] - 1] [PuyoBoardPosition[0][1]] == 0 &&
			PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
		{	
			
			PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] - 1;							// Forward y position of Puyo 2
			PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] - 1;							// Forward y position of Puyo 1
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		}

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		if (PuyoRotation == 0 && PuyoBoardPosition[1][0] > 0 && 
			Board [PuyoBoardPosition[1][0] - 1] [PuyoBoardPosition[1][1]] == 0 &&
			PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
		{	
			
			PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] - 1;							// Forward y position of Puyo 2
			PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] - 1;							// Forward y position of Puyo 1
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		}
		else 
		{
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
		}
		push = 0;
	}
	push ++;
}
void MoveRight()
{
	if (push == 2)
	{	
		Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
		Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = 0;					// Clear Puyo 2

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		if ((PuyoRotation == 1 || PuyoRotation == 3) && PuyoBoardPosition[0][0] < 5)
		{	
			if ( Board [PuyoBoardPosition[0][0] + 1] [PuyoBoardPosition[0][1]] == 0 &&
				 Board [PuyoBoardPosition[1][0] + 1] [PuyoBoardPosition[1][1]] == 0 &&
				 PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
			{						
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] + 1;							// Forward y position of Puyo 1
				PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] + 1;							// Forward y position of Puyo 2
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 2 on Board
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			}
			else
			{							
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			}
		}
		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		else if (PuyoRotation == 2 && PuyoBoardPosition[1][0] < 5 && 
			Board [PuyoBoardPosition[1][0] + 1] [PuyoBoardPosition[0][1]] == 0 &&
			PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
		{	
			
			PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] + 1;							// Forward y position of Puyo 2
			PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] + 1;							// Forward y position of Puyo 1
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		}

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		else if (PuyoRotation == 0 && PuyoBoardPosition[0][0] < 5 && 
			Board [PuyoBoardPosition[0][0] + 1] [PuyoBoardPosition[0][1]] == 0 &&
			PuyoImpact[0] == 0 && PuyoImpact[1] == 0)
		{	
			
			PuyoBoardPosition[1][0] = PuyoBoardPosition[1][0] + 1;							// Forward y position of Puyo 2
			PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] + 1;							// Forward y position of Puyo 1
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
		}
		else 
		{
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 2 on Board
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
		}
		push = 0;
	}
	push ++;
}
void MoveDown()
{	
	if (push1 == 2)
	{	
		Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
		Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = 0;					// Clear Puyo 2

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		if (PuyoRotation == 1 && PuyoBoardPosition[1][1] < 11 && Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1] + 1] == 0)
		{
			PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] + 1;							// Forward y position of Puyo 1
			PuyoBoardPosition[1][1] = PuyoBoardPosition[1][1] + 1;							// Forward y position of Puyo 2
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board	
		}

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		else if ( (PuyoRotation == 2 || PuyoRotation == 0 ) && PuyoBoardPosition[1][1] < 11 && PuyoBoardPosition[0][1] < 11)
		{
			if (Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1] + 1] == 0)
			{
				PuyoBoardPosition[1][1] = PuyoBoardPosition[1][1] + 1;							// Forward y position of Puyo 2
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board	
			}
			else
			{		
				Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board	
				PuyoImpact[1] = 1;
			}
			if (Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1] + 1] == 0)
			{
				PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] + 1;							// Forward y position of Puyo 1
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
			}
			else
			{
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				PuyoImpact[0] = 1;
			}
		}

		// If Puyo 2 doesn't leave the board or collides with another Puyo, to advance a position
		else if (PuyoRotation == 3 && PuyoBoardPosition[0][1] < 11 && Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1] + 1] == 0)
		{
			PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] + 1;							// Forward y position of Puyo 1
			PuyoBoardPosition[1][1] = PuyoBoardPosition[1][1] + 1;							// Forward y position of Puyo 2
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board	
		}
		else 
		{
			PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1];								// Forward y position of Puyo 1
			PuyoBoardPosition[1][1] = PuyoBoardPosition[1][1];								// Forward y position of Puyo 2
			Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
			Board [PuyoBoardPosition[1][0]] [PuyoBoardPosition[1][1]] = DrawPuyo[1];		// Draw new Puyo 2 on Board
			PuyoImpact[0] = 1;
			PuyoImpact[1] = 1;
		}
		push1 = 0;
	}
	push1 ++;
}
void Rotation() 
{
	if (push == 2)
	{	
		if (PuyoRotation == 1)  // If Puyo is one position
		{
			// If Puyo 1 doesn't leave the board or collides with another Puyo, to advance a position
			if (PuyoBoardPosition[0][0]  > 0 &&												
				Board [PuyoBoardPosition[0][0] - 1] [PuyoBoardPosition[0][1]] == 0 &&
				Board [PuyoBoardPosition[0][0] - 1] [PuyoBoardPosition[0][1] + 1] == 0)
			{						
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] - 1;							// Forward x position of Puyo 1
				PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] + 1;							// Forward y position of Puyo 1
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				PuyoRotation = 2;
			}
		}
		else if (PuyoRotation == 2)  // If Puyo is two position
		{
			// If Puyo 1 doesn't leave the board or collides with another Puyo, to advance a position
			if (PuyoBoardPosition[0][1]  < 11 &&												
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1] + 1] == 0 &&
				Board [PuyoBoardPosition[0][0] + 1] [PuyoBoardPosition[0][1] + 1] == 0)
			{						
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] + 1;							// Forward x position of Puyo 1
				PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] + 1;							// Forward y position of Puyo 1
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				PuyoRotation = 3;
			}
		}
		else if (PuyoRotation == 3)  // If Puyo is three position
		{
			// If Puyo 1 doesn't leave the board or collides with another Puyo, to advance a position
			if (PuyoBoardPosition[0][0] < 5 &&												
				Board [PuyoBoardPosition[0][0] + 1] [PuyoBoardPosition[0][1]] == 0 &&
				Board [PuyoBoardPosition[0][0] + 1] [PuyoBoardPosition[0][1] - 1] == 0)
			{						
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] + 1;							// Forward x position of Puyo 1
				PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] - 1;							// Forward y position of Puyo 1
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				PuyoRotation = 0;
			}
		}
		else if (PuyoRotation == 0)  // If Puyo is zero position
		{
			// If Puyo 1 doesn't leave the board or collides with another Puyo, to advance a position
			if (PuyoBoardPosition[0][1]  > 0 &&												
				Board [PuyoBoardPosition[0][0]]     [PuyoBoardPosition[0][1] - 1] == 0 &&
				Board [PuyoBoardPosition[0][0] - 1] [PuyoBoardPosition[0][1] - 1] == 0)
			{						
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = 0;					// Clear Puyo 1
				PuyoBoardPosition[0][0] = PuyoBoardPosition[0][0] - 1;							// Forward x position of Puyo 1
				PuyoBoardPosition[0][1] = PuyoBoardPosition[0][1] - 1;							// Forward y position of Puyo 1
				Board [PuyoBoardPosition[0][0]] [PuyoBoardPosition[0][1]] = DrawPuyo[0];		// Draw new Puyo 1 on Board
				PuyoRotation = 1;
			}
		}
		push = 0;
	}
	push ++;
}

void PuyoPuyo()
{
	appIsRunning = 1;									// Boolean flag to state whether app is running or not.

	Game_Over		= 0;
	PuyoImpact[0]	= 1;
	PuyoImpact[1]	= 1;
	nCount			= 0;
	push			= 0;
	push1			= 0;
	PuyoRotation	= 1;
	RamColor		= 1;
	
	/*for (i=0;i<6;i++)
		for(j=0;j<12;j++)
			Board[i][j] = 1;
	*/
	int nRefreshBoard=0;

	while(1)
	{	
		if(appIsRunning)
		{
			//////////////////////////////////////////
			//		Configuración para teclado		//
			//////////////////////////////////////////
			nRefreshBoard++;
			if(nRefreshBoard==100)
			{
				DrawBoard();
				nRefreshBoard=0;
			}
			/*if (Game_Over == 1)
			{
				ESS_Delay(1000);
				DrawBoard();				// Call DrawBoard
			}*/
			if (PuyoImpact[0] == 1 && PuyoImpact[1] == 1 )				// If Puyo is placed, it creates a new 
			{
				while(floodfill());

				NewPuyo();
			}
			if (nCount == 20)			// Puyo falls one position each 5 ms
			{
				MoveDown();				
				nCount = 0;	
			}	
			nCount++;	
		}

		/*
		PORTD=0x00;	
		TRISD=0xf0;
		
		if(KB_Hit() == 0xff)
		{
			ucTecla = KB_Get();
			
			switch(ucTeclaPresionada[ucTecla])
			{
				case '2':		//Rotar
				{
					Rotation();
					break;
				}
				case '4':		//Izquierda
				{
					MoveLeft();
					break;
				}
				case '5':		//Pausa
				{
					if(appIsRunning)
						appIsRunning = 0;
					else
						appIsRunning = 1;
					break;
				}
				case '6':		//Derecha
					MoveRight();
					break;
				case '8':		//Bajar
				{
					MoveDown();	
					break;	
				}
				case '*':		//Juego Nuevo
				{
					NewGame();
					break;
				}
			}
			ESS_Delay(400);
		}*/
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	PuyoPuyo();
	return 0;
}


