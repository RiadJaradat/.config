import word_listener
import json
import os
import time  # Import time for the cooldown delay

# ... Keep your SYSTEM_PROMPT and classify() function exactly as they are ...

print("Emma is running in the background...")

while True:
    # 1. Capture the audio text
    text = word_listener.getSentence(word_listener.mic, word_listener.recognizer)
    
    # Clean up the text to handle formatting
    if not text or text.strip() == "":
        continue
        
    clean_text = text.lower().strip()
    
    # 2. HARD FILTER: Only proceed if you explicitly say her wake words
    if "emma" not in clean_text and "system" not in clean_text:
        # It heard background noise, slang, or chatter without her name. Skip it!
        continue

    print(f"Heard wake word in: '{text}'")
    print("Emma active!")
    
    # 4. Play the notification sound
    os.system("paplay /usr/share/sounds/freedesktop/stereo/complete.oga")
    
    # 5. CRITICAL COOLDOWN: Give the system 1.5 seconds to finish 
    # playing the audio and flush the hardware buffers.
    time.sleep(1.5)