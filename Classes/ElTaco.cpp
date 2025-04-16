#include "ElTaco.h"

void TheTaco::Read(std::ostream& ostream, std::istream& istream)
{
	TheTaco::Read(ostream, istream);

	if (meat == tacosMeat::PASTOR)
	{
		ostream << "With pinnaple (1-Yes, 2-No): ";
		istream >> withPinnaple;
	}

	ostream << "With Green Souce (1-Yes, 2-No): ";
	istream >> withGreenSouce;
	
	ostream << "With Red Souce (1-Yes, 2-No): ";
	istream >> withRedSouce;

}

void TheTaco::Write(std::ostream& ostream) {
	TheTaco::Write(ostream);

	if (meat == tacosMeat::PASTOR) {
		ostream << "Pinnaple: " << (withPinnaple ? "Yes" : "No") << "\n";
	}

	ostream << "Green Souce: " << (withGreenSouce ? "Yes" : "No") << "\n";
	ostream << "Red Souce: " << (withRedSouce ? "Yes" : "No") << "\n";

	ostream << "----------------------------\n";
}