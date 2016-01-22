#include "globals.hlsli"

inline void affectWind(inout float3 pos, in float value, in uint randVertex){
	float3 wind = sin(g_xFrame_WindTime +(pos.x+pos.y+pos.z))*g_xFrame_WindDirection.xyz*0.1*value;
	pos+=wind;
}

