#pragma once

#include <chrono>

#include "EngineInterface/Definitions.h"
#include "Definitions.h"

class _StartupController
{
public:
    _StartupController(SimulationController const& simController, TemporalControlWindow const& temporalControlWindow);

    void process();
    enum class State
    {
        Unintialized,
        LoadSimulation,
        FadeOutLoadingScreen,
        LoadingControls,
        Ready
    };
    State getState();

    void activate();

private:
    void processLoadingScreen();

    void drawGrid(float yPos, float alpha);

    SimulationController _simController;
    TemporalControlWindow _temporalControlWindow;

    State _state = State::Unintialized;
    TextureData _logo;
    std::optional<std::chrono::steady_clock::time_point> _startupTimepoint;
    std::optional<std::chrono::steady_clock::time_point> _lastActivationTimepoint;
    float _lineDistance = 0;
};
