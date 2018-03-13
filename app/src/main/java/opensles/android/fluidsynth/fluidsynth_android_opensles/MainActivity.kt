package opensles.android.fluidsynth.fluidsynth_android_opensles

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.MotionEvent
import android.view.View
import kotlinx.android.synthetic.main.activity_main.*
import okio.Okio
import java.io.File

class MainActivity : AppCompatActivity(), View.OnTouchListener {

    companion object {

        private const val SF2_FILE_NAME = "PNS Drum Kit.SF2"

        private const val KEY = 60
        private const val VELOCITY = 127

        // Used to load the 'fluidsynth' library on application startup.
        // Check the CMakeLists.txt that is referenced in app/build.gradle,
        // within it there is the statement 'add_library' which specifies
        // this identifier.
        init {
            System.loadLibrary("fluidsynth")
        }
    }

    private val nativeLibJNI = NativeLibJNI()

    private lateinit var sf2file: File

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        sf2file = File(filesDir, SF2_FILE_NAME)
        copySF2IfNecessary() // sf2 file needs to be in internal directory, not assets
        nativeLibJNI.init(sf2file.absolutePath)
        sample_text.setOnTouchListener(this)
        sample_text.isEnabled = true
    }

    private fun copySF2IfNecessary() {
        if (sf2file.exists() && sf2file.length() > 0) return
        Okio.source(assets.open(SF2_FILE_NAME)).use { a ->
            Okio.buffer(Okio.sink(sf2file)).use { b ->
                b.writeAll(a)
            }
        }
    }

    private fun noteOn() {
        nativeLibJNI.noteOn(KEY, VELOCITY)
    }

    private fun noteOff() {
        nativeLibJNI.noteOff(KEY)
    }

    override fun onTouch(v: View?, event: MotionEvent?): Boolean {
        val action = event?.action
        when (action) {
            MotionEvent.ACTION_DOWN -> noteOn()
            MotionEvent.ACTION_UP -> noteOff()
        }
        return false
    }

    override fun onDestroy() {
        nativeLibJNI.destroy()
        super.onDestroy()
    }
}
