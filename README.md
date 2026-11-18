*This project has been created as part of the 42 curriculum by aberrami and msturma.*

# The Answer Protocol (TAP) - MUD Server

## Description
This project is a Multi-User Dungeon (MUD) server built in C. It implements the RFC 42TAP protocol, allowing multiple players to explore a persistent virtual world, interact with items, complete quests, and engage in combat via a TCP-based command interface. The goal is to provide a robust, multiplexed backend that supports interchangeable CLI and GUI clients.

## Instructions
### Compilation
To compile the server, use the provided Makefile:
```bash
make server
```

### Execution
Start the server by specifying the port (defaulting to 4242 if not modified):
```bash
./server_app
```
The server will load the world.json file automatically upon startup.

### Connect to the server using CLI client
After starting the server, open a new terminal and connect to the server:
```bash
./client_app localhost 4242
```

Connect to the server following the protocol rfc provided with the project:
```bash
CONNECT bob
```
You can then use other commands like ```LOOK```, ```MOVE north```...
The CLI provides simple translation logic to facilitate the movements between rooms
| cmd | Translation |
|---|---|
| n | MOVE north |
| s | MOVE south |
| e | MOVE east |
| w | MOVE west |
### Connect using the GUI client
You can also connect to the server using a GUI client by executing:
```bash
./client_app_gui 127.0.0.1 4242
```
After logging in, you can move using the arrows by left-clicking on them, pick up items, interact with NPCs or do other various actions using the controls below:

Controls:

| Key | Action |
|---|---|
| I | open inventory |
| Q | open a list of active/completed quests |
| TAB | open a list of players |
| G | open group menu |

---

### Command Reference
The server supports the following commands, adhering to the RFC 42TAP specification:

| Command | Arguments | Description |
| :--- | :--- | :--- |
| `CONNECT` | `<username>` | Establishes identity and joins the world. |
| `LOOK` | - | Retrieves current room data (JSON format). |
| `MOVE` | `<direction>` | Moves the player (`north`, `south`, `east`, `west`). |
| `CHAT` | `<scope> <msg>` | Sends a message to `GLOBAL`, `ROOM`, or `GROUP`. |
| `TAKE` | `<item_id>` | Picks up an item from the current room. |
| `DROP` | `<item_id>` | Drops an item from your inventory into the room. |
| `INVENTORY` | - | Lists items currently held by the player. |
| `TALK` | `<npc_name>` | Initiates dialogue with an NPC. |
| `ATTACK` | `<npc_name>` | Initiates combat with an enemy NPC. |
| `STATUS` | - | Displays player health and combat status. |
| `QUEST` | `<npc_name>` | Requests or completes a quest with an NPC. |
| `QUESTS` | - | Lists all active and completed quests. |
| `WHO` | - | Displays the total player count on the server. |
| `GROUP` | `<subcmd>` | Manages groups (`CREATE`, `INVITE <user>`, `JOIN <leader>`, `LEAVE`). |
| `QUIT` | - | Gracefully terminates the connection. |

*Note: All commands are case-insensitive. Arguments with spaces (e.g., multi-word items) are fully supported.*

---

## Architecture
- **Concurrency Model**: The server uses I/O Multiplexing via the poll() system call. This allows a single-threaded process to handle up to 128 simultaneous connections without the overhead of threads or processes.
- **Request Handling**: We implemented a Dispatcher pattern. Incoming strings are parsed and routed to specific command handlers (e.g., cmd_look, cmd_move) to ensure code maintainability and Norminette compliance.
- **State Management**: World data is stored in linked lists of structures (t_room, t_item, t_npc), allowing for dynamic movement of items between the environment and player inventories.

## Protocol Implementation
Our implementation strictly adheres to RFC 42TAP.
- **Encoding**: All communication is UTF-8.
- **Framing**: Messages are ```\n``` (newline) terminated.
- **Deviations**: No major deviations were made. However, for the ```LOOK``` command, we provide a compact JSON format to minimize network packet fragmentation.

## Combat System
- **Mechanics**: We use an Instant Exchange turn-based system. When a player uses the ```ATTACK``` command, the server calculates player damage and immediately triggers an NPC counter-attack. The player can defend using ```item.shield``` with the command ```USE_ITEM``` if it exists in his inventory
- **Formulas**:
    - Player Damage: (rand() % 10) + 5
    - NPC Damage: (rand() % 8) + 2
- **Death/Respawn**: Upon reaching 0 HP, players are teleported to the "Village Square" (start room) and their HP is reset to 50.
## Quest System
- Logic: The server supports Fetch Quests.
- Validation: Quests are validated by checking the player's ```t_item``` linked list for a specific ```req_item_id``` when they interact with the quest-giving NPC.
- Rewards: Completing a quest currently restores the player to 100 HP and removes the quest item from the world to maintain uniqueness.
## World Design
![World map](tap_world.svg)
- Layout: The world consists of 8 interconnected rooms including a central "Village Square," a "Bakery," and a "Dark Alley."
- Connections: The map contains one primary loop (Square -> Armory -> Gate -> Shop -> Bakery -> Alley -> Tavern -> Square) and one optional branch leading to the "Deep Woods."
- Distribution: Items like the "Rusty Sword" and "Healing Herbs" are placed strategically to encourage exploration and quest completion.

## Server Logging
- Format: All logs are written to server.log in Structured JSON for easy parsing.
- Event Types: We log INFO (connections, movements), WARN (malformed commands), and ERROR (file loading failures).
- Abuse Monitoring: The log tracks rapid connection/disconnection patterns to identify potential flooding.

## Testing
- **Multiplayer**: Connect multiple instances of ```nc localhost 4242``` to verify that ```EVT``` messages (like ```CHAT``` or ```PRESENCE```) are broadcast correctly to other clients.
- **Combat**: Engage the "Goblin" in the "Dark Alley" and monitor the ```STATUS``` command to ensure HP decreases correctly.
- **Quests**: Take the "Herbs" from the "Woods" and deliver them to the "Elder" using the ```QUEST``` command.

## Group Contributions
This project was a collaborative effort between two developers. Our responsibilities were divided to ensure both the backend logic and the user-facing interfaces were developed in parallel.
### Aberrami
- Server Implementation: Developed the core TCP server, including socket management, the poll() multiplexing engine, and the command-parsing dispatcher.
- Protocol Compliance: Ensured all communication strictly followed the RFC 42TAP, including the handshake process, error codes, and asynchronous event broadcasting.
- Game Logic: Implemented the combat system (HP, damage formulas, death/respawn), the quest progression mechanics, and the item management system (unique instances, inventory).
- CLI Client: Developed the text-based interface for direct server interaction.
- Data & Logging: Created the world.json schema and the structured JSON server logging system.
### Msturma
- GUI Client: Architected the graphical client interface using Raylib.
- Interface Logic: Implemented the real-time event listener for the GUI to ensure room details, item availability, and combat statuses update without manual refreshing.

## Resources

### Classic References

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/): An essential tutorial for implementing Berkeley sockets in C, particularly for handling socket, bind, listen, and poll.
- [JSMN Documentation](http://zserge.com/jsmn/): Consulted for implementing the lightweight JSON parser used to load world data.
- [The Linux Programmer's Manual (man pages)](https://man7.org/linux/man-pages/): Daily reference for system calls such as poll(), recv(), send(), sigaction, and fcntl.

### AI usage
AI tools were used to assist with architectural decisions—such as evaluating approaches for parsing JSON data in C and choosing between poll() and select() for I/O multiplexing. AI also helped debug issues in the codebase and generate the initial structure for this README.md.

