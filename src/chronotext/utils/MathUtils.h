#pragma once

#include "cinder/MatrixAffine2.h"
#include "cinder/Rect.h"

#include <vector>
#include <algorithm>

static const float D2R = M_PI / 180.0;
static const float R2D = 180.0 / M_PI;

static const float PI = M_PI;
static const float TWO_PI = M_PI * 2.0;
static const float HALF_PI = M_PI * 0.5;

static inline float bound(float value, float range)
{
    float bound = fmodf(value, range);
    return (bound < 0) ? (bound + range) : bound;
}

static inline int bound(int value, int range)
{
    int bound = value % range;
    return (bound < 0) ? (bound + range) : bound;
}

/*
 * S-SHAPED CROSS-FADE CURVE: 3 * (t ^ 2) - 2 * (t ^ 3)
 */
static inline float ease(float t)
{
    return (t * t * (3 - 2 * t));
}

/*
 * BASED ON QUAKE
 * http://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/
 */
static inline float FastSqrt(float x)
{
    int i = *(int*)&x; // store floating-point bits in integer
    i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
    float r = *(float*)&i; // convert new bits into float
    r *= (1.5f - 0.5f * x * r * r); // One round of Newton's method
    return r * x;
}

bool isRectNull(const ci::Rectf &rect);
bool compareRects(const ci::Rectf &r1, const ci::Rectf &r2);

ci::Rectf getBoundingBox(const std::vector<ci::Vec2f> &polygon);
float getShortestDistance(const ci::Vec2f &point, const std::vector<ci::Vec2f> &polygon, float threshold);

bool isPointInside(const ci::Vec2f &point, const std::vector<ci::Vec2f> &polygon);
bool isPointInside(const ci::Vec2f &point, const std::vector<std::vector<ci::Vec2f>> &polygons);

class MathUtils
{
public:
    static void transformVertices(const std::vector<ci::Vec2f> &source, std::vector<ci::Vec2f> &target, const ci::MatrixAffine2f &matrix);
};
