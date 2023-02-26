FROM alpine:latest
#Build args
ARG VCS_REF
ARG BUILD_DATE
# Setting resource quota
ARG MIN_MEM=2G
ARG MAX_MEM=2G

RUN addgroup -S dockergroup && adduser -S dockeruser -G dockergroup
RUN  apk add --no-cache build-base &&  mkdir -p /usr/src/app
#Adding Labels of build
LABEL maintainer="Gautham Prakash <github.com/gauthamp10>"
LABEL org.label-schema.build-date=$BUILD_DATE
LABEL org.label-schema.vcs-url="https://github.com/gauthamp10/dockerfile-boilerplates"
LABEL org.label-schema.vcs-ref=$VCS_REF


USER dockeruser
COPY assignment.cpp /usr/src/app
WORKDIR /usr/src/app
USER root
#Compiling source
RUN g++ -o main assignment.cpp
USER dockeruser
#Execution
CMD ["./main"]