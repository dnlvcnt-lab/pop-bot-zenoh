FROM ubuntu:22.04 as pop-bot

# environment
ENV DISPLAY :0
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
VOLUME /tmp/.X11-unix
ARG DEBIAN_FRONTEND=noninteractive

# install cmake dependencies
RUN DEBIAN_FRONTEND=noninteractive apt-get update -y \
&& DEBIAN_FRONTEND=noninteractive apt-get upgrade -y \
&& DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends --no-install-suggests -y \
    sudo build-essential gcc g++ libssl-dev cmake make tar wget nano vim zip unzip \
    apt-utils x11-xserver-utils bash-completion gnupg2 syslinux-utils tmux locales openssh-server libasio-dev

# set locale
RUN apt update && sudo apt install locales && \
    locale-gen en_US en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 && \
    export LANG=en_US.UTF-8

# setup sources
RUN apt install -y software-properties-common && \
    add-apt-repository universe && \
    apt update && sudo apt install curl && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# ROS2 packages
RUN apt update && apt upgrade -y && \
    apt install -y ros-humble-desktop ros-dev-tools \
    # gazebo fortress
    ros-humble-xacro ros-humble-ros-ign-gazebo ros-humble-ros-ign-bridge

# Gazebo Fortress
RUN apt-get update && apt-get install -y lsb-release wget gnupg && \
    wget https://packages.osrfoundation.org/gazebo.gpg -O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable jammy main" | tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null && \
    apt-get update && apt-get install  -y ignition-fortress

# source setup script
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

# user popbot
ENV USERNAME popbot
ENV HOME /home/$USERNAME
RUN useradd -m $USERNAME && \
        echo "$USERNAME:$USERNAME" | chpasswd && \
        usermod --shell /bin/bash $USERNAME && \
        usermod -aG sudo $USERNAME && \
        #mkdir /etc/sudoers.d && \
        echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/$USERNAME && \
        chmod 0440 /etc/sudoers.d/$USERNAME && \
        # Replace 1000 with your user/group id
        usermod  --uid 1000 $USERNAME && \
        groupmod --gid 1000 $USERNAME
		
SHELL ["/bin/bash", "-c"]
