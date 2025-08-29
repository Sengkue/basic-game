#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

// Simple color helpers (works on most modern Windows terminals)
namespace Color {
    const std::string reset = "\x1b[0m";
    const std::string red = "\x1b[31m";
    const std::string green = "\x1b[32m";
    const std::string yellow = "\x1b[33m";
    const std::string blue = "\x1b[34m";
    const std::string magenta = "\x1b[35m";
    const std::string cyan = "\x1b[36m";
    const std::string bold = "\x1b[1m";
}

struct RNG {
    std::mt19937 gen;
    RNG() : gen(std::random_device{}()) {}
    int range(int min, int max) { return std::uniform_int_distribution<>(min, max)(gen); }
    bool chance(int percent) { return range(1, 100) <= percent; }
} rng;

enum class ItemType { Weapon, Armor, Consumable };

struct Item {
    std::string name;
    ItemType type;
    int power = 0;       // Weapon: attack bonus, Armor: defense bonus
    int healAmount = 0;  // Consumable: heal amount
    int price = 0;
};

struct Inventory {
    std::vector<Item> items;

    void add(const Item& it) { items.push_back(it); }

    int findByName(const std::string& n) const {
        for (size_t i = 0; i < items.size(); ++i) if (items[i].name == n) return (int)i;
        return -1;
    }

    void removeAt(int idx) {
        if (idx >= 0 && idx < (int)items.size()) items.erase(items.begin() + idx);
    }

    void list() const {
        if (items.empty()) { std::cout << "  (empty)\n"; return; }
        for (size_t i = 0; i < items.size(); ++i) {
            const auto& it = items[i];
            std::cout << "  [" << i+1 << "] " << it.name << " - ";
            if (it.type == ItemType::Weapon) std::cout << "Weapon (ATK+" << it.power << ")";
            else if (it.type == ItemType::Armor) std::cout << "Armor (DEF+" << it.power << ")";
            else std::cout << "Consumable (Heal " << it.healAmount << ")";
            std::cout << ", $" << it.price << "\n";
        }
    }
};

struct Character {
    std::string name;
    int level = 1;
    int hp = 30;
    int maxHp = 30;
    int attack = 5;
    int defense = 2;
};

struct Player : Character {
    int xp = 0;
    int gold = 0;
    Item weapon{ "Fists", ItemType::Weapon, 0, 0, 0 };
    Item armor{ "Cloth", ItemType::Armor, 0, 0, 0 };
    Inventory inv;

    int atk() const { return attack + weapon.power; }
    int def() const { return defense + armor.power; }

    void levelUpIfNeeded() {
        int need = level * 20;
        while (xp >= need) {
            xp -= need;
            level++;
            maxHp += 5;
            attack += 2;
            defense += 1;
            hp = maxHp;
            std::cout << Color::yellow << "\n== Level Up! You are now level " << level << "! ==" << Color::reset << "\n";
            need = level * 20;
        }
    }
};

struct Enemy : Character {
    int xpReward = 10;
    int goldReward = 5;
    std::vector<Item> loot;
};

namespace Factory {
    Item potionSmall() { return Item{ "Small Potion", ItemType::Consumable, 0, 15, 10 }; }
    Item potionLarge() { return Item{ "Large Potion", ItemType::Consumable, 0, 35, 30 }; }
    Item sword() { return Item{ "Iron Sword", ItemType::Weapon, 4, 0, 40 }; }
    Item greatsword() { return Item{ "Greatsword", ItemType::Weapon, 8, 0, 100 }; }
    Item leather() { return Item{ "Leather Armor", ItemType::Armor, 3, 0, 35 }; }
    Item plate() { return Item{ "Plate Armor", ItemType::Armor, 7, 0, 120 }; }

    Enemy slime() {
        Enemy e; e.name = "Green Slime"; e.level = 1; e.maxHp = e.hp = 20; e.attack = 4; e.defense = 1; e.xpReward = 10; e.goldReward = 8; e.loot = { potionSmall() };
        return e;
    }
    Enemy wolf() {
        Enemy e; e.name = "Wild Wolf"; e.level = 2; e.maxHp = e.hp = 28; e.attack = 6; e.defense = 2; e.xpReward = 16; e.goldReward = 15; e.loot = { potionSmall() };
        return e;
    }
    Enemy bandit() {
        Enemy e; e.name = "Bandit"; e.level = 3; e.maxHp = e.hp = 36; e.attack = 8; e.defense = 3; e.xpReward = 25; e.goldReward = 25; e.loot = { potionLarge() };
        return e;
    }
    Enemy dragonling() {
        Enemy e; e.name = "Dragonling"; e.level = 5; e.maxHp = e.hp = 55; e.attack = 12; e.defense = 6; e.xpReward = 45; e.goldReward = 60; e.loot = { greatsword() };
        return e;
    }
}

