COMP2659_Project
Game for the Atari ST
Title: Mallard ShootOut
Authors: Jaunie W. & Edward M.

After running make, two test executables should be made:

Running "game" will render bitmaps and allow the user to track
x & y values of the reticle and the mallards as well as count down
the in-game clock.

Running "tst_rend" shows the frame by frame rendering in action.

Stage 8 is _challenged_ the PSG.C file has all running functions to help in implementing EFFECTS.C and MUSIC.
> That being said, the MUSIC.C file is not implemented just yet, this will be corrected soon.

Running "tst_rast" will allow the user to flip through pre-programmed

Running "mixer" will ride the scale of notes, holding each note for ~2.5 seconds and clock ticks are printed onto the screen.


Fixes from Stages 2-4:
- Submitted code compiles without errors
- There is no game specific data in raster module and plotting on x works smoothly
- Tst_rast is complete
- each routine's implementation is clear and concise
- model and events module have been appropriately seperated
- Tst_rend functions