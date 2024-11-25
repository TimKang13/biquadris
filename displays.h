#ifndef OBSERVERS_H
#define OBSERVERS_H
#include "observer.h"
#include "subject.h"
#include <iostream>

class TextDisplay: public Observer { // concrete Observer
    Subject *subject;
    public:
        TextDisplay(Subject *subject);
        void notify() override;
};

#endif
