//////////////////////////////////////
//Animation.h
//CS300 Group E
//This file contains the header info
//that main.cpp uses to display an
//animated welcome message for Frupal.
//////////////////////////////////////
#pragma once
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

int const in = 310000; //Time displaying welcome
int const out = 10; //Time blinking welcome
int const holdTime = 750000; //Hold time displaying
int const holdTimeOut = 350000; //Hold time blinking
int const HEADER = 2; //Room above FRUPAL

void blink(string x, int in, int out);
void welcomeAnimation();

const char frupal[] = " ________ ________  ___  ___  ________  ________  ___ \n|\\  _____\\\\   __  \\|\\  \\|\\  \\|\\   __  \\|\\   __  \\|\\ \
 \\\n\\ \\  \\__/\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\n \\ \\   __\\\\ \\   _  _\\ \\  \\\\\\  \\ \\   ____\\ \\  \
 __  \\ \\  \\\n  \\ \\  \\_| \\ \\  \\\\  \\\\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\____\n   \\ \\__\\   \\ \\__\\\\ _\\\\ \\_______\
\\ \\__\\    \\ \\__\\ \\__\\ \\_______\\\n    \\|__|    \\|__|\\|__|\\|_______|\\|__|     \\|__|\\|__|\\|_______|";

const char w[] = " #    # \n #    # \n #    # \n # ## # \n ##  ## \n #    #";
const char we[] = " #    # ###### \n #    # #      \n #    # #####  \n # ## # #      \n ##  ## #      \n #    # ###### ";
const char wel[] = " #    # ###### #      \n #    # #      #      \n #    # #####  #      \n # ## # #      #      \n ##  ## #      #      \n #  \
  # ###### ###### ";
const char welc[] = " #    # ###### #       ####  \n #    # #      #      #    # \n #    # #####  #      #      \n # ## # #      #      #      \\
n ##  ## #      #      #    # \n #    # ###### ######  ####  ";
const char welco[] = " #    # ###### #       ####   ####  \n #    # #      #      #    # #    # \n #    # #####  #      #      #    # \n # ## # \
#      #      #      #    # \n ##  ## #      #      #    # #    # \n #    # ###### ######  ####   ####  ";
const char welcom[] = " #    # ###### #       ####   ####  #    # \n #    # #      #      #    # #    # ##  ## \n #    # #####  #      #      # \
   # # ## # \n # ## # #      #      #      #    # #    # \n ##  ## #      #      #    # #    # #    # \n #    # ###### ######  ####   ####  #   \
 # ";
const char welcome[] = " #    # ###### #       ####   ####  #    # ###### \n #    # #      #      #    # #    # ##  ## #      \n #    # #####  #\
      #      #    # # ## # #####  \n # ## # #      #      #      #    # #    # #      \n ##  ## #      #      #    # #    # #    # #      \n #  \
  # ###### ######  ####   ####  #    # ###### ";

const char welcome_t[] = " #    # ###### #       ####   ####  #    # ######    ##### \n #    # #      #      #    # #    # ##  ## #           # \
  \n #    # #####  #      #      #    # # ## # #####       #   \n # ## # #      #      #      #    # #    # #           #   \n ##  ## #      #  \
    #    # #    # #    # #           #   \n #    # ###### ######  ####   ####  #    # ######      #   ";
const char welcome_to[] = " #    # ###### #       ####   ####  #    # ######    #####  ####  \n #    # #      #      #    # #    # ##  ## #     \
      #   #    # \n #    # #####  #      #      #    # # ## # #####       #   #    # \n # ## # #      #      #      #    # #    # #           # \
  #    # \n ##  ## #      #      #    # #    # #    # #           #   #    # \n #    # ###### ######  ####   ####  #    # ######      #    #### \
 \n";

 //Blinks a string x, while keeping it onscreen
 //for 'in' microseconds, off screen for
 //'off' microseconds
 void blink(string x, int in, int out)
 {
     for (int i = 0; i < HEADER; ++i) cout << "\n";
     cout << x << flush;
     usleep(in);
     system("clear");
     usleep(out);
 }

//Displays WELCOME TO FRUPAL
//But does so with an animation
 void welcomeAnimation()
 {
   cout << flush;
   system("clear");
   blink(w, in, out);
   blink(we, in, out);
   blink(wel, in, out);
   blink(welc, in, out);
   blink(welco, in, out);
   blink(welcom, in, out);
   blink(welcome, in, out);
   blink(welcome_t, in, out);
   blink(welcome_to, holdTime, holdTimeOut);
   blink(frupal, holdTime * 2, out);
 }
