#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TargetCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckpointReachedSignature, bool, NewValue);

UCLASS()
class ASYNCNODE_API ATargetCharacter : public ACharacter
{
  GENERATED_BODY()

public:

  ATargetCharacter();

  UFUNCTION(BlueprintCallable, BlueprintPure)
  bool IsCheckpointReached() const;

public:

  UPROPERTY(BlueprintAssignable)
  FCheckpointReachedSignature OnCheckpointReached;

protected: 

  UFUNCTION(BlueprintCallable)
  void SetCheckpointReached(bool IsReached);

protected: 

  bool m_IsCheckpointReached;

};
