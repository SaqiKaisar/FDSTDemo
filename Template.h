#pragma once
#include <string>
#include <memory>
#include "Decorator.h"
#include "Strategy.h"
#include <iostream>

using namespace std;

struct CombatResult
{
    string attacker;
    string target;
    string strategy;
    int baseDamage;
    int finalDamage;
    int damageDealt;
    string specialEffect;
};

class CombatAction
{
public:
    virtual ~CombatAction() = default;

    // Template method defining the attack sequence
    CombatResult executeAttack(shared_ptr<Character> attacker,
                               shared_ptr<Character> target,
                               shared_ptr<CombatStrategy> strategy)
    {

        prepareAttack(attacker);
        int baseDamage = calculateBaseDamage(attacker);

        map<string, int> stats = {
            {"attack", attacker->getAttack()},
            {"defense", attacker->getDefense()},
            {"speed", attacker->getSpeed()}};

        int finalDamage = strategy->calculateDamage(baseDamage, stats);
        int damageDealt = applyDefense(finalDamage, target);
        executeSpecialEffect(attacker, target);

        return {
            attacker->getDescription(),
            target->getDescription(),
            strategy->getStrategyName(),
            baseDamage,
            finalDamage,
            damageDealt,
            getSpecialEffectDescription()};
    }

protected:
    // Step 1: Prepare for attack (can be overridden)
    virtual void prepareAttack(shared_ptr<Character> attacker)
    {
        cout << attacker->getDescription() << " prepares to attack...\n";
    }

    // Step 2: Calculate base damage (must be implemented)
    virtual int calculateBaseDamage(shared_ptr<Character> attacker) = 0;

    // Step 3: Apply target's defense (can be overridden)
    virtual int applyDefense(int damage, shared_ptr<Character> target)
    {
        int defenseReduction = target->getDefense() / 2;
        return max(1, damage - defenseReduction);
    }

    // Step 4: Execute special effects (can be overridden)
    virtual void executeSpecialEffect(shared_ptr<Character> attacker,
                                      shared_ptr<Character> target) {}

    // Get description of special effects
    virtual string getSpecialEffectDescription()
    {
        return "No special effect";
    }

private:
    static random_device rd;
    static mt19937 gen;

protected:
    static int getRandomInt(int min, int max)
    {
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    static double getRandomDouble()
    {
        uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen);
    }
};

// Static member definitions
random_device CombatAction::rd;
mt19937 CombatAction::gen(CombatAction::rd());

class MeleeAttack : public CombatAction
{
private:
    bool stunApplied = false;

protected:
    int calculateBaseDamage(shared_ptr<Character> attacker) override
    {
        return attacker->getAttack() + getRandomInt(1, 4);
    }

    void executeSpecialEffect(shared_ptr<Character> attacker,
                              shared_ptr<Character> target) override
    {
        // Melee attacks have a chance to stun
        stunApplied = (getRandomDouble() < 0.1); // 10% chance
    }

    string getSpecialEffectDescription() override
    {
        return stunApplied ? "Stun applied!" : "No special effect";
    }
};

class RangedAttack : public CombatAction
{
private:
    bool criticalHit = false;

protected:
    void prepareAttack(shared_ptr<Character> attacker) override
    {
        cout << attacker->getDescription() << " takes aim...\n";
    }

    int calculateBaseDamage(shared_ptr<Character> attacker) override
    {
        // Ranged attacks benefit from speed
        return attacker->getAttack() + (attacker->getSpeed() / 3) + getRandomInt(1, 3);
    }

    void executeSpecialEffect(shared_ptr<Character> attacker,
                              shared_ptr<Character> target) override
    {
        // Ranged attacks have a chance for critical hit
        criticalHit = (getRandomDouble() < 0.15); // 15% chance
    }

    string getSpecialEffectDescription() override
    {
        return criticalHit ? "Critical Hit!" : "No special effect";
    }
};

class MagicAttack : public CombatAction
{
private:
    bool manaDrain = false;

protected:
    void prepareAttack(shared_ptr<Character> attacker) override
    {
        cout << attacker->getDescription() << " channels magical energy...\n";
    }

    int calculateBaseDamage(shared_ptr<Character> attacker) override
    {
        // Magic attacks have higher base damage but more variation
        return attacker->getAttack() + getRandomInt(2, 8);
    }

    int applyDefense(int damage, shared_ptr<Character> target) override
    {
        // Magic attacks partially ignore physical defense
        int defenseReduction = target->getDefense() / 3;
        return max(1, damage - defenseReduction);
    }

    void executeSpecialEffect(shared_ptr<Character> attacker,
                              shared_ptr<Character> target) override
    {
        // Magic attacks have a chance to drain mana/energy
        manaDrain = (getRandomDouble() < 0.2); // 20% chance
    }

    string getSpecialEffectDescription() override
    {
        return manaDrain ? "Mana Drained!" : "No special effect";
    }
};
