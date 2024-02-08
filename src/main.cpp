
#define DEBUG_QIT

#include "qit_debug.h"

#include <AutomaticStated.h>

class MyProgram : public State {
public:
  void init() { qit_debug("Works."); }
};

CreateStatemachine(MyProgram, 8);
