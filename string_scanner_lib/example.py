import string_scanner
import re
import os

def get_running_pids():
    return [int(pid) for pid in os.listdir('/proc') if pid.isdigit()]

p_id = input("Enter PID (or empty to loop all processes): ")
regex = re.escape(input("Enter REGEX: "))
offset = int(input("Enter offset from address (40 if python [default]): "))
offset = offset if offset else 40
if p_id:
    p_id = int(p_id)
    scanner = string_scanner.StringScanner(p_id)
    # Finds a secret string
    scanner.find_match(regex, offset)
    del scanner
else:
    # Loop through all pids
    for pid in get_running_pids():
        print("Current PID:", pid)
        scanner = string_scanner.StringScanner(pid)
        # Finds a secret string
        scanner.find_match(regex, offset)
    del scanner