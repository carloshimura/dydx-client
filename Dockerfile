FROM ubuntu:latest as builder
LABEL authors="carlos"

ENV DEBIAN_FRONTEND=noninteractive
RUN echo "deb http://cz.archive.ubuntu.com/ubuntu mantic main" | tee /etc/apt/sources.list.d/temporary-repository.list
RUN apt update && apt install gcc-13 python3 python3-pip cmake -y
RUN pip3 install conan===2.0.17
RUN mkdir /app
RUN conan profile detect

RUN mkdir /app/build
RUN mkdir /app/source
COPY ./conanfile.txt /app/conanfile.txt
COPY ./dependencies /app/dependencies
COPY ./conan_release_pr /root/.conan2/profiles/conan_release_pr
WORKDIR /app/dependencies/toolbox
RUN conan create . --build=missing -pr=conan_release_pr
WORKDIR /app/dependencies/bip3x
RUN conan create . --build=missing -pr=conan_release_pr
COPY . /app/source
WORKDIR /app/build
RUN conan install /app/conanfile.txt --build=missing -pr=conan_release_pr -of /app/build
RUN cmake -S /app/source -B /app/build -DCMAKE_BUILD_TYPE=Release
RUN make -j $(nproc --all)


FROM ubuntu:latest as runner
RUN mkdir /app
COPY --from=builder /app/build/dydx-client /app
ENTRYPOINT ["/app"]