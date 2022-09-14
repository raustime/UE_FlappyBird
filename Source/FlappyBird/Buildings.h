// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buildings.generated.h"

UCLASS()
class FLAPPYBIRD_API ABuildings : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
			TArray<UStaticMeshComponent*> Pillars;

		UPROPERTY(EditAnywhere)
			int NumOfPillars = 10;

		UPROPERTY(EditAnywhere)
			float PillarGap = 400.f;

		UPROPERTY(EditAnywhere)
			float MoveSpeed = -100.f;
		
		UPROPERTY(EditAnywhere)
			float ScreenWidth = 1000.f;
	
		UPROPERTY(EditDefaultsOnly)
			UStaticMesh* PillarMesh;

		UPROPERTY(EditDefaultsOnly)
			USceneComponent* Root;

		
public:	
	// Sets default values for this actor's properties
	ABuildings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	void RandomizePillars();
	void SpawnPillars();

	float Border;
	FVector RespPointDelta;
};
