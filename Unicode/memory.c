/* Copyright (C) 2000-2012 by George Williams */
/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.

 * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// For some reason including inc/fontforge-config.h here
// still leaves strdup() to be non GC_strdup when -O3 is set on gcc 4.7.2
#define malloc GC_malloc
#define realloc GC_realloc
#define free GC_free
#define strdup GC_strdup
#define strndup GC_strndup
#define calloc fontforge_calloc

#include <stdio.h>
#include <string.h>
#include "ustring.h"


void NoMoreMemMessage(void) {
/* Output an 'Out of memory' message, then continue */
    fprintf(stderr, "Out of memory\n" );
}

char *copy(const char *str) {
    return str ? strdup(str) : NULL;
}

char *copyn(const char *str,long n) {
    /**
     * MIQ: Note that there is at least one site that relies on
     *      copyn copying up to n bytes including embedded nulls.
     *      So using strndup() doesn't provide the same outcomes
     *      to that code.
     *      https://github.com/fontforge/fontforge/issues/1239
     */
    char *ret;
    if ( str==NULL )
    	return( NULL );

    ret = (char *) malloc(n+1);
    memcpy(ret,str,n);
    ret[n]='\0';
    return( ret );
}
