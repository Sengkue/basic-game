# 🎮 Rift of Realms: Text-Based RPG Adventure

A sophisticated text-based RPG game written in C++ featuring combat, inventory management, character progression, exploration, and save/load functionality.

## 🌟 Advanced Game Features

### Core RPG Systems
- **🎲 Turn-based Combat** - Strategic battles with attack options, critical hits, and power attacks
- **⚔️ Character Progression** - Level up system with XP, increasing stats, and abilities  
- **🎒 Inventory & Equipment** - Weapon and armor slots with stat bonuses
- **🛍️ Shop System** - Buy potions, weapons, and armor with earned gold
- **🌍 Multiple Locations** - Explore different areas with varying enemies and rewards
- **💾 Save/Load System** - Persistent game state using file I/O

### Combat Mechanics
- **Basic Attack** - Standard damage with 15% critical hit chance
- **Power Attack** - High damage special move (costs HP to use)
- **Defense System** - Armor reduces incoming damage
- **Enemy AI** - Enemies have special attacks and varied strategies
- **Run Away Option** - Escape from difficult battles (40% success rate)

### Character Development
- **Level System** - Gain XP from defeating enemies, level up increases all stats
- **Equipment Slots** - Separate weapon and armor with different bonuses
- **Health Management** - HP system with healing items and inn recovery
- **Gold Economy** - Earn money from battles, spend at shops and inns

### World & Exploration
- **Multiple Biomes** - Meadow (easy), Bandit Road (medium), Volcanic Cave (hard)
- **Random Events** - Find treasure, items, or peaceful rest areas
- **Dynamic Scaling** - Enemies have slight random stat variations
- **Loot Drops** - Defeated enemies may drop valuable items

## 🎯 Game Structure

```
Player Character
├── Stats (HP, Attack, Defense, Level, XP, Gold)
├── Equipment (Weapon + Armor slots)  
├── Inventory (Consumables and gear)
└── Progression (Automatic leveling system)

World
├── Meadow (Slimes & Wolves - Level 1-2)
├── Bandit Road (Bandits & Wolves - Level 2-3)  
└── Volcanic Cave (Dragonlings & Bandits - Level 3-5)

Combat System
├── Player Turn (Attack/Power Attack/Item/Run)
├── Enemy Turn (Attack with chance of special move)
├── Damage Calculation (Attack - Defense + variance)
└── Victory Rewards (XP, Gold, Possible Loot)
```

## 🛠️ Building the Game

### Prerequisites
- C++17 compatible compiler
- Windows, macOS, or Linux

### Quick Build (Windows)
1. **For MinGW/g++**: Double-click `build_rpg.bat`
2. **For Visual Studio**: Double-click `build_rpg_msvc.bat`

### Manual Build Commands

**Windows (MinGW):**
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o rpg.exe rpg.cpp
```

**Windows (Visual Studio):**
```bash
cl /EHsc /std=c++17 /O2 rpg.cpp /Fe:rpg.exe
```

**Linux/macOS:**
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o rpg rpg.cpp
```

## 🚀 How to Play

1. **Start the Game**: Run `rpg.exe` (Windows) or `./rpg` (Linux/macOS)
2. **Choose Your Name**: Enter your hero's name or press Enter for default
3. **Main Menu Options**:
   - **Explore**: Choose a location and encounter enemies/events
   - **Shop**: Buy weapons, armor, and healing potions
   - **Inventory**: Equip gear or use consumables
   - **Save/Load**: Persistent game progress
   - **Rest at Inn**: Restore HP for $10
   - **Quit**: Exit the game

### Combat Strategy Tips
- **Power Attacks** deal high damage but cost HP - use wisely!
- **Equipment** significantly impacts your combat effectiveness
- **Healing Potions** are crucial for longer exploration sessions
- **Running Away** can save your life in tough situations
- **Level Up** by fighting enemies - each level dramatically increases your power

## 🎨 Visual Features

- **Colorized Console Output** - Different colors for combat, menus, and status
- **Detailed Statistics Display** - See all your character information at a glance
- **Progress Feedback** - Clear indication of XP gains, level ups, and loot
- **Formatted Combat Log** - Easy to follow turn-by-turn battle descriptions

## ⚡ Advanced C++ Concepts Demonstrated

- **Object-Oriented Design** - Classes, inheritance, encapsulation
- **STL Containers** - vectors, strings, file streams
- **Modern C++ Features** - enum classes, range-based loops, auto
- **File I/O** - Save/load game state persistence  
- **Random Number Generation** - Modern C++11 random facilities
- **Template Usage** - Generic programming concepts
- **Memory Management** - RAII principles, no manual memory allocation
- **Error Handling** - Input validation and error recovery

## 📊 Game Balance

| Enemy Type | Level | HP  | Attack | Defense | XP Reward | Gold Reward |
|------------|-------|-----|--------|---------|-----------|-------------|
| Green Slime| 1     | 20  | 4      | 1       | 10        | $8          |
| Wild Wolf  | 2     | 28  | 6      | 2       | 16        | $15         |
| Bandit     | 3     | 36  | 8      | 3       | 25        | $25         |
| Dragonling | 5     | 55  | 12     | 6       | 45        | $60         |

## 🎮 Example Gameplay

```
===== Rift of Realms: Text RPG =====

== YourHero ==
LVL: 3  XP: 15  Gold: 125
HP:  45/45
ATK: 14 (Base 10+4)  DEF: 8 (Base 5+3)
Weapon: Iron Sword  Armor: Leather Armor

Choose an action:
  1) Explore
  2) Shop  
  3) Inventory/Equip
  4) Save Game
  5) Load Game
  6) Rest at Inn ($10)
  7) Quit

== A wild Bandit appears! ==

YourHero HP: 45/45  |  Bandit HP: 36/36

Your turn. Choose action:
  1) Attack
  2) Power Attack (costs 10 HP, high damage)
  3) Use/Equip Item
  4) Attempt to Run
> 1

You dealt 8 damage (CRITICAL)!
Bandit dealt 5 damage!

YourHero HP: 40/45  |  Bandit HP: 28/36
```

This RPG provides hours of engaging gameplay with meaningful progression, strategic combat, and exploration! Perfect for learning advanced C++ game development concepts.

## 🆚 Comparison with Simple Game

| Feature | Number Guessing | Text RPG |
|---------|-----------------|----------|
| Code Lines | ~150 | ~400+ |
| Classes | 2 simple | 6+ complex |
| Game Systems | 1 (guessing) | 8+ (combat, inventory, etc.) |
| Save/Load | ❌ | ✅ |
| Progression | ❌ | ✅ (Levels, XP, Equipment) |
| Combat | ❌ | ✅ (Turn-based with strategy) |
| Economy | ❌ | ✅ (Gold, Shopping, Items) |
| Replayability | Low | High |

Enjoy your adventure in the Rift of Realms! ⚔️✨
