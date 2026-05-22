#pragma once
class Executable
{

public:
    Executable() = default;
    virtual ~Executable() = default;

    //INTERFACE
    //===============================================================================
        
        virtual void operator()() = 0; // This is the operator

    //===============================================================================
};
