from flask import Flask, request
import sqlite3

app = Flask(__name__)

# Create a database connection
def init_db():
    conn = sqlite3.connect('sensor_data.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS SensorData (id INTEGER PRIMARY KEY, voltage REAL, current REAL, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_data():
    voltage = request.json.get('voltage')
    current = request.json.get('current')
    
    # Store the data in the database
    conn = sqlite3.connect('sensor_data.db')
    c = conn.cursor()
    c.execute("INSERT INTO SensorData (voltage, current) VALUES (?, ?)", (voltage, current))
    conn.commit()
    conn.close()
    return {'status': 'success'}, 200

if __name__ == '__main__':
    init_db()
    app.run(host='0.0.0.0', port=5000)
