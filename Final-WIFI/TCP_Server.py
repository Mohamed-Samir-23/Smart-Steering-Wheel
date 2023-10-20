from socket import * 

MCU1_file = open("WIFI-Project-STM32f103.hex" ,"r")
MCU1_Lines = MCU1_file.readlines()
MCU1_HEX_size =len(MCU1_Lines)

MCU2_file = open("WIFI-Project-STM32f103.hex" ,"r")
MCU2_Lines = MCU2_file.readlines()
MCU2_HEX_size =len(MCU2_Lines)

JETSON_file = open("WIFI-Project-STM32f103.hex" ,"r")
JETSON_Lines = JETSON_file.readlines()
JETSON_HEX_size =len(JETSON_Lines)

version_JETSON="1"
version_MCU1="1"
version_MCU2="1"
version = ""

def simple_xor_encrypt(text, key):
    encrypted = ""
    text_bytes = text.encode('utf-8')
    key_byte = key.encode('utf-8')
    
    for i in range(len(text_bytes)):
        encrypted_byte = text_bytes[i] ^ key_byte[i % len(key_byte)]
        encrypted += chr(encrypted_byte)
    
    return encrypted



hostname = "63.63.63.6"
port =8080

Server_socket = socket(AF_INET,SOCK_STREAM)

Server_socket.bind((hostname, port)) 

Server_socket.listen(1)

while True : 
    try:
        Client, address = Server_socket.accept()
        try:
            while True : 
                Client.settimeout(1)
                RecMsg=Client.recv(1024).decode()
                if not RecMsg: break
                Prefix_List = RecMsg.split(',')

                if Prefix_List[0] == "CheckForUpdates":
                    Client.send(f"Check,MCU1,{version_MCU1},MCU2,{version_MCU2},JETSON,{version_JETSON}".encode())
                    RecMsg == Client.recv(1024).decode()
                  
                    while(RecMsg!= "OK"):
                        Client.send(f"Check,MCU1,{version_MCU1},MCU2,{version_MCU2},JETSON,{version_JETSON}".encode())
                
                elif Prefix_List[0] == "Update":
                    #RecMsg=Client.recv(1024).decode()
                    if Prefix_List[1]=="MCU1":
                                                
                        if Prefix_List[2] =="GetHexSize" :
                            Client.send(f"MCU1,{MCU1_HEX_size},Hex Size".encode())
                            RecMsg =Client.recv(1024).decode()
                            while(RecMsg != "OK"):
                                    Client.send(f"MCU1,{MCU1_HEX_size},Hex Size]".encode())

                        elif Prefix_List[2] =="GetLine" :
                                                    
                            if(int(Prefix_List[3]) <= MCU1_HEX_size ):
                                Client.send(f"MCU1,{Prefix_List[3]},{MCU1_Lines[int(Prefix_List[3])]}".encode())
                                while(Client.recv(1024).decode() != "OK"):
                                    Client.send(f"MCU1,{Prefix_List[3]},{MCU1_Lines[int(Prefix_List[3])]}".encode())
                            
                    elif Prefix_List[1]=="MCU2":
                                                
                        if Prefix_List[2] =="GetHexSize" :
                            Client.send(f"MCU2,{MCU2_HEX_size},Hex Size".encode())
                            RecMsg =Client.recv(1024).decode()
                            while(RecMsg != "OK"):
                                    Client.send(f"MCU2,{MCU2_HEX_size},Hex Size]".encode())

                        elif Prefix_List[2] =="GetLine" :
                                                    
                            if(int(Prefix_List[3]) <= MCU2_HEX_size ):
                                Client.send(f"MCU2,{Prefix_List[3]},{MCU2_Lines[int(Prefix_List[3])]}".encode())
                                while(Client.recv(1024).decode() != "OK"):
                                    Client.send(f"MCU2,{Prefix_List[3]},{MCU2_Lines[int(Prefix_List[3])]}".encode())
                    elif Prefix_List[1]=="JETSON":
                                            
                        if Prefix_List[2] =="GetHexSize" :
                            Client.send(f"JETSON,{JETSON_HEX_size},Hex Size".encode())
                            RecMsg =Client.recv(1024).decode()
                            while(RecMsg != "OK"):
                                    Client.send(f"JETSON,{JETSON_HEX_size},Hex Size]".encode())

                        elif Prefix_List[2] =="GetLine" :
                                                    
                            if(int(Prefix_List[3]) <= JETSON_HEX_size ):
                                Client.send(f"JETSON,{Prefix_List[3]},{JETSON_Lines[int(Prefix_List[3])]}".encode())
                                while(Client.recv(1024).decode() != "OK"):
                                    Client.send(f"JETSON,{Prefix_List[3]},{JETSON_Lines[int(Prefix_List[3])]}".encode())
                    elif RecMsg=="Close":
                        Client.close()
                    else: 
                        Client.send("Wrong Choice".encode())
        except:
            print("Error 3")
        try:
            Client.close()
        except:
            print("Error 4")

    except:
        print("ERROR1")            
            