int clamp(int v, int lo, int hi) { return std::max(lo, std::min(hi, v)); }

int computeDamage(int atk, int def) {
    int dmg = atk - def;
    dmg = std::max(1, dmg);
    // +/- 20% variance
    int variance = std::max(1, dmg / 5);
    dmg += rng.range(-variance, variance);
    return std::max(1, dmg);
}

void pressEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void flushLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showPlayer(const Player& p) {
    std::cout << Color::cyan << "\n== " << p.name << " ==" << Color::reset << "\n";
    std::cout << "LVL: " << p.level << "  XP: " << p.xp << "  Gold: " << p.gold << "\n";
    std::cout << "HP:  " << p.hp << "/" << p.maxHp << "\n";
    std::cout << "ATK: " << p.atk() << " (Base " << p.attack << "+" << p.weapon.power << ")  DEF: " << p.def() << " (Base " << p.defense << "+" << p.armor.power << ")\n";
    std::cout << "Weapon: " << p.weapon.name << "  Armor: " << p.armor.name << "\n";
}

void equipItem(Player& p) {
    std::cout << "\nInventory:" << "\n";
    p.inv.list();
    std::cout << "\nEnter item number to equip/use (0 to cancel): ";
    int choice; if (!(std::cin >> choice)) { flushLine(); return; }
    flushLine();
    if (choice <= 0 || choice > (int)p.inv.items.size()) return;
    Item it = p.inv.items[choice-1];
    if (it.type == ItemType::Weapon) {
        std::cout << "Equipped weapon: " << it.name << " (ATK+" << it.power << ")\n";
        p.weapon = it;
    } else if (it.type == ItemType::Armor) {
        std::cout << "Equipped armor: " << it.name << " (DEF+" << it.power << ")\n";
        p.armor = it;
    } else if (it.type == ItemType::Consumable) {
        int before = p.hp;
        p.hp = clamp(p.hp + it.healAmount, 0, p.maxHp);
        std::cout << Color::green << "+" << (p.hp - before) << " HP" << Color::reset << " from " << it.name << "\n";
        p.inv.removeAt(choice-1);
        return;
    }
}

void shop(Player& p) {
    std::vector<Item> stock = { Factory::potionSmall(), Factory::potionLarge(), Factory::sword(), Factory::leather(), Factory::greatsword(), Factory::plate() };
    while (true) {
        std::cout << Color::magenta << "\n== Shop ==" << Color::reset << "  (Gold: $" << p.gold << ")\n";
        for (size_t i = 0; i < stock.size(); ++i) {
            const auto& it = stock[i];
            std::cout << "  [" << i+1 << "] " << it.name << " - $" << it.price << " (";
            if (it.type == ItemType::Weapon) std::cout << "ATK+" << it.power;
            else if (it.type == ItemType::Armor) std::cout << "DEF+" << it.power;
            else std::cout << "Heal " << it.healAmount;
            std::cout << ")\n";
        }
        std::cout << "  [0] Leave\nBuy which item? ";
        int c; if (!(std::cin >> c)) { flushLine(); return; }
        flushLine();
        if (c == 0) return;
        if (c < 0 || c > (int)stock.size()) continue;
        const Item& it = stock[c-1];
        if (p.gold < it.price) { std::cout << Color::red << "Not enough gold!" << Color::reset << "\n"; continue; }
        p.gold -= it.price;
        p.inv.add(it);
        std::cout << Color::green << "Purchased " << it.name << "!" << Color::reset << "\n";
    }
}

void giveLoot(Player& p, const Enemy& e) {
    p.xp += e.xpReward;
    p.gold += e.goldReward;
    std::cout << Color::yellow << "You gained " << e.xpReward << " XP and $" << e.goldReward << "!" << Color::reset << "\n";
    if (!e.loot.empty() && rng.chance(50)) {
        const Item& it = e.loot[rng.range(0, (int)e.loot.size()-1)];
        p.inv.add(it);
        std::cout << Color::yellow << "Loot found: " << it.name << "!" << Color::reset << "\n";
    }
    p.levelUpIfNeeded();
}

