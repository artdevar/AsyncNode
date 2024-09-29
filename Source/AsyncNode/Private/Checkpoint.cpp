#include "Checkpoint.h"

ACheckpoint::ACheckpoint()
{
  PrimaryActorTick.bCanEverTick = true;
  bReplicates = true;
}

void ACheckpoint::OnCharacterOverlap()
{
  OnCheckpointReached.Broadcast();
}