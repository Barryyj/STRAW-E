import time
import requests
import keyboard
import threading

ESP32_IP = "172.20.10.2"  # Replace with your ESP32's actual IP, you can see the ip in eps32 print log


def send_action(action):
    url = f"http://{ESP32_IP}/set_action"
    headers = {"Content-Type": "application/json"}
    data = {"action": action}

    try:
        response = requests.post(url, json=data, headers=headers)
        if response.status_code == 200:
            print(f"Action {action} executed successfully.")
        else:
            print("Error:", response.status_code, response.text)
    except requests.exceptions.RequestException as e:
        print("Request failed:", e)


def control_servos():
    print("Use arrow keys to send actions. Press 'q' to quit.")

    while True:
        if keyboard.is_pressed('up'):
            print("Executing Action 1")
            send_action(1)
            time.sleep(1.5)
        elif keyboard.is_pressed('down'):
            print("Executing Action 2")
            send_action(2)
            time.sleep(1.5)
        elif keyboard.is_pressed('space'):
            print("Executing Action 3")
            send_action(3)
            time.sleep(0.5)
        elif keyboard.is_pressed('q'):
            print("Exiting...")
            break
        time.sleep(0.1)

if __name__ == "__main__":
    control_servos()
