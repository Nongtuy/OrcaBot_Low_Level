#######################################################
#  Title: pySerialTransfer Test                       #
#  Version: 3                                         #
#  Author: Noto (Warit Yuvaniyama)                    #
#  Last edited: 2024/01/05                            #
#  Description: Stand alone test for pySerialTransfer #
#######################################################

## Problem: when adding kick_2 to the orca_dict, the data is too Large for the buffer (max 254) [Solved in V.4]
##          Old use 246 bytes (8 bytes left), New use 270 bytes (Over by 16 bytes)
## Solution: split the orca_dict into 2 parts, send the first part, then send the second part

import time
import numpy as np
from pySerialTransfer import pySerialTransfer as txfer
from icecream import ic

Serial_port = 'COM4'

send_size = 0

if __name__ == '__main__':
    link = txfer.SerialTransfer(Serial_port)
    
    try:
        ### Open the serial port ###
        link.open()
        time.sleep(2)  # wait for Arduino to reset
        
        ### Formating data ###
        # format = {robot_id : [Motor_0, Motor_1, Motor_2, Motor_3, Kicker_1, Kicker_2, Dribbler]
        #               0    : [ 1024  , -1024  ,  1024  ,  -1024 ,    0    ,    0    ,   1    ]}
        # orca_dict = {0: [-1024, -1024, -1024, -1024, 0, 0, 1],
        #              1: [-1024, -1024, -1024, -1024, 0, 0, 1],
        #              2: [-1024, -1024, -1024, -1024, 0, 1],
        #              3: [-1024, -1024, -1024, -1024, 0, 1],
        #              4: [-1024, -1024, -1024, -1024, 0, 1],
        #              5: [-1024, -1024, -1024, -1024, 0, 1]}
        orca_dict = {'0': [-1024, -1024, -1024, -1024, 0, 0, 1],
                     '1': [-1024, -1024, -1024, -1024, 0, 0, 1],
                     '2': [-1024, -1024, -1024, -1024, 0, 0, 1]}
        # orca_dict = {0: [-677.616191986388, -367.5788793595459, 1.7352242504862203, 0, 1, 1]}
        ## tx_obj(val, start_pos=0, byte_format='', val_type_override='')
        orca_tx = link.tx_obj(orca_dict, start_pos=send_size) - send_size # return the number of bytes in orca_dict
        ic(orca_tx)
        send_size += orca_tx # update the number of bytes in the buffer
        
        ### Send data ###
        start_time = time.perf_counter()
        link.send(send_size) # send the data packat
        
        ### Wait for a response and report any errors while receiving packets ###
        while not link.available():
            if link.status < 0:
                if link.status == txfer.CRC_ERROR:
                    print('ERROR: CRC_ERROR')
                elif link.status == txfer.PAYLOAD_ERROR:
                    print('ERROR: PAYLOAD_ERROR')
                elif link.status == txfer.STOP_BYTE_ERROR:
                    print('ERROR: STOP_BYTE_ERROR')
                else:
                    print('ERROR: {}'.format(link.status))
                    
        ### Prase feedback from Arduino ###
        orca_rx_dict = link.rx_obj(obj_type=type(orca_dict),
                              start_pos=0,
                              obj_byte_size=orca_tx,
                              list_format='i')
        
        ### Display the received data ###
        stop_time = time.perf_counter()
        print(f"Time: {stop_time - start_time}")
        ic(orca_tx)
        print(f"Sent: {orca_dict}")
        print(f"Received: {orca_rx_dict}")
    
    except KeyboardInterrupt:
        try:
            link.close()
        except:
            pass
        print('KeyboardInterrupt')
    except:
        import traceback
        traceback.print_exc()
        
        try:
            link.close()
        except:
            pass
        print('Exiting.')