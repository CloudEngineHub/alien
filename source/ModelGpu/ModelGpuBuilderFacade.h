#pragma once

#include "ModelBasic/Definitions.h"
#include "Definitions.h"

class ModelGpuBuilderFacade
{
public:
	virtual ~ModelGpuBuilderFacade() = default;

	struct Config {
		IntVector2D universeSize;
		SymbolTable* symbolTable;
		SimulationParameters* parameters;
	};
	virtual SimulationControllerGpu* buildSimulationController(Config const& config
		, ModelGpuData const& specificData
		, uint timestepAtBeginning) const = 0;
	virtual SimulationAccessGpu* buildSimulationAccess() const = 0;

};

