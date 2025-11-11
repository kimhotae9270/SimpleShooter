// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if (AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    }
    

}



void AShooterAIController::Tick(float DealtaSeconds)
{
    Super::Tick(DealtaSeconds);
     APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    

    // if (LineOfSightTo(PlayerPawn)){
    //     // SetFocus(PlayerPawn);
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PlayerPawn->GetActorLocation());

    //     // MoveToActor(PlayerPawn, AcceptanceRadius);

    // }
    // else{
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    //     // ClearFocus(EAIFocusPriority::Gameplay);
    //     // StopMovement();
    // }
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ControlledCharacter != nullptr){
        return ControlledCharacter->IsDead();
    }
    return true;
}
