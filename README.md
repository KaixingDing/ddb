# ddb

A simple file transfer tool using SSH/SCP, inspired by adb push/pull.

## Usage

```bash
ddb push /local/path /remote/path
ddb pull /remote/path /local/path
```

**Requires scp in your system path and SSH key/password configured.**

## Build

```bash
mkdir build
cd build
cmake ..
make
```
