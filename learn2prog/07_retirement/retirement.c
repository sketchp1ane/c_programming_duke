#include <stdio.h>
#include <stdlib.h>


struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
  
};
typedef struct _retire_info retire_info;

struct _age_month {
    int age;
    int month;
};
typedef struct _age_month age_month;

age_month format(int month) {
  age_month am;
  am.age = month / 12;
  am.month = month - am.age * 12;
  return am;
}

void retirement (int startAge,   //in months
                       double initial, //initial savings in dollars
                       retire_info working, //info about working
		 retire_info retired) { //info about being retired
  printf("Age %3d month %2d you have $%.2lf\n", format(startAge).age, format(startAge).month, initial);
  for (int i = 0; i < working.months; i++) {
    startAge++;
    initial += initial * (working.rate_of_return / 12);
    initial += working.contribution;
    printf("Age %3d month %2d you have $%.2lf\n", format(startAge).age, format(startAge).month, initial);
  }
  for (int i = 0; i < retired.months - 1; i++) {
    startAge++;
    initial += initial * (retired.rate_of_return / 12);
    initial += retired.contribution;
    printf("Age %3d month %2d you have $%.2lf\n", format(startAge).age, format(startAge).month, initial);
  }
    
    
  
}



  

int main(void) {
  retire_info test_working;
  test_working.months = 489;
  test_working.contribution = 1000;
  test_working.rate_of_return = 0.045;
  
  retire_info test_retired;
  test_retired.months = 384;
  test_retired.contribution = -4000;
  test_retired.rate_of_return = 0.01;
  
  retirement(327, 21345, test_working, test_retired);
  
  return 0;
  

  
 
}




