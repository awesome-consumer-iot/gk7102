/*!
*****************************************************************************
** \file        ./adidemo/src/app.h
**
**
** \brief       adi test app module header file.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2013-2014 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/

#ifndef _APP_H_
#define _APP_H_

#include "shell.h"
#include "isp.h"

#include "http_export.h"
#include "media_process.h"
#include "gbk_T_utf8.h"
#include "cjson.h"

#include "media_fifo.h"
#include "gk_rtsp.h"

//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************




//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

int web_register_testcase(void);
int web_open(void);
int web_close(void);

#ifdef __cplusplus
    }
#endif


#endif /* _APP_H_ */
