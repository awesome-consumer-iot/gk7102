/*!
*****************************************************************************
** \file        ./adi/test/src/osd_text.h
**
** \brief       adi test osd module header file.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2013-2014 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/

#ifndef _OSD_TEXT_H_
#define _OSD_TEXT_H_

#include "stdio.h"
#include "osd_common.h"

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
int osd_text_lib_init(FONT_LIBRARY_TYPE flib_type);
int osd_text_lib_exit(void);
int osd_text_set_font_attribute(const font_attribute_t *font_attr);
int osd_text_get_font_attribute(font_attribute_t *font_attr);
int osd_text_convert_character(const char * char_code,
              LATTICE_INFO *lattice_info, void *hook_data);


#ifdef __cplusplus
    }
#endif


#endif /* _OSD_TEXT_H_ */