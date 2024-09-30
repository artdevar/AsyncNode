#include "AsyncValueListener.h"
#include "Checkpoint.h"
#include "Listener.h"

UAsyncValueListener * UAsyncValueListener::WaitForCheckpointReached(ACheckpoint * Checkpoint, AListener * Listener)
{
  UAsyncValueListener * BlueprintNode = NewObject<UAsyncValueListener>();
  BlueprintNode->Checkpoint = Checkpoint;
  BlueprintNode->Listener   = Listener;
  return BlueprintNode;
}

void UAsyncValueListener::Activate()
{
  Super::Activate();

  ensure(Checkpoint.IsValid());
  ensure(Listener.IsValid());

  Listener->OnDestroyed.AddDynamic(this, &UAsyncValueListener::OnListenerDestroyed);
  Checkpoint->OnCheckpointReached.AddDynamic(this, &UAsyncValueListener::OnCheckpointReachedEvent);

  RegisterWithGameInstance(Listener.Get());
}

void UAsyncValueListener::OnListenerDestroyed(AActor * DestroyedActor)
{
  Checkpoint->OnCheckpointReached.RemoveDynamic(this, &UAsyncValueListener::OnCheckpointReachedEvent);
  Checkpoint.Reset();

  SetReadyToDestroy();
}

void UAsyncValueListener::OnCheckpointReachedEvent()
{
  OnCheckpointReached.Broadcast();
}