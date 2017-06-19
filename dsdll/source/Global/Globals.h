
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

    // Include Libraries
    #include <string>
    #include <time.h>
    #include "../GPG.h"

    using namespace std;

    enum eEquipSlot
    {
        ES_SHIELD_HAND = 0,
        ES_WEAPON_HAND,
        ES_FEET,
        ES_CHEST,
        ES_HEAD,
        ES_FOREARMS,
        ES_AMULET,
        ES_SPELLBOOK,
        ES_RING_0,
        ES_RING_1,
        ES_RING_2,
        ES_RING_3,
        ES_RING,
        ES_NONE,
        ES_ANY,

    };

    enum eActorAlignment
    {
        AA_GOOD = 0,
        AA_NEUTRAL,
        AA_EVIL,
    };

    enum eLifeState
    {
        LS_IGNORE = 0,
        LS_ALIVE_CONSCIOUS,
        LS_ALIVE_UNCONSCIOUS,
        LS_DEAD_NORMAL,
        LS_DEAD_CHARRED,
        LS_DEAD_FRESH,
        LS_DEAD_BONES,
        LS_DEAD_DUST,
        LS_GONE,
        LS_GHOST,
    };

    FEX eEquipSlot MakeEquipSlot (int es)
    {
        return (eEquipSlot)es;
    }

    FEX eActorAlignment MakeActorAlignment (int align)
    {
        return (eActorAlignment)align;
    }

    FEX eLifeState MakeLifeState (int ls)
    {
        return (eLifeState)ls;
    }

    FEX int MakeInt (eEquipSlot es)
    {
        return (int)es;
    }

    FEX int MakeInt (eActorAlignment align)
    {
        return (int)align;
    }

    FEX int MakeInt (eLifeState ls)
    {
        return (int)ls;
    }

    string m_strMemory;
    FEX const char * GenerateRandomString (unsigned int length)
    {
        srand ((unsigned) time(NULL));

        std::string random;
        char randomLetter;

        for (unsigned int i = 0; i < length; i++)
        {
                randomLetter = (char)(rand() % 26) + 'a';
                random += randomLetter;
        }

        m_strMemory = random;
        return (random.c_str());
    }

#endif