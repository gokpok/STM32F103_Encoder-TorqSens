
#ifndef __mbsFuncGetRegs_H
#define __mbsFuncGetRegs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "ModbusSlave.h"
	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03)
FuncRes mbs_FuncGetRegs(void);

#ifdef __cplusplus
}
#endif
#endif
