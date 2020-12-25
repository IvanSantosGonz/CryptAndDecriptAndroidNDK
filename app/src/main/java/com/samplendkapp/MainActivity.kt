package com.samplendkapp

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.samplendkapp.databinding.ActivityMainBinding
import java.util.*

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)

        binding.buttonEncrypt.setOnClickListener {
            run {
                val plainText = binding.encryptDecryptText.text.toString()
                val encryptedBytes = encryptFromJNI(plainText) // Example of a call to a native method
                binding.textEncryptedDecrypted.text = Base64.getEncoder().encodeToString(encryptedBytes)
                binding.textEncryptedDecrypted.visibility = View.VISIBLE
            }
        }

        binding.buttonDecrypt.setOnClickListener {
            run {
                val cipherText = binding.encryptDecryptText.text.toString()
                binding.textEncryptedDecrypted.text = decryptFromJNI(Base64.getDecoder().decode(cipherText)) // Example of a call to a native method
                binding.textEncryptedDecrypted.visibility = View.VISIBLE
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