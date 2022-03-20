import socket
import sys
import threading

# global variable
global user_list, clientNum
user_list = {}
clientNum = 0
lock = threading.Lock()

# string when client enters the server
def returnEnter(addr):
    global clientNum
    enterString1 = "> New user %s:%s entered (1 user online)"%(addr[0], addr[1])
    enterString2 = "> New user %s:%s entered (%d users online)"%(addr[0], addr[1], clientNum)
    if clientNum == 1:
        return enterString1
    else:
        return enterString2

# string when client leaves the server
def returnLeft(addr):
    global clientNum
    LeftString1 = "< The user %s:%s left (%d user online)"%(addr[0], addr[1], clientNum)
    LeftString2 = "< The user %s:%s left (%d users online)"%(addr[0], addr[1], clientNum)
    if clientNum < 2:
        return LeftString1
    else:
        return LeftString2

# send msg to clients when new client enters
def handle_Enter(client_socket, addr):
    global user_list, clientNum
    clientNum += 1
    printEnter = returnEnter(addr)
    print(printEnter)
    user = addr[1]
    user_list[user] = client_socket
    for con in user_list.values():
        con.send(printEnter.encode())

# send msg to clients when one client leaves the server
def handle_Left(client_socket, addr):
    global user_list, clientNum
    clientNum -= 1
    printLeft = returnLeft(addr)
    print(printLeft)
    for con in user_list.values():
            con.send(printLeft.encode())
    del user_list[addr[1]]
    client_socket.close()

# thread function
def handle_client(client_socket, addr):
    global user_list, clientNum
    lock.acquire()
    handle_Enter(client_socket, addr)
    lock.release()
    while True:
        data = client_socket.recv(1024)
        if not data: break
        msg = data.decode()
        string = "[%s:%s] %s"%(addr[0], addr[1], msg)
        print(string)
        for con in user_list.values():
            con.send(string.encode())
    lock.acquire()
    handle_Left(client_socket, addr)
    lock.release()

# main function
def main(Host, Port):
    global user_list
    startString = "Chat Server started on port %d."%(Port)
    print(startString)

    # Create Socket
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind((Host, Port))
    serverSocket.listen()

    while True:
        try:
            # if client access, return socket
            client_socket, addr = serverSocket.accept()
            receive_thread = threading.Thread(target=handle_client, args=(client_socket, addr))
            receive_thread.daemon = True
            receive_thread.start()
        # handle keyboard interrupt
        except KeyboardInterrupt:
            # close every sockets
            for con in user_list.values():
                con.close()
            serverSocket.close()
            print("\nexit")
            return

if __name__ == '__main__':
    Host = sys.argv[1]
    Port = int(sys.argv[2])
    main(Host, Port)
