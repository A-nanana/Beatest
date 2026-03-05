#include "object_common.h"

ObjectCommon::ObjectCommon(const int graph_handle, float x, float y)
    :GraphNode(graph_handle, x, y), hit_box_(x, y, NULL, NULL) {
    
    GetGraphSize(graph_handle_, &size_x_, &size_y_);
    hit_box_.SetToSize(size_x_, size_y_);

    hit_use_ = true;
}

void ObjectCommon::SetRotate(float angle)
{
    hit_box_.lotate_rad_ = angle;
    rotate_ = angle;
}

bool ObjectCommon::IsHit(ObjectCommon* other)
{
    //当たり判定を扱えるか
    if ((!hit_use_) || (!other->IsObject())) {
        return false;
    }
    return hit_box_.HitCheckToBox(other->GetHitBox());
}
