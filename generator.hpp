#pragma once
#include<random>


struct Generator_state
{
    int id;
    bool active;
    int currentOutput;
    int downTimeHours;

};

struct GeneratorConfig
{
    int id;
    int maxOutput;
    int baseSetPoint;
    int jitterLo,jitterHi;
    double pFail;
    int recoverAfter;
    unsigned seed;
};

class Generator
{
    public:
    explicit Generator(const GeneratorConfig &cfg);

    void step();

    Generator_state state() const;

    private:
    GeneratorConfig cfg_;
    Generator_state st_;
    std::mt19937 rng_;
    std::uniform_int_distribution<int> jitter_;
    std::bernoulli_distribution fail_;

};