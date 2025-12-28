#include "Crypto.h"
#include "Crypto_Cfg.h"

/*===========================================================================
 *                          Crypto Key Configuration
 *===========================================================================*/



/* MyKey_0 */
const Crypto_KeyType MyKey_0_Config = {
    .KeyId = 1,
    
    .KeyType = KEY_AES_128,
    
    
    /* Key Elements */
    .ElementsCount = 2,
    .Elements = {
        
        {
            .Id = 101,
            .Size = 16
        },
        
        {
            .Id = 102,
            .Size = 32
        }
        
    }
};



/* Array of all keys */
const Crypto_KeyType* const Crypto_KeysConfig[] = {


    &MyKey_0_Config


};
