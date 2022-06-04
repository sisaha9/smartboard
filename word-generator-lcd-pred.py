from serial import Serial
import time
from happytransformer import HappyWordPrediction
import warnings
warnings.filterwarnings("ignore")

arduino = Serial(port="/dev/ttyACM0", baudrate=9600, timeout=1) # Communication with Arduino
happy_wp = HappyWordPrediction() # NN for Word Prediction
arduino.write('ready'.encode()) # Send handshake
time.sleep(1) # Wait for Arduino to process this
print("Ready to receive input") # Ready to start receiving input
history = "" # Variable that stores all characters received so far
recent_word = "" # Variable that stores only the most recent word. Blank if recent word is complete
sentence = "" # Variable that is the same as history except it does not have the recent word

while True: # Run forever
    s = arduino.readline().decode() # Get input from Arduino
    if s != "": # If input is not empty
        s = s[:-2].lower() # Strip the \r\n and lowercase the character
        history += s # Add it to history
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
        print(f"One cycle done with {s} as input") # Debugging
        arduino.write(predictions.encode()) # Send predictions to Arduino
