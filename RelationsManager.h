#ifndef RELATIONS_MANAGER_H
#define RELATIONS_MANAGER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class RelationsManager 
{
private:
    vector<Relation> relations;

public:
    void addRelation(const string& from, const string& to, const string& type);

    // Check relation properties
    bool isReflexive(const string& type);
    bool isSymmetric(const string& type);
    bool isTransitive(const string& type);
    bool isEquivalenceRelation(const string& type);
    bool isPartialOrder(const string& type);

    // Relation operations
    vector<Relation> composeRelations(const string& type1, const string& type2);
    bool detectConflicts();

    // Get all entities in a relation
    vector<string> getDomainElements(const string& type);
    vector<string> getRangeElements(const string& type);
};

#endif // RELATIONS_MANAGER_H#pragma once
