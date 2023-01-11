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
	if (Mover == nullptr) return;

	AActor* AcceptableActor = GetAcceptableActor();

	
	FString AcceptableActorName;
	if (AcceptableActor != nullptr) {
		

		//In compile time this checks if the actor we got hold of is a UPrimitiveComponent and returns it,other wise return nullptr
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent());
		if (Component != nullptr) {

			Component->SetSimulatePhysics(false);
			AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform,
				NAME_None);
			
		}
		
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

		if (Actor->ActorHasTag(UnlockDungeonDoorTag) && !Actor->ActorHasTag("Grabbed")) {

			
			return Actor;
		}

	}
	return nullptr;
}