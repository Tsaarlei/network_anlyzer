# network_analyzer

A terminal network analyzer for Linux. It shows which websites you access by capturing outgoing DNS requests.

> Work in progress: an option to scan for incoming MAC addresses...

## Build

```sh
mkdir build && cd build
cmake ..
make
```

## Run

Needs root for raw socket access:

```sh
sudo ./dnsniffer
```

Press `Ctrl+C` to stop.

## Limitations

- Only plain DNS over UDP port 53 is captured (not DNS over HTTPS/TLS).
- Linux only.

