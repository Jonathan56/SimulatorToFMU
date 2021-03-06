#ifndef _SERVERINTERPRETER_H_
#define _SERVERINTERPRETER_H_
/*////////////////////////////////////////////////////////////////////////////*/
/* Function that evaluates a Server function using*/
/* embedded Server.*/
/* The Server function must take as an argument one or more doubles, integers*/
/* and strings, in this order. If there is only one argument of each data type,*/
/* then it must be a scalar. Multiple arguments of the same data type*/
/* must be put in a list.*/
/**/
/* See the User's Guide of the Modelica package for instructions.*/
/**/
/* The PYTHONPATH must point to the directory that contains the function.*/
/* On Linux, run for example*/
/* export PYTHONPATH=xyz*/
/* where xyz is the directory that contains the file that implements the*/
/* function multiply.*/
/**/
/**/
/* Thierry S. Nouidui, LBNL, 5/7/2013 */

/*////////////////////////////////////////////////////////////////////////////*/
#include <stddef.h>  /* stddef defines size_t */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "serverObjectStructure.h"
#include <curl/curl.h>
#include <sys/stat.h>

#ifdef _MSC_VER
#include <process.h>
#include <windows.h>
#endif

typedef struct cPtr
{
  void* ptr;
  char* conFilPat;
  char* cheSerPat;
  char* batFilPat;
  char* fulScriPat;
  char* address;
  char* port;
  char* locInVal;
  char* locInNam;
  char* inNam;
  char* inVal;
  char* outNam;
  int   isInitialized;
  CURL *curl_handle;
  char *strParNam;
  char *strParVal;
  char *dblParNam;
  char *dblParVal;
} cPtr;



struct MemoryStruct {
	char *memory;
	size_t size;
};

#define PATH_SEP "\\"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _MSC_VER
#ifdef EXTERNAL_FUNCTION_EXPORT
# define LBNLSERVERINTERPRETER_EXPORT __declspec( dllexport )
#else
# define LBNLSERVERINTERPRETER_EXPORT __declspec( dllimport )
#endif
#elif __GNUC__ >= 4
	/* In gnuc, all symbols are by default exported. It is still often useful,
	to not export all symbols but only the needed ones */
# define LBNLSERVERINTERPRETER_EXPORT __attribute__ ((visibility("default")))
#else
# define LBNLSERVERINTERPRETER_EXPORT
#endif

	/*
	* This function.simulators variables
	* with an external simulator.
	*
	* @param modTim the simulation time
	* @param nDblWri the number of double variables to write
	* @param strWri the string variables to write
	* @param dblValWri the double values to write
	* @param nDblRea the number of variables to read
	* @param strRea the string variables to read
	* @param dblValRea the double values to read
	* @param resWri the result flag
	* @param ModelicaFormatError the pointer
	* to the inModelicaFormatError
	* @param memory a Server object
	*/
	LBNLSERVERINTERPRETER_EXPORT void serverSimulatorVariables(
		double modTim,
		const size_t nDblWri,
		const char ** strWri,
		double * dblValWri,
		size_t nDblRea,
		const char ** strRea,
		double * dblValRea,
		int resWri,
		void(*inModelicaFormatError)(const char *string, ...),
		void* object);

	LBNLSERVERINTERPRETER_EXPORT void* initServerMemory(char* resScri, size_t nStrPar, char** strParNam, 
	char** strParVal, size_t nDblPar, char** dblParNam, double* dblParVal); 

	LBNLSERVERINTERPRETER_EXPORT void freeServerMemory(void* object);

#ifdef __cplusplus
}
#endif


#endif /* _SERVERINTERPRETER_H_ */
