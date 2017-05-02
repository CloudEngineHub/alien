#ifndef MAPCOMPARTMENTIMPL_H
#define MAPCOMPARTMENTIMPL_H

#include "model/context/MapCompartment.h"

class MapCompartmentImpl
	: public MapCompartment
{
	Q_OBJECT
public:
	MapCompartmentImpl(QObject* parent = nullptr);
	virtual ~MapCompartmentImpl() {}

	virtual void init(SpaceMetric* metric, IntRect mapRect) override;

	virtual void registerNeighborContext(RelativeLocation location, UnitContext* context) override;
	virtual UnitContext* getNeighborContext(RelativeLocation location) const override;
	virtual UnitContext* getNeighborContext(IntVector2D pos) const override;

private:
};

#endif // MAPCOMPARTMENTIMPL_H
