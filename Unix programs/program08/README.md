### Theory of Message Queues

**Message queues** are a method of **Inter-Process Communication (IPC)** that allows different processes (programs) to communicate with each other by sending and receiving messages. In simple terms, message queues are like a mailbox system where one program can drop a message into a box, and another program can pick it up later. This is especially useful when processes are running independently and need to exchange information.

#### Key Concepts

1. **Inter-Process Communication (IPC):**
   - **IPC** is a way for programs running on the same machine to exchange data. Different IPC mechanisms include **pipes, shared memory, and message queues**. Message queues are one of the most straightforward and easy-to-understand IPC methods.

2. **What is a Message Queue?**
   - A **message queue** is like a shared box where one program (called the **sender**) can place a message, and another program (called the **receiver**) can pick up the message.
   - The key feature is that the sender and receiver don’t have to run at the same time. The sender can put a message in the queue, and the receiver can collect it whenever it’s ready.

#### Steps in Message Queue Communication

1. **Creating a Key:**
   - Before creating or using a message queue, both programs (Sender and Receiver) need to agree on a **key**. This key is used to identify the message queue, just like a mailbox number.
   - The function `ftok()` is used to create this unique key based on a file path and an identifier. This ensures that both programs use the same mailbox (message queue).

2. **Creating or Accessing a Message Queue:**
   - Once a key is generated, the function `msgget()` is used to either **create** or **access** the message queue. The message queue is stored in the system's memory, and processes can send or receive messages using it.

3. **Sending a Message:**
   - The sender program creates a message, which consists of two parts:
     1. **Message type (`mtype`)**: This is a number that defines the type or category of the message. For example, `mtype = 1` could be used for one type of message, and `mtype = 2` for another.
     2. **Message content (`mtext`)**: This is the actual message (text) that the sender wants to send.
   - The sender uses `msgsnd()` to place the message into the queue.

4. **Receiving a Message:**
   - The receiver program picks up the message from the queue using `msgrcv()`. It can specify which type of message it wants to receive based on `mtype`.
   - The message content is then printed or used by the receiver.

5. **Permissions and Flags:**
   - The **permissions** (e.g., `0666`) ensure that both programs have the rights to read and write to the message queue.
   - The **`IPC_CREAT`** flag ensures that if the message queue doesn’t already exist, it will be created.

#### Benefits of Message Queues

- **Asynchronous Communication**: The sender and receiver don’t need to be active at the same time. The sender can place a message in the queue, and the receiver can pick it up later.
- **Message Persistence**: Messages remain in the queue until they are read. If the receiver is not ready, the message will wait in the queue.
- **Decoupled Programs**: Message queues allow programs to be independent of each other, improving flexibility and scalability.

### How It Works in the Sender and Receiver Program

1. **Sender Program:**
   - The **sender** creates or accesses the message queue and then sends a message (text) to the queue. This message is stored in the system’s memory until the receiver picks it up.

2. **Receiver Program:**
   - The **receiver** opens the same message queue and picks up the message sent by the sender. The receiver then prints the message, showing that communication was successful.

---

### Sender.cpp and Receiver.cpp: Simple Message Queue Communication

These two programs demonstrate how to send and receive messages using **message queues** in C++. They communicate with each other through a message queue, one program (Sender) sends a message, and the other program (Receiver) receives it.

#### Sender.cpp Explanation

1. **Including Libraries:**
   - `#include <iostream>`: Allows input and output operations.
   - `#include <cstring>`: Allows string manipulation like `strcpy()`.
   - `#include <cstdlib>`: Allows usage of `exit()` for program termination.
   - `#include <unistd.h>`, `#include <sys/types.h>`, `#include <sys/ipc.h>`, `#include <sys/msg.h>`: These libraries are necessary for working with message queues.

2. **Message Structure:**
   ```cpp
   struct Message {
       long mtype;
       char mtext[100];
   };
   ```
   - **`mtype`**: Represents the type of message (an integer value). This is used to differentiate between different types of messages.
   - **`mtext`**: Stores the actual message content (a string of up to 100 characters).

3. **Creating a Message Queue Key (ftok):**
   ```cpp
   key = ftok("/tmp", '1');
   ```
   - **`ftok()`**: Generates a unique key for the message queue, using a specified file path (`/tmp`) and an identifier (`'1'`).
   - This key is used to create or access a message queue.

4. **Creating or Accessing the Message Queue (msgget):**
   ```cpp
   msgid = msgget(key, 0666 | IPC_CREAT);
   ```
   - **`msgget()`**: Creates or accesses a message queue. The permissions (`0666`) allow the queue to be read and written by everyone, and the flag `IPC_CREAT` creates the queue if it doesn’t exist.

5. **Sending a Message (msgsnd):**
   ```cpp
   strcpy(message.mtext, "Hello, this is a message from the sender!");
   if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
       perror("msgsnd");
       exit(1);
   }
   ```
   - **`msgsnd()`**: Sends a message to the message queue. Here, the message "Hello, this is a message from the sender!" is copied into the `message.mtext` field and sent.
   - If sending fails, an error message is printed using `perror()`, and the program exits with an error code.

#### Receiver.cpp Explanation

1. **Including Libraries:**
   Similar to Sender.cpp, it includes libraries necessary for working with message queues.

2. **Creating a Message Queue Key:**
   ```cpp
   key = ftok("/tmp", '1');
   ```
   - **`ftok()`**: The same function is used here to generate the same unique key as in Sender.cpp, so both programs refer to the same message queue.

3. **Accessing the Message Queue:**
   ```cpp
   msgid = msgget(key, 0666 | IPC_CREAT);
   ```
   - **`msgget()`**: Same as in Sender.cpp, it either creates or accesses the message queue using the key generated by `ftok()`.

4. **Receiving a Message (msgrcv):**
   ```cpp
   if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
       perror("msgrcv");
       exit(1);
   }
   ```
   - **`msgrcv()`**: Receives a message from the message queue. The message with `mtype = 1` (as specified in the sender) is received here.
   - If receiving fails, an error message is printed, and the program exits.

5. **Printing the Received Message:**
   ```cpp
   cout << "Data received from message queue: " << message.mtext << endl;
   ```
   - This line prints the message received from the message queue to the screen.
