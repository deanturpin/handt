FROM ubuntu
RUN apt update
RUN apt install -y python3 make g++-8 git sloccount
COPY . /src
WORKDIR /src
# CMD make
