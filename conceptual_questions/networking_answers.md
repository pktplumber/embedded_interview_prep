# Networking Questions

## Fundamentals
### What is the difference between the OSI and TCP/IP model? Explain the role of each layer in both models.
The OSI is a layered conceptual framework for illustrating how data should flow in a network device. It is a theoretical model. From top to bottom, it consists of:
1. Application layer: Handles direct interaction with the user.
2. Presentation layer: Handles data formatting, encryption, and compression
3. Session layer: Manages sessions/connections between applications
4. Transport layer: Manages end-to-end comms, flow control, and error correction (TCP and UDP)
5. Network layer: Determines physical routing of data packets (think IP addresses)
6. Data link layer: Handle physical framing protocol/interaction with the hardware
7. Physical layer: Transmits raw bits over physical medium (cable or wireless)

The TCP/IP model is also a layered model, but is a practical/defined framework. It defines protocol suites used in real networks. The layers in the TCP/IP from top to bottom include:
1. Application layer: Also handles user interface, but includes data formatting and application access. Some protocols include HTTP/HTTPS, FTP, SMTP, etc..
2. Transport Layer: Same as OSI model, handles end-to-end comms, flow control, and error correction.
3. Internet layer: Handles addressing and routing packets across networks.
4. Network Access/Link Layer: Manages physical transmission of data, device/MAC addressing, and hardware interfaces.

### What layer does TCP operate at?
The transport layer.
### Explain what happens when an application sends data over a network.
1. User/app indicates some data should be sent. This might include file transfers (FTP), web pages (HTTP), etc..
2. The app passes the data to the transport layer handler.
3. The transport layer packages the data according to some protocol such as UDP or TCP. Depending on the protocol, it might establish/handle setting up the link and checking for communication errors.
4. The transport layer then 

### What are some ways to handle packet loss in a communication system?
1. Use an ack/retransmit mechanism for packet loss.

### How would you design a robust packet framing protocol for an embedded device?
1. Specify a start/sync marker
2. Specify source and destination fields or some form of addressing
3. 

## Programming
### What is a socket?
A socket is an OS object/utility that facilitates communication over a network. Effectively, it is a communication endpoint where it can receive and send data.

It is usually defined by:
1. An IP address - identifies the device on the network
2. Port number - identifies the specific application on the device
3. Protocol - Communication protocol in use. Typically UDP or TCP

### These functions are used for TCP connections. What do they do? `socket()`, `bind()`, `listen()`, `accept()`, `send()/receive()`
- `socket()` - Creates/opens a new communication socket
- `bind()` - Specifies the network address and port number the socket will receive data on
- `listen()` - Waits for new TCP connection requests
- `accept()` - 
- `send()` - Sends data to a specified address. If TCP, it will send data to the address that is connected to the socket
- `receive()` - Will attempt to receive data that has been sent to the socket over the network

### What happens during a TCP connection handshake?
### What is the difference between a client and a server?
A **client** is an object that connects to a server.

A **server** is an object that handles/accepts connections from clients. Usually provides a service for the client.

### Explain the TCP three way handshake.

## Ethernet
### What is a MAC address?
**Media Access Control** address. Determines a the ID/address of a  device's physical interface on a physical connection. 

### How does a MAC address differ from an IP address?
A MAC address is used at the data-link layer and an IP address is used at the network layer. For example, the MAC address is used for Ethernet. 

### How does a device find another's MAC address on a network?
Using 

## IP Addressing
### What is an IP address and its structure? Are there different versions?
An IPv4 address is made up of 32 bits. It's typically divided into 4 bytes/sections like "127.0.0.10".

An IPv6 is made up of 128 bits.

### What is a subnet mask and its use?
It is a 32 bit number that defines which portion of an IP address represents the number and which specifies the host. Devices can tell which addresses are on the same local-network by checking the subnet mask, so you can group addresses into smaller sub-networks which helps reduce congestion and makes routing more efficient.

