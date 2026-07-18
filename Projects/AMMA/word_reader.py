import pyttsx3
import subprocess
import os
from colorama import Fore, init


engine = pyttsx3.init()

init()

voices = engine.getProperty("voices")

def Talk_(sentence: str, model_name="gmw/en-us", printSent=True) -> None:
    engine.setProperty(
        "voice",
        model_name
    )    

    engine.say(sentence)
    if printSent:
        print(Fore.GREEN + sentence.strip())
    engine.runAndWait()

def Talk(sentence, model_path="~/piper/voices/en_US-hfc_female-medium.onnx", printSent=True):
    if printSent:
        print(Fore.GREEN + sentence.strip())
    
    model_path = os.path.expanduser(model_path)
    
    if not os.path.exists(model_path):
        raise FileNotFoundError
        
    pipe1 = subprocess.Popen(
        ["echo", sentence],
        stdout=subprocess.PIPE
    )
    
    pipe2 = subprocess.Popen(
        ["piper", "-m", model_path, "-f", "-"],
        stdin=pipe1.stdout,
        stdout=subprocess.PIPE
    )
    
    pipe1.stdout.close()
    
    audio, _ = pipe2.communicate()
    
    subprocess.run(["aplay"], input=audio)
    

if __name__ == '__main__':
    Talk("Hello, what's your name?")