import socket
import unittest
from contextlib import contextmanager

HOST = "127.0.0.1"
PORT = 6667
PASSWORD = "pass"
TIMEOUT = 0.5
import time

class IRCClient:
    def __init__(self, host=HOST, port=PORT, timeout=TIMEOUT):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock = None
        self.buffer = b""

    def connect(self):
        self.sock = socket.create_connection((self.host, self.port), timeout=self.timeout)
        self.sock.settimeout(self.timeout)
        self.buffer = b""
        return self

    def close(self):
        if self.sock:
            try:
                self.send("QUIT")
                self.sock.close()
            finally:
                self.sock = None

    def send(self, line):
        if not line.endswith("\r\n"):
            line += "\r\n"
        data = line.encode("utf-8")
        self.sock.sendall(data)

    def recv_lines(self, max_lines=20):
        lines = []
        self.sock.settimeout(self.timeout)
        try:
            while len(lines) < max_lines:
                data = self.sock.recv(4096)
                if not data:
                    break
                self.buffer += data
                while b"\r\n" in self.buffer:
                    line, self.buffer = self.buffer.split(b"\r\n", 1)
                    lines.append(line.decode("utf-8", errors="replace"))
                    if len(lines) >= max_lines:
                        break
        except socket.timeout:
            pass
        return lines

    def has_numeric(self, lines, code):
        return any(f" {code} " in line for line in lines)

    def has_message(self, lines, code, text):
        return any(f" {code} " in line and text in line for line in lines)

    def has_prefix(self, lines, prefix):
        return any(line.startswith(prefix) for line in lines)

    def has_string(self, lines, string):
        return any(f"{string}" in line for line in lines)

    def has_not_string(self, lines, string):
        return not any(f"{string}" in line for line in lines)

@contextmanager
def irc_connection():
    c = IRCClient().connect()
    try:
        yield c
    finally:
        c.close()

