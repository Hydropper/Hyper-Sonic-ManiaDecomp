#ifndef OBJ_HPZSETUP_H
#define OBJ_HPZSETUP_H

#include "Game.h"

// Object Class
struct ObjectHPZSetup {
    RSDK_OBJECT
    int32 unused1;
    int32 unused2;
    int32 unused3;
    Entity *cutsceneOutroK;
};

// Entity Class
struct EntityHPZSetup {
    RSDK_ENTITY
};

// Object Struct
extern ObjectHPZSetup *HPZSetup;

// Standard Entity Events
void HPZSetup_Update(void);
void HPZSetup_LateUpdate(void);
void HPZSetup_StaticUpdate(void);
void HPZSetup_Draw(void);
void HPZSetup_Create(void *data);
void HPZSetup_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void HPZSetup_EditorDraw(void);
void HPZSetup_EditorLoad(void);
#endif
void HPZSetup_Serialize(void);

// Extra Entity Functions
void HPZSetup_StageFinish_EndAct2K(void);
void HPZSetup_GetTileInfo(int32 x, int32 y, int32 moveOffsetX, int32 moveOffsetY, int32 cPlane, int32 *tile, uint8 *flags);

#endif //! OBJ_HPZSETUP_H
