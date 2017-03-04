#include "Collision2D.h"

Vec2D Collision2D::getReboundVec2D(Vec2D v, Vec2D N)
{
    Vec2D v2;
    float pscal = (v._x*N._x + v._y*N._y); // Produit scalaire
    v2._x = v._x -2*pscal*N._x;
    v2._y = v._y -2*pscal*N._y;

    return v2;

}


Vec2D Collision2D::getNormalPointLine(Vec2D A, Vec2D B, Vec2D C)
{
    Vec2D AC,u,N;

    u._x = B._x - A._x;
    u._y = B._y - A._y;

    AC._x = C._x - A._x;
    AC._y = C._y - A._y;

    float parenthesis = u._x*AC._y-u._y*AC._x;  // calcul une fois pour les deux

    N._x = -u._y*(parenthesis);
    N._y = u._x*(parenthesis);

    // normalisons
    float norme = sqrt(N._x*N._x + N._y*N._y);

    N._x/=norme;
    N._y/=norme;

    return N;
}


Vec2D Collision2D::projectionPointLine(Vec2D A, Vec2D B, Vec2D C)
{
    Vec2D u,AC;

    u._x = B._x - A._x;
    u._y = B._y - A._y;

    AC._x = C._x - A._x;
    AC._y = C._y - A._y;

    float ti = (u._x*AC._x + u._y*AC._y)/(u._x*u._x + u._y*u._y);

    Vec2D I;

    I._x = A._x + ti*u._x;
    I._y = A._y + ti*u._y;

    return I;
}


// Collision TEST !

bool Collision2D::pointRect(Vec2D p, Rect r)
{
    return (p._x > r._x && p._x < r._x + r._w &&
            p._y > r._y && p._y < r._y + r._h);
}
bool Collision2D::pointCircle(Vec2D p, Circle c)
{
    int d2 = (p._x-c._x)*(p._x-c._x) + (p._y-c._y)*(p._y-c._y);

    if (d2>c._r*c._r)
        return false;
    else
        return true;
}

bool Collision2D::pointPolygon(Vec2D P, Vec2D pTab[], int nbP)
{
    for (int i=0; i<nbP; ++i)
    {
        Vec2D A = pTab[i];
        Vec2D B;

        if (i == nbP-1) // if last point join to first point
            B = pTab[0];
        else            // else join to next point
            B = pTab[i+1];

        Vec2D D,T;

        D._x = B._x - A._x;
        D._y = B._y - A._y;
        T._x = P._x - A._x;
        T._y = P._y - A._y;

        auto d = D._x*T._y - D._y*T._x;
        // if d < 0 P is at LEFT of vector AB
        // if d > 0 P is at RIGHT of vector AB
        // if d < 0 P is on vector AB
        if (d<0)
            return false;
    }
    return true;
}

int Collision2D::segmentXSegment(Vec2D A, Vec2D B, Vec2D I, Vec2D P)
{
    Vec2D D,E;

    D._x = B._x - A._x;
    D._y = B._y - A._y;
    E._x = P._x - I._x;
    E._y = P._y - I._y;

    double denom = D._x*E._y - D._y*E._x;

    if (denom==0)
        return -1;   // ERROR , limit case

    float t = - (A._x*E._y-I._x*E._y-E._x*A._y+E._x*I._y) / denom;

    if (t<0 || t>=1)
        return 0;   // don't touch

    float u = - (-D._x*A._y+D._x*I._y+D._y*A._x-D._y*I._x) / denom;

    if (u<0 || u>=1)
        return 0;  // don't touch

    return 1;  // touch
}

bool Collision2D::lineSegment(Vec2D A, Vec2D B, Vec2D O, Vec2D P)
{
    Vec2D AO,AP,AB;

    AB._x = B._x - A._x;
    AB._y = B._y - A._y;
    AP._x = P._x - A._x;
    AP._y = P._y - A._y;
    AO._x = O._x - A._x;
    AO._y = O._y - A._y;

    if ((AB._x*AP._y - AB._y*AP._x)*(AB._x*AO._y - AB._y*AO._x)<0)
        return true;
    else
        return false;
}

bool Collision2D::segmentSegment(Vec2D A, Vec2D B, Vec2D O, Vec2D P)
{
    if (!lineSegment(A,B,O,P))
        return false;
    if (!lineSegment(O,P,A,B))
        return false;

    return true;
}

