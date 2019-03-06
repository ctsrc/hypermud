# HyperMUD: Mystery

![Header image](images/header.png)

A Multi-User Dungeon (multiplayer real-time virtual world)

Downloads:

* ~~[64-bit Linux client, v0.0.0](#)~~ (not yet available)
* ~~[64-bit Windows client, v0.0.0](#)~~ (not yet available)
* ~~[64-bit macOS client, v0.0.0](#)~~ (not yet available)

You find yourself in a dungeon.

In your hand you are holding a sword.

You hear strange noises.

You feel hungry.

Better start moving I guess!

Use the wasd or ,aoe keys to walk.

Use spacebar to interact.

## Table of Contents

* [Project status](#project-status)
* [Features](#features)
* [Running the client](#running-the-client)
* [News](#news)
* [Want to run your own server?](#want-to-run-your-own-server)
* [Want to build the client from source?](#want-to-build-the-client-from-source)
  - [Building the latest stable release of the client](#building-the-latest-stable-release-of-the-client)
  - [Building the current development version of the client](#building-the-current-development-version-of-the-client)
* [Want to build the server from source?](#want-to-build-the-server-from-source)
  - [Building the latest stable release of the server](#building-the-latest-stable-release-of-the-server)
  - [Building the current development version of the server](#building-the-current-development-version-of-the-server)
* [Copyright notice and license](#copyright-notice-and-license)

## Project status

Development has started. No usable server exists yet. No usable client exists yet.

## Features

Eventually the game will feature:

* RPG (role-playing game) elements
* Hack-and-slash playstyle
* PvP (player versus player)
* Online chat

## Running the client

Download the pre-compiled binary for your platform
([links provided above](#hypermud-mystery)).

Execute the binary to start the client.

```
./hypermud-client
```

The client will prompt you for which server it should connect to.
The hostname and port field will contain the name of the last
server you have successfully connected to. If you have never
connected to any server before then this field will be pre-filled
with the hostname and port of the official server;
`mystery.hypermud.com:2022`.

## News

* 2019-03-05: Development started.

## Want to run your own server?

Downloads:

* ~~[64-bit Linux server, v0.0.0](#)~~ (not yet available)
* ~~[64-bit Windows server, v0.0.0](#)~~ (not yet available)
* ~~[64-bit macOS server, v0.0.0](#)~~ (not yet available)

Execute the binary to start the server.

```
./hypermud-server
```

By default the *HyperMUD: Mystery* server
runs on port 2022. If you want to run it on
another port, provide `-p` and desired
port number as argument to the binary.

For example, to run the server on port 9022:

```
./hypermud-server -p 9022
```

## Want to build the client from source?

If you want to build the client from source
you will need a recent version of the Rust
toolchain installed.

Get the Rust toolchain from https://rustup.rs/

### Building the latest stable release of the client

Note: The latest stable release of the client will
always correspond to the latest pre-built binary
version. So if all you want is to have the latest
stable release of the client, all you need to do
is to download [the prebuilt binary for your platform](#hypermud-mystery).

With that being said, if you still want to build
the latest stable release of the client from source,
here's what to do:

```
cargo install hypermud-client
```

If you have your path set up correctly you will then
be able to run the client that you just built:

```
hypermud-client
```

### Building the current development version of the client

Note: The development version of the client is intended for
development only. It might contain partially implemented features,
and it might not be able to connect to the stable version of the server.
In general, only developers should run this version, and they should
connect to the corresponding development server version only.

So before you read on, you should first
[build and run the current development version of the server](#building-the-current-development-version-of-the-server).

In the root of this repository, execute:

```
cargo build --bin hypermud-client
```

To run the client that you just built:

```
cargo run --bin hypermud-client -- -s localhost:3022
```

## Want to build the server from source?

If you want to build the server from source
you will need a recent version of the Rust
toolchain installed.

Get the Rust toolchain from https://rustup.rs/

### Building the latest stable release of the server

Note: The latest stable release of the server will
always correspond to the latest pre-built binary
version. So if all you want is to have the latest
stable release of the server, all you need to do
is to download [the prebuilt binary for your platform](#want-to-run-your-own-server).

With that being said, if you still want to build
the latest stable release of the server from source,
here's what to do:

```
cargo install hypermud-server
```

If you have your path set up correctly you will then
be able to run the server that you just built:

```
hypermud-server
```

### Building the current development version of the server

Note: The development version of the server is intended for
development only. It might contain partially implemented features,
and stable clients might not be able to connect to the development
version of the server. In general, only developers should run
this version, and they should connect to it with the corresponding
development version client only.

Clone this repository and then in the root of the repository, execute:

```
cargo build --bin hypermud-server
```

To run the server that you just built:

```
cargo run --bin hypermud-server -- -p 3022
```

With the current development version of the server running you should then
[build and run the current development version of the client](#building-the-current-development-version-of-the-client).

## Copyright notice and license

Copyright (c) Erik Nordstrøm 2019

The *HyperMUD: Mystery* client and server source code and assets are released
under the terms of the ISC license. See file [LICENSE](LICENSE) for details.
