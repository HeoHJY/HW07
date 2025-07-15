#include "HealingItem.h"
#include "MainCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}
		
		DestroyItem();
	}
}