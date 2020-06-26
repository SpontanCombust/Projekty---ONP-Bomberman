#include "./rpn/rpn.hpp"
#include "./gui_ncurses/rpn_app.hpp"

#include <iostream>

int main()
{
    // RunRPNDemo();
    runRPNPerfTests( 20, 80, true, "MoreOperators" );
    
    return 0;
}

