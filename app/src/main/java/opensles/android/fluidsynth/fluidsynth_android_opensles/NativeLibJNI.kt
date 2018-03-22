package opensles.android.fluidsynth.fluidsynth_android_opensles

class NativeLibJNI {
    external fun init(sf2path: String)
    external fun noteOn(key: Int, velocity: Int)
    external fun noteOff(key: Int)
    external fun programChange(channel: Int, programNumber: Int) : Boolean
    external fun destroy()
}