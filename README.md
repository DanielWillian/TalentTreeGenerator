# Talent Tree Generator

A project I did for my undergraduate thesis. It generates random talent trees in an RPG environment.

## Definitions

For this project a talent is a list of a tuple composed of three elements: a property, a modifier and a value. For example, the talent

```
    { ( { AreaOfEffectDamage, NoDamageType, NoWeaponType }, *, 1.13 ),
      ( { CriticalChance, NoDamageType, NoWeaponType }, *, 1.04 ) }
```

increases the aoe damage a character does by 13% and increases its critical chance by 4%.

Properties are composed of three strings, a base property, a damage specialization and a weapon specialization. A talent specialized by damage and weapon only apply its modification if the character deals that type of damage or is wielding that type of weapon. These string can be these values:

| Base property         | Damage type    | Weapon type    |
| -------------         | -------------  | ------------   |
| Health                | No damage type | No weapon type |
| Mana                  | Physical       | One handed     |
| Health regen          | Magical        | Two handed     |
| Mana regen            | Acid           | Axe            |
| Attack speed          | Bludgeoning    | Bow            |
| Cast speed            | Cold           | Crossbow       |
| Dodge chance          | Fire           | Dagger         |
| Resistance            | Force          | Fist weapon    |
| Hit chance            | Lightning      | Gun            |
| Critical chance       | Necrotic       | Mace           |
| Critical amp          | Piercing       | Polearm        |
| Single target damage  | Poison         | Staff          |
| Area of effect size   | Psychic        | Sword          |
| Area of effect damage | Radiant        | Thrown         |
| Direct damage         | Slashing       | Wand           |
| Over time damage      | Thunder        |                |
| Duration of dot       |                |                |

Modifiers can be either * or +. Values attached to the * modifier are ranged are at mininum 1 and no more than 3. Values attached to the + modifier are between 0 and 50.

These talents are generated for a specific tree containing 628 nodes, an image of the tree is in the Images folder.

Detailed explanations on these strings and values are given in the paper.

## Installation

The project is built with cmake. There is no requirement of any specific generator or compiler.

Having cloned the repository and being in its root directory you can build it by using the following commands:

```
$ mkdir build && cd build && cmake .. && cmake --build .
```

The executable location depends on the generator used but it is usually in `build/Source`.

## Usage

The executable can be given an optional seed as a parameter, a random seed is used if no parameter is passed. The output is composed of the generated talent tree and a few random branches initialized by either a base property or a specialization.
A talent tree is a map, a talent is bound to a name of a node in the tree.

There are some outputs in the Output folder with some seeds in case you do not want to generate a talent tree yourself.

