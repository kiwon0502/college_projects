import socket
import sys
import threading

# global varaibles
global user, userNum
user = 0
userNum = 0

# string when client enters the server
def enterChat(clientSocket):
    global user, userNum
    # To know own ID
    ForID = clientSocket.recv(1024)
    ForID = ForID.decode()
    parseString = ForID.split(" ")
    index = parseString[3].find(':')
    user = parseString[3][index+1:]
    userNum = int(parseString[5][1:])
    enterString1 = "> Connected to the chat server (%d user online)"%(userNum)
    enterString2 = "> Connected to the chat server (%d users online)"%(userNum)
    if userNum < 2:
        print(enterString1)
    else:
        print(enterString2)

# function for receving msg from the server
def handle_receive(clientSocket):
    global user
    while True:
        data = clientSocket.recv(1024)
        data = data.decode()
        if not user in data:
            print(data)

# function for sending msg to the server
def handle_send(clientSocket):
    while True:
        data = input()
        print("\033[A[You]", data)
        clientSocket.send(data.encode())

# main function
def main(serverName, serverPort):
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect((serverName, serverPort))
    enterChat(clientSocket)
    try:
        # receive thread
        receive_thread = threading.Thread(target = handle_receive, args = (clientSocket,))
        receive_thread.daemon = True
        receive_thread.start()
        # send thread
        send_thread = threading.Thread(target=handle_send, args=(clientSocket,))
        send_thread.daemon = True
        send_thread.start()

        send_thread.join()
        receive_thread.join()
    # handle keyboard interrupt
    # close the socket
    except KeyboardInterrupt:
        clientSocket.close()
        print("\nexit")
        return

if __name__ == '__main__':
    serverName = sys.argv[1]
    serverPort = int(sys.argv[2])
    main(serverName, serverPort)
