#pragma once
#include <vector>
class Systemtenking
{
    using Age = float;
public:
    void Plot();
    void Simulate();
private:
    void PlotChildren();
    void PlotAdultFertile();

    std::vector<int> m_childPopultation;
    std::vector<int> m_adultFertilePopulation;
};
