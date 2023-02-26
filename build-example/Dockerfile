FROM alpine:latest
#Build args
ARG VCS_REF
ARG BUILD_DATE
# Setting resource quota
ARG MIN_MEM=2G
ARG MAX_MEM=2G

RUN addgroup -S dockergroup && adduser -S dockeruser -G dockergroup
RUN  apk add --no-cache build-base &&  mkdir /src


USER dockeruser
COPY assignment.cpp /usr/src/app
WORKDIR /usr/src/app
USER root
#Compiling source
RUN g++ -o main assignment.cpp
USER dockeruser
#Execution
CMD ["./main"]