#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Listener.generated.h"

class ACheckpoint;

UCLASS()
class ASYNCNODE_API AListener : public AActor
{
  GENERATED_BODY()

protected:

  AListener();

  void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

protected:

  UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Replicated)
  ACheckpoint * AssignedCheckpoint = nullptr;

};
