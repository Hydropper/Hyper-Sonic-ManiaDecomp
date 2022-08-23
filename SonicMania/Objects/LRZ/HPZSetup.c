// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HPZSetup Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHPZSetup *HPZSetup;

void HPZSetup_Update(void) {}

void HPZSetup_LateUpdate(void) {}

void HPZSetup_StaticUpdate(void) {}

void HPZSetup_Draw(void) {}

void HPZSetup_Create(void *data) {}

void HPZSetup_StageLoad(void)
{
#if MANIA_USE_PLUS
    if (SceneInfo->filter & FILTER_ENCORE) {
        RSDK.LoadPalette(0, "EncoreLRZ3.act", 0b0000000011111111);
        RSDK.CopyPalette(0, 240, 1, 240, 16);
    }
#endif
HPZSetup_GetTileInfo(player->position.x, player->position.y + (playerHitbox->bottom << 16), player->moveLayerPosition.x,
                                  player->moveLayerPosition.y, player->collisionPlane, &tileInfo, &behaviour);
    switch (behaviour) {

        case 1:
        break;

    }

    if (behaviour > 0 & < 9) {
        f
    }


}

void HPZSetup_StageFinish_EndAct2K(void) { HPZSetup->cutsceneOutroK->active = ACTIVE_NORMAL; }

#if RETRO_INCLUDE_EDITOR
void HPZSetup_EditorDraw(void) {}

void HPZSetup_EditorLoad(void) {}
#endif

void HPZSetup_Serialize(void) {}
