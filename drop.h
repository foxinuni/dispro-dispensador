#ifndef _MD_DROP_H
#define _MD_DROP_H

#include <Ds1302.h>
#define SCHEDULE_MAX 5

class DropController {
private:
  int next;
  int count;
  Ds1302::DateTime schedule[SCHEDULE_MAX];
  Ds1302::DateTime drop_time;
  Ds1302& rtc;
public:
  DropController(Ds1302& rtc);
};

#endif // _MD_DROP_H