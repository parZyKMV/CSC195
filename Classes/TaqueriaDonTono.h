#ifndef TAQUERIADT_H
#define TAQUERIADT_H

#include "Base.h"
#include <vector>

class TaqueriaDT {
private:
    std::vector<Tacos*> tacos;

public:
    ~TaqueriaDT();

    void AddTaco();
    void ShowEverthing();
    void LookForName(const std::string& name);
    void LookForMeat(Tacos::tacosMeat meat);
    void LookForTortilla(Tacos::tortillaType tortilla);
};

#endif 
