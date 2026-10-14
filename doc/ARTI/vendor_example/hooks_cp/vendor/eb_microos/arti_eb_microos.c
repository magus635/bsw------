
/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti_eb_microos.c
 *  Description:  Additional ARTI source file for Elektrobit MicroOS.
 *********************************************************************************************************************/

#include <Mk_kconfig.h>

/* only for debugging purposes
mk_objecttype_t  arti_typ;
int              arti_id;
const char*      arti_name;
mk_threadstate_t arti_old;
mk_threadstate_t arti_new;
*/

volatile unsigned int t32_runningtask[MK_MAXCORES];
