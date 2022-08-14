// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"//!!!
#include "Snake_IIGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeBase.h"//!!!

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));//!!!
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//!!!
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);//!!!

}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
	//MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);//!!!
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::SetFirstElementType_Implementation()//!!!
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);//!!!
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead)//!!!
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Destroy();
		
		ASnake_IIGameModeBase* game_mode = Cast<ASnake_IIGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (game_mode)
		{
			game_mode->EndGame = true;
		}

	}
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
										   AActor* OtherActor, 
										   UPrimitiveComponent* OtherComp, 
										   int32 OtherBodyIndex, 
									       bool bFromSweep, 
										   const FHitResult& SweepResult)//!!!
{
	if (IsValid(SnakeOwner))//!!!
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

void ASnakeElementBase::ToggleCollision()//!!!
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
