*This project has been created as part of the 42 curriculum by herolle, trgoel and srenaud.*

# ft_irc

## Description

`ft_irc` is a custom implementation of an IRC (Internet Relay Chat) server, written from
scratch in C++98 as part of the 42 curriculum.

The goal of the project is to understand and implement one of the fundamental protocols
of the Internet: a text-based, real-time messaging protocol that allows users to connect
through an IRC client, authenticate, choose a nickname, join channels, exchange public
and private messages, and manage channels through operator privileges.

The server does **not** implement server-to-server communication and does not include an
IRC client: it only implements the server side of the protocol, and is meant to be used
with an existing, unmodified IRC client (see [Reference client](#reference-client)).

Key implementation constraints (imposed by the subject):
- C++98 standard only, no external/Boost libraries.
- The server must never crash, whatever happens (bad input, disconnections, memory
  pressure, etc.).
- All I/O is non-blocking, and a **single** event-notification call
  (`epoll` on Linux / `kqueue` on macOS) multiplexes every socket (listening socket, all
  client reads and writes).
- Forking is forbidden.

## Features

- Client registration flow: `PASS` → `NICK` → `USER`, with proper welcome sequence
  (`RPL_WELCOME`, `RPL_YOURHOST`, MOTD, auto-join of a default channel, etc.).
- Channel management: `JOIN`, `PART`, `TOPIC`, `NAMES`, `LIST`, `KICK`, `INVITE`.
- Channel modes: `+i` (invite-only), `+t` (topic protection), `+k` (channel key/password),
  `+l` (user limit), `+m` (moderated), `+n` (no external messages), `+s` (secret),
  `+b` (ban list), plus the operator-hierarchy modes `+o`/`+h`/`+v`/`+a`/`+q`
  (operator / half-op / voice / protected / founder).
- Private messaging (`PRIVMSG`) to a user or to a channel, with away-message handling.
- Server operator support (`OPER`), including a `KILL` command reserved to operators.
- Graceful and forceful disconnection handling (`QUIT`, `KILL`, connection loss), with
  proper `QUIT` broadcast to every shared channel.
- Partial/aggregated TCP packet handling: commands are only processed once a full
  `\r\n`-terminated line has been received, even if it was sent in several `send()`/`recv()`
  chunks (see the `nc -C` example from the subject).
- Internally, command dispatch, nickname lookup and channel lookup are all backed by a
  custom **Trie** (compressed/radix trie) data structure instead of `std::map`, giving
  lookup/insertion costs proportional to the length of the key rather than the number of
  entries.

## Instructions

### Requirements

- A C++98-compatible compiler (`c++`/`clang++`/`g++`).
- Linux (uses `epoll`) or macOS (uses `kqueue`).
- `make`.

### Compilation

```sh
make
```

This builds the `ircserv` executable. Other standard rules are available:

```sh
make        # build ircserv
make clean  # remove object files
make fclean # remove object files and the binary
make re     # fclean + build
```

### Running the server

```sh
./ircserv <port> <password>
```

- `<port>`: the TCP port the server listens on (must be a positive integer greater
  than 3).
- `<password>`: the connection password required by clients (`PASS` command), must be
  at least 2 characters long.

Example:

```sh
./ircserv 6667 mypassword
```

### Connecting to the server

<a name="reference-client"></a>
The reference client used to develop and test this server is
[Halloy](https://halloy.chat/). Any standard IRC client (irssi, WeeChat, HexChat...)
should be able to connect the same way:

1. Connect to `127.0.0.1` (or the server's IP) on the chosen `<port>`.
2. Send the connection password (most clients have a dedicated "server password" field
   that sends `PASS` automatically).
3. Set a nickname and a username, then join a channel, e.g. `/join #general`.

Quick manual test with `nc`:

```sh
nc -C 127.0.0.1 6667
PASS mypassword
NICK bob
USER bob 0 * :Bob Bobson
JOIN #test
```

## Technical choices

- **Event loop**: a single call to `epoll_wait` (Linux) or `kevent` (macOS) handles the
  listening socket plus every connected client's read/write readiness, as required by
  the subject. Write interest on a socket is only enabled while that client's output
  buffer is non-empty, to avoid needless wake-ups.
- **Trie**: a compressed trie (each node stores a key *fragment*, not a single character)
  is used for command dispatch, nickname → fd lookup, channel name → `Channel*` lookup,
  and per-client channel membership/rights lookup.
- **Buffering**: every client keeps a raw input buffer that is only flushed a command at
  a time once a full `\r\n` has been received, and an output buffer that is drained
  progressively as the socket becomes writable, respecting `MAX_PACKET_SIZE` (512 bytes)
  as per the RFC.

## Resources

- [RFC 1459 – Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 – Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [RFC 2813 – Internet Relay Chat: Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)
- [modern IRC documentation](https://modern.ircdocs.horse/)
- Linux `man` pages: `epoll(7)`, `epoll_ctl(2)`, `epoll_wait(2)`
- macOS `man` pages: `kqueue(2)`, `kevent(2)`
- [Halloy IRC client](https://halloy.chat/) — used as the reference client

### AI usage

AI assistance (Claude) was used during this project for:
- Understanding parts of the existing codebase (event loop, Trie data structure,
  channel-mode handling) in preparation for the peer-evaluation, by walking through the
  code file by file and asking targeted questions about the more complex sections.
- Drafting and structuring this `README.md` file based on the actual source code and the
  project subject.

All AI-assisted explanations were cross-checked against the code and the RFCs listed
above before being relied upon.
