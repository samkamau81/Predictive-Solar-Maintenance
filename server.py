from flask import Flask, request, jsonify

app = Flask(__name__)

# Route to handle POST request and return the data in response
@app.route('/upload', methods=['POST'])
def upload_data():
    data = request.json #{"voltage":0.00,"current":0.00,"dustDensity":10.00,"temperature":20.10,"humidity":22.00,"lightIntensity":34.00}   # Get the JSON data from the POST request
    print(data)
    voltage = data.get('voltage')
    current = data.get('current')
    dustDensity = data.get('dustDensity')
    temperature = data.get('temperature')
    humidity = data.get('humidity')
    lightIntensity = data.get('lightIntensity')

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

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=9000)

