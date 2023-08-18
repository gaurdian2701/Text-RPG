#pragma once

#include <iostream>
#include <memory>
#include <cstdlib>
#include <vector>

class GameObject
{
protected:
    int health;
    int currentHealth;
    int meleeDamage;
    int rangedDamage;
    int defence;
    int healAmount = 5;
    int randomNumber;
    bool dead = false;
    bool damageReductionEnabled = false;

public:
    GameObject() {}

    virtual ~GameObject() {}

public:
    int GetHealth()
    {
        return health;
    }

    int GetMeleeDamage()
    {
        return meleeDamage;
    }

    int GetRangedDamage()
    {
        return rangedDamage;
    }

    int GetDefence()
    {
        return defence;
    }

    int GetHealAmount()
    {
        return healAmount;
    }

    void SetHealth(int amount)
    {
        health = amount;
    }

    void SetMeleeDamage(int amount)
    {
        meleeDamage = amount;
    }

    void SetRangedDamage(int amount)
    {
        rangedDamage = amount;
    }

    void SetDefence(int amount)
    {
        defence = amount;
    }

    void SetHealAmount(int amount){
        healAmount = amount;
    }

    bool isDead()
    {
        return dead;
    }

    virtual void takeDamage(int amount) = 0;
    virtual int Attack() = 0;
    virtual int RangedAttack() {}
    virtual void Heal(int amount) {}
    virtual void TakeTurn(std::unique_ptr<GameObject> &p) {}
    virtual void UpgradePlayer(int i) {}
    virtual void PoisonPlayer(){}

protected:
    inline virtual void PrintBorder() = 0;
};

class Player : public GameObject
{

private:
    enum GearEquipped{
        Map,
        Sword,
        Bow,
        Shield,
        Armour
    };

    bool swordSpecialUnlocked = false;
    bool rangedSpecialUnlocked = false;
    bool shieldSpecialUnlocked = false;
    bool armourSpecialUnlocked = false;
    bool poisoned = false;
    int poisonCount = 0;


public:
    GearEquipped gear = Map;
    
public:
    Player();

    ~Player();

public:
    virtual void takeDamage(int amount);
    virtual int Attack();
    virtual int RangedAttack();
    virtual void Heal(int amount);
    virtual void TakeTurn(std::unique_ptr<GameObject> &p);
    virtual void UpgradePlayer(int i);
    void PoisonPlayer();

private:
    void SwordSpecial(int &extraDamage);
    void ShieldSpecial(int &damageReceived);
    void ArmourSpecial();
    void IncreaseStats();
    void BowLocked(std::unique_ptr<GameObject> &enemy);
    void BowUnlocked(std::unique_ptr<GameObject> &enemy);
    void TakePoisonDamage(int amount);
    void CheckForPoison();

protected:
    inline virtual void PrintBorder();
};

class Goblin : public GameObject
{

public:
    int GoblinID;

public:
    Goblin(int ID);

    ~Goblin();

public:
    int GetGoblinID();
    virtual void takeDamage(int amount);
    virtual int Attack();
    virtual void TakeTurn(std::unique_ptr<GameObject> &p);

protected:
    inline virtual void PrintBorder();
};

class MurlochBoss : public GameObject
{

public: 
    MurlochBoss();

    ~MurlochBoss();

public:
    virtual void takeDamage(int amount);
    virtual int Attack();
    virtual int RangedAttack();
    virtual void Heal(int amount);
    virtual void TakeTurn(std::unique_ptr<GameObject> &p);
    
protected:
    inline virtual void PrintBorder();
};