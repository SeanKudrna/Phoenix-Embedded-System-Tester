#ifndef TYPES_H
#define TYPES_H

#include <string.h>
#include <QListWidget>
#include <QtGlobal>
#include "vars.h"

#define BK_BAUD (9600)
#define LINE_FEED (0x0A)
#define CARRIAGE_RETURN (0x0D)

#ifdef Q_OS_LINUX
#define SERIAL_PORT "/dev/ttyUSB2"
#define SERIAL_MOTORSUPPLY "/dev/ttyUSB3"
#define SERIAL_CHARGER "/dev/ttyUSB4"
#else
#define SERIAL_PORT "COM26"
#endif




#if(0) //fixme
//number description low result high p/f
#define TITLE_FORMAT  ("STEP \tDESCRIPTION \t\t\t\tLOW \tRESULT \tHIGH \tP/F")
#define RESULT_FORMAT_DOUBLE ("%.01f \t%s \t\t\t\t%.02f \t%.02f \t%.02f  \t%c")
#define RESULT_FORMAT_INT ("%.01f \t%s \t\t\t\t%d \t%d \t%d  \t%c")
#define RESULT_FORMAT_STRING ("%.01f \t%s \t\t\t\t%s \t%s \t%s  \t%c")
#define MAX_DESCRIPTION (128)
#define MAX_TEST_NAME (32)
#endif




typedef struct{
    QListWidget *pListWidget;
    double testNumber;
    bool testStatus;
}TestInfo_t;

typedef struct{
   double stepNumer; //step number to be added to test number
   double min; // limits for p/f
   double max;// limits for p/f
   double target;   // test result value
   bool   testSuccess; // true for pass
   char description[MAX_DESCRIPTION];  // brief test description
}FunctionTypeA_t;

// information for and a pointer to the individual tests
typedef struct{
   FunctionTypeA_t a;
   bool (*pFunc)(TestInfo_t *pti, FunctionTypeA_t *a); // call this function to run the test, returns true for pass
}FunctionTypeB_t;



//test pointer return types
typedef enum{
    TP_CALL_AGAIN,
    TP_STEP_FAILURE,
    TP_STEP_SUCCESS,
    TP_COMPLETE_FAILURE,
    TP_COMPLETE_SUCCESS

}TestPointer_e;

// name and pointer to the testgroup
typedef struct{
    char *name;  // use this name in the menu list
    TestPointer_e (*pFunc)(QListWidget *pListWidget,double testNumber,int *testStep); // call this function on double click of menu
    void (*pTimerFunc)();
}TestPointer_t;


#endif
