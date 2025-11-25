#include "RelationsManager.h"
#include <algorithm>

void RelationsManager::addRelation(const string& from, const string& to, const string& type) 
{
    relations.push_back(Relation(from, to, type));
}

bool RelationsManager::isReflexive(const string& type) 
{
    vector<string> domain = getDomainElements(type);

    // For each element x in the domain, check if (x,x) is in the relation
    for (const string& x : domain) 
    {
        bool found = false;
        for (const Relation& rel : relations) 
        {
            if (rel.type == type && rel.from == x && rel.to == x) 
            {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    return true;
}

bool RelationsManager::isSymmetric(const string& type) 
{
    // For each relation (a,b), check if (b,a) is also in the relation
    for (const Relation& rel : relations) 
    {
        if (rel.type == type) 
        {
            bool found = false;
            for (const Relation& rel2 : relations) 
            {
                if (rel2.type == type && rel2.from == rel.to && rel2.to == rel.from) 
                {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }

    return true;
}

bool RelationsManager::isTransitive(const string& type) 
{
    // For each pair of relations (a,b) and (b,c), check if (a,c) is in the relation
    for (const Relation& rel1 : relations) 
    {
        if (rel1.type == type) 
        {
            for (const Relation& rel2 : relations) 
            {
                if (rel2.type == type && rel1.to == rel2.from) 
                {
                    bool found = false;
                    for (const Relation& rel3 : relations) 
                    {
                        if (rel3.type == type && rel3.from == rel1.from && rel3.to == rel2.to) 
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found) return false;
                }
            }
        }
    }

    return true;
}

bool RelationsManager::isEquivalenceRelation(const string& type) 
{
    return isReflexive(type) && isSymmetric(type) && isTransitive(type);
}

bool RelationsManager::isPartialOrder(const string& type) 
{
    // A partial order is reflexive, antisymmetric, and transitive

    // Check reflexive and transitive properties
    if (!isReflexive(type) || !isTransitive(type)) return false;

    // Check antisymmetric: if (a,b) and (b,a) then a=b
    for (const Relation& rel1 : relations) 
    {
        if (rel1.type == type) 
        {
            for (const Relation& rel2 : relations) 
            {
                if (rel2.type == type && rel1.from == rel2.to && rel1.to == rel2.from) 
                {
                    // If a!=b, then this violates antisymmetry
                    if (rel1.from != rel1.to) 
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

vector<Relation> RelationsManager::composeRelations(const string& type1, const string& type2) 
{
    vector<Relation> composition;

    for (const Relation& rel1 : relations) 
    {
        if (rel1.type == type1) 
        {
            for (const Relation& rel2 : relations) 
            {
                if (rel2.type == type2 && rel1.to == rel2.from) 
                {
                    // Create a new relation from the composition
                    Relation newRel(rel1.from, rel2.to, "composed");
                    composition.push_back(newRel);
                }
            }
        }
    }

    return composition;
}

bool RelationsManager::detectConflicts() 
{
    // Example: Check if a student is enrolled in two courses at the same time
    // This is a simplified version - real implementation would need time information

    for (const Relation& rel1 : relations) 
    {
        if (rel1.type == "student-course") 
        {
            for (const Relation& rel2 : relations) 
            {
                if (rel2.type == "student-course" && rel1.from == rel2.from && /*Same student */ rel1.to != rel2.to)
                {     // Different courses

                    // Here we'd check for time conflicts
                    // For simplicity, assume we detect a conflict
                    return true;
                }
            }
        }
    }

    return false; // No conflicts
}

vector<string> RelationsManager::getDomainElements(const string& type) 
{
    vector<string> domain;

    for (const Relation& rel : relations) 
    {
        if (rel.type == type) 
        {
            if (find(domain.begin(), domain.end(), rel.from) == domain.end()) 
            {
                domain.push_back(rel.from);
            }
        }
    }

    return domain;
}

vector<string> RelationsManager::getRangeElements(const string& type) 
{
    vector<string> range;

    for (const Relation& rel : relations) 
    {
        if (rel.type == type) 
        {
            if (find(range.begin(), range.end(), rel.to) == range.end()) 
            {
                range.push_back(rel.to);
            }
        }
    }

    return range;
}