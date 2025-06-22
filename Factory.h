#pragma once
#include "Decorator.h"
#include <stdexcept>

using namespace std;

enum class CharacterType
{
    WARRIOR,
    MAGE,
    ARCHER
};

class WarriorCharacter : public BaseCharacter
{
public:
    WarriorCharacter(const string &name) : BaseCharacter(name)
    {
        baseAttack = 15;
        baseDefense = 12;
        baseSpeed = 5;
    }

    string getDescription() const override
    {
        return name + " the Warrior";
    }
};

class MageCharacter : public BaseCharacter
{
public:
    MageCharacter(const string &name) : BaseCharacter(name)
    {
        baseAttack = 12;
        baseDefense = 6;
        baseSpeed = 10;
    }

    string getDescription() const override
    {
        return name + " the Mage";
    }
};

class ArcherCharacter : public BaseCharacter
{
public:
    ArcherCharacter(const string &name) : BaseCharacter(name)
    {
        baseAttack = 11;
        baseDefense = 8;
        baseSpeed = 15;
    }

    string getDescription() const override
    {
        return name + " the Archer";
    }
};

class CharacterFactory
{
public:
    static shared_ptr<Character> createCharacter(CharacterType type, const string &name)
    {
        switch (type)
        {
        case CharacterType::WARRIOR:
            return make_shared<WarriorCharacter>(name);
        case CharacterType::MAGE:
            return make_shared<MageCharacter>(name);
        case CharacterType::ARCHER:
            return make_shared<ArcherCharacter>(name);
        default:
            throw invalid_argument("Unknown character type");
        }
    }
};
