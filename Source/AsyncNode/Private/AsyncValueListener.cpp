#include "AsyncValueListener.h"
#include "TargetCharacter.h"

UAsyncValueListener::UAsyncValueListener(const FObjectInitializer & ObjectInitializer):
  Super          (ObjectInitializer),
  m_TargetActor  (nullptr),
  m_ListenerActor(nullptr)
{
  // Empty
}

void UAsyncValueListener::Activate()
{
  Super::Activate();

  check(m_TargetActor);
  check(m_ListenerActor);

  m_TargetActor->OnCheckpointReached.AddDynamic(this, &UAsyncValueListener::OnWaitedValueChanged);
  m_TargetActor->OnDestroyed.AddDynamic(this, &UAsyncValueListener::OnActorDestroyed);
  m_ListenerActor->OnDestroyed.AddDynamic(this, &UAsyncValueListener::OnActorDestroyed);
}

UAsyncValueListener * UAsyncValueListener::WaitForBooleanChange(AActor * ListenerActor, AActor * TargetActor)
{
  UAsyncValueListener * BlueprintNode = NewObject<UAsyncValueListener>();
  BlueprintNode->m_TargetActor        = Cast<ATargetCharacter>(TargetActor);
  BlueprintNode->m_ListenerActor      = ListenerActor;
  BlueprintNode->RegisterWithGameInstance(ListenerActor);

  return BlueprintNode;
}

void UAsyncValueListener::OnWaitedValueChanged(bool Value)
{
  OnValueChanged.Broadcast(Value);
}

void UAsyncValueListener::OnActorDestroyed(AActor * Actor)
{
  check(m_TargetActor);
  check(m_ListenerActor);

  m_TargetActor->OnCheckpointReached.RemoveDynamic(this, &UAsyncValueListener::OnWaitedValueChanged);
  m_TargetActor->OnDestroyed.RemoveDynamic(this, &UAsyncValueListener::OnActorDestroyed);
  m_ListenerActor->OnDestroyed.RemoveDynamic(this, &UAsyncValueListener::OnActorDestroyed);
  
  SetReadyToDestroy();
}