bool playerTurn(Player& p, Enemy& e) {
    std::cout << "\nYour turn. Choose action:\n";
    std::cout << "  1) Attack\n  2) Power Attack (costs 10 HP, high damage)\n  3) Use/Equip Item\n  4) Attempt to Run\n> ";
    int c; if (!(std::cin >> c)) { flushLine(); return true; }
    flushLine();
    if (c == 1) {
        bool crit = rng.chance(15);
        int dmg = computeDamage(p.atk(), e.defense) * (crit ? 2 : 1);
        e.hp = std::max(0, e.hp - dmg);
        std::cout << Color::green << "You dealt " << dmg << " damage" << (crit? " (CRITICAL)" : "") << "!" << Color::reset << "\n";
    } else if (c == 2) {
        if (p.hp <= 10) { std::cout << Color::red << "Not enough HP to perform Power Attack!" << Color::reset << "\n"; }
        else {
            p.hp -= 10;
            int dmg = computeDamage(p.atk()+5, e.defense) + 5;
            e.hp = std::max(0, e.hp - dmg);
            std::cout << Color::green << "You unleashed a Power Attack for " << dmg << " damage!" << Color::reset << "\n";
        }
    } else if (c == 3) {
        equipItem(p);
    } else if (c == 4) {
        if (rng.chance(40)) { std::cout << Color::yellow << "You managed to run away!" << Color::reset << "\n"; return false; }
        else std::cout << Color::red << "Failed to run!" << Color::reset << "\n";
    }
    return true;
}

bool enemyTurn(Player& p, Enemy& e) {
    if (e.hp <= 0) return true;
    bool special = rng.chance(20);
    int dmg = computeDamage(e.attack + (special?2:0), p.def());
    p.hp = std::max(0, p.hp - dmg);
    std::cout << Color::red << e.name << " dealt " << dmg << " damage" << (special? " with a savage strike!" : "!") << Color::reset << "\n";
    return p.hp > 0;
}

bool combat(Player& p, Enemy e) {
    std::cout << Color::red << "\n== A wild " << e.name << " appears! ==" << Color::reset << "\n";
    while (p.hp > 0 && e.hp > 0) {
        std::cout << "\n" << p.name << " HP: " << p.hp << "/" << p.maxHp << "  |  " << e.name << " HP: " << e.hp << "/" << e.maxHp << "\n";
        bool stayed = playerTurn(p, e);
        if (!stayed) return false; // ran away
        if (e.hp <= 0) break;
        if (!enemyTurn(p, e)) break;
    }
    if (p.hp <= 0) {
        std::cout << Color::red << "\nYou were defeated..." << Color::reset << "\n";
        return false;
    }
    std::cout << Color::green << "\nYou defeated the " << e.name << "!" << Color::reset << "\n";
    giveLoot(p, e);
    return true;
}

struct Location {
    std::string name;
    std::vector<Enemy> encounters;
};

std::vector<Location> buildWorld() {
    return {
        { "Meadow", { Factory::slime(), Factory::wolf() } },
        { "Bandit Road", { Factory::bandit(), Factory::wolf() } },
        { "Volcanic Cave", { Factory::dragonling(), Factory::bandit() } }
    };
}

void saveGame(const Player& p, const std::string& path) {
    std::ofstream f(path);
    if (!f) { std::cout << Color::red << "Failed to save!" << Color::reset << "\n"; return; }
    // Very simple save format
    f << p.name << "\n" << p.level << " " << p.xp << " " << p.gold << "\n";
    f << p.hp << " " << p.maxHp << " " << p.attack << " " << p.defense << "\n";
    f << p.weapon.name << " " << p.weapon.power << "\n";
    f << p.armor.name << " " << p.armor.power << "\n";
    f << p.inv.items.size() << "\n";
    for (const auto& it : p.inv.items) {
        f << (int)it.type << "|" << it.name << "|" << it.power << "|" << it.healAmount << "|" << it.price << "\n";
    }
    std::cout << Color::green << "Game saved to " << path << Color::reset << "\n";
}

