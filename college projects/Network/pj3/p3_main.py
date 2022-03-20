import socket
import sys
import threading
import datetime

# gloabl variable
global threadNum, taskNum, imagE_filter, lock, start
threadNum = [0 for i in range(300)]
taskNum = 1
image_filter = False
lock = threading.Lock()

def handle_request(byte_data):
    global image_filter
    str_data = "".join([chr(b) for b in byte_data])
    if_get = False
    # Remove BODY from requestMSG
    withoutBody = str_data[:str_data.find('\r\n\r\n')]
    # Start line : http method, request target, http version
    start_line = withoutBody.split('\r\n')[0]
    httpV = start_line[start_line.find(' HTTP/'):]                      # http version
    req = start_line[:start_line.find(' HTTP/')]                        # method + target
    # check if the method is GET, and whether image filter should be on
    if "GET" in req:
        if_get = True
    
    if "?image_off" in req:
        image_filter = True
    elif "?image_on" in req:
        image_filter = False
    
    # request Header
    header = withoutBody[withoutBody.find('\r\n')+2:withoutBody.find('\r\n\r\n')]
    header_split = header.split('\r\n')
    host = "Host field Not Found"
    agent = "Agent field Not Found"
    # find host, agent and make connection close
    for i in range(len(header_split)):
        if "Host:" in header_split[i]:
            host = header_split[i][header_split[i].find(':')+2:]
        elif "User-Agent:" in header_split[i]:
            agent = header_split[i][header_split[i].find(':')+2:]
        elif "Connection:" in header_split[i]:
            header_split[i] = "Connection: close"
        elif "Proxy-Connection:" in header_split[i]:
            header_split[i] = "Connection: close"
    # print(header_split)
    # wrap up the data
    handled_data = start_line + "\r\n"
    for i in range(len(header_split)):
        handled_data += (header_split[i] + "\r\n")
    handled_data += "\r\n"
    return if_get, httpV, req, host, agent, handled_data

def url_handle(str_data, http_version):
    start_line = "GET http://www.linuxhowtos.org/" + http_version
    req = "GET http://www.linuxhowtos.org"
    header = str_data[str_data.find('\r\n')+2:str_data.find('\r\n\r\n')]
    header_split = header.split('\r\n')
    for i in range(len(header_split)):
        if "Host:" in header_split[i]:
            host = "www.linuxhowtos.org"
            header_split[i] = "Host: www.linuxhowtos.org"
            break
    handled_data = start_line + "\r\n"
    for i in range(len(header_split)):
        handled_data += (header_split[i] + "\r\n")
    handled_data += "\r\n"
    return req, host, handled_data

def handle_msg(http_version, byte_data):
    str_data = "".join([chr(b) for b in byte_data])
    # Remove BODY from responseMSG
    withoutBody = str_data[:str_data.find('\r\n\r\n')]
    res = withoutBody[:withoutBody.find('\r\n')]
    status = res[len(http_version):]
    from_content = withoutBody[withoutBody.find('Content-Type: '):]
    content_type = from_content[14:from_content.find('\r\n')]
    return status, content_type, withoutBody

def print_filter(i_f, u_f):
    if (i_f):
        if (u_f):
            return ("[O] URL filter | [O] Image filter\n")
        else:
            return ("[X] URL filter | [O] Image filter\n")
    else:
        if (u_f):
            return ("[O] URL filter | [X] Image filter\n")
        else:
            return ("[X] URL filter | [X] Image filter\n")

def checkThreadNum():
    global threadNum
    for i in range(300):
        if threadNum[i] == 0:
            threadNum[i] = 1
            return i + 1
    return 302

# thread function
def connect_client(client_socket, addr):
    global taskNum, image_filter, start
    url_filter = False

    # get request from the client
    data = client_socket.recv(8000)   
    # parsing request
    if_get, httpV, cli_req, cli_host, agent, cli_handled_data = handle_request(data)
    connection1 = ""
    if if_get:
        lock.acquire()
        t_id = checkThreadNum()
        connection1 = " [Conn:       " + str(t_id) + "/         " + str(threading.activeCount()-1) + "]\n"
        lock.release()
    # connection string to print in the end
    connection2 = "[CLI connected to " + str(addr[0]) + ":" + str(addr[1]) + "]\n"
    cli_prx = "[CLI ==> PRX --- SRV]\n" + "> " + cli_req + "\n> " + agent + "\n"

    # redirection flag
    if "yonsei" in cli_host:
        url_filter = True
    # if url filter on, change the host and request target
    if url_filter and if_get:
        srv_req, srv_host, srv_handled_data = url_handle(cli_handled_data, httpV)
    else:
        srv_host = cli_host
        srv_req = cli_req
        srv_handled_data = cli_handled_data
    try:
        serverHost = socket.gethostbyname(srv_host)
    except:
        client_socket.close()
        return
    # set socket which connects my proxy and the destination server
    srvSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srvSocket.connect((serverHost, 80))
    srvSocket.send(srv_handled_data.encode())
    dataSize = 0
    loopT = 0
    prx_srv = "[SRV connected to " + srv_host + ":80]\n[CLI --- PRX ==> SRV]\n> " + srv_req +"\n> " + agent + "\n"
    srv_prx = ""
    status = ""
    content_type = "ssssssssssssssssssssssss"
    response_header = ""
    cli_close = ""
    while True:
        loopT += 1
        msg = srvSocket.recv(4096)
        if not msg:
            client_socket.close()
            cli_close = "[CLI disconnected]\n"
            break
        dataSize += len(msg)
        if loopT == 1:
            status, content_type, response_header = handle_msg(httpV, msg)
            srv_prx = "[CLI --- PRX <== SRV]\n"
        if image_filter and ("image/" in content_type):
            client_socket.send(response_header.encode())
            client_socket.close()
            cli_close = "[CLI disconnected]\n"
            break
        client_socket.send(msg)

    srv_prx += "> " + status + "\n> " + content_type + " " + str(dataSize) + "bytes\n"
    prx_cli = "[CLI <== PRX --- SRV]\n> " + status + "\n> " + content_type + " " + str(dataSize) + "bytes\n"
    srvSocket.close()
    srv_close = "[SRV disconnected]"

    lock.acquire()
    if if_get:
        if image_filter:
            result = "-----------------------------------------------\n" + str(taskNum) + connection1 + print_filter(image_filter, url_filter)
            print(result)
        else:
            result = "-----------------------------------------------\n" + str(taskNum) + connection1 + print_filter(image_filter, url_filter) + "\n" + connection2 + cli_prx + prx_srv + srv_prx + prx_cli + cli_close + srv_close
            print(result)
    threadNum[t_id-1] = 0
    taskNum += 1
    lock.release()
    # print("exectution time :", datetime.datetime.now() - start)                   # 실행 시간 출력 용도
    return

# main function
def main(Port):
    global start
    startString = "Starting proxy server on port %d."%(Port)
    print(startString)

    # Create Socket
    proxySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    proxySocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    proxySocket.bind(("", Port))
    proxySocket.listen()
    start = datetime.datetime.now()                                                 # 시작시간
    while True:
        try:
            # if client access, return socket
            client_socket, addr = proxySocket.accept()
            receive_thread = threading.Thread(target=connect_client, args=(client_socket, addr))
            receive_thread.daemon = True
            receive_thread.start()
        # handle keyboard interrupt
        except KeyboardInterrupt:
            proxySocket.close()
            print("\nexit")
            return

if __name__ == '__main__':
    Port = int(sys.argv[1])
    main(Port)