It improves routing because routers don't have to broadcast packets to the entire network, they just send them to the specific subnet. Makes routing tables smaller, reduces broadcast traffic, and improves security since you can isolate groups.

### What is a default gateway and its use?
The default gateway is device's (usually the router) IP address that it sends data to when it needs to communicate with devices outside of its own LAN.

### What is a default route?
A default route specifies the gateway to communicate with an address that is not in the routing table. Typically this is "0.0.0.0". Think of it as "any destination".

### What is the difference between public and private IP addresses?
### What does 192.168.1.10/24 mean?
### Explain what happens when you send a packet to an IP address.

## Protocols
### What is DHCP and what does it do?
Dynamic Host Configuration Protocol is a protocol that automatically assigns IP addresses, subnet masks, default gateways, DNS, and other network configurations to devices on a network. Instead of manually configuring each device, a DHCP server gives IP leases, ensuring devices can join a network without conflict.

At startup, a device will send a broadcast "DHCP Discover Packet". The DHCP server will respond with a "DHCP Offer" that contains an available IP, subnet mask, etc.. The device then requests that IP with a "DHCP Request", and the server sends a "DHCP ACK" which acknowledges that the device now has that IP. The device can then use that IP until the lease expires.

### How does DNS resolution work?
"Domain Name Service" resolution works by sending a request asking what IP address corresponds to a a website/host name. You send the request containing the host name (e.g. www.google.com), the DNS server will look up and respond with the IP address of the host name, then the packets can be routed directly to the IP address. The idea is that people connect websites using names, and computers connect to other computers using a numeric address.

### What is ARP? What is it's purpose and how does it work?
"Address Resolution Protocol". It's used to map IP addresses to their MAC address. The host sends a message asking which device has the requested IP address. The device will respond with it's MAC address, then the host updates it's IP/MAC table. The table is used to quickly translate IP address to a devices MAC address.

### What is ICMP?
"Internet Control Message Protocol". It is a protocol that sends control and error information between devices on a network to communicate about network issues, reachability, and diagnostics.

Some common uses include:
- Ping - checks if a host is reachable
- Traceroute - Determine the path packets take to a destination
- Error reporting - Lets sender know about issues

Works at networking level (OSI layer 3).

### What happens when you run `ping`?
1. Your computer creates an ICMP Echo Request packet with the src/dest addresses and a timestamp
2. It travels to the destination via a router
3. The target responds if reachable and a generates an ICMP Echo Reply packet with the src/dest address, the same sequence number as the request, and the reception timestamp
4. It travels back to the sender which the calculates the round-trip time and any packet losses

### What is the difference between TCP and UDP? When would you use one over the other?
TCP requires a connection. UDP is connectionless. TCP is for reliable data but is slower. UDP is for unreliable data but is faster because it does not have the same overhead (handshaking/acks) as TCP.

### How does TCP ensure reliable delivery?
- Initial connection: A three way handshake is performed when the client wants to connect to a server. The client will send a SYN, the server responds with a SYN-ACK, then the client responds with an ACK. This ensures both sides are ready and synchronized.
- Sequence numbers: Each packet has a sequence number. If packets are received out of order (determined by sequence number), the receiving end will request the sender to re-transmit the dropped packets.
- Retransmission timer: If an ACK is not received after data has been sent after some time (specified by the retransmit timer), the sender will resend the packet.

### What is a TCP sliding window and how it helps control flow
The TCP sliding window defines how many bytes of data can be sent before needing an acknowledgment. As tge receiver acknowledges packets, the window slides forward, allowing more data to be sent.

## Network Configuration
### Explain static and dynamic IP configuration and their differences.
### What is DHCP and its process?
### What is a "default gateway"?
### What information is required to configure a static IP address?
### What is a port number and it's purpose?

## Electronics
### What is a switch?
A switch connects hardware devices within a LAN using cables by using packet switching. Operates at the data-link layer, is multi-port, and uses MAC addresses to forward received data.

