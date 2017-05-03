#ifndef UNITGRID_H
#define UNITGRID_H

#include "model/Definitions.h"

class UnitGrid
	: public QObject
{
	Q_OBJECT
public:
	UnitGrid(QObject* parent) : QObject(parent) {}
	virtual ~UnitGrid() {}

	virtual void init(IntVector2D gridSize, SpaceMetric* metric) = 0;

	virtual void registerUnit(IntVector2D gridPos, Unit* unit) = 0;
	virtual IntVector2D getSize() const = 0;
	virtual Unit* getUnit(IntVector2D gridPos) const = 0;
	virtual IntRect calcCompartmentRect(IntVector2D gridPos) const = 0;
};

#endif // UNITGRID_H
