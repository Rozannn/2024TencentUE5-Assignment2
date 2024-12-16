// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Target.generated.h"

UCLASS()
class ASSIGNMENT01_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh1P;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSpecial;

	UFUNCTION(BlueprintCallable, Category = "Goal")
	int Hit(float Damage);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int WasHit;

};
