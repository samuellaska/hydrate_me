//
//  CommonC.h
//  EmpaLink
//
//  Created by Maurizio Garbarino on 8/8/13.
//  Copyright (c) 2013 Empatica. All rights reserved.
//

#ifndef EmpaLink_CommonC_h
#define EmpaLink_CommonC_h
#include "stdio.h"


#define true 1
#define false 0

#if !defined(MAX)
#define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

#ifdef DEBUG
#define DEBUG_PRINTFING true
#endif

#if (DEBUG_PRINTFING)
    #define PRINTF printf
#else
    #define PRINTF(...)
#endif

#if (DEBUG_PRINTFING)
#warning DEBUG_PRINTFING
#endif

#define FREE(x) if(x!=NULL) free(x); (x)=NULL;

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO 0
#endif


#define NEW_KALMAN_VERSION
//#define DEBUG_KALMAN


/*#ifdef DEBUG_PRINTFING
#define PRINTF(a) printf a
#else
#define PRINTF(a) (void)0
#endif*/

//int CONFIG_A=1;

#endif
