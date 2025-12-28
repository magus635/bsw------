/* Crypto_Lcfg.c - EB Syntax Version */
#include "Crypto.h"

[!LOOP "CryptoDriverObject"!][!//!]
/* Driver Object: [!"node:name(.)"!] */
const Crypto_DriverObjectType Crypto_DriverObject_[!"node:name(.)"!] = {
    .Keys = {
        [!LOOP "CryptoKey"!][!//!]
        {
            .KeyId = [!"node:value(CryptoKeyId)"!],
            .Elements = {
                [!LOOP "CryptoKeyElement"!][!//!]
                {
                    .ElementId = [!"node:value(CryptoKeyElementId)"!],
                    .Size = [!"node:value(CryptoKeyElementSize)"!][!IF "node:exists('CryptoKeyElementFormat')"!],
                    .Format = [!"node:value(CryptoKeyElementFormat)"!][!ENDIF!]
                }[!IF "@index < @count - 1"!],[!ENDIF!]
                [!ENDLOOP!]
            }
        }[!IF "@index < @count - 1"!],[!ENDIF!]
        [!ENDLOOP!]
    }
};
[!ENDLOOP!]
