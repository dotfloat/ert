#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <enkf_types.h>
#include <util.h>


/*****************************************************************/


const char * enkf_types_get_impl_name(enkf_impl_type impl_type) {
  switch(impl_type) {
  case(INVALID):
    return "INVALID";
    break;
  case STATIC:
    return "STATIC";
    break;
  case FIELD:
    return "FIELD";
    break;
  case GEN_KW:
    return "GEN_KW";
    break;
  case SUMMARY:
    return "SUMMARY";
    break;
  case GEN_DATA:
    return "GEN_DATA";
    break;
  default:
    util_abort("%s: internal error - unrecognized implementation type: %d - aborting \n",__func__ , impl_type);
    return NULL;
  }
}


#define if_strcmp(s) if (strcmp(impl_type_string , #s) == 0) impl_type = s
static enkf_impl_type enkf_types_get_impl_type__(const char * impl_type_string) {
  enkf_impl_type impl_type;
  if_strcmp(STATIC);
  else if_strcmp(SUMMARY);
  else if_strcmp(FIELD);
  else if_strcmp(GEN_KW);
  else if_strcmp(GEN_DATA);
  else impl_type = INVALID;
  return impl_type;
}
#undef if_strcmp


enkf_impl_type enkf_types_get_impl_type(const char * __impl_type_string) {
  char * impl_type_string = util_alloc_string_copy(__impl_type_string);
  util_strupr(impl_type_string);  
  enkf_impl_type impl_type = enkf_types_get_impl_type__(impl_type_string);
  if (impl_type == INVALID) 
    util_abort("%s: enkf_type: %s not recognized - aborting \n",__func__ , __impl_type_string);
  
  free(impl_type_string);
  return impl_type;
}


/*
  This will return INVALIID if given an invalid
  input string - not fail.
*/
  
enkf_impl_type enkf_types_check_impl_type(const char * impl_type_string) {
  return enkf_types_get_impl_type__(impl_type_string);
}


/*****************************************************************/
/* 
   These two functions update the truncation variable to ensure that
   it applies truncate_min and truncate_max respectively. The somewhat
   involved implementation is to ensure that the functions can be
   called many times.
*/


void enkf_types_set_truncate_min(truncation_type * __trunc) {
  truncation_type trunc = *__trunc;

  if (!(trunc & TRUNCATE_MIN))
    trunc += TRUNCATE_MIN;

  *__trunc = trunc;
}


void enkf_types_set_truncate_max(truncation_type * __trunc) {
  truncation_type trunc = *__trunc;

  if (!(trunc & TRUNCATE_MAX))
    trunc += TRUNCATE_MAX;

  *__trunc = trunc;
}






