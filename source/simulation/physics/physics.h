#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector3D>
#include <cmath>

constexpr qreal degToRad = 3.14159265358979/180.0;
constexpr qreal radToDeg = 180.0/3.14159265358979;

class Physics
{
public:
    //Notice: all angles below are in DEG

    static void collision (QVector3D vA1, QVector3D vB1, QVector3D rAPp, QVector3D rBPp, qreal angularVelA1,
                           qreal angularVelB1, QVector3D n, qreal angularMassA, qreal angularMassB,
                           qreal massA, qreal massB,
                           QVector3D& vA2, QVector3D& vB2, qreal& angularVelA2, qreal& angularVelB2);
    static void fusion (QVector3D vA1, QVector3D vB1, QVector3D rAPp, QVector3D rBPp, qreal angularVelA1,
                           qreal angularVelB1, QVector3D n, qreal angularMassA, qreal angularMassB, qreal angularMassAB,
                           qreal massA, qreal massB,
                           QVector3D& v2, qreal& angularVel2);

    static void changeCenterOfMass (qreal mass, QVector3D vel, qreal angularVel, qreal oldAngularMass,
                                         qreal newAngularMass, QVector3D centerDiff,
                                         QVector3D& newVel, qreal& newAngularVel);

    static QVector3D calcTangentialVelocity (QVector3D r, QVector3D vel, qreal angularVel);

    static qreal calcKineticEnergy (qreal mass, QVector3D vel, qreal angularMass, qreal angularVel);
    static qreal calcNewAngularVelocity (qreal angularMassOld, qreal angularMassNew, qreal angularVelOld);
    static qreal calcNewAngularVelocity2 (qreal Ekin, qreal Etrans, qreal angularMass, qreal angularVelOld);
    static qreal calcAngularMomentum (QVector3D r, QVector3D v);
    static qreal calcAngularVelocity (qreal angularMomentum, qreal angularMass);

    static void applyImpulse (QVector3D impulse, QVector3D rAPp, qreal mass, QVector3D vel, qreal angularMass, qreal angularVel, QVector3D& newVel, qreal& newAngularVel);

    static QVector3D rotateQuarterCounterClockwise (QVector3D v);
    static qreal angleOfVector (QVector3D v);
    static qreal clockwiseAngleBetweenVectors (QVector3D v1, QVector3D v2);
    static QVector3D unitVectorOfAngle (qreal angle);
};

#endif // PHYSICS_H
