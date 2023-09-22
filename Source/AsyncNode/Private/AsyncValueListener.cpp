#include "AsyncValueListener.h"
#include "TargetCharacter.h"

UAsyncValueListener::UAsyncValueListener(const FObjectInitializer & ObjectInitializer) :
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

  RegisterWithGameInstance(m_ListenerActor);

  m_TargetActor->OnCheckpointReached.AddDynamic(this, &UAsyncValueListener::OnWaitedValueChanged);
  m_ListenerActor->OnDestroyed.AddDynamic(this, &UAsyncValueListener::OnListenerDestroyed);
}

UAsyncValueListener * UAsyncValueListener::WaitForBooleanChange(AActor * ListenerActor, AActor * TargetActor)
{
  UAsyncValueListener * BlueprintNode = NewObject<UAsyncValueListener>();
  BlueprintNode->m_TargetActor        = Cast<ATargetCharacter>(TargetActor);
  BlueprintNode->m_ListenerActor      = ListenerActor;

  check(BlueprintNode->m_TargetActor);
  check(BlueprintNode->m_ListenerActor);

  return BlueprintNode;
}

void UAsyncValueListener::OnWaitedValueChanged(bool Value)
{
  OnValueChanged.Broadcast(Value);
}

void UAsyncValueListener::OnListenerDestroyed(AActor * Listener)
{
  Listener->OnDestroyed.RemoveDynamic(this, &UAsyncValueListener::OnListenerDestroyed);
  
  if (m_TargetActor)
    m_TargetActor->OnCheckpointReached.RemoveDynamic(this, &UAsyncValueListener::OnWaitedValueChanged);

  SetReadyToDestroy();
}