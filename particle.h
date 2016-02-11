#include"camera.h"
#include<list>
#include<string>
//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 2/10/2016

struct Pexist
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vel;

	float time;
	float longevity;
	
	D3DXCOLOR colorTime;
	bool life;

	Pexist()
	{
		time = 0;
		longevity = 0;
		life = true;

	}

};

struct fire
{
	D3DXVECTOR3 pos;
	D3DCOLOR col;
	static const DWORD FVF;
};

class particle
{

public:
	void particleAdd( int num);


	list<Pexist> dots;

	void particleTexture(IDirect3DDevice9* dev, char* fileName);
	void particleUpdate(float dt);
	bool endParticle(float & x,float & y,float & z);
	void particleVector(D3DXVECTOR3* axis, D3DXVECTOR3* low, D3DXVECTOR3* upper);
	float particleValue(float little, float large);
	void particleDraw(IDirect3DDevice9* dev,int particleEffects);
	void setParticleDirection(list<Pexist>::iterator iter,float x,float y, float z);
	
	IDirect3DVertexBuffer9* partVB;
	IDirect3DTexture9* ParticleTexture;

	DWORD offset;
	DWORD size;
	DWORD numVerts;

};
