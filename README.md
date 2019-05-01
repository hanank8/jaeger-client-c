# Jaeger C Client

## Install

Install the project library dependencies. On Debian, the following command
should work.

### For ubunto
```
sudo apt install libhttp-parser-dev libjansson-dev protobuf-c-compiler \
                 libprotobuf-c-dev
```
### For CentOS
```
sudo yum -y install http-parser jansson-devel protobuf-c-devel
```

Run `git submodule update --init` to fetch the submodules.

== Compile and install

[source,sh]
----
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
----

To test:

[source,sh]
----
$ make test
----
