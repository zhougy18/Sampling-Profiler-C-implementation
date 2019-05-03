#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <libunwind.h>
#include "hotspots_sampling.h"

struct functionSampled record[MAX_FUNC_NUM];

struct timeval time_start, time_end;

int sampleFrequency;

int functionNumbers=0;

//for qsort
int cmpfunc(const void * a, const void * b){
   return (((struct functionSampled*)b)->count - ((struct functionSampled*)a)->count);
}

void end_analysis(){
  int i;
  int total=0;
  double time;

  //stop the timer
  struct itimerval timer;
  memset(&timer, 0, sizeof(timer));
  setitimer (ITIMER_REAL, &timer, NULL);

  gettimeofday(&time_end, NULL);
  time = 1000.0*(time_end.tv_sec-time_start.tv_sec) + (time_end.tv_usec-time_start.tv_usec)/1000.0;

  printf("sample frequency: %d Hz\n", sampleFrequency);
  printf("running time：%.2lf ms\n", time);
    
  qsort(record,functionNumbers,sizeof(struct functionSampled),cmpfunc);

  for (i=0;i<functionNumbers;i++)
    total += record[i].count;
  printf("rtime(%%)\t rtime(ms)\t name\n");

  for (i=0;i<functionNumbers;i++)
    printf("  %.2f  \t  %.2f  \t %s  \n", 1.0*record[i].count/total, time*record[i].count/total, record[i].name);
}

void recordFunction(char* name){
  int i=0;
  for(i=0;i<functionNumbers;i++){
    if(strcmp(name, record[i].name) == 0){
      record[i].count++;
      break;
    }
  }
  if(i==functionNumbers){
    strcpy(record[functionNumbers].name, name);
    record[functionNumbers].count = 1;
    functionNumbers++;
  }
}

void sigHandler(){
  unw_cursor_t  cp;
  unw_context_t ucp;
  unw_word_t offset;
  char functionName[MAX_NAME_LENGTH];
  //get current machine-state
  unw_getcontext(&ucp);
  //initialize cursor for local unwinding
  unw_init_local(&cp, &ucp);

  //advance the unwind cursor cp to the "killpg" stack frame
  unw_step(&cp);
  //advance the unwind cursor cp to the tested function stack frame
  if (unw_step(&cp) > 0){
    //get the function name of the stack frame pointed by cp
    unw_get_proc_name(&cp, functionName, sizeof(functionName), &offset);
    recordFunction(functionName);
  }
}

void init_timer(struct itimerval *timer, int freq){
  int us = 1000000/freq;
  //Timers decrement from it_value to zero, generate a signal, and reset to it_interval.
  (timer->it_value).tv_sec = 0;
  (timer->it_value).tv_usec = us;
  (timer->it_interval).tv_sec = 0;
  (timer->it_interval).tv_usec = us;
}

void start_analysis(int freq){
  struct sigaction act;
  struct itimerval timer;
  sampleFrequency = freq;
  init_timer(&timer,freq);
  memset(&act, 0, sizeof(act));
  act.sa_handler = &sigHandler;
  sigaction(SIGALRM, &act, NULL);
  gettimeofday(&time_start, NULL);
  setitimer (ITIMER_REAL, &timer, NULL);
}




