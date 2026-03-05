#include "object_common.h"

bool ObjectCommon::IsHit(ObjectCommon* other)
{
    //当たり判定を扱えるか
    if ((!hit_use_) || (!other->IsObject())) {
        return false;
    }
    return hit_box_.HitCheckToBox(other->GetHitBox());
}
