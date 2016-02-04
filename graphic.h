//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016



#include<d3dx9.h>
#include<d3d9.h>
#include"mesh.h"
#include"terrain.h"
#include"camera.h"
class graphics
{

public:
	void render(float dt,IDirect3DDevice9* dev,terrain t,vector<D3DMATERIAL9>& material01,vector<IDirect3DTexture9*> texture01,ID3DXMesh* model01,HINSTANCE h,HWND hwnd);

	ID3DXMesh* rings;
	ID3DXMesh* rings01;


};contents here
