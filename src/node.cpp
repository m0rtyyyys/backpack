#include "backpack/node.hpp"
#include <vector>

int Node::get_level() 
{
    return level;
}

void Node::set_level(int l) 
{
    level = l;
}

float Node::get_totalValue() 
{
    return totalValue;
}

void Node::set_totalValue(float v) 
{
    totalValue = v;
}

float Node::get_totalWeight() 
{
    return totalWeight;
}

void Node::set_totalWeight(float w) 
{
    totalWeight = w;
}

float Node::get_bound() 
{
    return bound;
}

void Node::set_bound(float b) 
{
    bound = b;
}

std::vector<Item> Node::get_structure() 
{
    return structure;
}

void Node::push_structure(Item i) 
{
    structure.emplace_back(i);
}

float Node::calculate_bound(float capacity, const std::vector<float>& weights, const std::vector<float>& values)
{   
    if (totalWeight > capacity) return 0;
    float last_lvl = level;
    float tWeight = totalWeight;
    float tValue = totalValue;
    for(int i = level + 1; (i < weights.size()-1) && (tWeight + weights.at(i) <= capacity) ; i++)
    {
        tWeight += weights.at(i);
        tValue += values.at(i);
        last_lvl = i;
    }
    if(last_lvl < int(weights.size()-1) && tWeight < capacity)
    {
        tValue += (values.at(last_lvl) / weights.at(last_lvl)) * (capacity - tWeight);
    }
    return tValue;
}