from ollama import chat

def chat(massage, used_role="user", used_model='phi', streamed=True):
    stream = chat(
        model=used_model,
        messages=[
            {'role': used_role, 'content': massage}
        ],
        stream=streamed
    )

    for chunk in stream:
        print(chunk.message.content, end='', flush=True)