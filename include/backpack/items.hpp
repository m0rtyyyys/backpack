#pragma once

class Item{
    private:
        float weight;
        float value;
        float unitPrice;
    public:
        Item(float w, float v): weight(w), value(v), unitPrice(v/w) {};
        ~Item() {};
        void set_weight(float w);
        float get_weight() const;
        void set_value(float v);
        float get_value() const;
        void set_unitPrice();
        float get_unitPrice() const;
};