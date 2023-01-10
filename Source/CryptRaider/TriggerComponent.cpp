// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


//Constructor

UTriggerComponent::UTriggerComponent() {
	//b is used to indicate the boolean type 
	PrimaryComponentTick.bCanEverTick = true;
	
}








// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UnlockDungeonDoorTag = "Unlock1";
	

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* AcceptableActor = GetAcceptableActor();

	
	FString AcceptableActorName;
	if (AcceptableActor != nullptr) {
		
		Mover->SetShouldMove(true);
	}
	else {
		Mover->SetShouldMove(false);
	}

}

void UTriggerComponent::SetMover(UMover* NewMover) {
	Mover = NewMover;

}


AActor* UTriggerComponent::GetAcceptableActor() const {
	
	TArray<AActor*> Actors;

	GetOverlappingActors(Actors);

	//foreach 
	for (AActor* Actor : Actors) {

		FString ActorName = Actor->GetActorNameOrLabel();

		if (Actor->ActorHasTag(UnlockDungeonDoorTag)) {

			UE_LOG(LogTemp, Display, TEXT("The door Has been Unlocked"));
			return Actor;
		}

	}
	return nullptr;
}