from flask import Flask
from flask import request
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
from empty_config import host, client_id, topic, root_ca_path, private_key_path, certificate_path

# configure flask
app = Flask(__name__)

@app.route("/", methods=["POST"])
def redirect_device_to_aws():
    data = request.get_json()
    myAWSIoTMQTTClient.publish(topic, str(data), 1)
    return "", 200

# initialize aws mqtt client
myAWSIoTMQTTClient = AWSIoTMQTTClient(client_id)
myAWSIoTMQTTClient.configureEndpoint(host, 8883)
myAWSIoTMQTTClient.configureCredentials(root_ca_path, private_key_path, certificate_path)
myAWSIoTMQTTClient.configureAutoReconnectBackoffTime(1, 32, 20)
myAWSIoTMQTTClient.configureOfflinePublishQueueing(-1)  # Infinite offline Publish queueing
myAWSIoTMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
myAWSIoTMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
myAWSIoTMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec

# connect to aws
myAWSIoTMQTTClient.connect()

# start server
app.run(host='0.0.0.0', port="80")