[!SELECT "as:modconf('Crc')[1]"!][!//
[!IF "not(node:exists(CrcGeneral))"!][!ERROR "CrcGeneral container is missing in Crc configuration"!][!ENDIF!][!//
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Crc_Cfg.h
 *            Module: Crc
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#if !defined (CRC_CFG_H)
# define CRC_CFG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* This is not the sub-package version but a compatibility version, which will only be updated if a change in the 
   generator (i.e. generated files) affects the implementation sub-package */
# define CRC_CFG_MAJOR_VERSION	(3u) 
# define CRC_CFG_MINOR_VERSION	(1u) 

/***** Supported CRC Calculation modes *******************************************************************************/

/* CRC 8 */
# define CRC_8_RUNTIME           (0u)
# define CRC_8_TABLE             (1u)
# define CRC_8_HARDWARE          (2u)

/* CRC 8H2F */
# define CRC_8H2F_RUNTIME        (0u)
# define CRC_8H2F_TABLE          (1u)
# define CRC_8H2F_HARDWARE       (2u)

/* CRC 16 */
# define CRC_16_RUNTIME          (0u)
# define CRC_16_TABLE            (1u)
# define CRC_16_HARDWARE         (2u)
# define CRC_16_TABLE_4          (3u)
# define CRC_16_TABLE_8          (4u)

/* CRC 32 */
# define CRC_32_RUNTIME          (0u)
# define CRC_32_TABLE            (1u)
# define CRC_32_HARDWARE         (2u)

/* CRC 32P4 */
# define CRC_32P4_RUNTIME        (0u)
# define CRC_32P4_TABLE          (1u)
# define CRC_32P4_HARDWARE       (2u)
# define CRC_32P4_TABLE_4        (3u)
# define CRC_32P4_TABLE_8        (4u)

/* CRC 64 */
# define CRC_64_RUNTIME          (0u)
# define CRC_64_TABLE            (1u)
# define CRC_64_HARDWARE         (2u)
# define CRC_64_TABLE_4          (3u)
# define CRC_64_TABLE_8          (4u)
        
/***** CRC Calculation configuration *********************************************************************************/

# define CRC_8_MODE              ([!"node:value(CrcGeneral/Crc8Mode)"!])
# define CRC_8H2F_MODE           ([!"node:value(CrcGeneral/Crc8H2FMode)"!])
# define CRC_16_MODE             ([!"node:value(CrcGeneral/Crc16Mode)"!])
# define CRC_32_MODE             ([!"node:value(CrcGeneral/Crc32Mode)"!])
# define CRC_32P4_MODE           ([!"node:value(CrcGeneral/Crc32P4Mode)"!])
# define CRC_64_MODE             ([!"node:value(CrcGeneral/Crc64Mode)"!])


/***** Optional API function *****************************************************************************************/

# define CRC_VERSION_INFO_API    ([!IF "node:value(CrcGeneral/CrcVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])



#endif  /* CRC_CFG_H */

/**********************************************************************************************************************
  END OF FILE: Crc_Cfg.h
**********************************************************************************************************************/[!ENDSELECT!]

