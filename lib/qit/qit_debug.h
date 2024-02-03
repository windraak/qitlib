
// simple debugger switch
#ifdef DEBUG_QIT
#define qit_debug(what) Serial.println(what)
#else
#define qit_debug(what) /* what */
#endif
