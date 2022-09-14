// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"

// Sets default values
APW_Bird::APW_Bird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 600.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APW_Bird::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetSimulatePhysics(true);
	Mesh->BodyInstance.bLockXTranslation=true;
	Mesh->BodyInstance.bLockYTranslation = true;
	Mesh->BodyInstance.bLockRotation = true;
	
}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APW_Bird::Jump);

}

void APW_Bird::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump!"));
	Mesh->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, false);
}

