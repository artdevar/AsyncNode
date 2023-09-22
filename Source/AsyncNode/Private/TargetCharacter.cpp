#include "TargetCharacter.h"

ATargetCharacter::ATargetCharacter():
  m_IsCheckpointReached(false)
{
  PrimaryActorTick.bCanEverTick = true;
}

void ATargetCharacter::SetCheckpointReached(bool IsReached)
{
  if (m_IsCheckpointReached != IsReached)
  {
    m_IsCheckpointReached = IsReached;
    OnCheckpointReached.Broadcast(IsReached);
  }
}

bool ATargetCharacter::IsCheckpointReached() const
{
  return m_IsCheckpointReached;
}
