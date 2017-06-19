
#include "Go.hpp"
#include "GoBody.hpp"

GoBody :: GoBody (Go * go) : GoComponent (go)
{
}

GoBody :: GoBody (Go * go, xmlNode * node) : GoComponent (go)
{
    if (node != NULL)
    {
        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "avg_move_velocity") != 0)
            {
                m_avg_move_velocity = xml::ReadAttribute<float> (current, "value", 0.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "max_move_velocity") != 0)
            {
                m_max_move_velocity = xml::ReadAttribute<float> (current, "value", 0.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "min_move_velocity") != 0)
            {
                m_min_move_velocity = xml::ReadAttribute<float> (current, "value", 0.0);
            }
        }
    }
}

float GoBody :: AvgMoveVelocity () const
{
    return m_avg_move_velocity;
}

float GoBody :: MaxMoveVelocity () const
{
    return m_max_move_velocity;
}

float GoBody :: MinMoveVelocity () const
{
    return m_min_move_velocity;
}

void GoBody :: SetAvgMoveVelocity (float velocity)
{
    m_avg_move_velocity = velocity;
}