### What is a router?
A router connects different networks by reading the IP address of packets and determining the best path for a packet. Operates at the networking layer of the OSI model.

### Explain how a packet is sent from a device to another device on a different network. Use an example.
Device A has an IP address of `192.168.1.10` wants to send a packet to Device B which has the address `10.0.0.2`.

Device A's default gateway is set to its router's IP address of `192.168.1.1`.

Device B's default gateway is set to its router's IP address of `10.0.0.1`.

1. Device A creates a packet (UDP or TCP) with the source IP set to `192.168.1.10` and the dest set to `10.0.0.1`.
2. Device A sends an ARP request to find the router's MAC address which the router replies with.
3. Device A builds the ethernet frame which contains the destination MAC address, source MAC address, and the IP packet data. Device A sends this to the switch.
4. The switch checks the destination MAC address and determines the port to send it out of.
5. The router receives the packet, checks the destination address, and determines where to send the packet to. The IP addresses stay the same, but the MAC addresses change with every hop. 
6. The destination router receives the packet and determines where to send the packet. This is achieved by sending an ARP request to determine device B's MAC address.
7. The destination router builds the ethernet frame with the Device B's MAC address and sends it to it's switch.
8. The switch reads the MAC address and forwards it to the corresponding port number.
9. Device B receives and processes the packet. 

### What happens if a router does not have the destination IP address/network in it's routing table?
The router will typically send the packet to it's default gateway which is the ISP's network. The ISP will then determine where to send the packet.

# Advanced Topics

## Protocols
### What is "Selective Acknowledgement" (SACK) in the TCP protocol? How can it improve communication in a high-latency or noisy network?
A TCP mechanism that allows receivers to inform senders about successfully received, out-of-order data blocks. Improves performance.

When a burst of packets is sent, and the receiver receives some packets, but some are dropped, the sender is notified and will only retransmit the missing segments instead of the entire window.

SACK is established during the connection/handshake by using the "SACK-permitted" option.

## RF Communication
### What is Time-Division Multiplexing (TDM) and Frequency-Division Multiplexing (FDM)? What is the advantage of using TDM over FDM?

TDM is a technique that transmits multiple signals over a single path by allocating unique, fixed time slots to each signal.

FDM is an analog technique that transmits multiple signals simultaneously over a single medium by assigning each user a unique frequency band.

TDM can make more efficient use of a single frequency band, so it's good for predictable data streams.

## Scheduling
### Name some packet scheduling algorithms and their uses
- First-In First-Out (FIFO): Packets are transmitted in the exact order they arrive
  - Simple, basic interfaces that don't need priority scheduling or bandwidth sharing
- Priority Queueing: Packets are classified by priority levels. The schedule services the packets with the highest priority first to the lowest
  - Useful for real-time traffic that requires guarantees for high priority messages
- Weighted Round Robin: Each queue gets a weight which determines how many packets can be sent per cycle.
  - Useful QoS and traffic requiring simple fairness and easy bandwidth differentiation
- Deficit Weighted RR: Like WRR, but each queue gets a weight/quantum (determines allowed bytes per round) and a deficit counter. Packets are transmitted if they fit in the deficit budget.
  - More advanced traffic control or bandwidth sharing between multiple classes of traffic in O(n) time complexity
- Weighted Fair Queueing (WFQ): Each packet/class gets a virtual finish time and the packet with the smallest finish time is sent first.
  - Useful as a very fair scheduling algorithm
- Earliest Deadline First
  - Optimal for meeting deadlines
- Token/Leaky Bucket: Traffic shaper which controls average bandwidth while allowing bursts

### Explain how Token Bucket traffic shaping works
Token Bucket algorithm allows traffic to burst up to a limit while enforcing an average rate over time.

- Buckets hold tokens that are added at a fixed rate (1000/s)
- Sending a packet costs tokens proportional to its size
- If enough tokens are available, the packet is sent immediately and tokens are subtracted
- Otherwise, the packet waits or is dropped
