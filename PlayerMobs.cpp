#include "Base.h"

#pragma region PlayerClass

Player::Player()
{
    std::cout << "YOU, the Player, have made your entrance!\n";
    health = 100;
    currentHealth = health;
    meleeDamage = 10;
    rangedDamage = 5;
    defence = 15;
    healAmount = 10;
}

Player::~Player()
{
    std::cout << "\nThe Game has ended.\n";
}

void Player::UpgradePlayer(int i)
{
    switch (i)
    {
    case 1:
        IncreaseStats();
        break;

    case 2:
        gear = Sword;
        IncreaseStats();
        break;

    case 3:
        gear = Shield;
        IncreaseStats();
        break;

    case 4:
        gear = Bow;
        IncreaseStats();
        break;

    case 5:
        gear = Armour;
        IncreaseStats();
        break;

    case 6:
        IncreaseStats();
        break;
    
    default:
        break;
    }
}

void Player::IncreaseStats()
{
    SetHealth(health + 10);
    SetMeleeDamage(meleeDamage + 5);
    SetDefence(defence + 5);
    SetHealAmount(healAmount + 2);

    if (rangedSpecialUnlocked)
        SetRangedDamage(rangedDamage + 5);

    currentHealth = health;
}

void Player::takeDamage(int amount)
{
    PrintBorder();

    CheckForPoison();

    if (damageReductionEnabled)
    {
        std::cout << "Reduced damage taken after ranged attack!\n";
        amount -= (25.0 / 100.0) * amount;
        !damageReductionEnabled;
    }

    if (gear == Shield)
    {
        randomNumber = rand() % 5;

        if (randomNumber == 3)
            ShieldSpecial(amount);
    }

    amount -= ((defence * 1.0) / 100.0) * amount;

    std::cout << "You have taken " << amount << " points of damage!\n";

    if (currentHealth - amount <= 0)
    {
        std::cout << "You have taken critical damage!\n\n";
        dead = true;
        currentHealth = 0;
        return;
    }
    else
        currentHealth -= amount;

    std::cout << "Remaining health is: " << currentHealth << "\n";
}

void Player::CheckForPoison()
{
    if (poisoned && poisonCount <= 2)
    {
        poisonCount++;
        TakePoisonDamage(10);
    }

    else
    {
        poisonCount = 0;
        !poisoned;
    }
}

void Player::TakePoisonDamage(int amount)
{
    std::cout << "You are getting poisoned!\n";
    if (currentHealth - amount <= 0)
    {
        std::cout << "You have taken critical damage!\n\n";
        currentHealth = 0;
        dead = true;
    }
    else
        currentHealth -= amount;

    std::cout << "Remaining health is: " << currentHealth << "\n\n";
}

void Player::PoisonPlayer()
{
    poisoned = true;
}

int Player::Attack()
{
    int extraDamage = 0;
    PrintBorder();
    CheckForPoison();

    if (gear == Armour)
        ArmourSpecial();

    if (gear == Armour || gear == Sword || gear == Shield || gear == Bow)
    {
        randomNumber = rand() % 4;

        if (randomNumber == 2)
            SwordSpecial(extraDamage);
    }

    std::cout << "You have dealt " << GetMeleeDamage() + extraDamage << " points of melee damage!\n";
    return GetMeleeDamage() + extraDamage;
}

int Player::RangedAttack()
{
    CheckForPoison();
    !damageReductionEnabled;
    std::cout << "You have dealt " << GetRangedDamage() << " points of ranged damage!\n";
    std::cout << "As a result, the damage you receive during the next attack will be reduced!\n";
    return GetRangedDamage();
}

void Player::Heal(int amount)
{
    PrintBorder();

    CheckForPoison();

    if (gear == Armour)
        ArmourSpecial();

    if (currentHealth == health)
    {
        std::cout << "You already have full health!\n";
        return;
    }

    else if (currentHealth + amount >= health)
        currentHealth = health;

    else
        currentHealth += amount;

    std::cout << "You have healed by " << amount << " health points!\n";
    std::cout << "Your current health is: " << currentHealth << "\n\n";
}

void Player::SwordSpecial(int &extraDamage)
{
    std::cout << "Sword Special: Activated!\n"
              << "As part of your sword special, you deal massive damage!\n";
    extraDamage += 20;
}

void Player::ShieldSpecial(int &damageReceived)
{
    std::cout << "Shield Special ---> Activated!\n"
              << "As part of your shield special, you take zero damage!";
    damageReceived = 0;
}

void Player::ArmourSpecial()
{
    std::cout << "As part of the special ability of your armour,"
              << "you automatically regenerate 5 health points for all your turns!\n";
    if (currentHealth + 5 >= health)
        currentHealth = health;
    else
        currentHealth += 5;
}

void Player::TakeTurn(std::unique_ptr<GameObject> &enemy)
{
    if (isDead())
        return;

    if (gear == Bow || gear == Armour)
        BowUnlocked(enemy);

    else
        BowLocked(enemy);
}

