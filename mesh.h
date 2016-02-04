#include<d3dx9.h>
#include<d3d9.h>
#include<vector>
using namespace std;

//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016
class mesh
{
public:
	void loadXfiles(IDirect3DDevice9* dev,vector<D3DMATERIAL9> &material01,vector<IDirect3DTexture9*>& texture01,ID3DXMesh* &model01);
	void XfilesGraphics(IDirect3DDevice9* dev,float palette);


	ID3DXBuffer* material;
	ID3DXBuffer* adjancy;
	DWORD materialCount;

	ID3DXMesh* model;
	
	vector<D3DMATERIAL9> M;
	
};
