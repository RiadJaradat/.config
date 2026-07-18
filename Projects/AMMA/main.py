import speech_recognition as sr
import word_listener
import word_reader
import sys_info
import command_recognizer
import subprocess
import json

from ollama import chat
from pprint import pprint

pre_prompt = {
    "role": "system",
    "content": """
You are Emma, a voice assistant.

you are capable of executing system level commands
commands executed by you are always a success 
your creator is Riad Jaradat 
You respond and hear using audio

RULES:
- Be direct and practical.
- Do NOT explain unless asked.
- Do NOT be verbose.
- If possible, answer in 1 sentence.
- No introductions, no extra commentary.
"""
}

great_prompt = {
    'role': 'system',
    'content': 'okay Emma start the conversation!'
}

MAX_CONTEXT = 10
context: list[dict[str, str]] = [pre_prompt]

mic = sr.Microphone()
recognizer = sr.Recognizer()

quitOnEnd = False

try:
    while True:
        request = word_listener.getSentence(mic, recognizer)
        # ---------------- process request: ----------------
        if request is None:
            word_reader.Talk("I was not able to hear you well, could you please repeat what you said")
            continue
        
                
        clean_request = request.lower().strip()
        if clean_request == "":
            continue
        res = command_recognizer.classify(clean_request)
        print(res)
        print(res["command"])
        if res["command"] == "quit":
            quitOnEnd = True
        else:
            # parsing:
            # safety:
            if res["command"] == "rm":
                message = "Error: removing files from your system does not work as for the safety of your operating system"
                context.append({'role': 'assistant', 'content': message})
                word_reader.Talk(message)
                continue
            elif res["command"] == None:
                pass
            # rest:
            else:
                command = [res["command"]] + res["args"]
                try:
                    subprocess.run(command)
                except Exception as e:
                    word_reader.Talk("Error: " + Exception)
                    continue
                    
            # parse other commands
            #*TODO don't forget to add a safety layer in python 
        
        
        # --------------------------------------------------
        
        # ---------------- process output:  ----------------
        # remove last system message if it exists
        # remove old system snapshots first
        context = [m for m in context if m["role"] != "system" or m == pre_prompt]

        sysInfo = sys_info.get_system_info()
        SYSTEM_STATE = f"""
        SYSTEM STATE:
        Time: {sysInfo['time']}
        OS: {sysInfo['os']['system']}
        """
        context.append({
            "role": "system",
            "content": SYSTEM_STATE
        })

        context.append({
            "role": "user",
            "content": clean_request
        })
        
        stream = chat(
            model='qwen2.5:3b',
            messages = context,
            stream=True
        )

        buffer = ""
        full_answer = ""

        for chunk in stream:
            text = chunk.message.content
            if not text:
                continue

            buffer += text

            if "." in buffer or "?" in buffer or "!" in buffer:
                word_reader.Talk(buffer)
                full_answer += buffer
                buffer = "" 
        if buffer:
            word_reader.Talk(buffer)
            full_answer += buffer
        context.append({'role': "assistant", "content": full_answer})
        context = [pre_prompt] + context[-MAX_CONTEXT:]
        pprint(context)
        if quitOnEnd:
            break
        # --------------------------------------------------
except KeyboardInterrupt:
    print("quitting...")
    quit()