#ifndef OBJ_DEBRIS_H
#define OBJ_DEBRIS_H

#include "Game.h"

// Object Class
struct ObjectDebris {
    RSDK_OBJECT
};

// Entity Class
struct EntityDebris {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 gravityStrength;
    int32 rotSpeed;
    Vector2 scaleSpeed;
    int32 delay;
    Animator animator;
};

// Object Struct
extern ObjectDebris *Debris;

// Standard Entity Events
void Debris_Update(void);
void Debris_LateUpdate(void);
void Debris_StaticUpdate(void);
void Debris_Draw(void);
void Debris_Create(void *data);
void Debris_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void Debris_EditorDraw(void);
void Debris_EditorLoad(void);
#endif
void Debris_Serialize(void);

// Extra Entity Functions
void Debris_FallFlickerAnimSetup(int32 aniFrames, int32 *entries, int32 animationID);
void Debris_FallFlickerSetup(int32 aniFrames, int32 *entries);

void Debris_State_Move(void);
void Debris_State_Fall(void);
void Debris_State_FallAndFlicker(void);

#endif //! OBJ_DEBRIS_H