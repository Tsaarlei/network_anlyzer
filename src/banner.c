#include "banner.h"

#include <stddef.h>
#include <stdio.h>

void print_banner(void) {
    static const char *art[] = {
        " _   _ _____ _______        _____  ____  _  __",
        "| \\ | | ____|_   _\\ \\      / / _ \\|  _ \\| |/ /",
        "|  \\| |  _|   | |  \\ \\ /\\ / / | | | |_) | ' / ",
        "| |\\  | |___  | |   \\ V  V /| |_| |  _ <| . \\ ",
        "|_| \\_|_____| |_|    \\_/\\_/  \\___/|_| \\_\\_|\\_\\",
        "    A N A L Y Z E R",
        "",
        " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        " 1. DNS Filter",
        " 2. MAC-Address Filter",
        " 0. Stop / Exit",
        "",
    };

    for (size_t i = 0; i < sizeof(art) / sizeof(art[0]); i++)
        puts(art[i]);
}



