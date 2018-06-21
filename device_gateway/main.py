from flask import Flask
from flask import request
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient


host = "a3rfy4atx9yqca.iot.eu-west-1.amazonaws.com"
rootCAPath = "secrets/root-ca.crt"
certificatePath = "secrets/a2212088dc-certificate.pem.crt"
privateKeyPath = "secrets/a2212088dc-private.key"
clientId = "arn:aws:iot:eu-west-1:677687728514:thing/test"
topic = "Topic/1"

app = Flask(__name__)

@app.route("/", methods=["POST"])
def hello():
    data = request.get_json()
    myAWSIoTMQTTClient.publish(topic, str(data), 1)
    return "", 200

myAWSIoTMQTTClient = AWSIoTMQTTClient(clientId)
myAWSIoTMQTTClient.configureEndpoint(host, 8883)
myAWSIoTMQTTClient.configureCredentials(rootCAPath, privateKeyPath, certificatePath)

myAWSIoTMQTTClient.configureAutoReconnectBackoffTime(1, 32, 20)
myAWSIoTMQTTClient.configureOfflinePublishQueueing(-1)  # Infinite offline Publish queueing
myAWSIoTMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
myAWSIoTMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
myAWSIoTMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec

myAWSIoTMQTTClient.connect()

app.run(host='0.0.0.0', port="80")