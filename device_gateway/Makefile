upload: remote_clean
	scp -r * ubuntu@ec2-54-229-221-128.eu-west-1.compute.amazonaws.com:/home/ubuntu/src

run:
	sudo python3 main.py

stress_test:
	while :; do curl -d '{"value":"stress"}' -X POST -H "Content-Type: application/json" 54.229.221.128; done
	
test:
	curl -d '{"value":"test"}' -X POST -H "Content-Type: application/json" 54.229.221.128

remote_clean:
	ssh ubuntu@ec2-54-229-221-128.eu-west-1.compute.amazonaws.com "sudo rm -rf src/*"