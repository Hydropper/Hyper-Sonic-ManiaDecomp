// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HPZEmerald Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHPZEmerald *HPZEmerald;
int32 counter = 0;

void HPZEmerald_Update(void)
{

    RSDK_THIS(HPZEmerald);
    HPZEmerald->hitboxHPZEmerald.left = -16;
    HPZEmerald->hitboxHPZEmerald.top = -29;
    HPZEmerald->hitboxHPZEmerald.right = 16;
    HPZEmerald->hitboxHPZEmerald.bottom = -16;

    if (self->type >= 1) {
    
    foreach_active(Player, player) {
    if (player->onGround == 1) {
            if ((Player_CheckCollisionTouch(player, self, &HPZEmerald->hitboxHPZEmerald)) == C_TOP) {
                if (counter == 0) {
                    counter = 1;
                    RSDK.SetScene("Special Stage", "");
                    SceneInfo->listPos += 14;
                    SceneInfo->listPos -= self->type;
                    Zone_StartFadeOut(10, 0xF0F0F0);
                    Music_Stop();
                }
            }
    }
    }
    }





    RSDK.ProcessAnimation(&self->emeraldAnimator);

    if (self->solid) {
        if (self->type != HPZEMERALD_MASTER) {
            foreach_active(Player, player) { Player_CheckCollisionPlatform(player, self, self->hitbox); }
        }

        foreach_active(HeavyKing, king)
        {
            if (king->bodyAnimator.animationID != 5 && !king->onGround
                && RSDK.CheckObjectCollisionPlatform(self, self->hitbox, king, &HeavyKing->hitboxBody, true)) {
                Camera_ShakeScreen(0, 0, 3);
                RSDK.PlaySfx(HeavyKing->sfxImpact2, false, 255);
            }
        }
    }

    if (!self->onGround) {
        self->velocity.y += 0x3800;
        self->position.y += self->velocity.y;

        if (self->position.y >= self->startPos.y && self->velocity.y > 0) {
            self->position.y = self->startPos.y;
            self->velocity.y = -(self->velocity.y >> 1);

            if (!self->velocity.y)
                self->onGround = true;
        }
    }
}

void HPZEmerald_LateUpdate(void) {}

void HPZEmerald_StaticUpdate(void) {}

void HPZEmerald_Draw(void)
{
    RSDK_THIS(HPZEmerald);

    self->inkEffect = INK_NONE;

    if (self->solid) {
        RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
    }
    else {
        RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);

        self->inkEffect = INK_ADD;
        RSDK.DrawSprite(&self->overlayAnimator, NULL, false);
    }
}


void HPZSetup_GetTileInfo(int32 x, int32 y, int32 moveOffsetX, int32 moveOffsetY, int32 cPlane, int32 *tile, uint8 *flags)
{
    int32 tileLow  = RSDK.GetTile(Zone->fgLayer[0], x >> 20, y >> 20);
    int32 tileHigh = RSDK.GetTile(Zone->fgLayer[1], x >> 20, y >> 20);

    int32 flagsLow  = RSDK.GetTileFlags(tileLow, cPlane);
    int32 flagsHigh = RSDK.GetTileFlags(tileHigh, cPlane);

    int32 tileMove  = 0;
    int32 flagsMove = 0;
    if (Zone->moveLayer) {
        tileMove  = RSDK.GetTile(Zone->moveLayer, (moveOffsetX + x) >> 20, (moveOffsetY + y) >> 20);
        flagsMove = RSDK.GetTileFlags(tileMove, cPlane);
    }

    int32 tileSolidLow  = 0;
    int32 tileSolidHigh = 0;
    int32 tileSolidMove = 0;
    if (cPlane) {
        tileSolidHigh = (tileHigh >> 14) & 3;
        tileSolidLow  = (tileLow >> 14) & 3;
    }
    else {
        tileSolidHigh = (tileHigh >> 12) & 3;
        tileSolidLow  = (tileLow >> 12) & 3;
    }

    if (Zone->moveLayer)
        tileSolidMove = (tileMove >> 12) & 3;

    *tile  = 0;
    *flags = HPZ_TFLAGS_NORMAL;
    if (flagsMove && tileSolidMove) {
        *tile  = tileMove;
        *flags = flagsMove;
    }
    else if (flagsHigh && tileSolidHigh) {
        *tile  = tileHigh;
        *flags = flagsHigh;
    }
    else if (flagsLow && tileSolidLow) {
        *tile  = tileLow;
        *flags = flagsLow;
    }
}

void HPZEmerald_Create(void *data)
{
    RSDK_THIS(HPZEmerald);

    if (!SceneInfo->inEditor) {
        self->visible = true;

        switch (self->type) {
            default:
            case HPZEMERALD_MASTER: self->drawGroup = 1; break;

            case HPZEMERALD_EMERALD_LOW:
                self->solid     = true;
                self->drawGroup = Zone->objectDrawGroup[0];
                break;

            case HPZEMERALD_EMERALD_HIGH:
                self->solid     = true;
                self->drawGroup = Zone->objectDrawGroup[1];
                break;
        }

        self->startPos      = self->position;
        self->active        = ACTIVE_BOUNDS;
        self->updateRange.x = 0x800000;
        self->updateRange.y = 0x800000;
        self->onGround      = true;

        if (self->type != HPZEMERALD_MASTER) {
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 2, &self->emeraldAnimator, true, (self->type) - 1);


        }
        else {
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->emeraldAnimator, true, 0);
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->overlayAnimator, true, 1);
        }

        self->hitbox = RSDK.GetHitbox(&self->emeraldAnimator, 0);
    }
}

void HPZEmerald_StageLoad(void) { 
    HPZEmerald->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/Emerald.bin", SCOPE_STAGE); 
    counter = 0;
}

#if RETRO_INCLUDE_EDITOR
void HPZEmerald_EditorDraw(void)
{
    RSDK_THIS(HPZEmerald);

    self->solid = false;
    switch (self->type) {
        default:
        case HPZEMERALD_MASTER:
        case HPZEMERALD_EMERALD_LOW: self->solid = true; break;

        case HPZEMERALD_EMERALD_HIGH: self->solid = true; break;
    }

    if (self->type) {
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &self->emeraldAnimator, true, 0);
    }
    else {
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->emeraldAnimator, true, 0);
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->overlayAnimator, true, 1);
    }

    HPZEmerald_Draw();
}

void HPZEmerald_EditorLoad(void)
{
    HPZEmerald->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/Emerald.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(HPZEmerald, type);
    RSDK_ENUM_VAR("Master Emerald", HPZEMERALD_MASTER);
    RSDK_ENUM_VAR("Stone Emerald (Low Group)", HPZEMERALD_EMERALD_LOW);
    RSDK_ENUM_VAR("Stone Emerald (High Group)", HPZEMERALD_EMERALD_HIGH);
}
#endif

void HPZEmerald_Serialize(void) { RSDK_EDITABLE_VAR(HPZEmerald, VAR_UINT8, type); }