bool Collision2D::segmentSegmentEX(Vec2D A, Vec2D B, Vec2D O, Vec2D P)
{
    if (lineSegment(A,B,O,P)==false)
        return false;  // inutile d'aller plus loin si le segment [OP] ne touche pas la droite (AB)

    Vec2D AB,OP;

    AB._x = B._x - A._x;
    AB._y = B._y - A._y;
    OP._x = P._x - O._x;
    OP._y = P._y - O._y;

    float k = -(A._x*OP._y-O._x*OP._y-OP._x*A._y+OP._x*O._y)/(AB._x*OP._y-AB._y*OP._x);

    if (k<0 || k>1)
        return false;
    else
        return true;
}


bool Collision2D::pointPolygonEX(Vec2D P, Vec2D pTab[],int nbP)
{
    Vec2D I;

    I._x = 10000 + rand()%100;   // 10000 + un nombre aléatoire entre 0 et 99
    I._y = 10000 + rand()%100;

    int nbintersections = 0;

    for(int i=0; i<nbP; i++)
    {
        Vec2D A = pTab[i];
        Vec2D B;

        if (i == nbP-1)  // si c'est le dernier point, on relie au premier
            B = pTab[0];
        else           // sinon on relie au suivant.
            B = pTab[i+1];

        int iseg = segmentXSegment(A,B,I,P);

        if (iseg == -1)
            return pointPolygonEX(P, pTab, nbP);  // cas limite, on relance la fonction.

        nbintersections+=iseg;
    }

    if (nbintersections%2==1)  // nbintersections est-il impair ?
        return true;
    else
        return false;
}

bool Collision2D::lineCircle(Vec2D A, Vec2D B, Circle C)
{
    Vec2D u;
    u._x = B._x - A._x;
    u._y = B._y - A._y;

    Vec2D AC;
    AC._x = C._x - A._x;
    AC._y = C._y - A._y;

    float numerateur = u._x*AC._y - u._y*AC._x;   // norme du vecteur v

    if (numerateur <0)
        numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.

    float denominateur = sqrt(u._x*u._x + u._y*u._y);  // norme de u

    float CI = numerateur / denominateur;

    if (CI<C._r)
        return true;
    else
        return false;
}

bool Collision2D::segmentCircle(Vec2D A, Vec2D B, Circle C)
{
    if (lineCircle(A,B,C) == false)
        return false;  // si on ne touche pas la droite, on ne touchera jamais le segment

    Vec2D AB,AC,BC;
    AB._x = B._x - A._x;
    AB._y = B._y - A._y;
    AC._x = C._x - A._x;
    AC._y = C._y - A._y;
    BC._x = C._x - B._x;
    BC._y = C._y - B._y;

    float pscal1 = AB._x*AC._x + AB._y*AC._y;  // produit scalaire
    float pscal2 = (-AB._x)*BC._x + (-AB._y)*BC._y;  // produit scalaire

    if (pscal1>=0 && pscal2>=0)
        return true;   // I entre A et B, ok.

    // dernière possibilité, A ou B dans le cercle
    if (pointCircle(A,C))
        return true;

    if (pointCircle(B,C))
        return true;

    return false;
}


bool Collision2D::circleCircle(Circle &c1, Circle &c2)
{
    int d2 = (c1._x - c2._x)*(c1._x - c2._x) + (c1._y - c2._y)*(c1._y - c2._y);

    if (d2 > (c1._r + c2._r)*(c1._r + c2._r))
        return false;
    else
        return true;
}
bool Collision2D::rectRect(Rect &r1, Rect &r2)
{
    if ((r2._x >= r1._x + r1._w)    // trop à droite
        || (r2._x + r2._w <= r1._x) // trop à gauche
        || (r2._y >= r1._y + r1._h) // trop en bas
        || (r2._y + r2._h <= r1._y))  // trop en haut
        return false;
    else
        return true;
}


void Collision2D::cancelAll(Clip* clip)
{
    for (unsigned i = 0; i < clip->vecSize(); ++i)
    {
        if (nullptr != clip->index(i))
        {
            clip->index(i)->_isCollide = false;

            clip->index(i)->_idCollideName = -1;
            clip->index(i)->_idCollideIndex = -1;

            clip->index(i)->_vecCollideBy.clear();
        }
    }
}

void Collision2D::makeCollide(Clip* clip1, Clip* clip2)
{
//    std::cout << "Hit : "<< i <<" & "<< j <<"\n" ;
//
//    std::cout << "_rect i : "<<
//    clip->index(i)->_rect._x << " , "<< clip->index(i)->_rect._y <<" : "<<
//    clip->index(i)->_rect._w << " , "<< clip->index(i)->_rect._h << "\n";
//
//    std::cout << "_rect j : "<<
//    clip->index(j)->_rect._x << " , "<< clip->index(j)->_rect._y <<" : "<<
//    clip->index(j)->_rect._w << " , "<< clip->index(j)->_rect._h << "\n";

    clip1->_isCollide = true;
    clip2->_isCollide = true;

    // Multiple collission possible !
//    clip1->_vecCollideBy.push_back(clip2->id());
//    clip2->_vecCollideBy.push_back(clip1->id());

    addIndexCollideBy(clip1, clip2->id());
    addIndexCollideBy(clip2, clip1->id());


}

