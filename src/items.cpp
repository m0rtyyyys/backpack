#include "backpack/items.hpp"


void Item::set_weight(float w) 
{
    weight = w;
    set_unitPrice();
}

float Item::get_weight() const 
{
    return weight;
}

void Item::set_value(float v) 
{
    value = v;
    set_unitPrice();
}

float Item::get_value() const 
{
    return value;
}

void Item::set_unitPrice() 
{
    unitPrice = value/weight;
}

float Item::get_unitPrice() const
{
    return unitPrice;
}

