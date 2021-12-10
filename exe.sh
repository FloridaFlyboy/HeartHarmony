#!/bin/bash
sudo spotifyd

printf "What song calms you down? (Type song name and artist)\n"
read songchoice

printf "\nThanks. We will run the program when you become anxious (Heart rate over 100 bpm)\n\n"

sudo python3 serialread.py

printf "Anxiousness detected. Starting Heart Harmony.\n\n"

sudo python3 app.py -a "$songchoice"

sudo spt play --device "heartharmony" --random --name "heartharmony" --playlist
sudo spt playback --shuffle