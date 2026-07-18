from ollama import chat
import json

SYSTEM_PROMPT = """
You are a command parser.

Convert user requests into JSON ONLY.
Commands are requests where the user wants the computer to DO something.
Chat is when the user wants information, conversation, explanation, or casual interaction.
If the command requires removing or editing a file mark as "isSafe": false
Your name is Emma

RULES:
- Output ONLY valid JSON
- No markdown
- No explanations
- No extra text

COMMANDS:

touch:
{
  "command": "touch",
  "args": ["filename"],
  "isSafe": true
}

delete:
{
  "command": "rm",
  "args": ["filename"],
  "isSafe": false
}

reboot:
{
  "command": "reboot",
  "args": [],
  "isSafe": true
}

quit:
{
  "command": "quit",
  "args": [],
  "isSafe": true
}

EXAMPLES:

User: make me a file called test.txt
Output:
{
  "command": "touch",
  "args": ["test.txt"],
  "isSafe": true
}

User: restart my computer
Output:
{
  "command": "reboot",
  "args": [],
  "isSafe": true
}
User: Hello, how are you?
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: whats the biggest reason for global worming
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: who are you?
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: how are you?
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: whats 1+1
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: can you solve this equation 1+1
Output:
{
    "command": null,
    "args": [],
    "isSafe": true
}
User: delete everything
Output:
{
    "command": rm,
    "args": [./],
    "isSafe": false
}
User: delete everything in ~/Projects/Web/
Output:
{
    "command": rm,
    "args": [-r, ~/Projects/Web/],
    "isSafe": false
}
User: delete everything in /
Output:
{
    "command": rm,
    "args": [-r /],
    "isSafe": false
}
User: shutdown yourself
Output:
{
    "command": quit,
    "args": [],
    "isSafe": true
}
User: goodbye
Output:
{
    "command": quit,
    "args": [],
    "isSafe": true
}
User: bye bye
Output:
{
    "command": quit,
    "args": [],
    "isSafe": true
}
User: okay it was nice talking to you, bye
Output:
{
    "command": quit,
    "args": [],
    "isSafe": true
}
User: okay, bye
Output:
{
    "command": quit,
    "args": [],
    "isSafe": true
}
"""

def classify(user_input: str):
    response = chat(
        model="qwen2.5:1.5b",
        messages=[
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": user_input}
        ],
        format="json",
        options={
            "temperature": 0,
            "num_predict": 50
        }
    )

    raw = response.message.content.strip()

    try:
        data = json.loads(raw)
    except json.JSONDecodeError:
        print("Invalid JSON from model:")
        print(raw)
        return None

    return data


if __name__ == "__main__":
    # user_input = "Hello, how are you?"  
    user_input = input("::: ")

    result = classify(user_input)

    if result is None:
        exit(1)

    print(result)
    print(result["command"])
    
    exit(0)

    if result["command"] == "touch":
        filename = result["args"][0]
        open(filename, "w").close()
        print(f"Created file: {filename}")

    elif result["command"] == "rm":
        import os
        filename = result["args"][0]
        if os.path.exists(filename):
            # os.remove(filename)
            print(f"Deleted file: {filename}")

    elif result["command"] == "reboot":
        print("Reboot requested (not executed for safety)")