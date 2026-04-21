#ifndef DISCOUNT_H
#define DISCOUNT_H

class DiscountStrategy{
    public:
    virtual double applyDiscount(double total)=0;
    virtual ~DiscountStrategy (){}
};

class PercentageDiscount : public DiscountStrategy{
    double percent;
    public:
    PercentageDiscount(double percent)
        : percent(percent){}

    double applyDiscount(double total) override{
        return total*(1-percent/100.0);
    }
};

class NoDiscount : public DiscountStrategy{
    public:
    double applyDiscount(double total) override{
        return total;
    }
};

#endif