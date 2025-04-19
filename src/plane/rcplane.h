#pragma once

class RCPlane
{
private:
    RCPlane();

public:
    static void init();

    static void tick();
    static void shutdown();
};