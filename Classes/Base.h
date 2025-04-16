#ifndef TACOS_H
#define TACOS_H

#include <string>
#include <iostream>
#include <vector>

class Tacos
{
public:
	enum class tortillaType
	{
		CLASSIS_CORN,
		BLUE_CORN,
		OTHER,
	};
	enum class tacosMeat
	{
		ASADA,
		SUADERO,
		CHORIZO,
		BISTEC,
		BARBACOA,
		CARNITAS,
		PASTOR,
		ARRACHERA,
		CHOCHINITA_PIBIL,
		CHIKEN,
	};

protected: 
	std::string name;
	tacosMeat meat;
	tortillaType tortilla;
	double price;
	bool withOnions;
	bool withCilantro;
public:
	virtual ~Tacos() {};

	virtual void Read(std::ostream& ostream, std::istream& istream);
	virtual void Write(std::ostream& ostream);

	std::string GetName() const { return name; }
	tacosMeat GetMeat() const { return meat; }
	tortillaType GetTortilla() const { return tortilla; }
	double GetPrice() const { return price; }

	static std::string MeatToString(tacosMeat meat) {
		switch (meat) {
		case tacosMeat::ASADA: return "Asada";
		case tacosMeat::SUADERO: return "Suadero";
		case tacosMeat::CHORIZO: return "Chorizo";
		case tacosMeat::BISTEC: return "Bistec";
		case tacosMeat::BARBACOA: return "Barbacoa";
		case tacosMeat::CARNITAS: return "Carnitas";
		case tacosMeat::PASTOR: return "Al Pastor";
		case tacosMeat::ARRACHERA: return "Arrachera";
		case tacosMeat::CHOCHINITA_PIBIL: return "Cochinita Pibil";
		case tacosMeat::CHIKEN: return "Chken";
		default: return "De perro";
		}
	};

	static std::string TortillaToString(tortillaType tortilla)
	{
		switch (tortilla)
		{
		case tortillaType::CLASSIS_CORN: return "Corn tortilla";
		case tortillaType::BLUE_CORN: return "Blue corn tortilla";
		case tortillaType::OTHER: return "DONT ASK FOR FLOUR TORTILLA O HARD - SHELL OR YOU BE KICKED OUT";
		default: return "DONT ASK FOR FLOUR TORTILLA O HARD-SHELL OR YOU BE KICKED OUT";
		}
	}

};

#endif