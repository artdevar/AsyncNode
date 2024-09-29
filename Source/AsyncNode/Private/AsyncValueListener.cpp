#include "AsyncValueListener.h"
#include "Checkpoint.h"
#include "Listener.h"

UAsyncValueListener * UAsyncValueListener::WaitForCheckpointReached(ACheckpoint * Checkpoint, AListener * Listener)
{
  UAsyncValueListener * BlueprintNode = NewObject<UAsyncValueListener>();
  BlueprintNode->Checkpoint = Checkpoint;
  BlueprintNode->RegisterWithGameInstance(Listener);
  Listener->OnDestroyed.AddDynamic(BlueprintNode, &UAsyncValueListener::OnActorDestroyed);
  Checkpoint->OnCheckpointReached.AddDynamic(BlueprintNode, &UAsyncValueListener::OnCheckpointReachedEvent);

  return BlueprintNode;
}

void UAsyncValueListener::OnActorDestroyed(AActor * Actor)
{
  Checkpoint->OnCheckpointReached.RemoveDynamic(this, &UAsyncValueListener::OnCheckpointReachedEvent);
  Checkpoint = nullptr;

  SetReadyToDestroy();
}

void UAsyncValueListener::OnCheckpointReachedEvent()
{
  OnCheckpointReached.Broadcast();
}