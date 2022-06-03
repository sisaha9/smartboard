from serial import Serial
from laser_tracker.laser_tracker.laser_tracker import LaserTracker
from happytransformer import HappyWordPrediction
from gtts import gTTS
import os

import time
import threading
import warnings
warnings.filterwarnings("ignore")

arduino = Serial(port="/dev/ttyACM0", baudrate=9600, timeout=1) # Communication with Arduino
happy_wp = HappyWordPrediction() # NN for Word Prediction

time.sleep(3) # Sleeping to give Arduino time to get ready
print("Ready to track") # Ready to start receiving input
history = "" # Variable that stores all characters received so far
recent_word = "" # Variable that stores only the most recent word. Blank if recent word is complete
sentence = "" # Variable that is the same as history except it does not have the recent word

hardcoded_sentence = "bring me an apple please"
i = 0

tracker = LaserTracker(
    cam_width=640,
    cam_height=480,
    hue_min=20,
    hue_max=160,
    sat_min=100,
    sat_max=255,
    val_min=200,
    val_max=255,
    display_thresholds=None
)

t = threading.Thread(target=tracker.run, name = "Laser Tracker")
t.daemon = True
t.start()
while True: # Run forever
    t = tracker.latest_letter
    if i == len(hardcoded_sentence):
        continue
    t = hardcoded_sentence[i]
    i += 1
    if t:
        s = t.lower()
        history += s # Add it to history
        myobj = gTTS(text=history, lang='en', slow=False)
        myobj.save("text.mp3")
        os.system("mpg321 text.mp3")
        if s != " ": # If it's not a space
            recent_word += s # Update the recent word
        else:
            recent_word = "" # Recent word is complete. Reset to blank
            sentence = history # Update sentence as the most recent word is complete
        print(history) # Printing for debugging purposes
        if recent_word == "": # If recent word is complete
            preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3) # Predict new word
        else:
            preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3, prefix = recent_word) # Complete existing word
        predictions = " ".join([pred.token for pred in preds]) # Join the top 3 predictions
        predictions = s + predictions
        print(f"One cycle done with {s} as input") # Debugging
        print(predictions[1:])
        arduino.write(predictions.encode()) # Send predictions to Arduino