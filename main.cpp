#include "Strategy.h"
#include "Decorator.h"
#include "Factory.h"
#include "Template.h"
using namespace std;

// ================================
// DEMO - Putting it all together
// ================================

void demonstrateCombatSystem()
{
    cout << "=== RPG Combat System Demo ===\n\n";

    // FACTORY PATTERN: Create different character types
    cout << "1. FACTORY PATTERN - Creating Characters:\n";
    auto warrior = CharacterFactory::createCharacter(CharacterType::WARRIOR, "Thorin");
    auto mage = CharacterFactory::createCharacter(CharacterType::MAGE, "Gandalf");
    auto archer = CharacterFactory::createCharacter(CharacterType::ARCHER, "Legolas");

    cout << "Created: " << warrior->getDescription() << "\n";
    cout << "Created: " << mage->getDescription() << "\n";
    cout << "Created: " << archer->getDescription() << "\n\n";

    // DECORATOR PATTERN: Apply weapon enchantments
    cout << "2. DECORATOR PATTERN - Applying Enchantments:\n";
    auto enchantedWarrior = make_shared<FireEnchantment>(
        make_shared<IceEnchantment>(warrior));
    auto enchantedMage = make_shared<LightningEnchantment>(mage);

    cout << "Original Warrior - Attack: " << warrior->getAttack()
         << ", Defense: " << warrior->getDefense()
         << ", Speed: " << warrior->getSpeed() << "\n";
    cout << "Enchanted Warrior - Attack: " << enchantedWarrior->getAttack()
         << ", Defense: " << enchantedWarrior->getDefense()
         << ", Speed: " << enchantedWarrior->getSpeed() << "\n";
    cout << "Description: " << enchantedWarrior->getDescription() << "\n";
    cout << "Enchanted Mage: " << enchantedMage->getDescription() << "\n\n";

    // STRATEGY PATTERN: Different combat strategies
    cout << "3. STRATEGY PATTERN - Combat Strategies:\n";
    auto aggressiveStrategy = make_shared<AggressiveStrategy>();
    auto defensiveStrategy = make_shared<DefensiveStrategy>();
    auto balancedStrategy = make_shared<BalancedStrategy>();

    vector<shared_ptr<CombatStrategy>> strategies = {
        aggressiveStrategy, defensiveStrategy, balancedStrategy};

    // TEMPLATE METHOD PATTERN: Execute combat actions
    cout << "4. TEMPLATE METHOD PATTERN - Combat Actions:\n";

    auto meleeAttack = make_shared<MeleeAttack>();
    auto rangedAttack = make_shared<RangedAttack>();
    auto magicAttack = make_shared<MagicAttack>();

    cout << "\n--- Combat Simulation ---\n";

    // Simulate several combat rounds
    struct CombatSetup
    {
        std::shared_ptr<Character> attacker;
        std::shared_ptr<Character> target;
        std::shared_ptr<CombatStrategy> strategy;
        std::shared_ptr<CombatAction> action;
        std::string actionName;
    };

    std::vector<CombatSetup> combats;
    combats.push_back({enchantedWarrior, archer, aggressiveStrategy, meleeAttack, "MeleeAttack"});
    combats.push_back({enchantedMage, enchantedWarrior, balancedStrategy, magicAttack, "MagicAttack"});
    combats.push_back({archer, mage, defensiveStrategy, rangedAttack, "RangedAttack"});

    // Error

    for (size_t i = 0; i < combats.size(); ++i)
    {
        auto &combat = combats[i];
        cout << "\nRound " << (i + 1) << ":\n";
        cout << "Attacker: " << combat.attacker->getDescription()
             << " (ATK: " << combat.attacker->getAttack()
             << ", DEF: " << combat.attacker->getDefense()
             << ", SPD: " << combat.attacker->getSpeed() << ")\n";
        cout << "Target: " << combat.target->getDescription()
             << " (ATK: " << combat.target->getAttack()
             << ", DEF: " << combat.target->getDefense()
             << ", SPD: " << combat.target->getSpeed() << ")\n";
        cout << "Strategy: " << combat.strategy->getStrategyName() << "\n";
        cout << "Attack Type: " << combat.actionName << "\n";

        CombatResult result = combat.action->executeAttack(
            combat.attacker, combat.target, combat.strategy);

        cout << "Base Damage: " << result.baseDamage << "\n";
        cout << "Strategy Modified Damage: " << result.finalDamage << "\n";
        cout << "Final Damage Dealt: " << result.damageDealt << "\n";
        cout << "Special Effect: " << result.specialEffect << "\n";
        cout << string(50, '-') << "\n";
    }
}

int main()
{
    demonstrateCombatSystem();
    return 0;
}