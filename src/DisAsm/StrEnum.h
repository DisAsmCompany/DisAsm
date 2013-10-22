/*
* Filename: StrEnum.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: tricky header to make
*              enum with string constant
*              definitions
*
*/

#ifdef _STR_ENUM
#undef _ENUM_START
#undef _ENUM_ELEMENT
#undef _ENUM_ELEMENT_VALUE
#undef _ENUM_STOP
#define _ENUM_START(name, base) char name##Table[][16] = {
#define _ENUM_ELEMENT(name) #name,
#define _ENUM_ELEMENT_VALUE(name, value) #name,
#define _ENUM_STOP(name, base) }; char * name##ToString(name value) { return name##Table[value - base]; }
#else /* _STR_ENUM */
#define _ENUM_START(name, base) typedef enum name##_t {
#define _ENUM_ELEMENT(name) name,
#define _ENUM_ELEMENT_VALUE(name, value) name = (value),
#define _ENUM_STOP(name, base) name##dummy} name;
#endif /* _STR_ENUM */
