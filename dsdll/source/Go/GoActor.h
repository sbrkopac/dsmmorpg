
#ifndef _GOACTOR_H_
#define _GOACTOR_H_

struct SkillEntry
{
    const char *name;
    DWORD unknown1;
    const char *screen_name;
    DWORD unknown2;
    float str_influence;
    float dex_influence;
    float int_influence;
    DWORD unknown3;
    DWORD unknown4;
    float value1;
    DWORD unknown5;
    float value2;
    float base_level;
    float current_level;
    DWORD unknown6;
    DWORD unknown7;
    float max_level;
    void *owner;
};

class GoActor
{
    FEX void SetBaseSkillLevel( const char* skill, float value )
    {
        DWORD *addr = (DWORD *) this;

        SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

        for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
        {
            if(stricmp(skill, skillEntry->name) == 0)
            {
                skillEntry->base_level = value;
                return;
            }
        }
    }

    FEX void ChangeBaseSkillLevel( const char* skill, float delta )
    {
        DWORD *addr = (DWORD *) this;
        SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

        for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
        {
            if(stricmp(skill, skillEntry->name) == 0)
            {
                skillEntry->base_level += delta;

                if(skillEntry->base_level < 0)
                {
                    skillEntry->base_level = 0;
                    return;
                }
            }
        }
    }

    FEX float GetBaseSkillLevel( const char* skill ) const
    {
        DWORD *addr = (DWORD *) this;

        SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

        for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
        {
            if(stricmp(skill, skillEntry->name) == 0)
            {
                return skillEntry->base_level;
            }
        }

        return 0.0f;
    }
};

#endif