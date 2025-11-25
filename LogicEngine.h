#ifndef LOGIC_ENGINE_H
#define LOGIC_ENGINE_H

#include "DataStructures.h"
#include <vector>
#include <string>

class LogicEngine 
{
private:
    vector<Rule> rules;

public:
    void addRule(const string& condition, const string& consequence);
    bool evaluateRule(const string& condition);
    bool checkImplication(const string& statement1, const string& statement2);
    bool verifyAllocation(const string& professor, const string& course, const string& lab);
    vector<string> getConsequences(const string& condition);
};

#endif // LOGIC_ENGINE_H