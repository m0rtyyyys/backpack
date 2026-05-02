#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include "backpack/items.hpp"
#include "backpack/node.hpp"

int main() 
{
    
    std::random_device rd;
    std::mt19937 gen(rd());
    int ch, N;
    float X;
    std::cout << "Choose item for weights:\n1. Uniform real distribution\n2. Normal distribution\nEnter num: ";
    std::cin >> ch;
    std::cout << "Choose number of items\nEnter num: ";
    std::cin >> N;
    std::cout << "Choose maximum value\nEnter num: ";
    std::cin >> X;
    std::uniform_real_distribution<float> distValues(0, X);

    
    std::vector<Item> items;
    switch (ch) 
    {
        case 1:
            {
            std::uniform_real_distribution<float> DistWeights(0,1);
            for(int i = 0; i < N; i++)
            {
                items.emplace_back(DistWeights(gen), distValues(gen));
            }
            break;
            }
        case 2:
            {
            std::normal_distribution<float> DistWeights(0.5f, 0.8f);
            for(int i = 0; i < N; i++)
            {
                items.emplace_back(DistWeights(gen), distValues(gen));
            }
            break;
            }
            default:
                return 1;
                break;
    }
    
    float maxValue= 0;
    float capacity = 1;
    int currentLvl = -1;
    std::vector<Item> bestStructure;
    bestStructure.reserve(0);
    // std::vector<float> weights = {20, 30, 50, 40, 10};
    // std::vector<float> values = {40, 50, 100, 95, 30};
    // for(int i = 0; i < 5; i++)
    // {
    //     items.emplace_back(weights[i], values[i]);
    // }
    // weights.clear();
    // values.clear();
    std::vector<float> weights;
    std::vector<float> values;

    std::sort(items.begin(), items.end(),[](const Item& a, const Item& b) 
    {
        return a.get_unitPrice() > b.get_unitPrice();
    });
    for(int i = 0; i < N; i++)
    {
        weights.push_back(items[i].get_weight());
    }
    for(int i = 0; i < N; i++)
    {
        values.emplace_back(items[i].get_value());
    }
    // for(int i = 0; i < N; i++)
    // {
    //     std::cout << "Item #" << i+1 << "\nvalue = " << items[i].get_value() << "\nweight = " << items[i].get_weight() << "\nUnit price = " << items[i].get_unitPrice() << "\n\n";
    // }
    Node node1(currentLvl, 0, 0);
    std::queue<Node> queue;
    queue.push(node1);
    float greedyWeight= 0.0f;
    float greedyValue = 0.0f;

    auto start_greedy = std::chrono::high_resolution_clock::now();

    for(int i = 0; greedyWeight + items[i].get_weight()< capacity; i++)
    {
        bestStructure.emplace_back(items[i]);
        greedyWeight += items[i].get_weight();
        greedyValue += items[i].get_value();
    }
    auto end_greedy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double> duration_greedy = end_greedy - start_greedy;

    std::cout << "***GREEDY ALGORITHM***" << std::endl;
    std::cout << "Execution time: " << std::fixed << std::setprecision(61) << duration_greedy.count() << std::endl;
    std::cout << "Backpack with the best value = " << std::fixed << std::setprecision(7) << greedyValue << " with weight = " << greedyWeight << std::endl;
    // for (int i = 0; i < bestStructure.size(); i++) 
    // {
    //     std::cout << "Item with weight = " << bestStructure[i].get_weight() << " and value = " << bestStructure[i].get_value() << std::endl;
    // }

    bestStructure.clear();
    auto start_BnB = std::chrono::high_resolution_clock::now();
    while (!queue.empty()) 
    {
        Node curr = queue.front();
        queue.pop();

        currentLvl = curr.get_level() + 1;

        if(currentLvl < weights.size())
        {
            Node left = curr;
            left.set_totalValue(curr.get_totalValue() + items[currentLvl].get_value());
            left.set_totalWeight(curr.get_totalWeight() + items[currentLvl].get_weight());
            left.set_level(currentLvl);
            left.push_structure(items[currentLvl]);
            if(left.get_totalWeight() <= capacity)
            {
                float bound = left.calculate_bound(capacity, weights, values);
                if(bound > maxValue) queue.push(left);
                if(left.get_totalValue() > maxValue) 
                {
                    maxValue = left.get_totalValue();
                    bestStructure = left.get_structure();
                }
            }
            Node right = curr;
            right.set_totalValue(curr.get_totalValue());
            right.set_totalWeight(curr.get_totalWeight());
            right.set_level(currentLvl);
            float bound = right.calculate_bound(capacity, weights, values);
            if(bound > maxValue) queue.push(right);
        }
    }
    auto end_BnB = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double> duration_BnB = end_BnB - start_BnB;
    std::cout << "***BRANCH AND BOUND ALGORITHM***" << std::endl;
    std::cout << "Execution time: " << std::fixed << std::setprecision(61) << duration_BnB.count() << std::endl;
    std::cout << "Backpack with the best value = " << std::fixed << std::setprecision(7) << maxValue << "" << std::endl;

    float delta = abs(maxValue - greedyValue);
    if(delta != 0)
    {
        delta /= maxValue;
    }
    std::cout << "Delta of greedy algorithm = " << delta * 100 << " %" << std::endl;
    // for (int i = 0; i < bestStructure.size(); i++) 
    // {
    //     std::cout << "Item with weight = " << bestStructure[i].get_weight() << " and value = " << bestStructure[i].get_value() << std::endl;
    // }
    return 0;
}