class TestIRCServerModes(unittest.TestCase):
    def login(self, c, nick):
        c.send(f"PASS {PASSWORD}")
        c.send(f"NICK {nick}")
        c.send(f"USER {nick} 0 * :{nick}")
        lines = c.recv_lines()
        self.assertTrue(c.has_numeric(lines, "001"), f"Login failed, got: {lines}")
        return lines

    def test_user_mode_add_and_remove(self):
        with irc_connection() as c:
            self.login(c, "usermode1")

            c.send("MODE usermode1 +i")
            lines = c.recv_lines()
            c.send("MODE usermode1")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+i") and c.has_numeric(lines, "221"),
                f"Expected +k response, got: {lines}"
            )

            c.send("MODE usermode1 -i")
            lines = c.recv_lines()
            c.send("MODE usermode1")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+i") and c.has_numeric(lines, "221"),
                f"Expected +k response, got: {lines}"
            )



    def test_channel_mode_add_and_remove_mode_combinaison(self):
        with irc_connection() as c:
            self.login(c, "test_mode_m")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +mni")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+imn") and c.has_numeric(lines, "324"),
                f"Expected +m | 324 numeric response, got: {lines}"
            )

            c.send("MODE #testmode -m")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+in") and c.has_numeric(lines, "324"),
                f"Expected no in response, got: {lines}"
            )
            c.send("MODE #testmode -n")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+i") and c.has_numeric(lines, "324"),
                f"Expected no i response, got: {lines}"
            )
            c.send("MODE #testmode +n-i")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+n") and c.has_numeric(lines, "324"),
                f"Expected no n response, got: {lines}"
            )
            c.send("MODE #testmode +ir")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+i"),
                f"Expected no n response, got: {lines}"
            )
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+in") and c.has_numeric(lines, "324"),
                f"Expected no n response, got: {lines}"
            )
            c.send("MODE #testmode +ispnt")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+isnt"),
                f"Expected no n response, got: {lines}"
            )
            c.send("MODE #testmode +klq password 50")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+kl"),
                f"Expected no n response, got: {lines}"
            )

    def test_channel_mode_add_and_remove(self):
        with irc_connection() as c:
            self.login(c, "test_mode_m")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +m")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+m") and c.has_numeric(lines, "324"),
                f"Expected +m | 324 numeric response, got: {lines}"
            )

            c.send("MODE #testmode -m")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+m") and c.has_numeric(lines, "324"),
                f"Expected no m response, got: {lines}"
            )


    def test_channel_mode_s(self):
        with irc_connection() as c:
            self.login(c, "test_mode_s")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +s")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+s") and c.has_numeric(lines, "324"),
                f"Expected +s | 324 numeric response, got: {lines}"
            )

            c.send("MODE #testmode -s")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+s") and c.has_numeric(lines, "324"),
                f"Expected no +s response, got: {lines}"
            )

    def test_channel_mode_t(self):
        with irc_connection() as c:
            self.login(c, "test_mode_n")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +t")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+t") and c.has_numeric(lines, "324"),
                f"Expected +t | 324 numeric response, got: {lines}"
            )

            c.send("MODE #testmode -t")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+t") and c.has_numeric(lines, "324"),
                f"Expected no +t response, got: {lines}"
            )

    def test_channel_mode_l(self):
        with irc_connection() as c:
            self.login(c, "test_mode_n")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +l 10")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+l 10") and c.has_numeric(lines, "324"),
                f"Expected +l 10 | 324 numeric response, got: {lines}"
            )

            c.send("MODE #testmode -l")
            lines = c.recv_lines()
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+l 10") and c.has_numeric(lines, "324"),
                f"Expected no 'l' response, got: {lines}"
            )

    def test_channel_mode_b(self):
        with irc_connection() as c:
            self.login(c, "test_mode_n")

            c.send("JOIN #testmode")
            lines = c.recv_lines()

            c.send("MODE #testmode +b")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_numeric(lines, "368"),
                f"Expected +b | 367 numeric response, got: {lines}"
            )
            c.send("MODE #testmode")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+") and c.has_numeric(lines, "324"),
                f"Expected +b | 324 numeric response, got: {lines}"
            )



    def test_channel_password_mode_set_and_remove(self):
        with irc_connection() as c:
            self.login(c, "keymode1")

            c.send("JOIN #keytest")
            _ = c.recv_lines()

            c.send("MODE #keytest +k secretpass")
            lines = c.recv_lines()
            c.send("MODE #keytest")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_string(lines, "+k") and c.has_numeric(lines, "324"),
                f"Expected +k response, got: {lines}"
            )

            c.close()

        with irc_connection() as c:
            self.login(c, "keymode2")

            c.send("JOIN #keytest secretpass")
            lines = c.recv_lines()
            self.assertTrue(
                any("JOIN" in line for line in lines),
                f"Expected join with key to succeed, got: {lines}"
            )

            c.send("MODE #keytest -k secretpass")
            lines = c.recv_lines()
            c.send("MODE #keytest")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_prefix(lines, ":") and c.has_not_string(lines, "+k") and c.has_numeric(lines, "324"),
                f"Expected +k response, got: {lines}"
            )

    def test_invalid_mode_command(self):
        with irc_connection() as c:
            self.login(c, "badmode1")

            c.send("MODE")
            lines = c.recv_lines()
            self.assertTrue(
                c.has_numeric(lines, "461") or c.has_numeric(lines, "502"),
                f"Expected parameter or permissions error, got: {lines}"
            )

    def test_reconnect_and_mode_again(self):
        with irc_connection() as c:
            self.login(c, "reconn1")
            c.send("MODE reconn1 +i")
            lines = c.recv_lines()
            c.send("MODE reconn1")
            lines = c.recv_lines()
            self.assertTrue(c.has_prefix(lines, ":") and c.has_numeric(lines, "221") and c.has_string(lines, "+i"), f"Got: {lines}")

        with irc_connection() as c:
            self.login(c, "reconn2")
            c.send("MODE reconn2 +i")
            lines = c.recv_lines()
            c.send("MODE reconn2")
            lines = c.recv_lines()
            self.assertTrue(c.has_prefix(lines, ":") and c.has_numeric(lines, "221") and c.has_string(lines, "+i"), f"Got: {lines}")