void Player::BowLocked(std::unique_ptr<GameObject> &enemy)
{

    std::string turnChoice;
    std::cout << "\n\nIt is your turn. Press 1 to attack. Press anything else to heal.\n";
    std::cout << "Your health: " << currentHealth << "\n";
    std::cin >> turnChoice;

    if (turnChoice == "1")
        enemy->takeDamage(Attack());
    else
        Heal(healAmount);
}

void Player::BowUnlocked(std::unique_ptr<GameObject> &enemy)
{

    std::string turnChoice;
    std::cout << "\n\nIt is your turn. Press 1 to attack, 2 for Bow Attack. Press anything else to heal.\n";
    std::cout << "Your health: " << currentHealth << "\n";
    std::cin >> turnChoice;

    if (turnChoice == "1")
        enemy->takeDamage(Attack());

    else if (turnChoice == "2")
        enemy->takeDamage(RangedAttack());

    else
        Heal(healAmount);
}

inline void Player::PrintBorder()
{
    std::cout << "\n----------PLAYER---------- \n";
}

#pragma endregion PlayerClass

#pragma region GoblinClass

Goblin::Goblin(int ID)
{
    GoblinID = ID;
    health = 60;
    currentHealth = health;
    meleeDamage = 20;
    rangedDamage = 0;
    defence = 0;

    std::cout << "Goblin " << GetGoblinID() << " has appeared!\n"
              << "Goblin " << GetGoblinID() << " health is " << GetHealth() << "\n\n";
}

int Goblin::GetGoblinID()
{
    return GoblinID;
}

Goblin::~Goblin()
{
    std::cout << "\nGoblin " << GetGoblinID() << " has died!.\n\n";
}

void Goblin::takeDamage(int amount)
{
    PrintBorder();

    if (damageReductionEnabled)
    {
        amount = 0;
        !damageReductionEnabled;
    }

    std::cout << "Goblin " << GetGoblinID() << " has taken " << amount << " points of damage!\n";
    if (currentHealth - amount <= 0)
    {
        std::cout << "Goblin " << GetGoblinID() << " has taken critical damage!\n\n";
        currentHealth = 0;
        dead = true;
    }

    else
        currentHealth -= amount;

    std::cout << "Remaining health is: " << currentHealth << "\n";
}

int Goblin::Attack()
{
    PrintBorder();
    std::cout << "Goblin " << GetGoblinID() << " has dealt " << GetMeleeDamage() << " points of damage!\n";
    return meleeDamage;
}

void Goblin::TakeTurn(std::unique_ptr<GameObject> &player)
{
    if (isDead())
        return;

    randomNumber = rand() % 4;

    if (randomNumber == 4)
    {
        PrintBorder();
        std::cout << "Goblin " << GetGoblinID() << " has braced itself!\n"
                  << "As a result, it takes zero damage in the next attack!\n\n";

        !damageReductionEnabled;
    }
    else
        player->takeDamage(Attack());
}

inline void Goblin::PrintBorder()
{
    std::cout << "\n----------GOBLIN " << GetGoblinID() << "----------\n";
}
#pragma endregion GoblinClass

#pragma region MurlochBoss

MurlochBoss ::MurlochBoss()
{
    health = 300;
    meleeDamage = 30;
    rangedDamage = 15;
    defence = 35;
    healAmount = 15;

    std::cout << "Murloch has appeared!\n"
              << "His health is: " << GetHealth() << "\n\n";
}

MurlochBoss::~MurlochBoss()
{
}

void MurlochBoss::takeDamage(int amount)
{
    PrintBorder();

    std::cout << "Murloch has taken " << amount << " points of damage!\n";

    if (currentHealth - amount <= 0)
    {
        std::cout << "Murloch has taken critical damage!\n\n";
        currentHealth = 0;
        dead = true;
        return;
    }

    else
        currentHealth -= amount;

    Heal((15.0/100.0)*amount);
    std::cout << "Murloch's remaining health after taking damage is: " << currentHealth << "\n";
}

void MurlochBoss::Heal(int amount)
{
\
    std::cout << "Murloch has healed by " << amount << " points!\n";

    if (currentHealth == health)
        return;

    else if (currentHealth + amount >= health)
        currentHealth = health;

    else
        currentHealth += amount;

    std::cout << "Murloch's remaining health after healing is: " << currentHealth << "\n";
}

int MurlochBoss::Attack()
{
    std::cout << "Murloch has dealt " << meleeDamage << " points of damage!\n\n";
    return meleeDamage;
}

int MurlochBoss::RangedAttack()
{
    std::cout << "Murloch has shot poison arrows at you and dealt " << rangedDamage << " points of ranged damage!\n"
              << "As a result, you will take 5 points of poison damage for the next two turns!\n\n";
    return rangedDamage;
}

void MurlochBoss::TakeTurn(std::unique_ptr<GameObject> &player)
{

    PrintBorder();
    randomNumber = rand() % 4;

    if (randomNumber == 2)
        player->takeDamage(Attack());

    else if (randomNumber == 1)
        Heal(15);

    else
    {
        player->takeDamage(RangedAttack());
        player->PoisonPlayer();
    }
}

inline void MurlochBoss::PrintBorder()
{
    std::cout << "\n---------- MURLOCH ----------\n";
}

#pragma endregion MurlochBoss