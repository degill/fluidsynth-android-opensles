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
    // Init settings
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "opensles");
    fluid_settings_setint(settings, "audio.opensles.use-callback-mode", 1);
    fluid_settings_setint(settings, "audio.period-size", 64);

    synth = new_fluid_synth(settings);

    // Init soundfont
    const char *nativeSf2Path = env->GetStringUTFChars(sf2path, NULL);
    fluid_synth_sfload(synth, nativeSf2Path, true);
    env->ReleaseStringUTFChars(sf2path, nativeSf2Path);

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
JNIEXPORT jboolean JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_programChange(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint programNumber) {
    return (jboolean) (FLUID_OK == fluid_synth_program_change(synth, (int) channel, (int) programNumber));
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_destroy(
        JNIEnv *env,
        jobject /* this */) {
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}
