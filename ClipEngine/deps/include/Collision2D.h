#ifndef COLLISION2D_H_INCLUDED
#define COLLISION2D_H_INCLUDED

#include "Clip.h"
#include "Collision2DGrid.h"
#include "Collision2DQuadTree.h"

namespace Collision2D
{

    Vec2D getReboundVec2D(Vec2D v, Vec2D N); // return Vec2D vector of Rebound Vector v & Normal N
    Vec2D getNormalPointLine(Vec2D A, Vec2D B, Vec2D C); // return Vec2D normal of C on line AB
    Vec2D projectionPointLine(Vec2D A, Vec2D B, Vec2D C); // return Vec2D projection of C on line AB

    // Collision Type
    bool pointRect(Vec2D p, Rect r); // Test Point in Rect
    bool pointCircle(Vec2D p, Circle c); // Test Point in Circle

    bool pointPolygon(Vec2D P, Vec2D pTab[], int nbP); // Test Point in Polygon Convexe
    bool pointPolygonEX(Vec2D P, Vec2D pTab[],int nbP); // Test Point in Polygon Any

    int segmentXSegment(Vec2D A, Vec2D B, Vec2D I, Vec2D P); // Test segment cut segment // recursive for count nb cut
    bool lineSegment(Vec2D A, Vec2D B, Vec2D O, Vec2D P); // Test line hit Segment
    bool segmentSegment(Vec2D A, Vec2D B, Vec2D O, Vec2D P); // Test Segment hit Segment
    bool segmentSegmentEX(Vec2D A, Vec2D B, Vec2D O, Vec2D P); // Test Segment hit Segment
    bool lineCircle(Vec2D A, Vec2D B, Circle C); // Test Circle hit Line
    bool segmentCircle(Vec2D A, Vec2D B, Circle C); // Test Circle hit Segment

    bool circleCircle(Circle &c1, Circle &c2); // Test Circle hit Circle
    bool rectRect(Rect &r1, Rect &r2); // Test Rect hit Rect

    void cancelAll(Clip* clip); // Reset all collide in the Clip
    void makeCollide(Clip* clip1, Clip* clip2); // Set collide on clip1 & clip2

    int onCollideByName(Clip* clip, std::string name); // Get id of clip collided by Name, if not found return -1
    int onCollideByIndex(Clip* clip, int id); // Get id of clip collided by Index, if not found return -1
    int onCollideByType(Clip* clip, int type);
    void addIndexCollideBy(Clip* clip, int id); // Add Id of clip collided, avoid duplication of id

    // Process Collision System Clip*Clip / rectRect
    void bruteForce(Clip* clip);
    void gridSpatialPart(Clip* clip, GridSpatialPart* grid);
    void quadTree(Clip* clip, QuadTree* quad);

}


#endif // COLLISION2D_H_INCLUDED
