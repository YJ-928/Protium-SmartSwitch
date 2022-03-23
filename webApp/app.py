# import libraries
from flask import Flask, render_template, request, jsonify, json
from flask.helpers import url_for
from flask_mqtt import Mqtt
import requests

mqtt = Mqtt()
app = Flask(__name__)
# MQTT configuration
app.config['MQTT_BROKER_URL'] = 'broker.hivemq.com'  # use the free broker from HIVEMQ
app.config['MQTT_BROKER_PORT'] = 1883  # default port for non-tls connection
app.config['MQTT_USERNAME'] = ''  # set the username here if you need authentication for the broker
app.config['MQTT_PASSWORD'] = ''  # set the password here if the broker demands authentication
# set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_KEEPALIVE'] = 5
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes

mqtt.init_app(app)

# global variables
jsn_server = {
    "led1": "OFF",
    "led2": "OFF",
    "led3": "OFF",
    "fan": "OFF"
}

# webhook url
webhook_url = "http://188.166.206.43/s0hUDieHK5E9HpX0iXHOfhSDgaDF5YVc/update/"


@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('protium/led1/switchStatus')


@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    global jsn_server
    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
    )
    if data['topic'] == "protium/led1/changeStatus":
        jsn_server['led1'] = data['payload']
    elif data['topic'] == "protium/led2/changeStatus":
        jsn_server['led2'] = data['payload']
    elif data['topic'] == "protium/led3/changeStatus":
        jsn_server['led3'] = data['payload']
    elif data['topic'] == "protium/fan/changeStatus":
        jsn_server['fan'] = data['payload']

    print(data)


@app.route('/protium')
def protium():
    global jsn_server
    # As the website is accessed, feed the initial status of LEDS
    send_initial_message = True
    mqtt.publish("protium/webConnect", "Connected.")
    """while(send_initial_message):
        if jsn_server['led1'] != "waiting":
            send_initial_message = False"""

    return render_template('index.html')


@app.route('/control', methods=['GET', 'POST'])
def control():
    global jsn_server

    if request.method == 'POST':
        jsn_website = request.get_json()
        if jsn_website['led1'] != jsn_server['led1']:
            mqtt.publish("protium/led1/switchStatus", "toggle")
            jsn_server['led1'] = jsn_website['led1']
            w_url = webhook_url + "D14"
            r = requests.put(w_url, data=json.dumps(['1']), headers={
                             'Content-Type': 'application/json'})
            print("----- sending led1 msg -----")

        if jsn_website['led2'] != jsn_server['led2']:
            mqtt.publish("protium/led2/switchStatus", "toggle")
            jsn_server['led2'] = jsn_website['led2']
            w_url = webhook_url + "D14"
            r = requests.put(w_url, data=json.dumps(['1']), headers={
                             'Content-Type': 'application/json'})
            print("----- sending led2 msg -----")

        if jsn_website['led3'] != jsn_server['led3']:
            mqtt.publish("protium/led3/switchStatus", "toggle")
            jsn_server['led3'] = jsn_website['led3']
            w_url = webhook_url + "D14"
            r = requests.put(w_url, data=json.dumps(['1']), headers={
                             'Content-Type': 'application/json'})
            print("----- sending led3 msg -----")

        if jsn_website['fan'] != jsn_server['fan']:
            mqtt.publish("protium/fan/switchStatus", "toggle")
            jsn_server['fan'] = jsn_website['fan']
            w_url = webhook_url + "D14"
            r = requests.put(w_url, data=json.dumps(['1']), headers={
                             'Content-Type': 'application/json'})
            print("----- sending fan msg -----")

        # print(jsn_website)
        return 'OK', 200


if __name__ == "__main__":
    app.run(debug=True)
