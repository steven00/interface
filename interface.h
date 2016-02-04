#include"graphics.h"


//IDirect3D9 *dir;
//vector<D3DMATERIAL9> material01(0);
//vector<IDirect3DTexture9*> texture01(0);
//ID3DXMesh* model01 = 0;
//D3DXMATRIX projection;
//terrain *terrains;
//graphics run;


class Interface
{
public:
	void XfilesColor(IDirect3DDevice9* dev,float color);
	void movement(IDirect3DDevice9* dev,float dt,terrain t,camera & camcorder,int & shipDirectionalFlag,bool autoMovement);
	void ringLocation(IDirect3DDevice9* dev,ID3DXMesh* rings,bool active,int shape,float speed,float scale,char rotate,float x, float y, float z);
	void arbitraryEffects(IDirect3DDevice9* dev,vector<D3DMATERIAL9>& material01,vector<IDirect3DTexture9*> texture01,ID3DXMesh* model01,bool active,int arbitraryNum);
	void terrainMode(IDirect3DDevice9* dev,terrain & t,bool active,bool wireframeFlag);
	void terrainColor(IDirect3DDevice9* dev,terrain & t,int color);
	void gameStop(float & speed,bool stopSoon);
private:
		float UserSpeed;
		float TempSpeed;
};