class TestIRCServerLogin(unittest.TestCase):
    def test_login_success(self):
        with irc_connection() as c:
            c.send(f"PASS {PASSWORD}")
            c.send("NICK unittestnick")
            c.send("USER unittestuser 0 * :Unit Test User")

            lines = c.recv_lines()
            self.assertTrue(c.has_numeric(lines, "001") and c.has_numeric(lines, "002") and c.has_numeric(lines, "003") and c.has_numeric(lines, "004") and c.has_numeric(lines, "005"), f"Expected 001/2/3/4/5, got: {lines}")

    def test_bad_password_returns_error(self):
        with irc_connection() as c:
            c.send("PASS wrongpass")
            c.send("NICK badpassnick")
            c.send("USER badpassuser 0 * :Bad Pass User")

            lines = c.recv_lines()
            self.assertTrue(
                c.has_message(lines, "464", "Password mismatch"),
                f"Expected 464 Password mismatch, got: {lines}"
            )

    def test_missing_password_or_not_registered(self):
        with irc_connection() as c:
            c.send("NICK nopassnick")
            c.send("USER nopassuser 0 * :No Pass User")

            lines = c.recv_lines()
            self.assertTrue(
                c.has_numeric(lines, "451") or c.has_numeric(lines, "464"),
                f"Expected 451 or 464, got: {lines}"
            )

    def test_cap_ls_and_end(self):
        with irc_connection() as c:
            c.send("CAP LS 302")
            c.send(f"PASS {PASSWORD}")
            c.send("NICK capnick")
            c.send("USER capuser 0 * :CAP User")
            c.send("CAP END")

            lines = c.recv_lines()
            self.assertTrue(
                c.has_numeric(lines, "001") and c.has_numeric(lines, "002") and c.has_numeric(lines, "003") and c.has_numeric(lines, "004") and c.has_numeric(lines, "005") or c.has_prefix(lines, "CAP"),
                f"Expected CAP response or 001, got: {lines}"
            )

    def test_invalid_cap_command_is_ignored(self):
        with irc_connection() as c:
            c.send("CAP FOO")
            c.send(f"PASS {PASSWORD}")
            c.send("NICK capnick")
            c.send("USER capuser 0 * :CAP User")
    
            lines = c.recv_lines()
            self.assertTrue(
                c.has_numeric(lines, "001") and c.has_numeric(lines, "002") and c.has_numeric(lines, "003") and c.has_numeric(lines, "004") and c.has_numeric(lines, "005"),
                f"Expected successful registration after invalid CAP, got: {lines}"
            )

    def test_reconnect_and_login_again(self):
        with irc_connection() as c:
            c.send(f"PASS {PASSWORD}")
            c.send("NICK reconnect1")
            c.send("USER reconnect1 0 * :Reconnect One")
            lines = c.recv_lines()
            self.assertTrue(c.has_numeric(lines, "001") and c.has_numeric(lines, "002") and c.has_numeric(lines, "003") and c.has_numeric(lines, "004") and c.has_numeric(lines, "005"), f"Expected 001, got: {lines}")

        with irc_connection() as c:
            c.send(f"PASS {PASSWORD}")
            c.send("NICK reconnect2")
            c.send("USER reconnect2 0 * :Reconnect Two")
            lines = c.recv_lines()
            self.assertTrue(c.has_numeric(lines, "001") and c.has_numeric(lines, "002") and c.has_numeric(lines, "003") and c.has_numeric(lines, "004") and c.has_numeric(lines, "005"), f"Expected 001, got: {lines}")


if __name__ == "__main__":
    unittest.main(verbosity=8)