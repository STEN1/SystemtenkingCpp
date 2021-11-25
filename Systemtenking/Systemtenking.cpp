#include "Systemtenking.h"

#include "Libs/ImGui/imgui.h"
#include "Libs/ImPlot/implot.h"

#include <vector>

void Systemtenking::Simulate()
{
    float simulationSteps = 200;
    m_childPopultation.resize(simulationSteps);
    m_adultFertilePopulation.resize(simulationSteps);
    m_childPopultation[0] = 400;
    m_adultFertilePopulation[0] = 300;

    float birthRate = 0.052f;
    float childMortality = 0.16f;

    std::vector<Age> children(m_childPopultation[0]);
    for (auto& age : children)
        age = (Age)(rand() % 17);
    std::vector<Age> adultFertile(m_adultFertilePopulation[0]);
    for (auto& age : adultFertile)
        age = (Age)(rand() % 42 + 17);

    int step = 1;
    while (step < simulationSteps)
    {
        for (auto& age : children) // children grow 1 year
            age += 1.f;
        for (auto& age : adultFertile) // adult fertile grow 1 year
            age += 1.f;

        int childBirth = m_adultFertilePopulation[step - 1] * birthRate;
        for (int i = 0; i < childBirth; i++) // push children that are born to the population
            children.push_back(0.f);
        int childDeath = m_adultFertilePopulation[step - 1] * (childMortality / 17.f);
        for (int i = 0; i < childDeath; i++) // kill random children based on mortality rate
        {
            if (children.size() > 0)
            {
                children.erase(children.begin() + rand() % children.size());
            }
        }

        auto childIterator = children.begin();
        while (childIterator != children.end()) // move children that are to old to the adult fertile population
        {
            auto age = *childIterator;
            if (age >= 17.f)
            {
                children.erase(childIterator);
                childIterator = children.begin();

                adultFertile.push_back(17.f);
            }
            else
            {
                childIterator++;
            }
        }
        auto adultFertileIterator = adultFertile.begin();
        while (adultFertileIterator != adultFertile.end()) // Move old people out
        {
            auto age = *adultFertileIterator;
            if (age >= 42)
            {
                adultFertile.erase(adultFertileIterator);
                adultFertileIterator = adultFertile.begin();
            }
            else
            {
                adultFertileIterator++;
            }
        }

        m_childPopultation[step] = children.size();
        m_adultFertilePopulation[step] = adultFertile.size();
        step++;
    }


}

void Systemtenking::PlotChildren()
{
    if (ImPlot::BeginPlot("Children"))
    {
        ImPlot::PlotBars("Bar", m_childPopultation.data(), m_childPopultation.size());
        ImPlot::PlotLine("Line", m_childPopultation.data(), m_childPopultation.size());
        ImPlot::EndPlot();
    }
}

void Systemtenking::PlotAdultFertile()
{
    if (ImPlot::BeginPlot("Adult Fertile"))
    {
        ImPlot::PlotBars("Bar", m_adultFertilePopulation.data(), m_adultFertilePopulation.size());
        ImPlot::PlotLine("Line", m_adultFertilePopulation.data(), m_adultFertilePopulation.size());
        ImPlot::EndPlot();
    }
}


void Systemtenking::Plot()
{
    ImGui::SetNextWindowSize({ 1200, 700 });
    // ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin("Systemtenking");

    PlotChildren();
    PlotAdultFertile();

    ImGui::End();
}
