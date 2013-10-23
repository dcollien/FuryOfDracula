#!/bin/sh


if [ $# -eq 1 ]; then
    rm -rf ROUND$1;
    rm -rf hunter/compiled_round_ROUND$1
    rm -rf hunter/submissions/ROUND$1

    rm -rf dracula/compiled_round_ROUND$1
    rm -rf dracula/submissions/ROUND$1
    rm -rf ~/public_html/13s2.dracula/ROUND$1
fi
