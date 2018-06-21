upload:
	scp -r * ubuntu@ec2-54-229-221-128.eu-west-1.compute.amazonaws.com:/home/ubuntu/src

run:
	sudo python3 main.py

test:
	curl -d '{"value":"hello"}' -X POST -H "Content-Type: application/json" 54.229.221.128