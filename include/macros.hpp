#ifndef MAC_HPP
#define MAC_HPP

#ifdef CN
#include <iostream>

/**
 * @brief Prints a message to the debug screen.
 *  \n must be used inside the message.
 */
#define CPRINT(message)       \
    {                         \
        std::cout << message; \
        std::cout.flush();    \
    }
#endif

#endif
