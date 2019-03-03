#ifndef timer_h
#define timer_h

// configures the handler function to trigger when SIGALRM is caught
void setupTimer(void(*handler)(int));

// set new timer alarm
void setTimerAlarm(int quantum);

#endif