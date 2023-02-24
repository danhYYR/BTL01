#include "knight.h"

string file_mush_ghost;
string file_asclepius_pack;
string file_merlin_pack;
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}

void display(knight *knight)
{
    cout << "HP=" << knight->HP
         << ", level=" << knight->level
         << ", remedy=" << knight->remedy
         << ", maidenkiss=" << knight->maidenkiss
         << ", phoenixdown=" << knight->phoenixdown
         << ", rescue=" << knight->rescue << endl;
}

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int *kngiht_address[6] = {&HP, &level, &remedy, &maidenkiss, &phoenixdown, &rescue};
    int *event_tmp[MAX];

    string *packet_address[3] = {&file_mush_ghost, &file_asclepius_pack, &file_merlin_pack};
    // In proccess
    rescue = -1;
    for (int i = 0; i < MAX; i++)
    {
        event_tmp[i] = new int(-1);
    }
    // FIle was import will change value HP,level,remedy,maidenkiss,resuce
    import(file_input, kngiht_address, event_tmp, packet_address);
    display(HP, level, phoenixdown, maidenkiss, phoenixdown, rescue);
    int i = 0;
    int num_event = 0;
    while (*event_tmp[i] != -1)
    {
        num_event++;
        i++;
    }
    int event_from_file[num_event];
    for (int i = 0; i < num_event; i++)
    {
        event_from_file[i] = *event_tmp[i];
    }
    // Count the num of event

    // Readfile import Knight's properties, events, bag_items.
    knight knight1;
    // HP,level,remedy,maidenkiss,pheonixdown
    knight1.HP = 998;
    knight1.level = 8;
    knight1.remedy = 0;
    knight1.maidenkiss = 0;
    knight1.phoenixdown = 0;

    knight1.rescue = NOT_OVER;
    knight1.MAX_HP = knight1.HP;
    knight1.id = NORMAL;
    knight1.tiny_lasted = 0;

    if (knight1.HP == 999)
    {
        knight1.id = ARTHUR;
    }
    else if (is_prime(knight1.HP))
    {
        knight1.id = LANCELOT;
    }

    // input events
    int event[] = {18, 19};

    // Loop all events and return rescue value.
    for (int i = 1; i <= sizeof(event) / sizeof(int); i++)
    {
        knightMeetsEvent(&i, event[i - 1], &knight1);
        // rescure CONDITION
        if (knight1.rescue == OVER)
        {
            cout << "WIN GAME\n";
            break;
        }
        else if (knight1.rescue == CANT_RESCUED)
        {
            cout << "princess cant be rescued\n";
            break;
        }
        else if (knight1.rescue == NOT_OVER)
        {
            if (i == sizeof(event) / sizeof(int))
            {
                knight1.rescue = OVER;
            }
        }

        // TINY CONDITION
        if (knight1.tiny_lasted > 0 && (knight1.id == FROG || knight1.id == TINY))
        {
            knight1.tiny_lasted--;
            printf("knight1.tiny_lasted: %d\n", knight1.tiny_lasted);
            if (knight1.tiny_lasted == 0)
            {
                printf("Tiny no longer, turn back to normal health x 5\n");
                knight1.HP *= 5;
            }
        }

        display(&knight1);
        std::cout << endl;
    }

    if (knight1.rescue == OVER)
        cout << "Passed all enemies: winner winner chicken dinner!!\n";
}