bool loadGame(Player& p, const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::string line;
    std::getline(f, p.name);
    if (!std::getline(f, line)) return false; {
        std::istringstream ss(line); ss >> p.level >> p.xp >> p.gold;
    }
    if (!std::getline(f, line)) return false; {
        std::istringstream ss(line); ss >> p.hp >> p.maxHp >> p.attack >> p.defense;
    }
    if (!std::getline(f, line)) return false; {
        std::istringstream ss(line); ss >> p.weapon.name >> p.weapon.power; p.weapon.type = ItemType::Weapon;
    }
    if (!std::getline(f, line)) return false; {
        std::istringstream ss(line); ss >> p.armor.name >> p.armor.power; p.armor.type = ItemType::Armor;
    }
    size_t n = 0; if (!std::getline(f, line)) return false; { std::istringstream ss(line); ss >> n; }
    p.inv.items.clear();
    for (size_t i = 0; i < n; ++i) {
        if (!std::getline(f, line)) break;
        std::istringstream ss(line);
        std::string token; std::vector<std::string> parts;
        while (std::getline(ss, token, '|')) parts.push_back(token);
        if (parts.size() == 5) {
            Item it;
            it.type = (ItemType)std::stoi(parts[0]);
            it.name = parts[1];
            it.power = std::stoi(parts[2]);
            it.healAmount = std::stoi(parts[3]);
            it.price = std::stoi(parts[4]);
            p.inv.add(it);
        }
    }
    p.hp = clamp(p.hp, 0, p.maxHp);
    std::cout << Color::green << "Loaded save from " << path << Color::reset << "\n";
    return true;
}

void explore(Player& p, const Location& loc) {
    std::cout << Color::blue << "\nExploring " << loc.name << "..." << Color::reset << "\n";
    if (rng.chance(60)) {
        const Enemy& proto = loc.encounters[rng.range(0, (int)loc.encounters.size()-1)];
        Enemy e = proto;
        // slight random scaling
        e.attack += rng.range(0, 2);
        e.defense += rng.range(0, 2);
        e.maxHp += rng.range(0, 6); e.hp = e.maxHp;
        combat(p, e);
    } else {
        int eventRoll = rng.range(1, 100);
        if (eventRoll <= 40) {
            int found = rng.range(5, 25);
            p.gold += found;
            std::cout << Color::yellow << "You found a pouch of coins: $" << found << "!" << Color::reset << "\n";
        } else if (eventRoll <= 70) {
            Item it = rng.chance(50) ? Factory::potionSmall() : Factory::potionLarge();
            p.inv.add(it);
            std::cout << Color::yellow << "You discovered an item: " << it.name << "!" << Color::reset << "\n";
        } else {
            std::cout << "It's quiet... You take a short rest and recover 5 HP.\n";
            p.hp = clamp(p.hp + 5, 0, p.maxHp);
        }
    }
}

void mainMenu(Player& p) {
    auto world = buildWorld();
    while (true) {
        std::cout << Color::bold << "\n===== Rift of Realms: Text RPG =====" << Color::reset << "\n";
        showPlayer(p);
        std::cout << "\nChoose an action:\n";
        std::cout << "  1) Explore\n  2) Shop\n  3) Inventory/Equip\n  4) Save Game\n  5) Load Game\n  6) Rest at Inn ($10)\n  7) Quit\n> ";
        int c; if (!(std::cin >> c)) { flushLine(); continue; }
        flushLine();
        if (c == 1) {
            std::cout << "Choose a location:\n";
            for (size_t i = 0; i < world.size(); ++i) std::cout << "  [" << i+1 << "] " << world[i].name << "\n";
            std::cout << "  [0] Cancel\n> ";
            int l; if (!(std::cin >> l)) { flushLine(); continue; }
            flushLine();
            if (l <= 0 || l > (int)world.size()) continue;
            explore(p, world[l-1]);
        } else if (c == 2) {
            shop(p);
        } else if (c == 3) {
            equipItem(p);
        } else if (c == 4) {
            saveGame(p, "save.txt");
        } else if (c == 5) {
            if (!loadGame(p, "save.txt")) std::cout << Color::red << "No save found." << Color::reset << "\n";
        } else if (c == 6) {
            if (p.gold < 10) std::cout << Color::red << "Not enough gold!" << Color::reset << "\n";
            else { p.gold -= 10; p.hp = p.maxHp; std::cout << Color::green << "You feel refreshed!" << Color::reset << "\n"; }
        } else if (c == 7) {
            std::cout << "Goodbye, adventurer!\n";
            break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Player p; p.name = "Hero"; p.level = 1; p.maxHp = p.hp = 35; p.attack = 6; p.defense = 2; p.gold = 30;
    p.inv.add(Factory::potionSmall());
    p.inv.add(Factory::potionSmall());

    std::cout << Color::bold << "\nWelcome to Rift of Realms!" << Color::reset << "\n";
    std::cout << "Enter your hero's name (press Enter for 'Hero'): ";
    std::string nm; std::getline(std::cin, nm);
    if (!nm.empty()) p.name = nm;

    mainMenu(p);
    return 0;
}

