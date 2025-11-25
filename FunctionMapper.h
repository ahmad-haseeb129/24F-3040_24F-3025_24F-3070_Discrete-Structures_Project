#ifndef FUNCTION_MAPPER_H
#define FUNCTION_MAPPER_H

#include "DataStructures.h"
#include <vector>
#include <string>

class FunctionMapper 
{
private:
    vector<Mapping> mappings;

public:
    void addMapping(const string& from, const string& to);

    // Function property tests
    bool isInjective();
    bool isSurjective(const vector<string>& domain, const vector<string>& codomain);
    bool isBijective(const vector<string>& domain, const vector<string>& codomain);

    // Function operations
    vector<Mapping> composeWith(const vector<Mapping>& otherMapping);
    vector<Mapping> getInverseMapping();

    // Get domain and codomain elements
    vector<string> getDomain();
    vector<string> getCodomain();
};

#endif // FUNCTION_MAPPER_H