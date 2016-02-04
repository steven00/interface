Enter file contents here//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016



#include<d3dx9.h>
#include<d3d9.h>
#include<vector>
#include<fstream>
#include<cmath>
#include <dinput.h>

using namespace std;

class camera
{
public:

	camera();
	void strafe(float a);
	
	void y(float a);
	void forward(float a);

	void angleUp(float a);
	void angleRight(float a);

	void getView(D3DXMATRIX* view);
	void getpos(D3DXVECTOR3* positions);
	void setpos(D3DXVECTOR3* positions);

	void Keyuse(char key,HINSTANCE h,HWND hwnd);
	bool keyAction(char key);
	D3DXVECTOR3 position;
	D3DXVECTOR3 up;
	D3DXVECTOR3 look;
	D3DXVECTOR3 right;

	IDirectInput8* input;
	IDirectInputDevice8* board;
	char state[256];
};
