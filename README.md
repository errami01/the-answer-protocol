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
- **Mechanics**: We use an Instant Exchange turn-based system. When a player uses the ```ATTACK``` command, the server calculates player damage and immediately triggers an NPC counter-attack.
- **Formulas**:
    - Player Damage: (rand() % 10) + 5
    - NPC Damage: (rand() % 8) + 2
- **Death/Respawn**: Upon reaching 0 HP, players are teleported to the "Village Square" (start room) and their HP is reset to 50.
## Quest System
- Logic: The server supports Fetch Quests.
- Validation: Quests are validated by checking the player's ```t_item``` linked list for a specific ```req_item_id``` when they interact with the quest-giving NPC.
- Rewards: Completing a quest currently restores the player to 100 HP and removes the quest item from the world to maintain uniqueness.
## World Design
- Layout: The world consists of 8 interconnected rooms including a central "Village Square," a "Bakery," and a "Dark Alley."
- Connections: The map contains one primary loop (Square -> Armory -> Gate -> Bakery -> Square) and one optional branch leading to the "Deep Woods."
- Distribution: Items like the "Rusty Sword" and "Healing Herbs" are placed strategically to encourage exploration and quest completion.

## Server Logging
- Format: All logs are written to server.log in Structured JSON for easy parsing.
- Event Types: We log INFO (connections, movements), WARN (malformed commands), and ERROR (file loading failures).
- Abuse Monitoring: The log tracks rapid connection/disconnection patterns to identify potential flooding.

## Testing
- **Multiplayer**: Connect multiple instances of ```nc localhost 4242``` to verify that ```EVT``` messages (like ```CHAT``` or ```PRESENCE```) are broadcast correctly to other clients.
- **Combat**: Engage the "Goblin" in the "Dark Alley" and monitor the ```STATUS``` command to ensure HP decreases correctly.
- **Quests**: Take the "Herbs" from the "Woods" and deliver them to the "Baker" using the ```QUEST``` command.



valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./server_app