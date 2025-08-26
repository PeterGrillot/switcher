#!/bin/bash

gcc switcher.c -o Switcher `pkg-config --cflags --libs gtk+-3.0`
sudo cp Switcher /usr/local/bin/
