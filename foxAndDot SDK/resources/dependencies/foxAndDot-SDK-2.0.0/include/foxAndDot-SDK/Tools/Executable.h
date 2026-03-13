#pragma once
class Executable
{
public:
    Executable() = default;
    virtual ~Executable() = default;

    virtual void operator()() = 0;
};
