#include <gtest/gtest.h>

#include "EngineInterface/DescriptionEditService.h"
#include "EngineInterface/Descriptions.h"
#include "EngineInterface/SimulationFacade.h"
#include "IntegrationTestFramework.h"

class NerveTests : public IntegrationTestFramework
{
public:
    NerveTests()
        : IntegrationTestFramework()
    {}

    ~NerveTests() = default;
};

TEST_F(NerveTests, noInput_execution)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setActivity(activity),
    });

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    auto actualData = _simulationFacade->getSimulationData();
    auto actualCellById = getCellById(actualData);

    EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
}

TEST_F(NerveTests, noInput_noExecution)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(1)
            .setActivity(activity),
    });

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    auto actualData = _simulationFacade->getSimulationData();
    auto actualCellById = getCellById(actualData);

    EXPECT_EQ(activity, actualCellById.at(1).activity);
}

TEST_F(NerveTests, inputBlocked)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0),
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
    }
}

TEST_F(NerveTests, outputBlocked)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setOutputBlocked(true)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
    }
}

TEST_F(NerveTests, underConstruction1)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setLivingState(LivingState_UnderConstruction)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
    }
}

TEST_F(NerveTests, underConstruction2)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5)
            .setLivingState(LivingState_UnderConstruction),
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
    }
}

TEST_F(NerveTests, transfer)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
        CellDescription()
            .setId(3)
            .setPos({3.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(1)
            .setInputExecutionOrderNumber(0),
    });
    data.addConnection(1, 2);
    data.addConnection(2, 3);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(activity, actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
    }

    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(activity, actualCellById.at(3).activity);
    }
    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
    }
}


TEST_F(NerveTests, cycle)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells(
        {CellDescription()
             .setId(1)
             .setPos({1.0f, 1.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(0)
             .setInputExecutionOrderNumber(3),
         CellDescription()
             .setId(2)
             .setPos({2.0f, 1.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(1)
             .setInputExecutionOrderNumber(0),
         CellDescription()
             .setId(3)
             .setPos({2.0f, 2.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(2)
             .setInputExecutionOrderNumber(1),
         CellDescription()
             .setId(4)
             .setPos({1.0f, 2.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(3)
             .setInputExecutionOrderNumber(2)
             .setActivity(activity)});
    data.addConnection(1, 2);
    data.addConnection(2, 3);
    data.addConnection(3, 4);
    data.addConnection(4, 1);

    _simulationFacade->setSimulationData(data);

    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(activity, actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(4).activity);
    }

    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(activity, actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(4).activity);
    }

    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(activity, actualCellById.at(3).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(4).activity);
    }

    for (int i = 0; i < 3; ++i) {
        _simulationFacade->calcTimesteps(1);
    }
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
        EXPECT_EQ(activity, actualCellById.at(4).activity);
    }

    _simulationFacade->calcTimesteps(1);
    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(activity, actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(4).activity);
    }
}

TEST_F(NerveTests, fork)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity),
        CellDescription()
            .setId(3)
            .setPos({3.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
    });
    data.addConnection(1, 2);
    data.addConnection(2, 3);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(activity, actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(activity, actualCellById.at(3).activity);
    }
}

TEST_F(NerveTests, noFork)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription().setId(1).setPos({1.0f, 1.0f}).setCellFunction(NerveDescription()).setMaxConnections(2).setExecutionOrderNumber(1),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity),
        CellDescription()
            .setId(3)
            .setPos({3.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
    });
    data.addConnection(1, 2);
    data.addConnection(2, 3);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
        EXPECT_EQ(activity, actualCellById.at(3).activity);
    }
}

TEST_F(NerveTests, merge)
{
    ActivityDescription activity1, activity2, sumActivity;
    activity1.channels = {1, 0, -1, 0, 0, 0, 0, 0};
    activity2.channels = {2, 0, 0.5f, 0, 0, 0, 0, 0};
    sumActivity.channels = {3, 0, -0.5f, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity1),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(5),
        CellDescription()
            .setId(3)
            .setPos({3.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(5)
            .setActivity(activity2),
    });
    data.addConnection(1, 2);
    data.addConnection(2, 3);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(sumActivity, actualCellById.at(2).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(3).activity);
    }
}

