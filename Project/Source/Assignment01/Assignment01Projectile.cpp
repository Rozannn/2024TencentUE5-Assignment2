// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment01Projectile.h"
#include "Assignment01Character.h"
#include "Target.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyUserWidget.h"
#include "Components/SphereComponent.h"

AAssignment01Projectile::AAssignment01Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAssignment01Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	Damage = 0.5f;
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAssignment01Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if (OtherActor->IsA(AAssignment01Character::StaticClass()))
	{
		return;
	}
	if ((OtherActor != nullptr) && (OtherActor != this) &&(OtherActor!=Owner)&& (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 50.0f, GetActorLocation());
		if (OtherActor->IsA(ATarget::StaticClass())) {
			ATarget* Target = Cast<ATarget>(OtherActor);
			if (Target) {
				int Score = Target->Hit(Damage);
				AAssignment01Character* Player = Cast<AAssignment01Character>(GetOwner());
				if (Player) {
					Player->Goal(Score);
					if (Player && Player->PlayerHUD)
					{
						// 将 CrossHair 设置为红色
						Player->PlayerHUD->SetCrossHairColor(FLinearColor(1.f, 0.f, 0.f, 1.f));

						// 启动定时器，1 秒后恢复颜色
						GetWorld()->GetTimerManager().SetTimer(
							ResetColorTimerHandle,
							[Player]() {
								if (Player->PlayerHUD)
								{
									Player->PlayerHUD->ResetCrossHairColor();
								}
							},
							.2f,  // 延迟时间
							false  // 仅调用一次
						);
					}

				}
			}
		}

		Destroy();
	}
}