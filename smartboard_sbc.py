from multiprocessing.sharedctypes import Value
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

# Initialize a tracker object
tracker = LaserTracker(
    cam_width=640,
    cam_height=480,
    hue_min=20,
    hue_max=160,
    sat_min=70,
    sat_max=255,
    val_min=200,
    val_max=255,
    display_thresholds=None
)

# Run tracker in separate background thread
t = threading.Thread(target=tracker.run, name = "Laser Tracker")
t.daemon = True
t.start()

while True: # Run forever
    t = tracker.get_latest_letter() # Get the latest letter
    if t: # If the letter is valid
        s = t.lower() # Lowercase the letter received
        history += s # Add it to history
        if s != " ": # If it's not a space
            recent_word += s # Update the recent word
        else:
            recent_word = "" # Recent word is complete. Reset to blank
            sentence = history # Update sentence as the most recent word is complete
        print(history) # Printing for debugging purposes
        try:
            if recent_word == "": # If recent word is complete
                preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3) # Predict new word
            else:
                preds = happy_wp.predict_mask(sentence + "[MASK]", top_k = 3, prefix = recent_word) # Complete existing word
        except ValueError:
            preds = "" # If we can't get a prediction send empty predictions
        predictions = " ".join([pred.token for pred in preds]) # Join the top 3 predictions
        predictions = s + predictions + "\n" # Combine for sending to ARduino
        print(f"One cycle done with {s} as input") # Debugging
        arduino.write(predictions.encode()) # Send predictions to Arduino
        myobj = gTTS(text=history, lang='en', slow=False) # Create a google text to speech object
        myobj.save("text.mp3") # Save the voice to mp3
        os.system("mpg321 -q text.mp3") # Play the mp3 without creating any console output
        time.sleep(3) # Sleep to get ready for the next letter and for Arduino to process