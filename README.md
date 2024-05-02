# ft_irc: A custom Internet Relay Chat Server

> "Internet Relay Chat (IRC) is a text-based chat system for instant messaging. IRC is designed for group communication in discussion forums, called channels, but also allows one-on-one communication via private messages as well as chat and data transfer, including file sharing.\
Internet Relay Chat is implemented as an application layer protocol to facilitate communication in the form of text. The chat process works on a client–server networking model. Users connect, using a client—which may be a web app, a standalone desktop program, or embedded into part of a larger program—to an IRC server, which may be part of a larger IRC network." ([source])

[source]: https://www.radware.com/security/ddos-knowledge-center/ddospedia/irc-internet-relay-chat/

As part of the "42 common-core" roadmap, we are asked to implement a custom IRC server, with a limited range of commands and handling only client-server communications.

## Requeriments

> [!NOTE]
> This project has been developed on Unix-based systems, so please note that it will not work correctly on other systems.

To correctly run this project on your computer, you need to have installed:

* An Unix-based system, such as MacOS, Ubuntu, Debian, etc.
* Git -> [installation tutorial]
* C++ programming language -> We use C++98 in the project, but a newer version also works
* Makefile
* An IRC client -> We test the server with **netcat command** and the **irssi** client

[installation tutorial]: https://git-scm.com/book/en/v2/Getting-Started-Installing-Git

## Install the project

Once you have fullfilled the requeriments, you are ready to start installing the project on your system.\
To install it, you have to run the following command in a terminal:

```
git clone https://github.com/jdomingu98/ft_irc.git
```

## Compile and run the server

Once you have downloaded the repository, you have to enter the directory using the `cd` command and compile it using `make` command.\
This will generate an executable called `ircserv` that can be execute using the following structure:

```
./ircserv <port> <password>
```

Where `<port>` is the port where the server will listen for new connections and commands and `<password>` is the connection password

## How to connect to the server

> [!WARNING]
> This project was tested with `netcat command` and with `irssi client`. Using other clients may lead to some errors and incorrect behaviour

* To connect using netcat (nc) command, you only have to launch:

    ```
    nc <host> <port>
    ```

* To install and use the **irssi client** you must follow [this] guide

[this]: https://irssi.org/download/

## Commands implemented

| Command | Description |
| :-----------: | :----------- |
| PASS | Set a ‘connection password’. If set, the password must be set before any attempt to register the connection is made. |
| NICK | Give the client a nickname or change the previous one. |
| USER | Used at the beginning of a connection to specify the username and realname of a new user. |
| JOIN | The client wants to join the given channel(s), using the given key (if necessary) for it. |
| PART | Removes the client from the given channel(s). |
| MODE | Set or remove options (or modes) from a given target. Our channels modes: i,t,k,o,l |
| INVITE| Invite a user to a invite-only channel. |
| KICK | Request the forced removal of a user from a channel. |
| TOPIC | Change or view the topic of the given channel. |
| PRIVMSG | Send private messages between users, as well as to send messages to channels. |
| NOTICE | Send notices between users, as well as to send messages to channels. |
| QUIT | Terminates a client’s connection to the server. |
| WHO | Used to retrieve information about users on a channel or the entire network. |
| UP | Uploads a file to a channel. |
| DOWN | Downloads a file from a channel. |

## See the wiki

For more detailed information about the project, please visit the [wiki]

[wiki]: https://github.com/jdomingu98/ft_irc/wiki

---

Project made by [@ruzafa8], [@Atrujillo02] and [@jdomingu98]

[@ruzafa8]: https://github.com/ruzafa8
[@Atrujillo02]: https://github.com/Atrujillo02
[@jdomingu98]: https://github.com/jdomingu98