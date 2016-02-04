//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016


#include<d3dx9.h>
#include<d3d9.h>
#include<vector>
#include<fstream>
#include<cmath>
#include"heightmap.h"
using namespace std;

class terrain
{
public:
	terrain(IDirect3DDevice9* dev,string file,int verRowCount,int verColCount,int grid,float scale);
	terrain();


	void terrainVertIndices(IDirect3DDevice9* dev,int verts,int width,int depth,int verRowCount,int verColCount,int grid);
	void texture(IDirect3DDevice9* dev,int verRowCount,int verColCount,float scale,int color);
	float getHeight(float xAxis,float zAxis,int verRowCount,int verColCount,int grid);
	float interpolation(float a,float b,float time){return a-(a*time) + (b*time);};
	void terrainDraw(IDirect3DDevice9* dev,D3DXMATRIX* W,bool tri,int verRowCount,int verColCount,bool wireFrame);
	IDirect3DVertexBuffer9* vb;
	IDirect3DIndexBuffer9* ib;
	IDirect3DTexture9* tex;


struct vertex
{
	vertex(){}

	float x1;
	float y1;
	float z1;
	
	float u1;
	float v1;

	vertex(float x, float y, float z, float u, float v)
	{
		x1 = x;
		y1 = y;
		z1 = z;
		u1 = u;
		v1 = v;
	}
	
};

};
