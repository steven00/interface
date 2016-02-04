#include"interface.h"


//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 2/3/2016

camera camcorder;
static float speed = 0;
int shipDirectionalFlag = 0;
Interface User;


//This is used for method        User.gameStop()
#define STOP_GAME TRUE
#define DONT_STOP_GAME FALSE

//shapes for the rings
//this is used for the method 	 User.ringLocation()
#define CIRCLE 1
#define TRIANGLE 2
#define DIAMOND 3
#define ALL 4

//colors for the ship
//This is used for the method	 User.XfilesColor()
#define SHIP_RED 1
#define SHIP_GREEN 2
#define SHIP_BLUE 3
#define SHIP_PURPLE 4
#define SHIP_LIGHTBLUE 5


//This is use for the method    User.terrainColor()
#define HILL_RED 1
#define HILL_PURPLE 2
#define HILL_BLUE 3
#define HILL_PINK 4
#define HILL_YELLOW 5
#define HILL_GREEN 6
#define HILL_PLAIN 7

//This is used for the method   User.movement()
#define AUTO_MOVE TRUE
#define MANUAL_MOVE FALSE

//This is used for the method   User.terrainMode()
#define WIREFRAME TRUE
#define NON_WIREFRAME FALSE





void graphics::render(float dt,IDirect3DDevice9* dev,terrain t,vector<D3DMATERIAL9>& material01,vector<IDirect3DTexture9*> texture01,ID3DXMesh* model01,HINSTANCE hInstance,HWND hwnd)
{
	//speed += .01;
	

	
	User.gameStop(speed,STOP_GAME);

	User.XfilesColor(dev,SHIP_PURPLE);

	User.terrainColor(dev,t,HILL_GREEN);
	dev->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0xff000fff,1.0f,0);
	dev->BeginScene();
	
	
	
	
	User.movement(dev,dt,t,camcorder,shipDirectionalFlag,MANUAL_MOVE);

	//This function still has some bugs
	User.arbitraryEffects(dev,material01,texture01,model01,true,3);
	

	User.terrainMode(dev,t,true,NON_WIREFRAME);

	//This will have the user pick which shape they want as for its direction, speed, and rotation
for(int i =0;i < 4; i++)
	User.ringLocation(dev,rings,true,CIRCLE,.0005,3,'y',-20+ (i *35),60,140);
	/*rings01->Release();
	rings->Release();*/
	dev->EndScene();
	dev->Present(0,0,0,0);

}


	





	
