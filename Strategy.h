#pragma once
#include <string>
#include <map>
#include <random>

using namespace std;

class CombatStrategy
{
public:
    virtual ~CombatStrategy() = default;
    virtual int calculateDamage(int baseDamage, const std::map<std::string, int> &characterStats) = 0;
    virtual std::string getStrategyName() const = 0;
};

class AggressiveStrategy : public CombatStrategy
{
public:
    int calculateDamage(int baseDamage, const map<string, int> &characterStats) override
    {
        // Aggressive strategy increases damage by 50% but reduces defense
        return static_cast<int>(baseDamage * 1.5);
    }

    string getStrategyName() const override
    {
        return "Aggressive";
    }
};

class DefensiveStrategy : public CombatStrategy
{
public:
    int calculateDamage(int baseDamage, const map<string, int> &characterStats) override
    {
        // Defensive strategy reduces damage by 25% but increases defense
        return static_cast<int>(baseDamage * 0.75);
    }

    string getStrategyName() const override
    {
        return "Defensive";
    }
};

class BalancedStrategy : public CombatStrategy
{
public:
    int calculateDamage(int baseDamage, const map<string, int> &characterStats) override
    {
        // Balanced strategy keeps normal damage with slight random variation
        static random_device rd;
        static mt19937 gen(rd());
        uniform_real_distribution<> dis(0.9, 1.1);
        return static_cast<int>(baseDamage * dis(gen));
    }

    string getStrategyName() const override
    {
        return "Balanced";
    }
};
