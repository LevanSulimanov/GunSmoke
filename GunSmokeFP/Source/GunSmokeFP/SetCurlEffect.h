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

	UFUNCTION(BlueprintCallable, meta = (Keywords = "CurlSetUpGFG"), Category = "Rendering|Material")
		void CurlSetUP(UMaterialInstanceDynamic *Velocity_SeedMID,
					   UMaterialInstanceDynamic *Color_SeedMID,
					   FName Temp,
				       FName OverallVelMult,
					   FName RadForce,
					   float TempValue,
					   float OverallVelMultValue,
					   float RadForceValue);
	
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SetFloatParameterValueGFG"), Category = "Rendering|Material")
		void SetCurlEffectFunction(UMaterialInstanceDynamic *VelocitySeedMID, FName CurlTiling, 
																			  FName CurlStrength, 
																			  float CurlTilingValue,
																			  float CurlStrengthValue);
		
	UFUNCTION(BlueprintCallable)
	void calculateDivergence(UTextureRenderTarget2D *sourceTexture, UTextureRenderTarget2D *destinationTexture, UMaterialInstanceDynamic *divergenceMID);

};
