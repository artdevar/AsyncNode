#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncValueListener.generated.h"

class AListener;
class ACheckpoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointReachedEventFired);

UCLASS()
class ASYNCNODE_API UAsyncValueListener : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UFUNCTION(BlueprintCallable, Category="Async", Meta=(DefaultToSelf="Listener", BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))
  static UAsyncValueListener * WaitForCheckpointReached(ACheckpoint * Checkpoint, AListener * Listener);

  UPROPERTY(BlueprintAssignable)
  FOnCheckpointReachedEventFired OnCheckpointReached;

protected:

  UFUNCTION()
  void OnActorDestroyed(AActor * Actor);

  UFUNCTION()
  void OnCheckpointReachedEvent();

protected:

  ACheckpoint * Checkpoint = nullptr;

};