/// @brief
/// @param event_id
/// @param knight: knight's infomation
/// @return knight->rescue
void knightMeetsEvent(int *event_index, int event_id, knight *knight)
{
    string mush_ghost_arr_id;
    if (std::to_string(event_id).substr(0, 2) == std::to_string(13))
    {
        mush_ghost_arr_id = std::to_string(event_id).substr(2);
        event_id = MUSH_GHOST;
    }

    switch (event_id)
    {
    case BOWSER_SURRENDER:
        std::cout << "BOWSER_SURRENDER\n";
        knight->level += 1;
        knight->rescue = OVER;
        break;

    case MADBEAR:
        std::cout << "MEET MADBEAR\n";
        enemy madbear;
        madbear.baseDamge = 1;
        madbear.id = MONSTER;
        battle(event_index, knight, &madbear);
        break;

    case BANDIT:
        std::cout << "MEET BANDIT\n";

        enemy bandit;
        bandit.baseDamge = 1.5;
        bandit.id = MONSTER;
        battle(event_index, knight, &bandit);
        break;

    case LORDLUPIN:
        std::cout << "MEET LORDLUPIN\n";
        enemy LordLupin;
        LordLupin.baseDamge = 4.5;
        LordLupin.id = MONSTER;
        battle(event_index, knight, &LordLupin);
        break;

    case ELF:
        std::cout << "MEET ELF\n";
        enemy elf;
        elf.baseDamge = 7.5;
        elf.id = MONSTER;
        battle(event_index, knight, &elf);
        break;

    case TROLL:
        std::cout << "MEET TROLL\n";
        enemy troll;
        troll.baseDamge = 9.5;
        troll.id = MONSTER;
        battle(event_index, knight, &troll);
        break;

    case SHAMAN:
        std::cout << "MEET SHAMAN\n";
        enemy shaman;
        shaman.id = WITCH;
        shaman.name = SHAMAN;
        battle(event_index, knight, &shaman);
        break;

    case VAJISH:
        std::cout << "MEET VAJISH\n";
        enemy vajish;
        vajish.id = WITCH;
        vajish.name = VAJISH;
        battle(event_index, knight, &vajish);
        break;

    case MUSH_MARIO:
        std::cout << "MEET MUSH_MARIO\n";
        int n1, s1;
        n1 = ((knight->level + knight->phoenixdown) % 5 + 1) * 3;
        s1 = sum_largest_odds(n1);
        knight->HP = knight->HP + (s1 % 100);
        if (knight->HP > knight->MAX_HP)
        {
            knight->HP = knight->MAX_HP;
        }

        break;

    case MUSH_FIB:
        std::cout << "MEET MUSH_FIB\n";
        if (knight->HP > 1)
        {
            printf("nearest_fibonacci(%d): %d\n", knight->HP, nearest_fibonacci(knight->HP));
            knight->HP = nearest_fibonacci(knight->HP);
        }
        else if (knight->HP == 1)
        {
            knight->HP = 1;
        }

        break;

    case MUSH_GHOST:
        std::cout << "MEET MUSH_GHOST\n";
        for (size_t i = 0; i < mush_ghost_arr_id.length(); i++)
        {
            cout << mush_ghost_arr_id[i] << endl;
        }

        break;

    case REMEDY:
        std::cout << "MEET REMEDY\n";
        increaseRemedy(knight, 1);
        if (knight->id == TINY)
        {
            useRemedy(knight);
        }

        break;

    case MAIDEN_KISS:
        std::cout << "MEET MAIDEN_KISS\n";
        increaseMaidenKiss(knight, 1);
        if (knight->id == FROG)
            useMaidenKiss(knight);

        break;

    case PHOENIX_DOWN:
        std::cout << "MEET PHOENIX_DOWN\n";
        increasePhoenixDown(knight, 1);
        break;

    case MERLIN:
        std::cout << "MEET MERLIN\n";
        int *item;
        item = get_item(file_merlin_pack, event_id);
        increaseHP(knight, *item);
        break;

    case ASCLEPIUS:
        std::cout << "MEET ASCLEPIUS\n";
        item = get_item(file_asclepius_pack, event_id);
        increaseRemedy(knight, *(item + 1));
        increaseMaidenKiss(knight, *(item + 2));
        increasePhoenixDown(knight, *(item + 3));
        break;

    case BOWSER:
        std::cout << "MEET BOWSER\n";
        enemy bowser;
        bowser.name = BOWSER;
        battle(event_index, knight, &bowser);
        break;

    default:
        break;
    }
}

void battle(int *event_index, knight *knight, enemy *enemy)
{
    int b = *event_index % 10;
    enemy->level = *event_index > 6 ? (b > 5 ? b : 5) : b;
    printf("Enemy LevelO: %d\n", enemy->level);

    switch (compareLevel(knight, enemy))
    {
    case GREATER:
        // LEVEL UP KNIGHT
        if (knight->level < 10)
        {
            if (enemy->id == MONSTER)
            {
                knight->level += 1;
            }
            else if (enemy->id == WITCH)
            {
                knight->level += 2;
            }
        }

        if (knight->level > 10)
            knight->level = 10;

        knight->rescue = NOT_OVER;
        break;

    case LESS:
        // CAL ENEMY HP
        if (enemy->id == MONSTER)
        {
            enemy->realDamge = enemy->baseDamge * enemy->level * 10;
            std::cout << "knight's health lost: " << enemy->realDamge << endl;
            knight->HP = knight->HP - enemy->realDamge;
            // CAL KNIGHT HP
            if (knight->HP <= 0)
            {
                printf("knight's HP < 0\n");
                if (knight->phoenixdown > 0)
                {
                    usePhoenixDown(knight);
                    knight->rescue = NOT_OVER;
                    break;
                }
                else
                {
                    knight->rescue = CANT_RESCUED;
                    break;
                }
            }
            knight->rescue = NOT_OVER;
        }
        // MEET Shaman or Vajish
        else if (enemy->id == WITCH)
        {
            if (knight->id == TINY || knight->id == FROG)
            {
                printf("knight already a frog or being tiny\n");
                break;
            }

            if (enemy->name == SHAMAN)
            {
                printf("Turn knight to tiny\n");
                knight->id = TINY;
                // 4 = current event + next 3 events
                knight->tiny_lasted = 4;

                // HEX ENEMY
                /*
                if (knight->HP < 5)
                {
                    knight->HP = 1;
                }
                else
                {
                    knight->HP = knight->HP / 5;
                }
                */
                (knight->HP < 5) ? (knight->HP = 1) : (knight->HP = knight->HP / 5);

                // USE Remedy
                if (knight->remedy > 0)
                    useRemedy(knight);

                /*
                Nếu HP của hiệp sĩ giảm xuống bằng hoặc dưới 0 khi hiệp sĩ ở
                trạng thái tí hon và hiệp sĩ có PhoenixDown để sử dụng
                */
                if (knight->HP <= 0 && knight->phoenixdown > 0)
                {
                    usePhoenixDown(knight);
                    knight->id = NORMAL; // normal
                    knight->HP = knight->MAX_HP;
                }
                break;
            }

            if (enemy->name == VAJISH)
            {
                printf("Turn knight to frog with level 1\n");
                knight->id = FROG;
                knight->before_turn_frog_level = knight->level;
                knight->level = 1;
                // 4 = current event + next 3 events
                knight->tiny_lasted = 4;

                if (knight->maidenkiss > 0)
                    useMaidenKiss(knight);

                break;
            }
        }

        break;

    case EQUAL:
        printf("FIGHT EVEN\n");
        break;

    default:
        break;
    }
}

