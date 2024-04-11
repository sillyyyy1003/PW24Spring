struct Light
{
	float3 lightStrength; //light strength/Color
	float fallOffStart; //??????????:???????????
	float3 lightDir; //?????????????
	float fallOffEnd; //??????????:???????????
	float3 lightPos; //?????
	float spotPower; // ??????????
};

struct Material
{
	float4 diffuseAlbedo;
	float3 fresnelR0;
	float shiness; //shiness=1-roughness
};

float CalcAttenuation(float d, float fallOffStart, float fallOffEnd)
{
	return saturate((fallOffEnd - d) / (fallOffEnd - fallOffStart));
}

/*?????*/
float3 SchlickFresnel(float3 R0, float3 normal, float3 lightVec)
{
	float cosIncidentAngle = saturate(dot(normal, lightVec)); //max(n*l,0)
	float f0 = 1.0f - cosIncidentAngle;
	float3 reflectPercent = R0 + (1.0f - R0) * pow(f0, 5);
	return reflectPercent;
}

//BlingPhont ????
float3 BlinnPhong(float3 lightStrength, float3 lightVec, float3 normal, float3 toEye, Material mat)
{
	const float m = mat.shiness * 256.0f;
	float3 halfVec = normalize(toEye + lightVec); //?????????????????????????????????
	
	float roughnessFactor = (m + 8.0f) * pow(max(dot(halfVec, normal), 0.0f), m) / 8.0f; //???????
	float3 fresnelFactor = SchlickFresnel(mat.fresnelR0, halfVec, lightVec); //?????????
	
	float3 specAlbedo = fresnelFactor * roughnessFactor; //????????
	specAlbedo = specAlbedo / (specAlbedo + 1.0f); //??0?1???
	
	return (mat.diffuseAlbedo.rgb + specAlbedo) * lightStrength; //???????????????????????
	
}

//????
float3 ComputeDirectionalLight(Light L, Material mat, float3 normal, float3 toEye)
{
	float3 lightVec = -L.lightDir;
	
	float ndol = max(dot(lightVec, normal), 0.0f);
	float3 lightStrength = L.lightStrength * ndol;
	
	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
	
}

//???????
float3 ComputePointLight(Light L, Material mat, float3 pos, float3 normal, float3 toEye)
{
	float3 lightVec = normalize(L.lightPos - pos);
	float d = length(L.lightPos - pos);
	
	if (d > L.fallOffEnd)
	{
		return 0.0f;
	}
	
	float ndotl = max(dot(lightVec, normal), 0.0f);
	float lightStrength = L.lightStrength * ndotl;
	
	//light fade
	float att = CalcAttenuation(d, L.fallOffStart, L.fallOffEnd);
	
	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

float3 ComputeSpotLight(Light L, Material mat, float3 pos, float3 normal, float toEye)
{
	return 0;
}


float4 ComputeLighting()
{
	return float4(0.f, 0.f, 0.f, 0.f);
}