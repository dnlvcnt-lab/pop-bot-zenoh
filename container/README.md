# POP-BOT Ubuntu 22.04 ROS 2 Container

## Prerequisites

* docker-compose

## Steps

* Build the docker image
```bash
cd ~/pop-bot-zenoh/container
docker-compose build
```

* Run the docker image
```bash
cd ~/pop-bot-zenoh/container
docker-compose -p  <container_name> up
```
 