TEST_F(NerveTests, sameExecutionOrderNumber)
{
    ActivityDescription activity;
    activity.channels = {1, 0, -1, 0, 0, 0, 0, 0};

    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setActivity(activity),
        CellDescription()
            .setId(2)
            .setPos({2.0f, 1.0f})
            .setCellFunction(NerveDescription())
            .setMaxConnections(2)
            .setExecutionOrderNumber(0)
            .setInputExecutionOrderNumber(0),
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);

    {
        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        EXPECT_EQ(ActivityDescription(), actualCellById.at(1).activity);
        EXPECT_EQ(ActivityDescription(), actualCellById.at(2).activity);
    }
}

TEST_F(NerveTests, constantPulse)
{
    auto data = DataDescription().addCells({
        CellDescription()
            .setId(1)
            .setPos({1.0f, 1.0f})
            .setCellFunction(NerveDescription().setPulseMode(3).setAlternationMode(0))
            .setMaxConnections(2)
            .setExecutionOrderNumber(0),
         CellDescription()
             .setId(2)
             .setPos({2.0f, 1.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(1)
             .setInputExecutionOrderNumber(0)
             .setOutputBlocked(true)
    });
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);

    for (int i = 0; i <= 18; ++i) {
        _simulationFacade->calcTimesteps(1);

        auto actualData = _simulationFacade->getSimulationData();
        auto actualCellById = getCellById(actualData);

        ActivityDescription activity;
        if (i % 18 == 0) {
            activity.channels = {1, 0, 0, 0, 0, 0, 0, 0};
        }
        EXPECT_EQ(activity, actualCellById.at(1).activity);
    }
}

TEST_F(NerveTests, alternatingPulse)
{
    auto data = DataDescription().addCells(
        {CellDescription()
             .setId(1)
             .setPos({1.0f, 1.0f})
             .setCellFunction(NerveDescription().setPulseMode(3).setAlternationMode(4))
             .setMaxConnections(2)
             .setExecutionOrderNumber(0),
         CellDescription()
             .setId(2)
             .setPos({2.0f, 1.0f})
             .setCellFunction(NerveDescription())
             .setMaxConnections(2)
             .setExecutionOrderNumber(1)
             .setInputExecutionOrderNumber(0)
             .setOutputBlocked(true)});
    data.addConnection(1, 2);

    _simulationFacade->setSimulationData(data);
    _simulationFacade->calcTimesteps(1);
    {
        auto actualCellById = getCellById(_simulationFacade->getSimulationData());
        EXPECT_EQ(ActivityDescription().setChannels({1, 0, 0, 0, 0, 0, 0, 0}), actualCellById.at(1).activity);
    }

    for (int pulse = 0; pulse < 3; ++pulse) {
        for (int i = 0; i < 6*3; ++i) {
            _simulationFacade->calcTimesteps(1);
        }
        auto actualCellById = getCellById(_simulationFacade->getSimulationData());
        EXPECT_EQ(ActivityDescription().setChannels({1, 0, 0, 0, 0, 0, 0, 0}), actualCellById.at(1).activity);
    }

    for (int pulse = 0; pulse < 4; ++pulse) {
        for (int i = 0; i < 6*3; ++i) {
            _simulationFacade->calcTimesteps(1);
        }
        auto actualCellById = getCellById(_simulationFacade->getSimulationData());
        EXPECT_EQ(ActivityDescription().setChannels({-1, 0, 0, 0, 0, 0, 0, 0}), actualCellById.at(1).activity);
    }
    for (int pulse = 0; pulse < 4; ++pulse) {
        for (int i = 0; i < 6*3; ++i) {
            _simulationFacade->calcTimesteps(1);
        }
        auto actualCellById = getCellById(_simulationFacade->getSimulationData());
        EXPECT_EQ(ActivityDescription().setChannels({1, 0, 0, 0, 0, 0, 0, 0}), actualCellById.at(1).activity);
    }
}
