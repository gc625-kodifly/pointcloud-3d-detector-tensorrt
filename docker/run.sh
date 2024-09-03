#!/bin/bash

DOCKER_ARGS+=("-v /tmp/.X11-unix:/tmp/.X11-unix")
DOCKER_ARGS+=("-v $HOME/.Xauthority:/home/admin/.Xauthority:rw")
DOCKER_ARGS+=("-e DISPLAY")

docker run -it --rm \
    --privileged \
    --network host \
    ${DOCKER_ARGS[@]} \
    -v /dev/*:/dev/* \
    -v /home/gabriel/pointcloud-3d-detector-tensorrt:/workspace/src/pointcloud-3d-detector-tensorrt \
    --name "$CONTAINER_NAME" \
    --gpus all \
    $@ \
    docker.io/gc625kodifly/iassd-trt:x86\
    /bin/bash