FROM ubuntu:latest

USER root

RUN apt update && apt install -y \
    clang-15 clang-format-15 clang-tidy-15 clang-tools-15 clang-15-doc \
    build-essential cmake git vim shellcheck shfmt sudo
RUN ln -sf /usr/bin/clang-15 /usr/local/bin/clang
RUN ln -sf /usr/bin/clang++-15 /usr/local/bin/clang++
RUN ln -sf /usr/bin/clang-format-15 /usr/local/bin/clang-format
RUN ln -sf /usr/bin/clang-tidy-15 /usr/local/bin/clang-tidy
RUN ln -sf /usr/bin/clangd-15 /usr/local/bin/clangd

ARG USERNAME=local
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

RUN usermod -s /bin/bash $USERNAME

ENV CC=clang
ENV CXX=clang++