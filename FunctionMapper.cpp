#include "FunctionMapper.h"
#include <algorithm>

void FunctionMapper::addMapping(const string& from, const string& to) 
{
    mappings.push_back(Mapping(from, to));
}

bool FunctionMapper::isInjective() 
{
    // A function is injective if no two elements in the domain map to the same element in codomain
    // (No two x values map to same y value)

    for (int i = 0; i < mappings.size(); i++) 
    {
        for (int j = i + 1; j < mappings.size(); j++) 
        {
            if (mappings[i].to == mappings[j].to) 
            {
                return false; // Found two elements mapping to the same value
            }
        }
    }

    return true;
}

bool FunctionMapper::isSurjective(const vector<string>& domain, const vector<string>& codomain) 
{
    // A function is surjective if every element in codomain is mapped to by at least one element from domain
    // Every y must be hit by at least one x

    // Check that each codomain element is in our mappings
    for (const string& y : codomain) 
    {
        bool found = false;

        for (const Mapping& mapping : mappings) 
        {
            if (mapping.to == y) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            return false; // Found a codomain element that is not mapped to
        }
    }

    return true;
}

bool FunctionMapper::isBijective(const vector<string>& domain, const vector<string>& codomain) 
{
    // A function is bijective if it is both injective and surjective
    return isInjective() && isSurjective(domain, codomain);
}

vector<Mapping> FunctionMapper::composeWith(const vector<Mapping>& otherMapping) 
{
    vector<Mapping> result;

    // For each mapping (a,b) in this function and (b,c) in otherMapping, 
    // the composition is (a,c)
    for (const Mapping& mapping1 : mappings) 
    {
        for (const Mapping& mapping2 : otherMapping) 
        {
            if (mapping1.to == mapping2.from) 
            {
                result.push_back(Mapping(mapping1.from, mapping2.to));
            }
        }
    }

    return result;
}

vector<Mapping> FunctionMapper::getInverseMapping() 
{
    vector<Mapping> inverse;

    // If the function is injective (one-to-one), we can find its inverse
    if (isInjective()) 
    {
        // Swap from and to for each mapping
        for (const Mapping& mapping : mappings) 
        {
            inverse.push_back(Mapping(mapping.to, mapping.from));
        }
    }

    return inverse;
}

vector<string> FunctionMapper::getDomain() 
{
    vector<string> domain;

    for (const Mapping& mapping : mappings) 
    {
        if (find(domain.begin(), domain.end(), mapping.from) == domain.end()) 
        {
            domain.push_back(mapping.from);
        }
    }

    return domain;
}

vector<string> FunctionMapper::getCodomain() 
{
    vector<string> codomain;

    for (const Mapping& mapping : mappings) 
    {
        if (find(codomain.begin(), codomain.end(), mapping.to) == codomain.end()) 
        {
            codomain.push_back(mapping.to);
        }
    }

    return codomain;
}