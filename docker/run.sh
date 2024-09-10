#!/bin/bash
SCRIPT_DIR=$(dirname "$(readlink -f "$0")") # current dir .../iassd_trt_ws/src/pointcloud-3d-detector-tensorrt/docker
WORKSPACE_DIR=$SCRIPT_DIR 
# Traverse up the directory tree until .catkin_workspace is found
while [ "$WORKSPACE_DIR" != "/" ]; do
    echo checking ${WORKSPACE_DIR}
    if [ -e "$WORKSPACE_DIR/.catkin_workspace" ]; then
        break  # Found the .catkin_workspace file
    fi
    WORKSPACE_DIR=$(dirname "$WORKSPACE_DIR")  # Move one directory up
done

# If not found, error out
if [ ! -e "$WORKSPACE_DIR/.catkin_workspace" ]; then
    echo "Error: .catkin_workspace file not found in any parent directories."
    exit 1
fi
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
    docker.io/gc625kodifly/iassd-trt:x86