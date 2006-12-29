/* -------------------------------------------------------------------------
Package initialization
Copyright (c) 2006 Oleg Sklyar
See: ../LICENSE for license, LGPL
------------------------------------------------------------------------- */

#include "common.h"
#include <R_ext/Rdynload.h>

/*----------------------------------------------------------------------- */
static R_CallMethodDef libraryRCalls[] = {
    {"lib_",               (DL_FUNC) &lib_,               1},
    {"lib_readImages",     (DL_FUNC) &lib_readImages,     2},
    {"lib_chooseImages",   (DL_FUNC) &lib_chooseImages,   0},
    {"lib_writeImages",    (DL_FUNC) &lib_writeImages,    3},
    {"lib_display",        (DL_FUNC) &lib_display,        2},
    {"lib_channel",        (DL_FUNC) &lib_channel,        2},
    {"lib_filterMagick",   (DL_FUNC) &lib_filterMagick,   3},
    {"lib_erode_dilate",   (DL_FUNC) &lib_erode_dilate,   4},
    {"lib_filterThresh",   (DL_FUNC) &lib_filterThresh,   2},
    {"lib_filterFill",     (DL_FUNC) &lib_filterFill,     5},
    {"lib_distMap",        (DL_FUNC) &lib_distMap,        4},
    {"lib_filterInvWS",    (DL_FUNC) &lib_filterInvWS,    6},
    
    /* add above all R-lib functions from common.h */
    {NULL, NULL, 0}
};

/*----------------------------------------------------------------------- */
void
/*
#ifdef HAVE_VISIBILITY_ATTRIBUTE
    __attribute__ ((visibility ("default")))
#endif
*/
R_init_EBImage (DllInfo * winDll) {
    R_registerRoutines (winDll, NULL, libraryRCalls, NULL, NULL);
    R_useDynamicSymbols (winDll, FALSE);
    /* this initialization is not required on Linux */  
    /* in fact I am not sure this is required on Windows! */
#   ifdef WIN32
    InitializeMagick ("");
    if ( !IsMagickInstantiated () )
        error ( _("cannot initialize ImageMagick") );
#   endif
}

void
/*
#ifdef HAVE_VISIBILITY_ATTRIBUTE
    __attribute__ ((visibility ("default")))
#endif
*/
R_unload_EBImage (DllInfo * winDll) {
    /* this destroy is not required on Linux */  
    /* in fact I am not sure this is required on Windows! */
#   ifdef WIN32
    if ( IsMagickInstantiated() )
        DestroyMagick();
#   endif
}

