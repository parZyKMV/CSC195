#ifndef THETACO_H
#define THETACO_H

#include "Base.h"

class TheTaco : public Tacos {
private:
	bool withPinnaple;
	bool withGreenSouce;
	bool withRedSouce;

public:
	virtual void Read(std::ostream& ostream, std::istream& istream);
	virtual void Write(std::ostream& ostream);

	bool GetWithPinnaple() const { return withPinnaple; }
	bool GetWithGreenSouce() const { return withGreenSouce; }
	bool GetWithRedSouce() const { return withRedSouce; }
};

#endif
