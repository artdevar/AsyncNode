#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncValueListener.generated.h"

class ATargetCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForValueChangedOutputPin, bool, NewValue);

UCLASS()
class ASYNCNODE_API UAsyncValueListener : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

  UAsyncValueListener(const FObjectInitializer & ObjectInitializer = FObjectInitializer::Get());

  void Activate() override;

  UFUNCTION(BlueprintCallable, Category="Async", Meta=(DefaultToSelf="ListenerActor", BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))
  static UAsyncValueListener * WaitForBooleanChange(AActor * ListenerActor, AActor * TargetActor);

public:

  UPROPERTY(BlueprintAssignable)
  FWaitForValueChangedOutputPin OnValueChanged;

protected:

  UFUNCTION()
  void OnWaitedValueChanged(bool Value);

  UFUNCTION()
  void OnListenerDestroyed(AActor * Listener);

protected:

  ATargetCharacter * m_TargetActor;
  AActor *           m_ListenerActor;
};
