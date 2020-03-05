#include "Isometry.h"

Vec2 Isometry::toIsometric(Vec2 _pos) {
    Vec2 pos(0.0f, 0.0f);

    pos.x = _pos.x - _pos.y ;
    pos.y = (_pos.x + _pos.y) / 2;

    return pos;
}

Vec2 Isometry::fromIsometric(Vec2 _pos) {
    Vec2 pos(0.0f, 0.0f);
    pos.x = (2 * _pos.y + _pos.x) / 2 ;
    pos.y = (2 * _pos.y - _pos.x) / 2;
    return pos;
}
