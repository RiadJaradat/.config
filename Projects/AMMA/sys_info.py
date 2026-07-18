import platform
import psutil
from datetime import datetime

def get_system_info():
    return {
        "time": datetime.now().strftime("%I:%M:%S %p"),
        "os": {
            "system": platform.system(),
            "release": platform.release(),
            "version": platform.version(),
            "machine": platform.machine()
        }
    }