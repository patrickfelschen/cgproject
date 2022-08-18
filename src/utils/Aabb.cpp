#include "AABB.h"

#define EPSILON 1e-5

AABB AABB::UnitBox(Vector3f(-1,-1,-1), Vector3f(1,1,1));

AABB::AABB()
{

}
AABB::AABB(const Vector3f& min, const Vector3f& max) : Min(min), Max(max)
{

}
AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) : Min(minX, minY, minZ), Max(maxX, maxY, maxZ)
{

}

Vector3f AABB::size() const
{
    return Max-Min;
}

AABB AABB::transform(const Matrix& m) const
{
    Vector3f c[8];
    corners(c);
    for (int i = 0; i < 8; ++i)
        c[i] = m * c[i];
    AABB r;
    r.fromPoints(c, 8);
    return r;
}

AABB AABB::merge(const AABB& a, const AABB& b) const
{
    AABB r;

    r.Min.x = a.Min.x < b.Min.x ? a.Min.x : b.Min.x;
    r.Min.y = a.Min.y < b.Min.y ? a.Min.y : b.Min.y;
    r.Min.z = a.Min.z < b.Min.z ? a.Min.z : b.Min.z;

    r.Max.x = a.Max.x > b.Max.x ? a.Max.x : b.Max.x;
    r.Max.y = a.Max.y > b.Max.y ? a.Max.y : b.Max.y;
    r.Max.z = a.Max.z > b.Max.z ? a.Max.z : b.Max.z;

    return r;
}

AABB& AABB::merge(const AABB& a)
{
    Min.x = a.Min.x < Min.x ? a.Min.x : Min.x;
    Min.y = a.Min.y < Min.y ? a.Min.y : Min.y;
    Min.z = a.Min.z < Min.z ? a.Min.z : Min.z;

    Max.x = a.Max.x > Max.x ? a.Max.x : Max.x;
    Max.y = a.Max.y > Max.y ? a.Max.y : Max.y;
    Max.z = a.Max.z > Max.z ? a.Max.z : Max.z;

    return *this;
}

void AABB::corners(Vector3f c[8]) const
{
    c[0].x = Min.x; c[0].y = Min.y; c[0].z = Min.z;
    c[1].x = Max.x; c[1].y = Min.y; c[1].z = Min.z;
    c[2].x = Max.x; c[2].y = Max.y; c[2].z = Min.z;
    c[3].x = Max.x; c[3].y = Min.y; c[3].z = Min.z;

    c[4].x = Min.x; c[4].y = Min.y; c[4].z = Max.z;
    c[5].x = Max.x; c[5].y = Min.y; c[5].z = Max.z;
    c[6].x = Max.x; c[6].y = Max.y; c[6].z = Max.z;
    c[7].x = Max.x; c[7].y = Min.y; c[7].z = Max.z;
}

void AABB::fromPoints(const Vector3f* Points, unsigned int PointCount)
{
    Max = Vector3f(-1e20f, -1e20f, -1e20f);
    Min = Vector3f(1e20f, 1e20f, 1e20f);

    for (unsigned int i = 0; i < PointCount; ++i)
    {
        if (Min.x > Points[i].x) Min.x = Points[i].x;
        if (Min.y > Points[i].y) Min.y = Points[i].y;
        if (Min.z > Points[i].z) Min.z = Points[i].z;
        if (Max.x < Points[i].x) Max.x = Points[i].x;
        if (Max.y < Points[i].y) Max.y = Points[i].y;
        if (Max.z < Points[i].z) Max.z = Points[i].z;
    }

}

Vector3f AABB::center() const
{
    return (Max + Min)*0.5f;
}

const AABB& AABB::unitBox()
{
    return UnitBox;
}

// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_aabb.html
bool AABB::intersection(const Ray &ray) const {
//    printf("Ray-Origin: X: %f Y: %f Z: %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
//    printf("Ray-Direction: X: %f Y: %f Z: %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
//    printf("Min: X: %f Y: %f Z: %f\n", Min.x, Min.y, Min.z);
//    printf("Max: X: %f Y: %f Z: %f\n", Max.x, Max.y, Max.z);
//    printf("----------------------------------\n");

    // xt = Ray bis zur Intersection, xn = normalisierter Einheitsvektor der AABB Fläche, zur Bestimmung, ob Fläche in gleiche Richtung schaut wie Ray
    float xt, xn;
    if(ray.origin.x < Min.x) {
        // Distanz zwischen Ray-Origin und Box auf X-Achse
        xt = Min.x - ray.origin.x;
//        printf("INTERSECTION:: Spieler vor Objekt, Distanz: %f\n", xt);

        // Wenn xt > Ende des Rays -> Ray endet, bevor Box erreicht wurde
        if(xt > ray.direction.x) {
            printf("INTERSECTION:: Objekt ausser Reichweite (X-Achse)\n");
            return false;
        }

        xt /= ray.direction.x;
        xn = -1.0f;

    }
    else if(ray.origin.x > Max.x) {
        // Distanz zwischen Ray-Origin und Box auf X-Achse
        xt = Max.x - ray.origin.x;
//        printf("INTERSECTION:: Spieler hinter Objekt, Distanz: %f\n", xt);

        // Wenn xt < Ende des Rays -> Ray endet, bevor Box erreicht wurde
        if(xt < ray.direction.x) {
            printf("INTERSECTION:: Objekt ausser Reichweite (X-Achse)\n");
            return false;
        }

        xt /= ray.direction.x;
        xn = 1.0f;

    }
    else {
        xt = -1.0f;
    }

    float yt, yn;
    if(ray.origin.y < Min.y) {
        yt = Min.y - ray.origin.y;

        if(yt > ray.direction.y) {
            printf("INTERSECTION:: Objekt ausser Reichweite (Y-Achse)\n");
            return false;
        }

        yt /= ray.direction.y;
        yn = -1.0f;
    }
    else if(ray.origin.y > Max.y) {
        yt = Max.y - ray.origin.y;

        if(yt < ray.direction.y) {
            printf("INTERSECTION:: Objekt ausser Reichweite (Y-Achse)\n");
            return false;
        }

        yt /= ray.direction.y;
        yn = 1.0f;
    }
    else {
        yt = -1.0f;
    }

    float zt, zn;
    if(ray.origin.z < Min.z) {
        zt = Min.z - ray.origin.z;

        if(zt > ray.direction.z) {
            printf("INTERSECTION:: Objekt ausser Reichweite (Z-Achse)\n");
            return false;
        }

        zt /= ray.direction.z;
        zn = -1.0f;
    }
    else if(ray.origin.z > Max.z) {
        zt = Max.z - ray.origin.z;

        if(zt < ray.direction.z) {
            printf("INTERSECTION:: Objekt ausser Reichweite (Z-Achse)\n");
            return false;
        }

        zt /= ray.direction.z;
        zn = 1.0f;
    }
    else {
        zt = -1.0f;
    }

    int which = 0;
    float t = xt;
    if(yt > t) {
        which = 1;
        t = yt;
    }
    if(zt > t) {
        which = 2;
        t = zt;
    }

    switch(which) {
        case 0: {
            float y = ray.origin.y + ray.direction.y * t;
            if(y < Min.y || y > Max.y) return false;

            float z = ray.origin.z + ray.direction.z * t;
            if(z < Min.z || z > Max.z) return false;
        }
        break;
        case 1: {
            float x = ray.origin.x + ray.direction.x * t;
            if(x < Min.x || x > Max.x) return false;

            float z = ray.origin.z + ray.direction.z * t;
            if(z < Min.z || z > Max.z) return false;
        }
        break;
        case 2: {
            float x = ray.origin.x + ray.direction.x * t;
            if(x < Min.x || x > Max.x) return false;

            float y = ray.origin.y + ray.direction.y * t;
            if(y < Min.y || y > Max.y) return false;
        }
        break;
    }

    printf("INTERSECTION:: TREFFER\n");
    return true;
}

