#!/bin/bash
SCRIPT_DIR=$(dirname "$(readlink -f "$0")") # current dir .../iassd_trt_ws/src/pointcloud-3d-detector-tensorrt/docker
WORKSPACE_DIR=$(readlink -f "$SCRIPT_DIR/../../..") # workspace dir .../iassd_trt_ws/

# echo ${PROJECT_DIR}

DOCKER_ARGS+=("-v /tmp/.X11-unix:/tmp/.X11-unix")
DOCKER_ARGS+=("-v $HOME/.Xauthority:/home/admin/.Xauthority:rw")
DOCKER_ARGS+=("-e DISPLAY")

docker run -it --rm \
    --privileged \
    --network host \
    ${DOCKER_ARGS[@]} \
    -v /dev/*:/dev/* \
    -v ${WORKSPACE_DIR}:/home/admin/workspace \
    --name "$CONTAINER_NAME" \
    --gpus all \
    $@ \
    docker.io/gc625kodifly/iassd-trt:x86\
    /bin/bash