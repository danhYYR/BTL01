#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

/// @brief id, level, baseDamge, realDamge
typedef struct enemy
{
    int id;
    int name;
    int level;
    float baseDamge;
    float realDamge;
} enemy;

typedef struct knight
{
    /// @brief 1: normal, 2: tiny, 3: frog
    int id;
    int HP;
    int MAX_HP;
    int level;
    int old_level;
    int remedy;
    int maidenkiss;
    int phoenixdown;
    int tiny_lasted;

    /// @brief -1: not over, 1: over, 0: cant rescued
    int rescue;
} knight;

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void display(knight *knight);
void knightMeetsEvent(int *event_index, int event_id, knight *knight);

#define GREATER 21
#define LESS -21
#define EQUAL 20
int compareLevel(knight *knight, enemy *enemy);

void battle(int *event_index, knight *knight, enemy *enemy);

void usePhoenixDown(knight *knight);
void useRemedy(knight *knight);
void useMaidenKiss(knight *knight);


int sum_largest_odds(int n1);

#endif // __KNIGHT_H__