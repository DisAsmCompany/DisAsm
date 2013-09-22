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
#undef _ENUM_ELEMENT_VALUE_SKIP
#undef _ENUM_STOP
#define _ENUM_START(name) char * name##ToString(name value) { switch(value) {
#define _ENUM_ELEMENT(name) case name : return #name;
#define _ENUM_ELEMENT_VALUE(name, value) case name : return #name;
#define _ENUM_ELEMENT_VALUE_SKIP(name, value)
#define _ENUM_STOP(name) } return ""; }
#else /* _STR_ENUM */
#define _ENUM_START(name) typedef enum name##_t {
#define _ENUM_ELEMENT(name) name,
#define _ENUM_ELEMENT_VALUE(name, value) name = (value),
#define _ENUM_ELEMENT_VALUE_SKIP(name, value) name = (value),
#define _ENUM_STOP(name) } name;
#endif /* _STR_ENUM */
