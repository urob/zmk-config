// The default layout has 36 keys. Additional keys can be added by pre-setting any of
// the macros defined in this file to one or more keys before sourcing this file.

/* left of left half */
#if !defined X_LT  // top row, left
    #define X_LT
#endif
#if !defined X_LM  // middle row, left
    #define X_LM
#endif
#if !defined X_LB  // bottom row, left
    #define X_LB
#endif

/* right of right half */
#if !defined X_RT  // top row, right
    #define X_RT
#endif
#if !defined X_RM  // middle row, right
    #define X_RM
#endif
#if !defined X_RB  // bottom row, right
    #define X_RB
#endif

