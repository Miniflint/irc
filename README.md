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
IRC client: it only implements the server side of the protocol. It is specifically built
and tested to work with [Halloy](https://halloy.chat/), an existing, unmodified IRC client
used as the reference client for this project (see [Reference client](#reference-client)).

Key implementation constraints (imposed by the subject):
- C++98 standard only, no external/Boost libraries.
- The server must never crash, whatever happens (bad input, disconnections, memory
  pressure, etc.).
- All I/O is non-blocking, and a **single** event-notification call
  (`epoll` on Linux / `kqueue` on macOS) multiplexes every socket (listening socket, all
  client reads and writes).
- Forking is forbidden.

## Features

### Mandatory

| Command | Purpose |
|---|---|
| `PASS` | Server connection password |
| `NICK` | Set/change nickname |
| `USER` | Set username, complete registration |
| `JOIN` | Join one or more channels |
| `PRIVMSG` | Send a message to a user or a channel |
| `KICK` | Operator: eject a client from a channel |
| `INVITE` | Operator: invite a client to a channel |
| `TOPIC` | Operator: view/change a channel topic |
| `MODE` | Channel modes `+i`, `+t`, `+k`, `+o`, `+l` (see [Channel modes](#channel-modes)) |

### Bonus

| Feature | Purpose |
|---|---|
| Bot | Capable of executing the commands listed in [Bot commands](#bot-commands) |
| File transfer | Allows clients to send and receive files directly through the server |

#### Bot commands

| Trigger | Purpose |
|---|---|
| `$ping` | Replies "Pong !" |
| `$joke` | Replies with a random joke from a static list |
| `$lightspeed` | Replies with the speed of light |
| `$second` | Replies with the physical definition of a second (Cesium 133) |
| `$rpn <expression>` | Evaluates a Reverse Polish Notation expression (`+ - * /`) and replies with the result |

### Additional (not required, not bonus, implemented anyway)

| Command | Purpose |
|---|---|
| `QUIT` | Voluntary disconnection |
| `PART` | Leave a channel |
| `PING` | Keep-alive, server replies `PONG` |
| `CAP` | Capability negotiation (required by some modern clients) |
| `OPER` | Elevate to server operator/admin |
| `KILL` | Operator: force-disconnect a client |
| `DIE` | Operator: shut down the server |
| `RESTART` | Operator: restart the server — dead code, never reachable (dispatch table off-by-one, see [Known issues](#known-issues)) |
| `INFO` | Server banner and version info |
| `WHO` | List users of a channel |
| `AWAY` | Set/clear an away message |
| `NAMES` | List members of a channel |
| `LIST` | List existing channels |
| `MODE` (user) | User modes `i`,`x`,`d`,`R`,`g`,`B`,`o`/`O`,`a`/`A` (see [User modes](#user-modes)) |
| `MODE` (channel, extra) | `+m`, `+n`, `+s`, `+b`, plus operator hierarchy `+v`/`+h`/`+o`/`+a`/`+q` |

## Channel modes

| Mode | Name | Effect |
|---|---|---|
| `i` | Invite-only | Only invited clients can join |
| `s` | Secret | Hidden from `LIST` and user profiles |
| `m` | Moderated | Only voiced (`+v`) or operator (`+o`+) members can talk |
| `n` | No external messages | Clients outside the channel cannot `PRIVMSG` it |
| `t` | Topic protection | Only channel operators can change the topic |
| `k` | Key | Sets/removes a channel password |
| `l` | User limit | Caps the number of members |
| `b` | Ban | Banned clients cannot join |

## Channel-level user privileges (per-channel, hierarchical)

| Symbol | Name | Role |
|---|---|---|
| `+v` | Voice | Can talk in a moderated (`+m`) channel without being operator |
| `+h` | Half-operator | Partial operator rights |
| `+o` | Operator | Full channel rights: `KICK`, `TOPIC`, `MODE`, `INVITE` |
| `+a` | Protected | Cannot be kicked by a plain operator |
| `+q` | Founder | Channel creator, highest privilege level

## User modes

| Mode | Name | Effect |
|---|---|---|
| `i` | Invisible | Hidden from generic `WHO` results |
| `x` | Hidden host | Masks the real IP/host |
| `d` | Deaf | Blocks reception of channel messages |
| `R` | Registered only | Rejects private messages from unregistered clients |
| `g` | Caller-ID | Rejects private messages except from clients already messaged |
| `B` | Bot | Marks the client as a bot |
| `o`/`O` | Server operator | Granted only via `OPER`, not settable through `MODE` |
| `a`/`A` | Server admin | Granted only via `OPER`, not settable through `MODE` |

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

- **Event loop**: `epoll` is used on Linux and `kqueue` on macOS — two different OS-specific
  APIs, chosen because macOS does not support `epoll` — but both are wired to behave the
  same way in this project: a single blocking call per loop iteration multiplexes the
  listening socket and every client's read/write readiness (whether a socket has data to
  read or room to write without blocking), as required by the subject.
- **Trie**: a custom compressed trie — a tree where each node stores a key *fragment*
  rather than a single character, branching only where keys actually diverge
  — used as an optimized lookup structure for command dispatch.
- **Buffering**: client requests are limited to `MAX_PACKET_SIZE` (512 bytes), as required
  by RFC 2812.

## Resources

- [RFC 1459 – Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 – Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [modern IRC documentation](https://modern.ircdocs.horse/)
- Linux `man` pages: `epoll(7)`, `epoll_ctl(2)`, `epoll_wait(2)`
- macOS `man` pages: `kqueue(2)`, `kevent(2)`
- [Halloy IRC client](https://halloy.chat/) — used as the reference client

### AI usage

AI assistance was used during this project for:
- Understanding parts of the existing codebase (srenaud)
- structuring this `README.md`

