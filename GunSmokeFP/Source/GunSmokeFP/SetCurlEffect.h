// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "SetCurlEffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSMOKEFP_API USetCurlEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USetCurlEffect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Author: Levan Sulimanov
	UFUNCTION(BlueprintCallable, meta = (Keywords = "CurlSetUpGFG"), Category = "Rendering|Material")
		void CurlSetUP(UMaterialInstanceDynamic *Velocity_SeedMID,
					   UMaterialInstanceDynamic *Color_SeedMID,
					   FName Temp,
				       FName OverallVelMult,
					   FName RadForce,
					   float TempValue,
					   float OverallVelMultValue,
					   float RadForceValue);
	
	// Author: Levan Sulimanov
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SetFloatParameterValueGFG"), Category = "Rendering|Material")
		void SetCurlEffectFunction(UMaterialInstanceDynamic *VelocitySeedMID, FName CurlTiling, 
																			  FName CurlStrength, 
																			  float CurlTilingValue,
																			  float CurlStrengthValue);

	// Author: Levan Sulimanov
	UFUNCTION(BlueprintCallable, meta = (Keywords = "BindRendTargGFG"), Category = "Rendering|Material")
		void BindRendGFG(UMaterialInstanceDynamic *VelocitySeedMID,
			UMaterialInstanceDynamic *VolumePreviewMID,
			UMaterialInstanceDynamic *VelocityPreviewMID,
			UMaterialInstanceDynamic *ColorPreviewMID,
			UMaterialInstanceDynamic *RaymarchVelocityMID,
			UTextureRenderTarget2D *ColorText,
			UTextureRenderTarget2D *VelocityText,
			UTextureRenderTarget2D *PressureText);
		

	//Ryan C
	UFUNCTION(BlueprintCallable)
	void calculateDivergence(UTextureRenderTarget2D *sourceTexture, UTextureRenderTarget2D *destinationTexture, UMaterialInstanceDynamic *divergenceMID);
	
	//Ryan C
	UFUNCTION(BlueprintCallable, meta = (Keywords = "setSimParamsGFG"), Category = "Rendering|Material")
	void setSimParams(UMaterialInstanceDynamic *advectMID, UMaterialInstanceDynamic *divMID,
		UMaterialInstanceDynamic *pressIterMID, UMaterialInstanceDynamic *gradSubMID,
		UMaterialInstanceDynamic *colorPrevMID, UMaterialInstanceDynamic *rayMarchVelMID,
		UMaterialInstanceDynamic *volPrevMID, UMaterialInstanceDynamic *velSeedMID,
		UMaterialInstanceDynamic *colSeedMID,
		UTextureRenderTarget2D *obsTex,
		float twoDRes, float constCurlTiling, float constCurlStrength,
		FVector2D rtSize, FVector2D xyFrames);
};
