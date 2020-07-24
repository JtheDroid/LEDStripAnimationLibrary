#pragma once
struct Color {
    unsigned int r{0}, g{0}, b{0}, w{0};
};

class Animation {
private:
    unsigned int ledNum;
    unsigned long counter = 0;
    bool showOnRun = true;
public:
    explicit Animation(unsigned int ledNum) : ledNum(ledNum) {}

    unsigned int getLedNum() const {
        return ledNum;
    }

    unsigned int getCounter() const {
        return counter;
    }

    void setShowOnRun(bool showOnRun_) {
        showOnRun = showOnRun_;
    }

    virtual void run();

    void runTimed(unsigned long interval, unsigned long &lastRun);

    virtual void show() = 0;

protected:
    //Set led at position p to color
    virtual void setLed(unsigned int p, Color color) = 0;

    //Set all leds to color using setLed
    void setAllLeds(Color color);

    //Set pixel colors using setLed
    virtual void animationStep() = 0;
};

void Animation::run() {
    animationStep();
    if (showOnRun) show();
    ++counter;
}

void Animation::runTimed(unsigned long interval, unsigned long &lastRun) {
    unsigned long now = millis();
    bool showTemp = showOnRun, shown = false;
    showOnRun = false;
    while (now > lastRun && now - lastRun >= interval) {
        Animation::run();
        shown = true;
        if (counter == 1) lastRun = now;
        else lastRun += interval;
        if (interval == 0) break;
    }
    showOnRun = showTemp;
    if (showOnRun && shown) show();
}

void Animation::setAllLeds(Color color) {
    for (unsigned int p = 0; p < ledNum; ++p) setLed(p, color);
}
