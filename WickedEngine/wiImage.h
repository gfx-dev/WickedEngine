#pragma once
#include "CommonInclude.h"
#include "wiGraphicsAPI.h"

class wiImageEffects;
enum BLENDMODE;

class wiImage
{
private:
	//static mutex MUTEX;
protected:
	GFX_STRUCT ImageCB
	{
		XMMATRIX mViewProjection;
		XMMATRIX mTrans;
		XMFLOAT4 mDimensions;
		XMFLOAT4 mOffsetMirFade;
		XMFLOAT4 mDrawRec;
		XMFLOAT4 mBlurOpaPiv;
		XMFLOAT4 mTexOffset;
		XMFLOAT4 mMaskDistort;

		CB_SETBINDSLOT(CBSLOT_IMAGE_IMAGE)

		ALIGN_16
	};
	GFX_STRUCT PostProcessCB
	{
		float params[16];

		CB_SETBINDSLOT(CBSLOT_IMAGE_POSTPROCESS)

		ALIGN_16
	};
	
	static BlendState		blendState, blendStateAdd, blendStateNoBlend, blendStateAvg;
	static BufferResource           constantBuffer,processCb;

	static VertexShader     vertexShader,screenVS;
	static PixelShader      pixelShader,blurHPS,blurVPS,shaftPS,outlinePS,dofPS,motionBlurPS,bloomSeparatePS
		,fxaaPS,ssaoPS,ssssPS,deferredPS,linDepthPS,colorGradePS,ssrPS;
	

	
	static RasterizerState		rasterizerState;
	static DepthStencilState	depthStencilStateGreater,depthStencilStateLess,depthNoStencilState;

public:
	static void LoadShaders();
private:
	static void LoadBuffers();
	static void SetUpStates();

public:
	wiImage();
	
	static void Draw(TextureView texture, const wiImageEffects& effects);
	static void Draw(TextureView texture, const wiImageEffects& effects,DeviceContext context);

	static void DrawDeferred(TextureView texture
		, TextureView depth, TextureView lightmap, TextureView normal
		, TextureView ao, DeviceContext context, int stencilref = 0);

	static void Load();
	static void CleanUp();
};

