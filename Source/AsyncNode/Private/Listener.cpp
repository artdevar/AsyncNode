#include "Listener.h"
#include "Net/UnrealNetwork.h"

AListener::AListener()
{
  PrimaryActorTick.bCanEverTick = true;
  bReplicates = true;
}

void AListener::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(AListener, AssignedCheckpoint);
}
