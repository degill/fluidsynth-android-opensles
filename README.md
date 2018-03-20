# fluidsynth-android-opensles
This is a sample project which strives to use fluidsynth as a native android library with OpenSL ES support


The original fluidsynth repository can be found here: [FluidSynth/fluidsynth](https://github.com/FluidSynth/fluidsynth)

Adjustments, or better yet additions, to build fluidsynth for the Android platform where made by VolcanoMobile in this repository: [VolcanoMobile/fluidsynth-android](https://github.com/VolcanoMobile/fluidsynth-android)

I set up a fresh Android project via AndroidStudio, simply copied over all relevant files from [VolcanoMobile/fluidsynth-android](https://github.com/VolcanoMobile/fluidsynth-android) and referenced the `android/CMakeLists.txt` within the app's `build.gradle`. That works in the sense that it compiles and fluidsynth can be used within the app (i.e. JNI). But in order to be able to build fluidsynth for Android VolcanoMobile exluded all Audio-Driver classes, thus removing the ability to actually hear any MIDI events.

To enable audio with fluidsynth on Android with the OpenSL ES audio framework [atsushieno](https://github.com/atsushieno) made independent changes to fluidsynth in his own fluidsynth [fork](https://github.com/atsushieno/fluidsynth). I was not able to build that project. But, since I was able to build VolcanoMobiles version of fluidsynth I thought it might be possible to only include atsushienos changes into VolcanoMobiles version. This project tries to do exactly that.

**NOTE**:
I know that this project currently scrambles fluidsynth library code with sample app code. I wanted to extract the fluidsynth part into it's own gradle-module library inside this project and have another module (i.e. the android sample app) with it's own native code use that library. But I couldn't get it to work. The native code inside the sample app then couldn't find the headers provided by the fluidsynth library. Any ideas are welcome.


## Progress:
* [X] Include VolcanoMobiles version of [fluidsynth](https://github.com/VolcanoMobile/fluidsynth-android)
* [X] Include atsushienos additions to fluidsynth to enable OpenSL ES support. His changes can be found in this [patch](https://gist.github.com/atsushieno/539e4e14d4eafcad724e446ad73dc1ad)
* [X] Be able to build the project again. Update: It now builds with changes taken from [here](https://github.com/atsushieno/fluidsynth/issues/8#issuecomment-371875875) and [here](https://gist.github.com/atsushieno/950eb50626e0009d5e919588a0ca9ef9).
* [ ] Extract the fluidsynth part into its own gradle-module and have a sample app reference it
* [ ] Fix `W/libOpenSLES: Leaving BufferQueue::Enqueue (SL_RESULT_BUFFER_INSUFFICIENT)`. After a while the output stumbles and logcat is filled with this log statement.

## Acknowledgements
- [FluidSynth](https://github.com/FluidSynth/) for open sourcing [fluidsynth](https://github.com/FluidSynth/fluidsynth)
- [VolcanoMobile](https://github.com/VolcanoMobile/) for getting fluidsynth to build on android in this [fork: fluidsynth-android](https://github.com/VolcanoMobile/fluidsynth-android)
- [atsushieno](https://github.com/atsushieno) for implementing an audio driver in fluidsynth using OpenSL ES on android in his own fork of fluidsynth. All of the used changes by him can be found in this [issue](https://github.com/atsushieno/fluidsynth/issues/8)
