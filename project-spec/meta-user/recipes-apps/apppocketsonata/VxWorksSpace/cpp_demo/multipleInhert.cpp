/* multipleInhert.cpp - implements multiple inheritance demo */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

class Radio
{
public:
    Radio() :
        freq(88.3),
        freqStep(0.2),
        volume(2)
        {}
    void    setFreq(float f)
        {
            freq = f;
        }
    float   getFreq() const
        {
            return freq;
        }
    void    setFreqStep(float f)
        {
            freqStep = f;
        }
    float   getFreqStep() const
        {
            return freqStep;
        }
    void    setVolume(int v)
        {
            volume = v;
        }
    int     getVolume() const
        {
            return volume;
        }

private:
    float   freq;
    float   freqStep;
    int     volume;
};

class Clock
{
public:
    typedef unsigned long time_type;

    Clock()
        {
            clockTime = time_type(&clockTime);
        }
    void setTime(time_type t)
        {
            clockTime = t;
        }
    time_type getTime() const
        {
            return clockTime;
        }
    virtual void tick()
        {
            clockTime++;
        }

private:
    time_type clockTime;
};

/* This class derives from both the Clock class and Radio classes to
 * make a ClockRadio class.
 */
class ClockRadio : public Clock, public Radio
{
public:
    void    setAlarm(time_type t)
        {
            alarm = t;
        }
    time_type getAlarm() const
        {
            return alarm;
        }
    /* This will override the tick member function from the Clock class.
     */
    void    tick()
        {
            time_type t = getTime();
            setTime(t+1);
            chkAlarm();
        }
    bool chkAlarm() const
        {
            if (getTime() == alarm)
                return true;
            else
                return false;
        }

private:
    time_type alarm;
};

/* Now the demo.
 */
void multipleInheritanceDemo()
{
    ClockRadio  cr;

    /* Setting the Freq will call into the Radio class.
     */
    cr.setFreq(94.5);
    
    /* The time will be read from the Clock class.
     */
    ClockRadio::time_type t = cr.getTime();
    
    /* The alarm will be set in the ClockRadio class.
     */
    cr.setAlarm(t+2);

    /* The ClockRadio class overrides the tick function to
     * also check for an alarm.
     */
    cr.tick();
    cr.tick();
    cr.tick();
    cr.tick();
} /* multipleInheritanceDemo */
