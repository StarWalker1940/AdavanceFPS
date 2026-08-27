#include "ItemDefinition.h"

UItemDefinition* UItemDefinition::CreateItemCopy() const
{
    UItemDefinition* CopyItem = NewObject< UItemDefinition>(StaticClass());

    CopyItem->ID = this->ID;
    CopyItem->ItemType = this->ItemType;
    CopyItem->ItemText = this->ItemText;
    CopyItem->WorldMesh = this->WorldMesh;
    return CopyItem;
}

//TODO CTO 