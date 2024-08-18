#include "mcu_init.h"
#include "io.h"

/*// cppcheck-suppress unusedFunction*/
void mcu_init(void)
{

    // Initialize all pins
    io_init();
}