// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings.h"


// Sets default values
ABuildings::ABuildings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

}

void ABuildings::SpawnPillars()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning pillars"));
	for (size_t i = 0; i < Pillars.Num(); ++i)
	{
		if (Pillars[i])
			Pillars[i]->DestroyComponent();
	}
	Pillars.Empty();

	for (size_t i = 0; i < NumOfPillars; ++i)
	{
		UStaticMeshComponent* smc = (UStaticMeshComponent*)AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform(), true);
		if (smc)
		{
			smc->RegisterComponent();
			smc->SetMobility(EComponentMobility::Movable);
			smc->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			smc->SetWorldLocation(this->GetActorLocation() + FVector(0, PillarGap * i, 0));
			//smc->SetWorldScale3D(FVector(1,1,FMath::RandRange(1,4)));
			smc->SetStaticMesh(PillarMesh);
			Pillars.Emplace(smc);
		}
	}
	RandomizePillars();
	
}

// Called when the game starts or when spawned
void ABuildings::BeginPlay()
{
	Super::BeginPlay();
	Border = -1 * (PillarGap * NumOfPillars + 300);
	RespPointDelta = FVector(0, PillarGap * NumOfPillars + ScreenWidth, 0);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Border);
	
}

// Called every frame
void ABuildings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + FVector(0, MoveSpeed * DeltaTime, 0));

	if (GetActorLocation().Y < Border)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Border);
		SetActorLocation(GetActorLocation() + RespPointDelta);
	}
}

void ABuildings::RandomizePillars()
{
	for (size_t i = 0; i < NumOfPillars; ++i)
	{
		if (Pillars[i])
			Pillars[i]->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, 6)));
	}
}

void ABuildings::OnConstruction(const FTransform& Transform)
{
	SpawnPillars();
}

