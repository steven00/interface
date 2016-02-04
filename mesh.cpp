#include"mesh.h";

//REFERENCE:
//this code is a modified version from the book "INTRODUCTION TO 3D GAME Programming with DirectX 9.0 by Frank Luna
//code changed and modified by stephan vinent
// Date modified: 1/21/2016
vector<IDirect3DTexture9*> text(0);
void mesh::loadXfiles(IDirect3DDevice9* dev,vector<D3DMATERIAL9>& material01,vector<IDirect3DTexture9*>& texture01,ID3DXMesh* &model01)
{
	 material = 0;
	 adjancy = 0;
	 materialCount = 0;

	D3DXLoadMeshFromX("Assets/bigship1.x",D3DXMESH_MANAGED,dev,&adjancy,&material,0,&materialCount,&model01);// This ship model belongs to frank Luna


	if(material != 0 && adjancy != 0)
	{
		D3DXMATERIAL* mat = (D3DXMATERIAL*)material->GetBufferPointer();


		for(int i = 0; i < materialCount; i++)
		{
			mat[i].MatD3D.Ambient = mat[i].MatD3D.Diffuse;

			material01.push_back(mat[i].MatD3D);

			texture01.push_back(0);
		}

	}

	model01->OptimizeInplace(D3DXMESHOPT_ATTRSORT |D3DXMESHOPT_COMPACT|D3DXMESHOPT_VERTEXCACHE,(DWORD*)adjancy->GetBufferPointer(),0,0,0);



}

//THIS WILL GET THE LIGHTING FOR THE OBJECT
void mesh::XfilesGraphics(IDirect3DDevice9* dev,float palette)
{
	dev->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	dev->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	dev->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_POINT);

	D3DXVECTOR3 direction(1,-1,1);
	float red = 1;
	float blue = 1;
	float green = 1;

	if(palette == 1)
	{
		red = 1;
		blue = 0;
		green = 0;

	}

	if(palette == 2)
	{
		red = 0;
		blue = 0;
		green = 1;

	}

	if(palette == 3)
	{
		red = 0;
		blue = 1;
		green = 0;

	}

	if(palette == 4)
	{
		red = 1;
		blue = 1;
		green = 0;

	}


	if(palette == 5)
	{
		red = 1;
		blue = .2;
		green = .8;

	}

	if(palette == 6)
	{
		red = 1;
		blue = .1;
		green = .5;

	}

	if(palette == 7)
	{
		red = 0;
		blue = 0;
		green = 0;

	}


	if(palette == 8)
	{
		red = 1;
		blue = 1;
		green = 1;

	}


	D3DXCOLOR color(red,green,blue,1);
	
	

	D3DLIGHT9 lig;
	ZeroMemory(&lig,sizeof(lig));

	lig.Ambient = color * 0.666f;
	lig.Diffuse = color;
	lig.Direction = direction;
	lig.Specular = color * 0.543f;
	lig.Type = D3DLIGHT_DIRECTIONAL;

	dev->SetLight(0,&lig);
	dev->LightEnable(0,true);
	dev->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	dev->SetRenderState(D3DRS_SPECULARENABLE,true);

	D3DXVECTOR3 position(4,11,-3);
	D3DXVECTOR3 post(0,0,0);
	D3DXVECTOR3 y(1,0,0);

	D3DXMATRIX ver;
	D3DXMatrixLookAtLH(&ver,&position,&post,&y);

	dev->SetTransform(D3DTS_VIEW,&ver);



}
