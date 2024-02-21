#include "TYPES.H"
#include <osbind.h>
#include <stdio.h>

UINT32 get_time();

int main() {
  UINT32 timeThen, timeNow, timeElapsed;
  timeNow = get_time();
  timeElapsed = timeNow - timeThen;

  if (timeElapsed > 0) {

    printf("%ld\n", timeNow);
    timeThen = timeNow;
  }
  return 0;
}

UINT32 get_time() {
  long old_ssp;
  UINT32 timeNow;
  long *timer = (long *)0x462;

  old_ssp = Super(0);
  timeNow = *timer;
  Super(old_ssp);

  return timeNow;
}
