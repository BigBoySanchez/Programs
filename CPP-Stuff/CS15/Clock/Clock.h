class Clock {

private:

 int second, minute, hour;

 bool isMorning;

public:

 Clock(int h = 12, int m = 0, int s = 0, bool ismorn = true);
 Clock(char timeZone, bool isDST);


 // Accessors

 int getSecond() const;

 int getMinute() const;

 int getHour() const;

 bool getIsMorning() const;



 // Mutators

 void setSecond(int s);

 void setMinute(int m);

 void setHour(int h);

 void setIsMorning(bool ismorn);

 void tick();
 void tickAlternateVersion();

 void printTime() const;

};