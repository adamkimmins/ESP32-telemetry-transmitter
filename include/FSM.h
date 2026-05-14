#pragma once

enum class SystemState
{
    OFF,
    BOOTING,
    RUNNING,
    SHUTDOWN
};

enum class SystemEvent
{
    START,
    STOP,
    CONNECTION_LOST,
    BUTTON_PRESS
};

