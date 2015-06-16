# HOW TO CREATE IMAGES

### Open a terminal emulator


Invoke `gnome-terminal`, `xterm`, or any other emulator in whatever terminal you were using.

This will open an 80x24 window.

Then, invoke `bin/main` whenever you see fit.

Alternatively, if the terminal is to be linked to the game, type `<terminal emulator> -e "bin/main"`.
This should work on most.

### Capture a screenshot

Requires `gnome-screenshot`

1. Type `gnome-screenshot -d 10 -w -B &`.
This sends a gnome-screenshot with focus on the calling window, borderless, and with a delay of 10 seconds to the background.

2. Save where needed and push to github.
All images belong in their tutorial's respective `.img` directory.
Links should already exist in the readme.
Please use png format.

# HOW TO CAPTURE VIDEO

Requires `avconv` and `SimpleScreenRecorder`.

1. Start SimpleScreenRecorder.

2. In the second window, select the `Record a fixed rectangle` option.  Use the `Select widnow...` button, then click the terminal you want.

3. Set a save location, and save the video to be a MP4 file in H.264 codec, with constant rate factor 0 and preset 'fast'.  Allow frame skipping.

4. Capture the video with some brief and representative actions.

5. Invoke `mkdir frames` and `avconv -i <filename>.mp4 -r 10 frames/out%03d.png`.  This will dump the video's frames into the `frames` directory.  Animation can be arranged using the numeric ordering of these frame files.

6. Invoke `convert -delay 10 -loop 0 frames/* <filename>.gif`.  This constructs a gif out of the frames.  The animation delay can be set to any number, and looping set to on/off.
