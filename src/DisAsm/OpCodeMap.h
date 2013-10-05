/*
* Filename: OpCodeMap.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: maps of x86 opcodes :
*              opcode <-> info
*              (mnemonic, etc)
*
*/

#include "OpCodeMapElement.h"
#include "OpCodeMapOneByte.h"
#include "OpCodeMapTwoByte0F.h"
#include "OpCodeMapTwoByte0FPrefix66.h"
#include "OpCodeMapTwoByte0FPrefixF2.h"
#include "OpCodeMapTwoByte0FPrefixF3.h"
#include "OpCodeMapThreeByte0F38.h"
#include "OpCodeMapThreeByte0F38Prefix66.h"
#include "OpCodeMapThreeByte0F38PrefixF2.h"
#include "OpCodeMapThreeByte0F38PrefixF3.h"
#include "OpCodeMapThreeByte0F3A.h"
#include "OpCodeMapThreeByte0F3APrefix66.h"
#include "OpCodeMapThreeByte0F3APrefixF2.h"
#include "OpCodeMapThreeByte0F3APrefixF3.h"
#include "OpCodeMapX87.h"
