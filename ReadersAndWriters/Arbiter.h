#pragma once


class Arbiter
{
public:
	virtual void startRead() = 0;

	virtual void endRead() = 0;

	virtual void startWrite() = 0;

	virtual void endWrite() = 0;
};
