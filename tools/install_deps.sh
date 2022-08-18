#!/bin/bash
#
# Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
# Copyright (C) 2022 Xu Shaohua <shaohua@biofan.org>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Install package dependencies for development environment.

sudo apt install -y \
    btrfs-progs \
    cmake \
    dosfstools \
    e2fsprogs \
    g++ \
    gettext \
    jfsutils \
    libattr1-dev \
    libparted-dev \
    libqt5x11extras5-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxss-dev \
    libxtst-dev \
    mtools \
    ninja-build \
    ntfs-3g \
    os-prober \
    parted \
    pkg-config \
    qt5-qmake \
    qtbase5-dev \
    qttools5-dev \
    qttools5-dev-tools \
    reiserfsprogs \
    squashfs-tools \
    tshark \
    udev \
    util-linux \
    x11-xserver-utils \
    xfsprogs \
    xkb-data \
    zlib1g-dev
