#pragma once
#include <vector>
#include "backpack/items.hpp"

class Node{
    private:
        int level;
        double totalValue;
        double totalWeight;
        // float bound;
        // std::vector<Item> structure;
    public:
        Node(int lvl, float tV, float tW): level(lvl), totalValue(tV), totalWeight(tW)/*, bound(0)*/ {};
        int get_level();
        void set_level(int l);
        double get_totalValue();
        void set_totalValue(float v);
        double get_totalWeight();
        void set_totalWeight(float w);
        // float get_bound();
        // void set_bound(float b);
        // std::vector<Item> get_structure();
        // void push_structure(Item i);
        float calculate_bound(double capacity, const std::vector<double>& weights, const std::vector<double>& values);
};