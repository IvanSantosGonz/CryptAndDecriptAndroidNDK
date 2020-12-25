package com.samplendkapp

import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.util.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var encryptedText = findViewById<TextView>(R.id.text_encrypted_decrypted)

        // Example of a call to a native method
        var encryptButton = findViewById<Button>(R.id.button_encrypt)
        encryptButton.setOnClickListener {
            run {
                val plainText = findViewById<EditText>(R.id.encrypt_decrypt_text).text.toString()
                val encryptedBytes = encryptFromJNI(plainText)
                encryptedText.text = Base64.getEncoder().encodeToString(encryptedBytes)
                encryptedText.visibility = View.VISIBLE
            }
        }

        var decryptedText = findViewById<TextView>(R.id.text_encrypted_decrypted)

        var decryptButton = findViewById<Button>(R.id.button_decrypt)
        decryptButton.setOnClickListener {
            run {
                val cipherText = findViewById<EditText>(R.id.encrypt_decrypt_text).text.toString()

                decryptedText.text = decryptFromJNI(Base64.getDecoder().decode(cipherText))
                decryptedText.visibility = View.VISIBLE
            }
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private external fun encryptFromJNI(message: String): ByteArray
    private external fun decryptFromJNI(message: ByteArray): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}