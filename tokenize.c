/**
* @file   tokenize.c
* @author Dan Noland <nolandda@nolandda.org>
* @date   Wed Mar  7 17:10:49 2018
* 
* @brief  Implementation of the tokenizing tools
* 
* 
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>
#include "tokenize.h"

// Predefined whitespece set
const char* ASCII_WHITESPACE_CHARS = " \t\r\n\v\f";

// Forward decl of helper function
static void do_token_trim( tokset_t* set );


/** 
 * Tokenizes a string based on separators and records the result in a
 * token set
 * 
 * @param set The output token set
 * @param str The string to be tokenized
 * @param sep An array of characters to tokenize on
 * @param trim Boolean value determining if zero length tokens (i.e. empty string "") be removed
 * 
 * @return The number of tokens created. 
 */
size_t create_tokens( tokset_t* set, const char* str, 
		      const char* sep, uint8_t trim ) {
  size_t i=0, j=0;
  size_t len = 0;
  size_t tokcount = 0;
  char* tstr = NULL;
  char** tokens = NULL;
  char* prev = NULL;

  if( str && sep ) {
    tokcount = 1;
    tstr = strdup(str);
    // Make a first pass marking seperators with '\0' and counting tokens.
    while(tstr[i]) {
      j = 0;
      while(sep[j]) {
	if(tstr[i] == sep[j]) {
	  // found a seperator
	  tokcount += 1;
	  tstr[i] = '\0';
	}
	j += 1;
      }
      i += 1;
    }
    // we accidentially compute strlen along the way. Minor
    // optimization here to avoid a call. 
    len = i;

    // Allocate the tokens
    tokens = calloc(tokcount, sizeof(char*));

    // Second pass to assign token pointers
    prev = tstr;
    j = 0;
    for(i=0; i<len; i+=1) {
      if( tstr[i] == '\0' ) {
	tokens[j] = prev;
	prev = tstr+i+1;
	j += 1;
      }
    }
    // one more left over after the loop (we never see the final '\0')
    tokens[j] = prev;
  }
  set->victimstr = tstr;
  set->numtok = tokcount;
  set->tokens = tokens;
  set->curidx = 0;  
  // Trim out null tokens if the user requested
  if( trim ) {
    do_token_trim( set );
  }

  return set->numtok;
}

/** 
 * Helper function for the common case where the user wishes to
 * tokenize on the ASCII whitespace characters. 
 * 
 * @param set The output token set
 * @param str The string to be tokenized
 * 
 * @return The number of tokens created
 */
size_t create_ws_delimited_tokens( tokset_t* set, const char* str ) {
  return create_tokens( set, str, ASCII_WHITESPACE_CHARS, 1 );

}

/** 
 * Get a token by its index
 * 
 * @param set The tokenset containing tokens
 * @param idx The index of the token requested
 * 
 * @return A constant pointer to the token. The tokenset retains
 * ownership of this memory. If idx is beyond then number of tokens
 * NULL is returned. 
 */
const char* get_token( tokset_t* set, size_t idx ) {
  size_t tidx = idx;
  if(idx < set->numtok) {
    set->curidx = idx;
    return set->tokens[tidx];
  }
  else {
    return NULL;
  }
}

/** 
 * Get the next token from the tokenset
 * 
 * @param set The tokenset containing tokens
 * 
 * @return A constant pointer to the token. The tokenset retains
 * ownership of this memory. If the set is already past the final
 * token NULL is returned. 
 */
const char* get_next_token( tokset_t* set ) {
  size_t tidx = set->curidx;
  if(set->curidx < set->numtok) {
    set->curidx += 1;
    return set->tokens[tidx];
  }
  else {
    return NULL;
  }
}

/** 
 * Accessor for the tokenset length.
 * 
 * @param set The token set
 * 
 * @return The number of tokens in the set
 */
size_t get_num_tokens( const tokset_t* set ) {
  return set->numtok;
}

/** 
 * Reset the internal counter used by get_next_token(...)
 * 
 * @param set The token set
 */
void reset_token_counter( tokset_t* set ) {
  set->curidx = 0;
  return;
}

/** 
 * Free all memory internal to the token set, but not the set iteslf.
 * 
 * @param set The token set to be destroyed
 */
void free_tokens( tokset_t* set ) {
  if( set ) {
    free(set->tokens); set->tokens = NULL;
    free(set->victimstr); set->victimstr = NULL;
    set->numtok = 0;
    set->curidx = 0;
  }
  return;
}

/** 
 * Print the internal state of the token set including all tokens
 * 
 * @param set The token set to be printed
 */
void print_tokens( const tokset_t* set ) { // TODO: creates stdio dep. Keep?
  size_t i = 0;
  int tok_ok = 0;
  int vs_ok = 0;
  char* cur = NULL;
  printf(":::::::::::::::::::::::::::::::::\n");
  if( set ) {
    printf("::    Context at %p\n", set);
    printf("::      Num Tokens %zu\n", set->numtok);
    if( set->tokens ) {
      tok_ok = 1;
      printf("::      Tokens ptr at %p\n", set->tokens);
    }
    else {
      printf("::      Tokens are NULL\n");
    }
    if( set->victimstr ) {
      vs_ok = 1;
      printf("::      Victim string at %p\n", set->victimstr);
    }
    else {
      printf("::      Victim string is NULL\n");
    }
    if( tok_ok && vs_ok ) {
      for(i=0; i<set->numtok; i+=1) {
	cur = set->tokens[i];
	printf("::        Token[%zu] = %p = [%s]\n", i, cur, cur);
      }
      cur = set->tokens[set->curidx];
      printf("::      Current Token is %zu = %p = [%s]\n", 
	     set->curidx, cur, cur);

    }
  }
  else { 
    printf("::    Context is NULL\n");
  }
  printf(":::::::::::::::::::::::::::::::::\n");
  return;
}


static void do_token_trim( tokset_t* set ) {
  size_t i=0, j=0;
  size_t count = 0;
  char** newtoks = NULL;
  for(i=0; i<set->numtok; i+=1) {
    if(set->tokens[i][0] != '\0') {
      // Found an non-empty token
      count+=1;
    }
  }
  
  // reallocate and assign non-empty tokens
  newtoks = calloc(count, sizeof(char*));
  for(i=0; i<set->numtok; i+=1) {
    if(set->tokens[i][0] != '\0') {
      newtoks[j] = set->tokens[i];
      j += 1;
    }
  }

  free(set->tokens);
  set->tokens = newtoks;
  set->numtok = count;
  return;
}
