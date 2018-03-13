#include <jni.h>
#include <fluidsynth.h>

fluid_settings_t *settings;
fluid_synth_t *synth;
fluid_audio_driver_t *adriver;

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_init(
        JNIEnv *env,
        jobject /* this */,
        jstring sf2path) {
    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);

    // Init soundfont
    const char *nativeSf2Path = env->GetStringUTFChars(sf2path, NULL);
    fluid_synth_sfload(synth, nativeSf2Path, true);
    env->ReleaseStringUTFChars(sf2path, nativeSf2Path);

    fluid_settings_setstr(settings, "audio.driver", "opensles");
    adriver = new_fluid_audio_driver(settings, synth);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_noteOn(
        JNIEnv *env,
        jobject /* this */,
        jint key,
        jint velocity) {
    fluid_synth_noteon(synth, 0, key, velocity);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_noteOff(
        JNIEnv *env,
        jobject /* this */,
        jint key) {
    fluid_synth_noteoff(synth, 0, key);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_destroy(
        JNIEnv *env,
        jobject /* this */) {
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}
