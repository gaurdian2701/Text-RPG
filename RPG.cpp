#include "Base.h"

class InfoManager
{

public:
  void PrintStoryInfo()
  {

    std::cout << "\n\n----------INTRO----------\n\n"
              << "You are a humble retired warrior, residing in your cozy village in the mountains.\n"
              << "Other than it being a small trade center for the surrounding villages, not much else happens in this village.\n"
              << "No crimes or trials for punishment have ever happened here, not an inkling of heated matters that"
              << "would catch the attention of the townspeople.\n"
              << "Everyone was happy and content with their lives, and minded their own business without troubling others.\n"
              << "All the village residents are very fond of you and they respect you.\n"
              << "Normally most villages would shun you out of caution due to your violent past, but these people were different.\n"
              << "They saw good in you despite your flaws, took you in, and treated you as one of their own.\n"
              << "You grew accustomed to this comfortable life, and even started to like it.\n"
              << "Everything was fine until one day, the most terrible and haunting event imaginable occurred.....\n\n\n";

    std::cout << "It's the usual day, you're tending to your usual wood chopping duties.\n"
              << "You hear a guttural cry from the center of the village. It sounded terrible, but very familiar to you,\n"
              << "reminding you of the final cries of innocents from your war days..\n"
              << "A village woman was holding her dead son in her arms, and was about to be cut down to death by a goblin.\n"
              << "Surrounding her were the bodies of many other village people.\n"
              << "You've fought goblins before. Absolute scum of the earth, they are.\n"
              << "Spawns from the deepest depths of the underworld, their only intention is to kill and pillage small villages\n"
              << "like the one you've lived in till now.\n\n"
              << "You incapacitate the goblin in one hit, and start interrogating it.\n"
              << "It said that their leader, Murloch was the one who had been sending packs of goblins on daily raids.\n"
              << "Before you can get more information, another goblin shows up!\n"
              << "You scan the second goblin to see if it has anything interesting.\n"
              << "You see a map sticking out from its belt pocket.\n"
              << "The Goblin charges at you.\n"
              << "You get yourself into a fighting stance.\n\n\n";
  }

  void PrintRewardInfo(int i)
  {

    switch (i)
    {
    case 1:
      std::cout << "You have been rewarded with a MAP!\n"
                << "Using the map, you now can track down Murloch's location and hunt him down!\n\n";
      break;

    case 2:
      std::cout << "You have been rewarded with a SWORD!\n"
                << "This unlocks your sword special, which has a 25% chance of dealing extra 20 damage for every attack!\n\n";
      break;

    case 3:
      std::cout << "You have been rewarded with a SHIELD!\n"
                << "This unlocks your shield special, which has a 20% chance of blocking the next attack you receive,"
                << "thus receiving 0 damage!\n\n";
      break;

    case 4:
      std::cout << "You have been rewarded with a BOW!\n"
                << "This unlocks your bow special, where you deal ranged damage and receive less damage during the next attack!\n\n";
      break;

    case 5:
      std::cout << "You have been rewarded with an ARMOUR SET!\n"
                << "This unlocks your armour special, which automatically regenerates your health by 5 points"
                << "during all of your turns!\n";
      break;

    case 6:
      PrintEpilogue();
      break;

    default:
      break;
    }
  }

  void ShowStatIncrease(std::unique_ptr<GameObject> &player)
  {

    std::cout << "\n\n--------STATS INCREASED--------\n\n";
    std::cout << "Health: " << player->GetHealth() << "\n";
    std::cout << "Melee Damage: " << player->GetMeleeDamage() << "\n";
    std::cout << "Ranged Damage: " << player->GetRangedDamage() << "\n";
    std::cout << "Defence: " << player->GetDefence() << "\n";
    std::cout << "Health Regen: " << player->GetHealAmount() << "\n\n";
  }

