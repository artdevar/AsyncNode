#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckpointReachedSignature);

UCLASS()
class ASYNCNODE_API ACheckpoint : public AActor
{
  GENERATED_BODY()

protected:

  ACheckpoint();

  UFUNCTION(BlueprintCallable)
  void OnCharacterOverlap();

public:

  UPROPERTY(BlueprintAssignable)
  FCheckpointReachedSignature OnCheckpointReached;
};
