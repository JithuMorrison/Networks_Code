# Networks Codes  

Welcome to the **Networks Code** repository! This repository contains implementations of various networking concepts, including client-server models for TCP and UDP protocols written in **C**, as well as network simulations using **NS2** with **TCL scripts**.  

## 📚 Contents  

This repository includes the following:  

- **Single Client-Server Connections**  
  - TCP-based single client-server communication.  
  - UDP-based single client-server communication.  

- **Multi-Client Connections**  
  - TCP-based multi-client-server communication.  
  - UDP-based multi-client-server communication.  

- **Network Simulations**  
  - Simulation of network scenarios using **NS2**.  

## 🛠️ Technologies Used  

- **Languages**:  
  - **C** for client-server implementations.  
  - **TCL** for NS2 network simulations.  
- **Tools**:  
  - **GCC** for compiling C programs.  
  - **Network Simulator 2 (NS2)** for network simulations.  

## 🚀 How to Use  

### Single and Multi Client-Server Communication  

1. **TCP and UDP**  
   - Compile the server:  
     ```bash
     gcc tcp_single_server.c -o server
     ```  
   - Compile the client:  
     ```bash
     gcc tcp_single_client.c -o client
     ```  
   - Start the server:  
     ```bash
     ./server
     ```  
   - Start the client:  
     ```bash
     ./client
     ```
   - Send message first from client

### NS2 Simulations  

1. Install **NS2**
2. Install **Nam**
3. Install **Xgraph**
4. Run the simulation script:  
   ```bash
   ns script_name.tcl
   ```
