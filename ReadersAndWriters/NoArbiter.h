#pragma once

#include "Arbiter.h"

class NoArbiter : public Arbiter
{
public:
	virtual void startRead()
	{
	}

	virtual void endRead()
	{
	}

	virtual void startWrite()
	{
	}

	virtual void endWrite()
	{
	}
};
