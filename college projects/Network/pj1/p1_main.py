import pcapy

# Convert int to IP address
def int_to_IP(num):
    D = num%256
    num = int(num/256)
    C = num%256
    num = int(num/256)
    B = num%256
    num = int(num/256)
    A = num%256
    IP_addr = '.'.join([str(A),str(B),str(C),str(D)])
    return IP_addr

def main():
    # Selection Interface
    devices = pcapy.findalldevs()
    if len(devices) < 1 :
        print("No proper network devices")
        return -1
    i = 1
    for device in devices:
        print(i, end='')
        print("." + device)
        i += 1            
    d = int(input("Enter the device number: "))
    sm = int(input("Which header do you want to sniff? Enter the number (HTTP = 1, DNS = 2): "))
    print()                                             # for newline
    dev = devices[d-1]

    # open device
    cap = pcapy.open_live(dev, 65536, True, 0)
    if cap == None:
        print("Can not open the device")
        return -1

    #start sniffing packet
    count = 1
    while 1:
        header, payload = cap.next()
        # Structure of Frame header
        # destination addr(6 byte), source addr(6 byte), type(2 byte)
        fhdr = payload[:14]
        eth_type = int.from_bytes(fhdr[-2:], byteorder='big')
        # 0x0800 -> IP type, Use only IP
        if eth_type != 0x0800:
            continue

        # Structure of IP header
        # (base +) 0-3 bit: IP version / 4-7 bit: IP header length / 8-15 bit: type of service(recently not used) / 16-31 bit: total length(IP packet)
        # (base +) 8~9byte : Time to live / ~10byte : Protocol / ~12byte : Header Checksum
        # Sourse IP Address
        # Destination IP Address
        iphdr_len = payload[14]%16 * 4                  # 4byte per 1
        # Protocol types
        # {1:ICMP, 2:IGMP, 3:IP, 6:TCP, 8:EGP, 17:UDP, 41:IPv6, 46:RSVP, 89:OSPF}
        protocol = payload[13 + 10]
        srcIP = int.from_bytes(payload[26:30], byteorder='big')
        dstIP = int.from_bytes(payload[30:34], byteorder='big')
        srcIP = int_to_IP(srcIP)
        dstIP = int_to_IP(dstIP)        
        # slice the IP header
        packet = payload[14 + iphdr_len:]

        # ~2byte: Source Port / ~4byte: Destination Port
        # HTTP : port 80, DNS : port 53
        srcPort = int.from_bytes(packet[:2], byteorder='big')
        dstPort = int.from_bytes(packet[2:4], byteorder='big')

        # Structure of TCP Header
        # 12~12.5byte: Data offset(TCP header length)
        if protocol == 6:
            tcphr_len = packet[12]//16 * 4              # 4byte per 1
            data_packet = packet[tcphr_len:]
            # HTTP
            if sm == 1:
                if srcPort == 80 or dstPort == 80:
                    data_packet_str = "".join([chr(b) for b in data_packet])
                    # check if the packet protocol is HTTP
                    if 'HTTP' in data_packet_str:
                        http_header = data_packet_str[:data_packet_str.find('\r\n\r\n')]
                        # request/status line // header line
                        req_stat_line = http_header[:http_header.find('\r\n')]
                        hdr_line = http_header[http_header.find('\r\n')+2:]
                        # Request
                        if srcPort == 80:
                            print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, " HTTP Request", sep = '')
                            print(req_stat_line)
                            print(hdr_line)
                            print()                         # for newline
                        # Response
                        elif dstPort == 80:
                            print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, " HTTP Response", sep = '')
                            print(req_stat_line)
                            print(hdr_line)
                            print()                         # for newline
                        count += 1
            # DNS
            # ID // OR Opcode AA TC RD RA Z RCODE // QDCOUNT // ANCOUNT //  NSCOUNT // ARCOUNT                   
            else:
                if srcPort == 53 or dstPort == 53:
                    # DNS header is 12 byte size
                    dns_ID = format(int.from_bytes(data_packet[:2], byteorder='big'), 'x')
                    dns_flags = format(int.from_bytes(data_packet[2:4], byteorder='big'), 'b').zfill(16)
                    dns_QD = format(int.from_bytes(data_packet[4:6], byteorder='big'), 'x')
                    dns_AN = format(int.from_bytes(data_packet[6:8], byteorder='big'), 'x')
                    dns_NS = format(int.from_bytes(data_packet[8:10], byteorder='big'), 'x')
                    dns_AR = format(int.from_bytes(data_packet[10:12], byteorder='big'), 'x')
                    print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, " DNS ID : ", dns_ID, sep = '')
                    print(dns_flags[0], "|", dns_flags[1:5], "|", dns_flags[5], "|", dns_flags[6], "|", dns_flags[7], "|", dns_flags[8], "|", dns_flags[9:12], "|", dns_flags[12:16])
                    print("QDCOUNT:", dns_QD)
                    print("ANCOUNT:", dns_AN)
                    print("NSCOUNT:", dns_NS)
                    print("ARCOUNT:", dns_AR)
                    print()                                 # for newline
                    count += 1
                    
        # Structure of UDP Header
        # srcPort, dstPort // Length, Checksum
        elif protocol == 17:
            udp_len = int.from_bytes(packet[4:6], byteorder='big')          # no use for this project
            data_packet = packet[8:]                                        # length of udp header is 8 byte
            # HTTP
            if sm == 1:
                if srcPort == 80 or dstPort == 80:
                    # check if the packet protocol is HTTP
                    data_packet_str = "".join([chr(b) for b in data_packet])
                    if 'HTTP' in data_packet_str:
                        data_packet_str = "".join([chr(b) for b in data_packet])
                        http_header = data_packet_str[:data_packet_str.find('\r\n\r\n')]
                        req_stat_line = http_header[:http_header.find('\r\n')]
                        hdr_line = http_header[http_header.find('\r\n')+2:]
                        # Request
                        if srcPort == 80:
                            print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, "HTTP Request", sep = '')
                            print(req_stat_line)
                            print(hdr_line)
                            print()                         # for newline
                        # Response
                        elif dstPort == 80:
                            print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, "HTTP Response", sep = '')
                            print(req_stat_line)
                            print(hdr_line)
                            print()                         # for newline
                        count += 1
            # DNS
            # ID // OR Opcode AA TC RD RA Z RCODE // QDCOUNT // ANCOUNT //  NSCOUNT // ARCOUNT
            else:
                if srcPort == 53 or dstPort == 53:
                    # DNS header is 12 byte size
                    dns_ID = format(int.from_bytes(data_packet[:2], byteorder='big'), 'x')
                    dns_flags = format(int.from_bytes(data_packet[2:4], byteorder='big'), 'b').zfill(16)
                    dns_QD = format(int.from_bytes(data_packet[4:6], byteorder='big'), 'x')
                    dns_AN = format(int.from_bytes(data_packet[6:8], byteorder='big'), 'x')
                    dns_NS = format(int.from_bytes(data_packet[8:10], byteorder='big'), 'x')
                    dns_AR = format(int.from_bytes(data_packet[10:12], byteorder='big'), 'x')
                    print(count, ' ', srcIP, ":", srcPort, ' ', dstIP, ":", dstPort, " DNS ID : ", dns_ID, sep = '')
                    print(dns_flags[0], "|", dns_flags[1:5], "|", dns_flags[5], "|", dns_flags[6], "|", dns_flags[7], "|", dns_flags[8], "|", dns_flags[9:12], "|", dns_flags[12:16])
                    print("QDCOUNT:", dns_QD)
                    print("ANCOUNT:", dns_AN)
                    print("NSCOUNT:", dns_NS)
                    print("ARCOUNT:", dns_AR)
                    print()                                 # for newline
                    count += 1                   

if __name__ == "__main__":
    main()
