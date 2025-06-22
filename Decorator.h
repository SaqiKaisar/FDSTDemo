#pragma once
#include <string>
#include <memory>

using namespace std;

class Character
{
public:
    Character(const string &name) : name(name), baseAttack(10), baseDefense(5), baseSpeed(8) {}
    virtual ~Character() = default;

    virtual int getAttack() const = 0;
    virtual int getDefense() const = 0;
    virtual int getSpeed() const = 0;
    virtual string getDescription() const = 0;

    string getName() const { return name; }

protected:
    string name;
    int baseAttack;
    int baseDefense;
    int baseSpeed;
};

class BaseCharacter : public Character
{
public:
    BaseCharacter(const string &name) : Character(name) {}

    int getAttack() const override { return baseAttack; }
    int getDefense() const override { return baseDefense; }
    int getSpeed() const override { return baseSpeed; }

    std::string getDescription() const override
    {
        return name + " (Base Stats)";
    }
};

class WeaponDecorator : public Character
{
public:
    WeaponDecorator(shared_ptr<Character> character)
        : Character(character->getName()), character(character)
    {
        baseAttack = character->getAttack();
        baseDefense = character->getDefense();
        baseSpeed = character->getSpeed();
    }

protected:
    shared_ptr<Character> character;
};

class FireEnchantment : public WeaponDecorator
{
public:
    FireEnchantment(shared_ptr<Character> character) : WeaponDecorator(character) {}

    int getAttack() const override { return character->getAttack() + 5; }
    int getDefense() const override { return character->getDefense(); }
    int getSpeed() const override { return character->getSpeed(); }

    string getDescription() const override
    {
        return character->getDescription();
    }
};

class IceEnchantment : public WeaponDecorator
{
public:
    IceEnchantment(shared_ptr<Character> character) : WeaponDecorator(character) {}

    int getAttack() const override { return character->getAttack() + 3; }
    int getDefense() const override { return character->getDefense() + 2; }
    int getSpeed() const override { return character->getSpeed() - 1; }

    string getDescription() const override
    {
        return character->getDescription();
    }
};

class LightningEnchantment : public WeaponDecorator
{
public:
    LightningEnchantment(shared_ptr<Character> character) : WeaponDecorator(character) {}

    int getAttack() const override { return character->getAttack() + 4; }
    int getDefense() const override { return character->getDefense(); }
    int getSpeed() const override { return character->getSpeed() + 3; }

    string getDescription() const override
    {
        return character->getDescription();
    }
};