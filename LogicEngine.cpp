#include "LogicEngine.h"
#include <algorithm>

void LogicEngine::addRule(const string& condition, const string& consequence)
{
    // Check for duplicate rules
    for (const auto& rule : rules) {
        if (rule.condition == condition && rule.consequence == consequence) {
            cout << "Error: This rule already exists in the system.\n";
            return;
        }
    }

    // No duplicate found, add the new rule
    rules.push_back(Rule(condition, consequence));
    cout << "Rule added successfully!\n";
}

bool LogicEngine::evaluateRule(const string& condition) 
{
    // Simple placeholder implementation
    // In a real system, this would parse and evaluate logical expressions
    for (const Rule& rule : rules) 
    {
        if (rule.condition == condition) 
        {
            return true;
        }
    }
    return false;
}

bool LogicEngine::checkImplication(const string& statement1, const string& statement2) 
{
    // p -> q is true except when p is true and q is false
    bool p = evaluateRule(statement1);
    bool q = evaluateRule(statement2);

    return !p || q;  // Logical implication: !p || q
}

bool LogicEngine::verifyAllocation(const string& professor, const string& course,
    const string& lab) 
{
    // Example rule: "If Prof. X teaches CS101, the lab must be Lab A"
    string condition = "Professor " + professor + " teaches " + course;
    string consequence = "Lab must be " + lab;

    // Check if this allocation violates any rules
    for (const Rule& rule : rules) 
    {
        if (rule.condition == condition && rule.consequence != consequence) 
        {
            return false; // Violates a rule
        }
    }
    return true;
}

vector<string> LogicEngine::getConsequences(const string& condition) 
{
    vector<string> results;

    for (const Rule& rule : rules) 
    {
        if (rule.condition == condition) 
        {
            results.push_back(rule.consequence);
        }
    }

    return results;
}