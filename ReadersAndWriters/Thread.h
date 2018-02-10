#pragma once

#include <Windows.h>
//Klasa Thread to klasa w¹tku, po której dziedzicz¹ klasy w¹tków-czytelników oraz w¹tków-pisarzy
class Thread
{
public:
	virtual void run() = 0;

	//Metoda statyczna uruchamiaj¹ca w¹tek
	static DWORD WINAPI runThread(LPVOID args)
	{
		Thread* thread = (Thread*)args;
		thread->run();
		return 0;
	}

};
