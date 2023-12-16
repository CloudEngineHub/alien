#pragma once

#include <cstdint>

#include "SimulationParametersSpotValues.h"
#include "RadiationSource.h"
#include "SimulationParametersSpot.h"
#include "Motion.h"

/**
 * NOTE: header is also included in kernel code
 */

using CellColorization = int;
enum CellColorization_
{
    CellColorization_None,
    CellColorization_CellColor,
    CellColorization_MutationId,
    CellColorization_LivingState,
    CellColorization_GenomeSize
};

struct SimulationParameters
{
    SimulationParametersSpotValues baseValues;

    uint32_t backgroundColor = 0x1b0000;
    CellColorization cellColorization = CellColorization_CellColor;
    float zoomLevelNeuronalActivity = 2.0f;
    bool showDetonations = true;

    float timestepSize = 1.0f;
    MotionType motionType = MotionType_Fluid;
    MotionData motionData = {FluidMotion()};

    float innerFriction = 0.3f;
    float cellMaxVelocity = 2.0f;              
    float cellMaxBindingDistance = 3.6f;

    ColorVector<float> cellNormalEnergy = {100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f};
    float cellMinDistance = 0.3f;         
    float cellMaxForceDecayProb = 0.2f;
    int cellNumExecutionOrderNumbers = 6;

    float radiationProb = 0.03f;
    float radiationVelocityMultiplier = 1.0f;
    float radiationVelocityPerturbation = 0.5f;
    ColorVector<int> radiationMinCellAge = {0, 0, 0, 0, 0, 0, 0};
    ColorVector<float> radiationAbsorptionVelocityPenalty = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ColorVector<float> radiationAbsorptionLowConnectionPenalty = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ColorVector<float> highRadiationFactor = {0, 0, 0, 0, 0, 0, 0};
    ColorVector<float> highRadiationMinCellEnergy = {500.0f, 500.0f, 500.0f, 500.0f, 500.0f, 500.0f, 500.0f};
    bool clusterDecay = false;
    ColorVector<float> clusterDecayProb = {0.0001f, 0.0001f, 0.0001f, 0.0001f, 0.0001f, 0.0001f, 0.0001f};
    ColorVector<int> cellMaxAge = {
        Infinity<int>::value,
        Infinity<int>::value,
        Infinity<int>::value,
        Infinity<int>::value,
        Infinity<int>::value,
        Infinity<int>::value,
        Infinity<int>::value};
    bool cellMaxAgeBalancer = false;
    int cellMaxAgeBalancerInterval = 10000;
    bool particleTransformationAllowed = false;
    bool particleTransformationRandomCellFunction = false;
    int particleTransformationMaxGenomeSize = 300;
    
    ColorVector<float> cellFunctionConstructorOffspringDistance = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    ColorVector<float> cellFunctionConstructorConnectingCellMaxDistance = {1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f};
    ColorVector<float> cellFunctionConstructorActivityThreshold = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
    bool cellFunctionConstructorCheckCompletenessForSelfReplication = false;

