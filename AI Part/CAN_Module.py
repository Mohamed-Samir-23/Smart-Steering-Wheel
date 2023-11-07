import spidev
import Jetson.GPIO as GPIO

# Constants for MCP2515 instructions
INST_RESET          = 0xC0
INST_READ           = 0x03
INST_WRITE          = 0x02
INST_RTS_TXB0       = 0x81
INST_RTS_TXB1       = 0x82
INST_RTS_TXB2       = 0x84
INST_READ_STATUS    = 0xA0
INST_RX_STATUS      = 0xB0
INST_BIT_MODIFY     = 0x05

# MCP2515 Register Addresses
CNF1        = 0x2A
CNF2        = 0x29
CNF3        = 0x28
CANCTRL     = 0x0F
CANSTAT     = 0x0E
TXB0CTRL    = 0x30
RXB0CTRL    = 0x60
CANINTF     = 0x2C

# Define GPIO pin for MCP2515 CS (Chip Select)
CS_PIN = 8

# MCP2515 modes
MCP2515_MODE_NORMAL         = 0x0
MCP2515_MODE_SLEEP          = 0x1
MCP2515_MODE_LOOPBACK       = 0x2
MCP2515_MODE_LISTEN_ONLY    = 0x3
MCP2515_MODE_CONFG          = 0x4

# SPI Configuration
SPI_BUS     = 0
SPI_DEVICE  = 0

# Initialize SPI
spi = spidev.SpiDev()
spi.open(SPI_BUS, SPI_DEVICE)
spi.max_speed_hz = 1000000 

# Initialize GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(CS_PIN, GPIO.OUT)

def chip_select(enable):
    if(enable == True):
        GPIO.output(CS_PIN,GPIO.LOW)  # Active Low CS
    elif(enable == False):
        GPIO.output(CS_PIN,GPIO.HIGH)  # Active Low CS
    else:
        raise Exception('value must be True or Flase')
    

def read_register(address):
    chip_select(True)
    spi.xfer2([INST_READ, address])
    read_value = spi.xfer2([0])
    chip_select(False)
    return read_value[0]

def write_register(address, value):
    chip_select(True)
    spi.xfer2([INST_WRITE, address, value])
    chip_select(False)

def set_bit_timing(cnf1_value, cnf2_value, cnf3_value):
    write_register(CNF1, cnf1_value)
    write_register(CNF2, cnf2_value)
    write_register(CNF3, cnf3_value)

def reset_mcp2515():
    chip_select(True)
    spi.xfer2([INST_RESET])
    chip_select(False)

def modify_bits(reg_address, mask, value):
    chip_select(True)
    spi.xfer2([INST_BIT_MODIFY, reg_address, mask, value])
    chip_select(False)

def set_mode(mode):
    modify_bits(CANCTRL, 0xE0, mode << 5)
    while (read_register(CANSTAT) >> 5) != mode:
        pass

def init_mcp2515():
    reset_mcp2515()
    # Enter configuration mode and enable CLKOUT with no prescaler
    write_register(CANCTRL, 0x84) # --> 8MHZ so i need to change it
    while (read_register(CANSTAT) >> 5) != MCP2515_MODE_CONFG:
        pass
    # Set bit timing for 250KHz bitrate using 8MHz osc
    set_bit_timing((2 << 6), (1 << 7) | (6 << 3) | (1), 5)
    set_mode(MCP2515_MODE_NORMAL)

# Function to receive CAN message
def receive_can_msg():
    chip_select(True)
    spi.xfer2([INST_READ, RXB0CTRL])
    read_buffer = spi.xfer2([0] * 14)
    chip_select(False)
    write_register(CANINTF, 0)

# Function to send CAN message
def send_can_msg(buf_idx, msg_id, data, properties):
    chip_select(True)
    spi.xfer2([INST_WRITE, TXB0CTRL])
    spi.xfer2([properties >> 6, (msg_id >> 3), (msg_id << 5), 0, 0, (properties & 0x0F)])
    for i in range(properties & 0x0F):
        spi.xfer2([data[i]])
    chip_select(False)
    chip_select(True)
    spi.xfer2([INST_RTS_TXB0])
    chip_select(False)

