#include "lightHF.hlsli"
#include "dirLightHF.hlsli"



float4 main( VertexToPixel PSIn ) : SV_TARGET
{
	float4 color = float4(lightColor.rgb,1);
	float2 screenPos;
		screenPos.x = PSIn.pos2D.x/PSIn.pos2D.w/2.0f + 0.5f;
		screenPos.y = -PSIn.pos2D.y/PSIn.pos2D.w/2.0f + 0.5f;
	float depth = depthMap.SampleLevel(Sampler,screenPos,0);
	//clip(depth<1?1:-1);

	[branch]if(depth<g_xCamera_ZFarP){

		float4 norU = normalMap.SampleLevel(Sampler,screenPos,0);
		bool unshaded = isUnshaded(norU.w);

		[branch]if(!unshaded){
			float4 material = materialMap.SampleLevel(Sampler,screenPos,0);
			float specular = material.w*specularMaximumIntensity;
			uint specular_power = material.z;
			float3 normal = norU.xyz;
			bool toonshaded = isToon(norU.w);


			float3 pos3D = getPosition(screenPos,depth);
			float3 eyevector = normalize(g_xCamera_CamPos -pos3D.xyz);
			float lighting = dirLight(pos3D,normal,color,toonshaded);

			//float rimLight = saturate(1.0f-specular) * saturate(pow(saturate(1.0f-dot(normal,eyevector)),3));
			//lighting+=rimLight;

			color.rgb *= (lighting);

			//SPECULAR
			applySpecular(color, lightColor*lighting, normal, eyevector, lightDir.xyz, 1, specular_power, specular, toonshaded);
			//else 
			//	color.a=0;
		}
		else
			color=float4(1,1,1,1);

	}

	return max(color, 0);
}