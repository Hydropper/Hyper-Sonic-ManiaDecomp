#ifndef OBJ_HPZEMERALD_H
#define OBJ_HPZEMERALD_H

#include "Game.h"

typedef enum {
    HPZEMERALD_MASTER,
    HPZEMERALD_EMERALD_LOW,
    HPZEMERALD_EMERALD_HIGH,
} HPZEmeraldTypes;

typedef enum { HPZ_TFLAGS_NORMAL} TileFlagsLRZ2;
// Object Class
struct ObjectHPZEmerald {
    RSDK_OBJECT
    uint16 aniFrames;
    int32 counter;
    Hitbox hitboxHPZEmerald;
};

// Entity Class
struct EntityHPZEmerald {
    RSDK_ENTITY
    StateMachine(state); // unused
    int32 type;
    int32 counter;
    bool32 solid;
    Vector2 startPos;
    Hitbox *hitbox;
    Animator emeraldAnimator;
    Animator overlayAnimator;
};

// Object Struct
extern ObjectHPZEmerald *HPZEmerald;

// Standard Entity Events
void HPZSetup_GetTileInfo(int32 x, int32 y, int32 moveOffsetX, int32 moveOffsetY, int32 cPlane, int32 *tile, uint8 *flags);
void HPZEmerald_Update(void);
void HPZEmerald_LateUpdate(void);
void HPZEmerald_StaticUpdate(void);
void HPZEmerald_Draw(void);
void HPZEmerald_Create(void *data);
void HPZEmerald_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void HPZEmerald_EditorDraw(void);
void HPZEmerald_EditorLoad(void);
#endif
void HPZEmerald_Serialize(void);

// Extra Entity Functions

#endif //! OBJ_HPZEMERALD_H