  void PrintMurlochIntro()
  {

    std::cout << "Murloch is sits on his throne made of human bones.\n"
              << "You realize that these are probably the bones of several innocent people,\n"
              << "cut down the same way you witnessed in your village.\n"
              << "This makes your blood boil...\n\n"
              << "Every goblin you fought until now was a pushover,\n"
              << "the only rewards you reaped were the muscle memory of your fighting experience and some equipment and loot along the way.\n"
              << "But this leader was different. He had a dangerous aura around him. You know you have to be careful around this monster.\n"
              << "You ready yourself for a serious battle.\n\n";

    std::cout << "--------IMPORTANT--------\n\n"
              << "Murloch heals every time you attack him.\n"
              << "He heals by 15% of the damage you deal to him, so make sure he doesn't heal too much!\n"
              << "He can also shoot poison arrows at you, thus poisoning you and dealing continuous damage to you for the\n"
              << "next two turns!\n\n\n";
  }

private:
  void PrintEpilogue()
  {

    std::cout << "Murloch has been defeated.\n"
              << "You know that he is not the only one organizing these raids, and there are many more leaders out there.\n"
              << "\"IS THAT ALL YOU HAVE GOT, YOU FOOLS!\" \nYou howl at the sky, hoping your taunting will reach the other leaders.\n"
              << "With a fiery soul and a mind ready for battle, you walk into the sunset, \n"
              << "and continue your hunt for the other goblin leaders.....\n\n\n";
  }
};

class LevelManager
{

  InfoManager infoManager;

public:
  void PlayLevel(int i, std::unique_ptr<GameObject> &player)
  {
    if (i < 6)
      InitiateBattle(i, player);

    else
      InitiateBattle("Murloch", player);

    if (CheckWinCondition(player))
      RewardPlayer(player, i);

    else
      return;
  }

private:
  void InitiateBattle(int GoblinCount, std::unique_ptr<GameObject> &player)
  {
    std::cout << "\n\nLEVEL " << GoblinCount << "\n\n";
    std::vector<std::unique_ptr<GameObject>> GoblinList;

    CreateGoblinList(GoblinList, GoblinCount);

    while (true)
    {
      if (GoblinList.at(0)->isDead())
        GoblinList.erase(GoblinList.begin());

      if (GoblinList.empty() || player->isDead())
      {
        GoblinList.clear();
        break;
      }

      player->TakeTurn(GoblinList.at(0));

      (GoblinList.at(0))->TakeTurn(player);
    }
  }

  void InitiateBattle(std::string BossName, std::unique_ptr<GameObject> &player)
  {
    std::cout << "BOSS LEVEL: MURLOCH\n\n";
    infoManager.PrintMurlochIntro();
    std::unique_ptr<GameObject> murloch(new MurlochBoss());

    while (!player->isDead() && !murloch->isDead())
    {
      player->TakeTurn(murloch);

      if (murloch->isDead())
        return;

      murloch->TakeTurn(player);
    }
  }

  void RewardPlayer(std::unique_ptr<GameObject> &player, int level)
  {
    infoManager.PrintRewardInfo(level);
    player->UpgradePlayer(level);
    infoManager.ShowStatIncrease(player);
  }

  bool CheckWinCondition(std::unique_ptr<GameObject> &player)
  {

    if (player->isDead())
    {
      std::cout << "You have died!\n\n";
      return false;
    }

    return true;
  }

  void CreateGoblinList(std::vector<std::unique_ptr<GameObject>> &GoblinList, int GoblinCount)
  {
    int i = 1;

    while (i <= GoblinCount)
    {
      GoblinList.push_back(std::make_unique<Goblin>(i));
      i++;
    }
  }
};

class GameManager
{

  LevelManager levelManager;

public:
  void PlayGame()
  {
    std::unique_ptr<GameObject> player(new Player());
    int i = 1;

    while (i <= 6)
    {
      levelManager.PlayLevel(i, player);

      if (player->isDead())
        return;

      i++;
    }
  }
};

int main()
{
  InfoManager infoManager;
  GameManager gameManager;
  infoManager.PrintStoryInfo();
  gameManager.PlayGame();
  return 0;
}