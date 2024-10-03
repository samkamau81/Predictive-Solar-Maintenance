from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# Configure the SQLite database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///sensor_data.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# Initialize the database
db = SQLAlchemy(app)

# Define the SensorData model to represent the table in the database
class SensorData(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    voltage = db.Column(db.Float, nullable=False)
    current = db.Column(db.Float, nullable=False)
    dustDensity = db.Column(db.Float, nullable=False)
    temperature = db.Column(db.Float, nullable=False)
    humidity = db.Column(db.Float, nullable=False)
    lightIntensity = db.Column(db.Float, nullable=False)

    def __init__(self, voltage, current, dustDensity, temperature, humidity, lightIntensity):
        self.voltage = voltage
        self.current = current
        self.dustDensity = dustDensity
        self.temperature = temperature
        self.humidity = humidity
        self.lightIntensity = lightIntensity

# Route to handle POST request and save data to the database
@app.route('/upload', methods=['POST'])
def upload_data():
    data = request.json
    print(data)
    
    voltage = data.get('voltage')
    current = data.get('current')
    temperature = data.get('temperature')
    humidity = data.get('humidity')
    lightIntensity = data.get('lightIntensity')

    # Create a new record in the SensorData table
    new_data = SensorData(voltage, current, dustDensity, temperature, humidity, lightIntensity)
    
    # Add the new record to the session and commit (save) to the database
    db.session.add(new_data)
    db.session.commit()

    # Return the received data back as a response
    response_data = {
        'voltage': voltage,
        'current': current,
        'dustDensity': dustDensity,
        'temperature': temperature,
        'humidity': humidity,
        'lightIntensity': lightIntensity
    }
    
    return jsonify(response_data), 200  # Return the data as a JSON response

# Ensure the database and tables are created before running the app
if __name__ == '__main__':
    # Create tables if they don't exist
    with app.app_context():
        db.create_all()
    app.run(debug=True, host='0.0.0.0', port=9000)