    ColorMatrix<bool> cellFunctionConstructorMutationColorTransitions = {
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true},
        {true, true, true, true, true, true, true}};
    bool cellFunctionConstructorMutationPreventDepthIncrease = false;
    bool cellFunctionConstructorMutationSelfReplication = false;
    ColorVector<float> cellFunctionConstructorExternalEnergy = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ColorVector<float> cellFunctionConstructorExternalEnergySupplyRate = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    ColorVector<float> cellFunctionInjectorRadius = {3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f};
    ColorMatrix<int> cellFunctionInjectorDurationColorMatrix = {
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3}
    };
    float cellFunctionInjectorActivityThreshold = 0.1f;

    ColorVector<float> cellFunctionAttackerRadius = {1.6f, 1.6f, 1.6f, 1.6f, 1.6f, 1.6f, 1.6f};
    ColorVector<float> cellFunctionAttackerStrength = {0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f};
    ColorVector<float> cellFunctionAttackerEnergyDistributionRadius = {3.6f, 3.6f, 3.6f, 3.6f, 3.6f, 3.6f, 3.6f};
    ColorVector<float> cellFunctionAttackerEnergyDistributionValue = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
    ColorVector<float> cellFunctionAttackerColorInhomogeneityFactor = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    ColorMatrix<float> cellFunctionAttackerGenomeSizeBonus = {
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
    };
    ColorMatrix<float> cellFunctionAttackerSameMutantPenalty = {
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
    };
    ColorVector<float> cellFunctionAttackerSensorDetectionFactor = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float cellFunctionAttackerActivityThreshold = 0.1f;
    bool cellFunctionAttackerDestroyCells = false;

    ColorVector<float> cellFunctionDefenderAgainstAttackerStrength = {1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f};
    ColorVector<float> cellFunctionDefenderAgainstInjectorStrength = {1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f};

    bool cellFunctionTransmitterEnergyDistributionSameCreature = true;
    ColorVector<float> cellFunctionTransmitterEnergyDistributionRadius = {3.6f, 3.6f, 3.6f, 3.6f, 3.6f, 3.6f, 3.6f};
    ColorVector<float> cellFunctionTransmitterEnergyDistributionValue = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};

    ColorVector<float> cellFunctionMuscleContractionExpansionDelta = {0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f};
    ColorVector<float> cellFunctionMuscleMovementAcceleration = {0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f};
    ColorVector<float> cellFunctionMuscleBendingAngle = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
    ColorVector<float> cellFunctionMuscleBendingAcceleration = {0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f};
    float cellFunctionMuscleBendingAccelerationThreshold = 0.1f;

    ColorVector<float> cellFunctionSensorRange = {255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f};
    float cellFunctionSensorActivityThreshold = 0.1f;

    ColorVector<float> cellFunctionReconnectorRadius = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    float cellFunctionReconnectorActivityThreshold = 0.1f;

    ColorVector<float> cellFunctionDetonatorRadius = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
    ColorVector<float> cellFunctionDetonatorChainExplosionProbability = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float cellFunctionDetonatorActivityThreshold = 0.1f;

    //particle sources
    int numParticleSources = 0;
    RadiationSource particleSources[MAX_PARTICLE_SOURCES];
    ColorVector<float> cellFunctionConstructorPumpEnergyFactor = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    //spots
    int numSpots = 0;
    SimulationParametersSpot spots[MAX_SPOTS];

    //inherit color
    bool operator==(SimulationParameters const& other) const
    {
        if (motionType != other.motionType) {
            return false;
        }
        if (motionType == MotionType_Fluid) {
            if (motionData.fluidMotion != other.motionData.fluidMotion) {
                return false;
            }
        }
        if (motionType == MotionType_Collision) {
            if (motionData.collisionMotion != other.motionData.collisionMotion) {
                return false;
            }
        }
         
        for (int i = 0; i < MAX_COLORS; ++i) {
            if (cellFunctionAttackerSensorDetectionFactor[i] != other.cellFunctionAttackerSensorDetectionFactor[i]) {
                return false;
            }
            if (cellFunctionConstructorPumpEnergyFactor[i] != other.cellFunctionConstructorPumpEnergyFactor[i]) {
                return false;
            }
            if (cellMaxAge[i] != other.cellMaxAge[i]) {
                return false;
            }
            if (radiationAbsorptionVelocityPenalty[i] != other.radiationAbsorptionVelocityPenalty[i]) {
                return false;
            }
            if (radiationAbsorptionLowConnectionPenalty[i] != other.radiationAbsorptionLowConnectionPenalty[i]) {
                return false;
            }
            if (cellFunctionInjectorRadius[i] != other.cellFunctionInjectorRadius[i]) {
                return false;
            }
            if (cellFunctionDefenderAgainstAttackerStrength[i] != other.cellFunctionDefenderAgainstAttackerStrength[i]) {
                return false;
            }
            if (cellFunctionDefenderAgainstInjectorStrength[i] != other.cellFunctionDefenderAgainstInjectorStrength[i]) {
                return false;
            }
            if (cellFunctionTransmitterEnergyDistributionRadius[i] != other.cellFunctionTransmitterEnergyDistributionRadius[i]) {
                return false;
            }
            if (cellFunctionTransmitterEnergyDistributionValue[i] != other.cellFunctionTransmitterEnergyDistributionValue[i]) {
                return false;
            }
            if (cellFunctionMuscleBendingAcceleration[i] != other.cellFunctionMuscleBendingAcceleration[i]) {
                return false;
            }
            if (cellFunctionMuscleContractionExpansionDelta[i] != other.cellFunctionMuscleContractionExpansionDelta[i]) {
                return false;
            }
            if (cellFunctionMuscleMovementAcceleration[i] != other.cellFunctionMuscleMovementAcceleration[i]) {
                return false;
            }
            if (cellFunctionMuscleBendingAngle[i] != other.cellFunctionMuscleBendingAngle[i]) {
                return false;
            }
            if (cellFunctionMuscleContractionExpansionDelta[i] != other.cellFunctionMuscleContractionExpansionDelta[i]) {
                return false;
            }
            if (cellFunctionMuscleMovementAcceleration[i] != other.cellFunctionMuscleMovementAcceleration[i]) {
                return false;
            }
            if (cellFunctionMuscleBendingAngle[i] != other.cellFunctionMuscleBendingAngle[i]) {
                return false;
            }
            if (cellFunctionAttackerRadius[i] != other.cellFunctionAttackerRadius[i]) {
                return false;
            }
            if (cellFunctionAttackerEnergyDistributionRadius[i] != other.cellFunctionAttackerEnergyDistributionRadius[i]) {
                return false;
            }
            if (cellFunctionAttackerEnergyDistributionValue[i] != other.cellFunctionAttackerEnergyDistributionValue[i]) {
                return false;
            }
            if (cellFunctionAttackerStrength[i] != other.cellFunctionAttackerStrength[i]) {
                return false;
            }
            if (cellFunctionSensorRange[i] != other.cellFunctionSensorRange[i]) {
                return false;
            }
            if (cellFunctionAttackerColorInhomogeneityFactor[i] != other.cellFunctionAttackerColorInhomogeneityFactor[i]) {
                return false;
            }
            if (cellFunctionConstructorActivityThreshold[i] != other.cellFunctionConstructorActivityThreshold[i]) {
                return false;
            }
            if (cellFunctionConstructorConnectingCellMaxDistance[i] != other.cellFunctionConstructorConnectingCellMaxDistance[i]) {
                return false;
            }
            if (cellFunctionConstructorOffspringDistance[i] != other.cellFunctionConstructorOffspringDistance[i]) {
                return false;
            }
            if (clusterDecayProb[i] != other.clusterDecayProb[i]) {
                return false;
            }
            if (cellNormalEnergy[i] != other.cellNormalEnergy[i]) {
                return false;
            }
            if (highRadiationFactor[i] != other.highRadiationFactor[i]) {
                return false;
            }
            if (highRadiationMinCellEnergy[i] != other.highRadiationMinCellEnergy[i]) {
                return false;
            }
            if (radiationMinCellAge[i] != other.radiationMinCellAge[i]) {
                return false;
            }
            if (cellFunctionReconnectorRadius[i] != other.cellFunctionReconnectorRadius[i]) {
                return false;
            }
            if (cellFunctionDetonatorRadius[i] != other.cellFunctionDetonatorRadius[i]) {
                return false;
            }
            if (cellFunctionDetonatorChainExplosionProbability[i] != other.cellFunctionDetonatorChainExplosionProbability[i]) {
                return false;
            }
            if (cellFunctionConstructorExternalEnergy[i] != other.cellFunctionConstructorExternalEnergy[i]) {
                return false;
            }
            if (cellFunctionConstructorExternalEnergySupplyRate[i] != other.cellFunctionConstructorExternalEnergySupplyRate[i]) {
                return false;
            }
        }
        if (numParticleSources != other.numParticleSources) {
            return false;
        }
        for (int i = 0; i < numParticleSources; ++i) {
            if (particleSources[i] != other.particleSources[i]) {
                return false;
            }
        }
        for (int i = 0; i < MAX_COLORS; ++i) {
            for (int j = 0; j < MAX_COLORS; ++j) {
                if (cellFunctionConstructorMutationColorTransitions[i][j] != other.cellFunctionConstructorMutationColorTransitions[i][j]) {
                    return false;
                }
                if (cellFunctionInjectorDurationColorMatrix[i][j] != other.cellFunctionInjectorDurationColorMatrix[i][j]) {
                    return false;
                }
                if (cellFunctionAttackerGenomeSizeBonus[i][j] != other.cellFunctionAttackerGenomeSizeBonus[i][j]) {
                    return false;
                }
                if (cellFunctionAttackerSameMutantPenalty[i][j] != other.cellFunctionAttackerSameMutantPenalty[i][j]) {
                    return false;
                }
            }
        }
        if (numSpots != other.numSpots) {
            return false;
        }
        for (int i = 0; i < numSpots; ++i) {
            if (spots[i] != other.spots[i]) {
                return false;
            }
        }

        return backgroundColor == other.backgroundColor && cellColorization == other.cellColorization
            && zoomLevelNeuronalActivity == other.zoomLevelNeuronalActivity && showDetonations == other.showDetonations
            && baseValues == other.baseValues
            && timestepSize == other.timestepSize && cellMaxVelocity == other.cellMaxVelocity && cellMaxBindingDistance == other.cellMaxBindingDistance
            && cellMinDistance == other.cellMinDistance
            && cellMaxForceDecayProb == other.cellMaxForceDecayProb
            && cellNumExecutionOrderNumbers == other.cellNumExecutionOrderNumbers
            && radiationProb == other.radiationProb && radiationVelocityMultiplier == other.radiationVelocityMultiplier
            && radiationVelocityPerturbation == other.radiationVelocityPerturbation
            && cellFunctionAttackerActivityThreshold == other.cellFunctionAttackerActivityThreshold
            && particleTransformationMaxGenomeSize == other.particleTransformationMaxGenomeSize
            && cellFunctionTransmitterEnergyDistributionSameCreature == other.cellFunctionTransmitterEnergyDistributionSameCreature
            && particleTransformationAllowed == other.particleTransformationAllowed
            && particleTransformationRandomCellFunction == other.particleTransformationRandomCellFunction
            && particleTransformationMaxGenomeSize == other.particleTransformationMaxGenomeSize
            && clusterDecay == other.clusterDecay
            && cellFunctionSensorActivityThreshold == other.cellFunctionSensorActivityThreshold
            && cellFunctionMuscleBendingAccelerationThreshold == other.cellFunctionMuscleBendingAccelerationThreshold
            && cellFunctionConstructorMutationSelfReplication == other.cellFunctionConstructorMutationSelfReplication
            && cellMaxAgeBalancer == other.cellMaxAgeBalancer && cellMaxAgeBalancerInterval == other.cellMaxAgeBalancerInterval
            && cellFunctionConstructorMutationPreventDepthIncrease == other.cellFunctionConstructorMutationPreventDepthIncrease
            && cellFunctionConstructorCheckCompletenessForSelfReplication == other.cellFunctionConstructorCheckCompletenessForSelfReplication
            && cellFunctionAttackerDestroyCells == other.cellFunctionAttackerDestroyCells
            && cellFunctionReconnectorActivityThreshold == other.cellFunctionReconnectorActivityThreshold
            && cellFunctionDetonatorActivityThreshold == other.cellFunctionDetonatorActivityThreshold;
    }

    bool operator!=(SimulationParameters const& other) const { return !operator==(other); }
};
