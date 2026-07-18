import speech_recognition as sr
import sys
from faster_whisper import WhisperModel
import tempfile

from colorama import Fore, init

init()

# mic = sr.Microphone(device_index=12)
recognizer = sr.Recognizer()

def listMics() -> dict[int, str]:
    mics = {}
    for i, name in enumerate(sr.Microphone.list_microphone_names()):
        mics[i] = name
    return mics

def getSentence_(mic, recognizer, printSent=True) -> str:
    with mic as source:
        audio = recognizer.listen(source)
        try:
            text = recognizer.recognize_google(audio)
            if printSent:
                print(Fore.BLUE + text)
            return text
        except:
            if printSent:
                print(Fore.RED + "was not able to hear!")
            return None
    

# Install the optimized turbo model
model = WhisperModel("small.en", device="cpu", compute_type="int8", cpu_threads=4)
recognizer = sr.Recognizer()
mic = sr.Microphone()

def getSentence(mic, recognizer, printSent=True) -> str:
    with mic as source:
        print("speak!")
        audio = recognizer.listen(source)

    # Convert microphone audio → temp wav file
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
        f.write(audio.get_wav_data())
        path = f.name

    segments, _ = model.transcribe(path, language="en", no_speech_threshold=0.8)

    text = "".join([s.text for s in segments]).strip()
    if printSent:
        print(Fore.BLUE + text)
    if text == "Thanks for watching!":
        return None
    return text

if __name__ == '__main__':
    try:
        while True:
            text = getSentence(mic, recognizer)
            print(text)
    except KeyboardInterrupt:
            print("quitting...")
            sys.exit(1)