void useMaidenKiss(knight *knight)
{
    printf("knight uses maiden kiss\n");
    knight->maidenkiss--;
    knight->id = NORMAL; // normal
    knight->level = knight->before_turn_frog_level;
    knight->tiny_lasted = 0;
}

void usePhoenixDown(knight *knight)
{
    printf("knight has Phoenix Down\n");
    knight->phoenixdown--;
    knight->HP = knight->MAX_HP;
    knight->tiny_lasted = 0;
}

void useRemedy(knight *knight)
{
    printf("knight uses remedy\n");
    knight->remedy--;
    knight->id = NORMAL; // normal condition
    knight->HP *= 5;
    knight->tiny_lasted = 0;
}

int compareLevel(knight *knight, enemy *enemy)
{
    // Meet Bowser
    /*
    (arthur or lancelot with level < 8) vs bowser => lose
    normal knight with level < 10 vs bowser => lose
    */
    if (((knight->id == NORMAL && knight->level < 10) or (knight->level < 8 && (knight->id == ARTHUR || knight->id == LANCELOT))) && enemy->name == BOWSER)
    {
        printf("Meets bowser and lost\n");
        knight->rescue = CANT_RESCUED;
        return 123;
    }

    // Arthur
    if (knight->id == ARTHUR)
    {
        printf("Arthur WIN\n");
        return GREATER;
    }

    // Lancelot
    if (knight->id == LANCELOT && (enemy->id == MONSTER or enemy->id == WITCH))
    {
        printf("Lancelot wins Monster and Witch\n");
        return GREATER;
    }

    // normal knight
    if (knight->level > enemy->level)
    {
        if (enemy->name == BOWSER)
        {
            knight->level = 10;
            printf("Arthur or lancelot or knight's level 10 wins bowser\n");
            return GREATER;
        }

        printf("knight level > enemy level\n");
        return GREATER;
    }
    else if (knight->level < enemy->level)
    {
        printf("knight level < enemy level\n");
        return LESS;
    }

    else if (knight->level == enemy->level)
    {
        printf("knight level = enemy level\n");
        return EQUAL;
    }
    else
    {
        printf("WTF IS THIS???\n");
        return -99;
    }
}

int sum_largest_odds(int n1)
{
    int sum = 0;

    for (int i = 99; i > 0; i -= 2)
    {
        if (n1 > 0)
        {
            sum += i;
        }
        else
        {
            break;
        }
        n1--;
    }
    return sum;
}

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n; // base case
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2); // recursive case
    }
}

int nearest_fibonacci(int num)
{
    int i = 0;
    while (true)
    {
        int fib = fibonacci(i);
        if (std::abs(fib - num) < std::abs(fibonacci(i + 1) - num))
        {
            return fib; // found nearest Fibonacci number
        }
        i++;
    }
}

void increaseHP(knight *knight, int HP_increase)
{
    knight->HP += HP_increase;
    if (knight->HP > knight->MAX_HP)
    {
        knight->HP = knight->MAX_HP;
    }
}

void increaseRemedy(knight *knight, int num_increase)
{
    printf("knight's remedy %d\n", num_increase);
    knight->remedy += num_increase;
    if (knight->remedy > 99)
    {
        knight->remedy = 99;
    }
}
void increaseMaidenKiss(knight *knight, int num_increase)
{
    printf("knight's maidenkiss %d\n", num_increase);

    knight->maidenkiss += num_increase;
    if (knight->maidenkiss > 99)
    {
        knight->maidenkiss = 99;
    }
}
void increasePhoenixDown(knight *knight, int num_increase)
{
    printf("knight's phoenixdown %d\n", num_increase);

    knight->phoenixdown += num_increase;
    if (knight->phoenixdown > 99)
    {
        knight->phoenixdown = 99;
    }
}

int is_prime(int n)

{
    if (n <= 1)
    {
        return 0; // 1 and below are not prime
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0; // n is divisible by i, so it is not prime
        }
    }
    return 1; // n is prime
}
