from serial import Serial
import time
from happytransformer import HappyWordPrediction
import warnings
warnings.filterwarnings("ignore")

arduino = Serial(port="/dev/ttyACM0", baudrate=9600, timeout=1)
happy_wp = HappyWordPrediction()
time.sleep(3)
arduino.write('ready'.encode())
time.sleep(3)
print("Ready to receive input")
history = ""
recent_word = ""
sentence = ""

while True:
    s = arduino.readline().decode()
    if s != "":
        s = s[:-2].lower()
        history += s
        if s != " ":
            recent_word += s
        else:
            recent_word = ""
            sentence = history
        print(history)
        print(recent_word)
        print(sentence)
        if recent_word == "":
            preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3)
        else:
            preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3, prefix = recent_word)
        predictions = " ".join([pred.token for pred in preds])
        print(f"One cycle done with {s} as input")
        arduino.write(predictions.encode())
        time.sleep(3)
        predictions_from_arduino = arduino.readline().decode()
        if predictions_from_arduino:
            print(predictions_from_arduino[:-2])