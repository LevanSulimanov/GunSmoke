// Fill out your copyright notice in the Description page of Project Settings.

#include "SetCurlEffect.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

 

// Sets default values for this component's properties
USetCurlEffect::USetCurlEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void USetCurlEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USetCurlEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USetCurlEffect::CurlSetUP(UMaterialInstanceDynamic *Velocity_SeedMID, 
							   UMaterialInstanceDynamic *Color_SeedMID,        
							   FName Temp, 
						   	   FName OverallVelMult,
							   FName RadForce,																				
							   float TempValue,
							   float OverallVelMultValue, 
							   float RadForceValue) 
{

	Velocity_SeedMID->SetScalarParameterValue(Temp, TempValue);

	Color_SeedMID->SetScalarParameterValue(Temp, TempValue);

	Velocity_SeedMID->SetScalarParameterValue(OverallVelMult, OverallVelMultValue);

	Color_SeedMID->SetScalarParameterValue(OverallVelMult, OverallVelMultValue);

	Velocity_SeedMID->SetScalarParameterValue(RadForce, RadForceValue);

	Color_SeedMID->SetScalarParameterValue(RadForce, RadForceValue);	

}

/*
FName Offset,
FName TempMult,
FName HeatInset,
float TempValue,
float OffsetValue,
float TempMultValue,
float HeatInsetValue


Velocity_Color_SeedMID->SetScalarParameterValue(Offset, OffsetValue);

Velocity_Color_SeedMID->SetScalarParameterValue(TempMult, TempMultValue);

Velocity_Color_SeedMID->SetScalarParameterValue(HeatInset, HeatInsetValue);



*/



void USetCurlEffect::SetCurlEffectFunction(UMaterialInstanceDynamic *VelocitySeedMID, FName CurlTiling,
																					  FName CurlStrength,
																					  float CurlTilingValue,
																					  float CurlStrengthValue) {
	// twisting the smoke by increasing the amount feed into it
	for (int i = 0; i < 2; i++) {

		// setting tiling and sending it to the function
		VelocitySeedMID->SetScalarParameterValue(CurlTiling, CurlTilingValue);

		// setting strength for the curls and sending it to the functions
		VelocitySeedMID->SetScalarParameterValue(CurlStrength, CurlStrengthValue);

		// increasing the whirl
		CurlTilingValue = CurlTilingValue + 5;

	}

}

void USetCurlEffect::setSimParams(UMaterialInstanceDynamic *advectMID, UMaterialInstanceDynamic *divMID,
										UMaterialInstanceDynamic *pressIterMID, UMaterialInstanceDynamic *gradSubMID,
										UMaterialInstanceDynamic *colorPrevMID, UMaterialInstanceDynamic *rayMarchVelMID,
										UMaterialInstanceDynamic *volPrevMID, UMaterialInstanceDynamic *velSeedMID,
										UMaterialInstanceDynamic *colSeedMID,
										UTextureRenderTarget2D *obsTex,
										float twoDRes, float constCurlTiling, float constCurlStrength,
										FVector2D rtSize, FVector2D xyFrames) {
	//Set up Masks for MIDS
	FName pName = FName("Mask");  //parameter Name
	advectMID->SetTextureParameterValue(pName, obsTex);
	divMID->SetTextureParameterValue(pName, obsTex);
	pressIterMID->SetTextureParameterValue(pName, obsTex);
	gradSubMID->SetTextureParameterValue(pName, obsTex);
	colorPrevMID->SetTextureParameterValue(pName, obsTex);
	
	//Set up resolution for MIDS
	pName = FName("Resolution");
	advectMID->SetScalarParameterValue(pName, twoDRes);
	divMID->SetScalarParameterValue(pName, twoDRes);
	pressIterMID->SetScalarParameterValue(pName, twoDRes);
	gradSubMID->SetScalarParameterValue(pName, twoDRes);

	FLinearColor linCol;
	linCol.R = rtSize.X;
	linCol.G = rtSize.Y;
	linCol.B = 0.0;
	linCol.A = 1.0;

	advectMID->SetVectorParameterValue(pName, linCol);
	divMID->SetVectorParameterValue(pName, linCol);
	pressIterMID->SetVectorParameterValue(pName, linCol);
	gradSubMID->SetVectorParameterValue(pName, linCol);
	rayMarchVelMID->SetVectorParameterValue(pName, linCol);

	//set up frame resolution
	pName = FName("FrameResolution");
	
	linCol.R = rtSize.X / xyFrames.X;
	linCol.G = rtSize.Y / xyFrames.Y;
	linCol.B = xyFrames.X * xyFrames.Y;

	advectMID->SetVectorParameterValue(pName, linCol);
	divMID->SetVectorParameterValue(pName, linCol);
	pressIterMID->SetVectorParameterValue(pName, linCol);
	gradSubMID->SetVectorParameterValue(pName, linCol);
	rayMarchVelMID->SetVectorParameterValue(pName, linCol);

	//set up XYFrames
	pName = FName("XYFrames");
	linCol.R = xyFrames.X;
	linCol.G = xyFrames.Y;
	linCol.B = 0.0;

	advectMID->SetVectorParameterValue(pName, linCol);
	divMID->SetVectorParameterValue(pName, linCol);
	pressIterMID->SetVectorParameterValue(pName, linCol);
	gradSubMID->SetVectorParameterValue(pName, linCol);
	volPrevMID->SetVectorParameterValue(pName, linCol);
	velSeedMID->SetVectorParameterValue(pName, linCol);
	colSeedMID->SetVectorParameterValue(pName, linCol);
	rayMarchVelMID->SetVectorParameterValue(pName, linCol);

	//set Temp
	pName = FName("Temp");
	advectMID->SetScalarParameterValue(pName, constCurlTiling);

	//set Force
	pName = FName("Force");
	advectMID->SetScalarParameterValue(pName, constCurlStrength);

	//set Constant Curl
	pName = FName("Constant Curl");
	advectMID->SetScalarParameterValue(pName, constCurlStrength);

	//set Constant Curl Tiling
	pName = FName("Constant Curl Tiling");
	advectMID->SetScalarParameterValue(pName, constCurlStrength);
}


void USetCurlEffect::calculateDivergence(UTextureRenderTarget2D *sourceTexture, 
										UTextureRenderTarget2D *destinationTexture, 
										UMaterialInstanceDynamic *divergenceMID)
{
	divergenceMID->SetTextureParameterValue(FName("Velocity"), sourceTexture);
	UKismetRenderingLibrary::DrawMaterialToRenderTarget((UObject *)this->GetWorld(), destinationTexture, divergenceMID);
}