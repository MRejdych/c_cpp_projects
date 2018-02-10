#pragma once

#include "Arbiter.h"
#include <mutex>

/*
Algorytm dopuszcza do zasobu tylko jeden w�tek w danym czasie.
Wykorzystywany jako punkt odniesienia do oceny wydajno�ci pozosta�ych algorytm�w.
*/


class MutexArbiter : public Arbiter {
private:
    std::mutex *_mutex;
public:
    MutexArbiter() {
        _mutex = new std::mutex();
    }

    virtual void startRead() {
        _mutex->lock();
    }

    virtual void endRead() {
        _mutex->unlock();
    }

    virtual void startWrite() {
        _mutex->lock();
    }

    virtual void endWrite() {
        _mutex->unlock();
    }

    ~MutexArbiter() {
        delete _mutex;
    }
};
