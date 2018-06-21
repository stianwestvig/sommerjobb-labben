# Python gateway for aws connection!

## Device mock
```
curl -d '{"value":"hello"}' -X POST -H "Content-Type: application/json" 172.31.12.85
```

## Upload to server
```
scp main.py  ubuntu@ec2-54-229-221-128.eu-west-1.compute.amazonaws.com:/home/ubuntu/src
```