void Collision2D::addIndexCollideBy(Clip* clip, int id) // Avoid collision duplication
{
//    if (!clip->_vecCollideBy.empty())
//        for (auto & it: clip->_vecCollideBy)
//        {
//            if (it == id)
//                return;
//        }

    clip->_vecCollideBy.insert(id);
}


int Collision2D::onCollideByName(Clip* clip, std::string name)
{
    if (!clip->_vecCollideBy.empty())
        for (auto & it: clip->_vecCollideBy)
        {
            if (nullptr != clip->_parent->index(it))
                if (clip->_parent->index(it)->_name == name)
                {
                    clip->_idCollideName = it;
                    return it;
                }
        }

    clip->_idCollideName = -1;
    return -1;

}

int Collision2D::onCollideByIndex(Clip* clip, int id)
{
    if (!clip->_vecCollideBy.empty())
        for (auto & it: clip->_vecCollideBy)
        {
            if (nullptr != clip->_parent->index(it))
                if (clip->_parent->index(it)->_id == id)
                {
                    clip->_idCollideIndex = it;
                    return it;
                }
        }

    clip->_idCollideIndex = -1;
    return -1;
}

int Collision2D::onCollideByType(Clip* clip, int type)
{
    if (!clip->_vecCollideBy.empty())
        for (auto & it: clip->_vecCollideBy)
        {
            if (nullptr != clip->_parent->index(it))
                if (clip->_parent->index(it)->_type == type)
                {
                    clip->_idCollideIndex = it;
                    return it;
                }
        }

    clip->_idCollideIndex = -1;
    return -1;
}


void Collision2D::bruteForce(Clip* clip)
{

    for (unsigned i = 0; i < clip->vecSize(); ++i)
    {
        for (unsigned j = i+1; j < clip->vecSize(); ++j)
        {

            if (nullptr != clip->index(i) &&
                nullptr != clip->index(j))
            {
                if (clip->index(i)->_isCollidable &&
                    clip->index(j)->_isCollidable)
                {
                    if (rectRect(clip->index(i)->_rect,
                                 clip->index(j)->_rect))
                    {
                        makeCollide(clip->index(i),clip->index(j));
                    }
                }
            }
        }
    }
}

void Collision2D::gridSpatialPart(Clip* clip, GridSpatialPart* grid)
{
    grid->clearAll();

    for (unsigned i = 0 ; i < clip->vecSize(); ++i)
    {
        if (nullptr != clip->index(i))
            grid->insert(i, clip->index(i)->_rect);
    }

    for (unsigned i = 0; i < clip->vecSize(); ++i)
    {
        if (nullptr != clip->index(i))
        {
            grid->_vecEntity.clear();
            grid->findNear(grid->_vecEntity, clip->index(i)->_rect);

            if (!grid->_vecEntity.empty())
            {
                for (unsigned x = 0; x < grid->_vecEntity.size(); ++x)
                {
                    unsigned j = grid->_vecEntity[x]->_index;
                    if (i != j)
                    {
                        if (j >= 0 && j < clip->vecSize())
                        {
                            if (clip->index(i)->_isCollidable &&
                                clip->index(j)->_isCollidable)
                            {
                                if (rectRect(clip->index(i)->_rect,
                                             clip->index(j)->_rect))
                                {
                                    makeCollide(clip->index(i),clip->index(j));
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}

void Collision2D::quadTree(Clip* clip, QuadTree* quad)
{
    quad->clearNode();
    for (unsigned i = 0; i < clip->vecSize(); ++i)
    {
        quad->insert(i, clip->index(i)->_rect);
    }

    for (unsigned i = 0; i < clip->vecSize(); ++i)
    {
        quad->_vecEntity.clear();
        quad->findNear(quad->_vecEntity, clip->index(i)->_rect);

                for (unsigned x = 0; x < quad->_vecEntity.size(); ++x)
                {
                    unsigned j = quad->_vecEntity[x]->_index;
                    if (i != j)
                    {
                        if (j >= 0 && j < clip->vecSize())
                        {
                            if (clip->index(i)->_isCollidable &&
                                clip->index(j)->_isCollidable)
                            {
                                if (rectRect(clip->index(i)->_rect,
                                             clip->index(j)->_rect))
                                {
                                    makeCollide(clip->index(i),clip->index(j));
                                }
                            }
                        }
                    }
                }
    }
}

