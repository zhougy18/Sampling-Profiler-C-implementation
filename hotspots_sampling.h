#include <sys/time.h>
#define MAX_FUNC_NUM 100
#define MAX_NAME_LENGTH 128

struct functionSampled{
    char name[MAX_NAME_LENGTH];
    int  count;
};

void start_analysis(int freq);
void init_timer(struct itimerval *timer, int freq);
void sigHandler();
void recordFunction(char* name);
void end_analysis();
int cmpfunc(const void * a, const void * b);

