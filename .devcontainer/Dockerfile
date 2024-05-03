FROM mcr.microsoft.com/devcontainers/cpp:1.0.9-ubuntu22.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.29.2"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
 RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends npm pipx ninja-build libpng-dev libgl-dev libgl1-mesa-dev libxcb-util-dev \
     libfontenc1 libice6 libsm6 libuuid1 libxaw7 libxcb-composite0 libxcb-cursor0 libxcb-ewmh2 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 \
libxcb-render-util0 libxcb-render0 libxcb-res0 libxcb-shape0 libxcb-shm0-dev libxcb-xinerama0 libxcb-xkb1 libxcomposite1 libxcursor1 libxdamage1 \
libxi6 libxinerama1 libxkbfile1 libxmu-headers libxmu6 libxmuu1 libxpm4 libxrandr2 libxrender1 libxres1 libxss1 libxt6 libxtst6 libxv1 x11-common \
libice-doc libsm-doc libxaw-doc libxext-doc libxt-doc uuid-runtime libfontenc-dev libfontenc1 libice-dev libice6 libsm-dev libsm6 libx11-xcb-dev \
libxaw7 libxaw7-dev libxcb-composite0 libxcb-composite0-dev libxcb-cursor-dev libxcb-cursor0 libxcb-dri2-0-dev libxcb-dri3-dev libxcb-ewmh-dev libxcb-ewmh2 \
libxcb-glx0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-image0 libxcb-image0-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-present-dev libxcb-randr0-dev libxcb-render-util0 \
libxcb-render-util0-dev libxcb-render0 libxcb-render0-dev libxcb-res0 libxcb-res0-dev libxcb-shape0 libxcb-shape0-dev libxcb-shm0-dev \
libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0 libxcb-xinerama0-dev libxcb-xkb-dev libxcb-xkb1 libxcomposite-dev libxcomposite1 libxcursor-dev \
libxcursor1 libxdamage-dev libxdamage1 libxext-dev libxfixes-dev libxi-dev libxi6 libxinerama-dev libxinerama1 libxkbfile-dev libxkbfile1 \
libxmu-dev libxmu-headers libxmu6 libxmuu-dev libxmuu1 libxpm-dev libxpm4 libxrandr-dev libxrandr2 libxrender-dev libxrender1 libxres-dev libxres1 \
libxss-dev libxss1 libxt-dev libxt6 libxtst-dev libxtst6 libxv-dev libxv1 libxxf86vm-dev uuid-dev x11-common

RUN pipx ensurepath   
RUN pipx install conan   
RUN npm install http-server -g   

RUN cd /opt && git clone https://github.com/emscripten-core/emsdk.git && cd emsdk && ./emsdk install latest && ./emsdk activate latest && echo 'source "/opt/emsdk/emsdk_env.sh"' >> $HOME/.bashrc

WORKDIR /opt/app

